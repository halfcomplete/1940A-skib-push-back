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
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-46.818, 13.547, 90);

    // Move to three blocks on the left
    StartIntake();
    chassis.moveToPoint(-26.066, 20, 3000, {.minSpeed=50, .earlyExitRange=15});
    chassis.moveToPoint(-16.066, 26, 6000, {.maxSpeed=22});
    chassis.waitUntilDone();

    // Score in high goal
    chassis.turnToHeading(311, 1000, {.maxSpeed=60});
    chassis.waitUntilDone();
    chassis.moveToPoint(-13.5, 14, 1500, {.forwards=false, .maxSpeed=50});
    chassis.waitUntilDone();
    chassis.turnToHeading(315, 1000, {.maxSpeed=60});
    chassis.waitUntilDone();
    StartScoring(false, true);
    pros::delay(1600);

    // Move to matchloader
    chassis.moveToPoint(-39, 49, 1500);
    StartIntake();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(-67, 49, 1400, {.maxSpeed=70});
    pros::delay(900);
    chassis.moveToPoint(-65, 49, 500);
    pros::delay(200);
    chassis.moveToPoint(-68, 49, 1400, {.minSpeed=80});
    pros::delay(900);
    // Score in long goal
    chassis.moveToPoint(-30.614, 50, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring();
    pros::delay(1030);
    StopScoring();
}

void Right_7B_2G()
{
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-46.818, -13.547, 90);

    // Move to three blocks on the right
    StartIntake();
    chassis.moveToPoint(-26.066, -19.266, 3000, {.minSpeed=45, .earlyExitRange=15});
    chassis.moveToPoint(-16.066, -25.266, 3000, {.maxSpeed=24});
    chassis.waitUntilDone();

    // Score in low goal
    chassis.moveToPoint(-28, -28, 1000,{.forwards=false});
    chassis.moveToPoint(-12.25, -14.75, 1500, {.maxSpeed=50});
    chassis.waitUntilDone();
    chassis.turnToHeading(48, 1000, {.maxSpeed=60});
    chassis.waitUntilDone();
    pros::delay(200);
    StartOuttake();
    pros::delay(2800);

    // Move to matchloader
    chassis.moveToPoint(-46.818, -47.6, 1500, {.forwards=false});
    StartIntake();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(-74, -47.6, 1600);
    pros::delay(1000);
    chassis.moveToPoint(-62, -47.6, 1400, {.forwards=false});
    pros::delay(300);
    chassis.moveToPoint(-74, -47.6, 700);
    pros::delay(200);

    // Score in long goal
    chassis.moveToPoint(-30.614, -49, 2000, {.forwards=false, .maxSpeed=60});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring();
    pros::delay(1200);
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
    float firstY = -47.4;
    chassis.moveToPoint(-48.599, firstY + 0.4, 1500);
    
    // Move to matchloader
    chassis.turnToHeading(270, 700, {.minSpeed=60});
    StartIntake();
    chassis.moveToPoint(-69, firstY + 0.4, 500, {.minSpeed=150});
    chassis.waitUntilDone();
    left_mg.move(127);
    right_mg.move(127);
    pros::delay(300);
    left_mg.move(-30);
    right_mg.move(-30);
    pros::delay(80);
    left_mg.move(127);
    right_mg.move(127);
    pros::delay(300);

    // Move to right long goal
    chassis.moveToPose(-25, firstY - 1.2, 270, 1000, {.forwards=false, .minSpeed=85});
    chassis.waitUntilDone();
    left_mg.move(-127);
    right_mg.move(-127);
    StartScoring();
    Matchloader.retract();
    pros::delay(800);
    chassis.setPose(-30.9, -51.1, 270);
    chassis.waitUntilDone();
    chassis.moveToPoint(-46, -50.6, 1000, {.minSpeed=80, .earlyExitRange=1});
    chassis.turnToPoint(-27, -27, 1000, {.minSpeed=90});
    chassis.waitUntilDone();
    StartIntake();


    // Move to 3 blocks on the right
    chassis.moveToPoint(-24, -29, 1500, {.minSpeed=90, .earlyExitRange=21.7});
    chassis.moveToPoint(-22, -28, 3000, {.maxSpeed=30});
    chassis.waitUntilDone();

    // Move to low goal
    chassis.moveToPoint(-13, -19, 1500, {.maxSpeed=70});
    chassis.turnToHeading(41, 1000);
    StartOuttake(true);
    pros::delay(1200);
    chassis.moveToPoint(-25, -25, 1000, {.forwards=false, .minSpeed=70});
    chassis.turnToPoint(-25, 4, 1200, {.minSpeed=70, .earlyExitRange=7});
    
    // Move to 3 blocks on the left
    StartIntake();
    chassis.moveToPoint(-25, 4, 1000, {.minSpeed=80, .earlyExitRange=3.4}); 
    chassis.moveToPoint(-25, 22, 1800, {.maxSpeed=30});
    chassis.waitUntilDone();

    // Move to matchloader on the left
    float y = 40;
    chassis.turnToPoint(-47, y, 1500, {.minSpeed=70, .earlyExitRange=2});
    Matchloader.extend();
    chassis.moveToPose(-57, y, 280, 1500, {.minSpeed=80});

    chassis.moveToPose(-71, y, 280, 500, {.minSpeed=150 });
    chassis.waitUntilDone();
    left_mg.move(127);
    right_mg.move(127);
    pros::delay(400);
    left_mg.move(-30);
    right_mg.move(-30);
    pros::delay(100);
    left_mg.move(127);
    right_mg.move(127);
    pros::delay(150);

    // Score in left long goal
    chassis.moveToPose(-30.436, y - 1.5, 270, 930, {.forwards=false, .minSpeed=80});
    chassis.waitUntilDone();
    StartScoring();
}

