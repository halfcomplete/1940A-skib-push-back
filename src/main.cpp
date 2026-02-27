#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
//#include "pros/colors.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "pros/screen.h"
#include "robot.hpp"
#include "auton.h"
#include "skills_auton.h"
#include "helpers.hpp"
//#include <iomanip>
#include "auton.h"
#include <atomic>
//#include "lemlib/asset.hpp"




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	chassis.calibrate();
	Wing.retract();
	// imu.reset(true);

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });

	printf("init done");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// 0 = skills
	// 1 = left match
	// 2 = right match
	// 3 = right match solo awp
	// 4 = left finals match
	// 5 = right finals match
	// 6 = test pid turn
	// 7 = test pid move

    // 8 = test motor move
	auton(5);
    
    // Auton selector
	// int autonToRun;
	// // Loop until a valid button is pressed to select an auton
	// while (true) {
	// 	// Check if the X button is pressed, if so then run auton skills
	// 	if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
	// 	{
	// 		autonToRun = 0;
	// 		break;
	// 	}

	// 	// Check if the A button is pressed, if so then run the cornerAuton
	// 	if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
	// 	{
	// 		autonToRun = 1;
	// 		break;
	// 	}

	// 	// Delay to reduce resource usage
	// 	pros::delay(25);
	// }
	// auton(autonToRun);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	int isHighGoal = 127;
    bool controllerHighGoal = false;
	bool slowDownTopRoller = false;
	Wing.extend();
	right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	while (true) {
		double forwards = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		double turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(forwards, turn);

		
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            if (slowDownTopRoller) {
                First_Stage_Intake.move_voltage(-12000);
				Second_Stage_Intake.move_voltage(-12000);
            } else {
                First_Stage_Intake.move_voltage(-12000);
				Second_Stage_Intake.move_voltage(-12000);
            }
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            if (slowDownTopRoller) {
                First_Stage_Intake.move_voltage(12000);
				Second_Stage_Intake.move_voltage(12000);
				Outtake.move_voltage(-3000);
            } else {
                Second_Stage_Intake.move(12000);
				First_Stage_Intake.move_voltage(12000);
				Outtake.move_voltage(-2000);
            }
		} else {
			Second_Stage_Intake.move(0);
			First_Stage_Intake.move(0);
			Outtake.move(0);
		}

		
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            if (controllerHighGoal) {
                Outtake.move_voltage(-12000);
				Outtake_Lift.extend();
            } else {
                Outtake.move_voltage(-12000);
				Outtake_Lift.extend();
            }
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            if (controllerHighGoal) {
                Outtake.move_voltage(12000);
				Outtake_Lift.retract();
            } else {
                Outtake.move_voltage(12000);
				Outtake_Lift.retract();
            }
		} else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			Outtake.move(0);
			Outtake_Lift.retract();
		}

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			Wing.toggle();
		}
		
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			Matchloader.extend();
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			Matchloader.retract();
		}
		 
		// Matchloader and Switcheroo have activation buttons opposite to the actual buttons that activate them.
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
			Intake_Lift.extend();
			controllerHighGoal = true;
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			Intake_Lift.retract();
			controllerHighGoal = false;
		}



		pros::delay(20);                               // Run for 20 ms then update
	}
}
