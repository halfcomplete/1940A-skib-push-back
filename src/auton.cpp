#include "auton.h"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robot.hpp"
#include "skills_auton.h"
#include "finals_auton.h"
#include "helpers.hpp"

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
        Right_Solo_AWP();
    }
    if (autonToRun == 4)
    {
        finals_left_auton();
    }

    if (autonToRun == 5)
    {
        finals_right_auton();
    }

    if (autonToRun == 6)
    {
        TestPidTurn();
    }

    if (autonToRun == 7)
    {
        TestPidMove();
    }

    if (autonToRun == 8)
    {
        MotorMoveTest();
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
    chassis.setPose(-46.818, -13.547, 90);

    // Move to three blocks on the right
    StartIntake();
    chassis.moveToPoint(-26.066, -19.266, 3000, {.minSpeed=45, .earlyExitRange=9});
    chassis.moveToPoint(-16.066, -25.266, 3000, {.maxSpeed=20});
    chassis.waitUntilDone();

    // Score in low goal
    chassis.turnToHeading(45, 1000, {.maxSpeed=60});
    chassis.waitUntilDone();
    chassis.moveToPoint(-10.37, -11, 1500, {.maxSpeed=50});
    chassis.waitUntilDone();
    chassis.turnToHeading(46.7, 1000, {.maxSpeed=60});
    chassis.waitUntilDone();
    StartOuttake();
    pros::delay(1400);

    // Move to matchloader
    chassis.moveToPoint(-46.818, -45, 1500, {.forwards=false});
    StartIntake();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(-63, -45, 1400);
    pros::delay(600);
    chassis.moveToPoint(-66, -45, 500);
    pros::delay(600);
    chassis.moveToPoint(-63, -45, 1400);
    pros::delay(600);

    // Score in long goal
    chassis.moveToPoint(-30.614, -48, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring();
    pros::delay(1100);
    StopScoring();
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
    chassis.setPose(-48.599, -15.328, 180);
    StartIntake();
    Matchloader.extend();
    chassis.moveToPoint(-48.599, -49, 1500);
    chassis.waitUntilDone();

    // Move to matchloader
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(-69, -47, 1400);
    chassis.waitUntilDone();
    pros::delay(800);

    // Move to right long goal
    chassis.moveToPose(-30.614, -50, 270, 1000, {.forwards=false, .earlyExitRange=1});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring();
    pros::delay(1000);
    chassis.moveToPoint(-44, -49, 1000);
    chassis.waitUntilDone();
    StartIntake();


    // Move to 3 blocks on the right
    chassis.moveToPoint(-24, -27, 1500);
    chassis.waitUntilDone();
}

void MotorMoveTest() {
    Conveyer.move(700);
}

void Right_Solo_AWP() {
    chassis.setPose(-48.599, -15.328, 180);
    StartIntake();
    Matchloader.extend();
    chassis.moveToPoint(-48.599, -49, 1500);
    chassis.waitUntilDone();

    // Move to matchloader
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(-69, -47, 1400);
    chassis.waitUntilDone();
    pros::delay(800);

    // Move to right long goal
    chassis.moveToPose(-30.614, -50, 270, 1000, {.forwards=false, .earlyExitRange=1});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring();
    pros::delay(1000);
    chassis.moveToPoint(-44, -49, 1000);
    chassis.waitUntilDone();
    StartIntake();


    // Move to 3 blocks on the right
    chassis.moveToPoint(-24, -27, 1500);
    chassis.waitUntilDone();
    chassis.turnToHeading(0, 1000, {.minSpeed=70, .earlyExitRange=10});
    chassis.waitUntilDone();
    
    // Move to 3 blocks on the left
    chassis.moveToPoint(-28, 10, 1000, {.minSpeed=70, .earlyExitRange=1}); 
    chassis.waitUntilDone();
    chassis.moveToPoint(-28, 25.544, 1500, {.maxSpeed=60, .earlyExitRange=1});
    chassis.waitUntilDone();

    // Move to high goal
    chassis.moveToPose(-14, 4.67, 315, 1500, {.forwards = false, .minSpeed=60, .earlyExitRange=2});
    chassis.waitUntilDone();
    chassis.turnToHeading(315, 1000);
    chassis.waitUntilDone();
    StartScoring();
    Top_Roller.move(-467);
    pros::delay(1200);
    StartIntake();

    // Move to matchloader on the left
    chassis.moveToPoint(-46.818, 35.5, 1500,{.minSpeed=90});
    chassis.waitUntilDone();
    Matchloader.extend();
    chassis.turnToHeading(270, 1000);

    chassis.moveToPose(-66, 35.5, 270, 1400, {.minSpeed=90 });
    chassis.waitUntilDone();
    pros::delay(1200);

    // Score in left long goal
    chassis.moveToPose(-30.436, 38, 270, 2000, {.forwards=false, .minSpeed=80});
    chassis.waitUntilDone();
    StartScoring();
}

