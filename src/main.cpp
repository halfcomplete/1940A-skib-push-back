#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "pros/colors.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "robot.hpp"
#include "auton.h"
#include "skills_auton.h"
#include "helpers.hpp"
#include <iomanip>
#include "auton.h"
#include "lemlib/asset.hpp"




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
	SkIbIdI_oPtIcAl.set_led_pwm(100);

    // pros::lcd::initialize();
    // pros::Task screenTask([&]()->void {
    //     while (true) {
    //         pros::lcd::print(0, "X, %f", chassis.getPose().x);
    //         pros::lcd::print(1, "Y,%f", chassis.getPose().y);
    //         pros::lcd::print(2, "Theta, %f", chassis.getPose().theta);

	// 		printf("x: %f\n", chassis.getPose().x);
	// 		printf("y: %f\n", chassis.getPose().y);
	// 		printf("theta: %f\n", chassis.getPose().theta);

    //         pros::delay(100);
    //     }
    // });

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
	// 3 = left finals match
	// 4 = right finals match
	// 5 = test pid turn
	// 6 = test pid move
	auton(7);
	// // Auton selector
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
	Wing.extend();
	right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	while (true) {
		double forwards = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		double turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(forwards, turn);

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			Conveyer.move_voltage(-12000);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			Conveyer.move_voltage(12000);
		} else {
			Conveyer.move(0);
		}	
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			Top_Roller.move_voltage(-12000);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			Top_Roller.move_voltage(12000);
		} else {
			Top_Roller.move(0);
		}	
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			Wing.extend();
		} else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			Wing.retract();
		}
	
		if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			Matchloader.extend();
		} else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			Matchloader.retract();
		}
		 
		// Matchloader and Switcheroo have activation buttons opposite to the actual buttons that activate them.
		if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
			Trapdoor.extend();
		} else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
			Trapdoor.retract();
		}

		if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
			Double_Park.extend();
		} else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			Double_Park.retract();
		}

		pros::delay(20);                               // Run for 20 ms then update
	}
}
