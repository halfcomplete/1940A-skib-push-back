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
#include "auton_type.h"
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
	pros::delay(100); // Give odom task time to start
	pros::lcd::initialize();
	Wing.retract();
 	chassis.setPose(-46.818, 13.547, 90);
    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // Debug: print raw sensor values
            pros::lcd::print(3, "IMU heading: %f", imu.get_heading());
            pros::lcd::print(4, "IMU status: %d", imu.is_calibrating());
            pros::lcd::print(5, "Vert rot: %d", verticalRotation.get_position());
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
	// Auton selector - wait for controller button press
	AutonType selectedAuton;
	bool autonSelected = false;

	// Display instructions on brain screen
	pros::lcd::print(4, "Select Auton:");
	pros::lcd::print(5, "A:L_7B_2G  B:R_7B_2G  X:SKILLS");
	pros::lcd::print(6, "Y:SOLO_AWP  UP:L_4B_1G  DOWN:R_4B_1G");
	pros::lcd::print(7, "L1:PID_MOVE24  L2:PID_MOVE48  R1:TURN90  R2:TURN180");

	// Loop until a valid button is pressed to select an auton
	while (!autonSelected) {
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			selectedAuton = AutonType::L_7B_2G;
			autonSelected = true;
		}
		else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			selectedAuton = AutonType::R_7B_2G;
			autonSelected = true;
		}
		else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			selectedAuton = AutonType::SKILLS;
			autonSelected = true;
		}
		else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
			selectedAuton = AutonType::SOLO_AWP;
			autonSelected = true;
		}
		else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			selectedAuton = AutonType::L_4B_1G;
			autonSelected = true;
		}
		else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			selectedAuton = AutonType::R_4B_1G;
			autonSelected = true;
		}
		else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			selectedAuton = AutonType::PID_MOVE_TEST_24;
			autonSelected = true;
		}
		else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			selectedAuton = AutonType::PID_MOVE_TEST_48;
			autonSelected = true;
		}
		else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
			selectedAuton = AutonType::PID_TURN_TEST_90;
			autonSelected = true;
		}
		else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
			selectedAuton = AutonType::PID_TURN_TEST_180;
			autonSelected = true;
		} else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
			selectedAuton = AutonType::NONE;
			autonSelected = true;
		}

		// Delay to reduce resource usage
		pros::delay(25);
	}

	if (selectedAuton == AutonType::NONE)
	{
		return; // No auton selected, skip autonomous phase
	}

	// Run the selected auton
	auton(selectedAuton);
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
	autonomous(); // run auton in opcontrol for testing purposes
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
				overrideOuttake(-3000);
            } else {
                Second_Stage_Intake.move(12000);
				First_Stage_Intake.move_voltage(12000);
				overrideOuttake(-5000);
            }
		} else {
			Second_Stage_Intake.move(0);
			First_Stage_Intake.move(0);
			overrideOuttake(-5000);
		}

		
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            if (controllerHighGoal) {
                overrideOuttake(-12000);
				Outtake_Lift.extend();
            } else {
                overrideOuttake(-12000);
				Outtake_Lift.extend();
            }
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            if (controllerHighGoal) {
                overrideOuttake(12000);
				Outtake_Lift.retract();
            } else {
                overrideOuttake(12000);
				Outtake_Lift.retract();
            }
		} else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			overrideOuttake(-5000);
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
