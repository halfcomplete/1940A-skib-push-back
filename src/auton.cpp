#include "auton.h"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robot.hpp"
#include "skills_auton.h"
#include "finals_auton.h"

ASSET(path1_txt);
ASSET(path3_txt);
ASSET(testpath_txt);

void auton(int autonToRun) {
    if (autonToRun == 0)
    {
        skills_auton();
    }

    if (autonToRun == 1)
    {
        Left_7B_2G();
    }
    if (autonToRun == 2)
    {
        Right_7B_2G();
    }

    if (autonToRun == 3)
    {
        finals_left_auton();
    }

    if (autonToRun == 4)
    {
        finals_right_auton();
    }

    if (autonToRun == 5)
    {
        TestPidTurn();
    }

    if (autonToRun == 6)
    {
        TestPidMove();
    }

    if (autonToRun == 7)
    {
        raygoon_righ_tauton();
    }
    
};

void Left_7B_2G()
{
    // Initialise
    chassis.setPose(-50.425, 15, 0);
    Conveyer.move(-12000);
    Top_Roller.move(12000);
    Trapdoor.retract();

    // Move to matchloader
    chassis.moveToPose(-47, 45, 0, 1000);
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();

    // Collect blocks from matchloader
    Matchloader.extend();
    chassis.moveToPose(-62, 45, 270, 1500);
    for (int i = 0; i < 3; i++) {
        chassis.moveToPoint(-68, 45, 400);
        chassis.moveToPoint(-62, 45, 400);
    }
 
    // Move to long goal
    chassis.moveToPoint(-55, 45, 1000);
    chassis.waitUntilDone();
    Matchloader.retract();
    pros::delay(200);
    chassis.turnToHeading(90, 1000, {.minSpeed = 70});
    chassis.moveToPose(-32, 45, 90, 1000, {.maxSpeed = 80});
    chassis.waitUntilDone();

    // Score all 3 blocks in the long goal
    Trapdoor.extend();
    Conveyer.move(-12000);
    Top_Roller.move(12000);
    // Inside_Roller.move(-12000);
    pros::delay(2700);

    // Move back slightly
    chassis.moveToPoint(-57, 45, 3000, {.forwards=false});
    chassis.turnToHeading(135, 500);

    // Intake 3 blocks and score in the high goal
    Top_Roller.move_velocity(-8000);
    
    chassis.moveToPoint(-24.8, 10, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();

    // Pause
    pros::delay(900);
    Conveyer.brake();

    // Ram
    chassis.moveToPoint(-20, 10,2000, {.minSpeed = 100});
}

void Right_7B_2G()
{
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(50.425, 15, 0);
    Conveyer.move(-12000);
    Top_Roller.move(12000);
    Trapdoor.retract();

    // Move to matchloader
    chassis.moveToPose(47, 48, 0, 1000);
    chassis.turnToHeading(90, 1000);
    chassis.waitUntilDone();

    // Collect blocks from matchloader
    Matchloader.extend();
    chassis.moveToPose(60, 46, 90, 1500);
    for (int i = 0; i < 3; i++) {
        chassis.moveToPoint(61.5, 46, 450, {.minSpeed = 100});
        chassis.moveToPoint(59.5, 46, 450, {.minSpeed = 100});
    }
 
    // Move to long goal
    chassis.waitUntilDone();
    chassis.moveToPoint(56, 47.6, 1000);
    Matchloader.retract();
    pros::delay(100);
    chassis.turnToHeading(90, 1000, {.minSpeed = 70});
    chassis.moveToPoint(34, 47.3, 1900, {.maxSpeed = 70});
    chassis.waitUntilDone();

    // Score all 4 blocks in the long goal
    Trapdoor.extend();
    Conveyer.move(-12000);
    Top_Roller.move(12000);
    // Inside_Roller.move(-12000);
    pros::delay(2700);
    // Inside_Roller.brake();
    // Switcheroo.toggle();
    pros::delay(200);

    // Move back slightly
    chassis.moveToPoint(50, 46, 1000, {.forwards=false});

    // Score 3 blocks in the low goal
    chassis.turnToHeading(225, 500);
    chassis.moveToPoint(25, 16.7, 2000, {.maxSpeed = 50});
    
    chassis.waitUntilDone();
    // Inside_Roller.move_velocity(-75);
    Top_Roller.move_velocity(-32);
    Matchloader.toggle();
}

void StartIntake()
{
    // Inside_Roller.brake();
    Conveyer.move(12000);
}

void StopIntake()
{
    // Inside_Roller.brake();
    Top_Roller.brake();
    Conveyer.brake();
}

void TestPidTurn()
{
    chassis.setPose(0, 0, 0);
    pros::delay(100);
    chassis.turnToHeading(90, 10000);
}

void TestPidMove()
{
    chassis.setPose(0, 0, 0);
    pros::delay(100);
    chassis.moveToPose(0, 48, 0, 10000);
}

void raygoon_righ_tauton() {
    chassis.setPose(-49.705, -17.961, 180);
    StartIntake();
    Matchloader.extend();
    chassis.moveToPoint(-49.705,  -53, 1500);
    pros::delay(500);
    chassis.moveToPose(-65.445,-53, 270, 2500);
    pros::delay(100);
    chassis.moveToPose(-27.905,-53,270,2000,{.forwards=false});
    Top_Roller.move(-12000);
}   