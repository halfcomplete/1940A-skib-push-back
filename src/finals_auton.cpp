#include "finals_auton.h"
//#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
//#include "lemlib/pose.hpp"
#include "robot.hpp"
#include "helpers.hpp"

void finals_right_auton()
{
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-46.818, -13.547, 90);
    Wing.extend();

    // Move to three blocks on the right
    StartIntake();
    chassis.moveToPoint(-26.066, -19.266, 3000, {.minSpeed=80, .earlyExitRange=13});
    chassis.moveToPoint(-16.066, -25.266, 3000, {.maxSpeed=43});
    chassis.waitUntilDone();

    // Move to two blocks under the long goal
    chassis.turnToHeading(150, 1000, {.minSpeed=60, .earlyExitRange=1});
    chassis.waitUntilDone();
    chassis.moveToPoint(-7.75, -40.6, 1000,{.minSpeed=60});
    // chassis.turnToHeading(110, 1000);
    pros::delay(350);
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(-16.066, -28, 2000, {.forwards=false, .minSpeed=80});

    // Move to right long goal
    chassis.turnToHeading(235, 700);
    chassis.waitUntilDone();
    Matchloader.retract();
    chassis.moveToPoint(-40, -47, 1000);
    chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(-22, -47, 1500, {.forwards=false, .minSpeed=70});
    chassis.waitUntilDone();
    StartScoring();
    pros::delay(2100);

    // Move to matchloader
    Matchloader.extend();
    StartIntake();
    chassis.moveToPoint(-75, -48.4, 1800, {.maxSpeed=46});

    // Move to right long goal
    chassis.moveToPose(-24, -48, 270, 3000, {.forwards=false, .minSpeed=60});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring();
    pros::delay(2000);
    chassis.moveToPoint(-34, -48, 1000);
    chassis.moveToPoint(-22, -48, 10000, {.forwards=false, .minSpeed=80});
    // Wing.extend();
    // chassis.moveToPoint(-51, -47, 1500);
    // chassis.turnToHeading(225, 500, {.minSpeed=50, .earlyExitRange=5});
    // chassis.moveToPose(-30, -39.8, 270, 1000, {.forwards=false, .minSpeed=50, .earlyExitRange=7});
    // Wing.retract();
    // chassis.moveToPoint(-16.7, -40.5, 10000, {.forwards=false, .maxSpeed=50});
}

void finals_left_auton()
{
    // right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    // left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    // chassis.setPose(-46.818, 13.547, 90);

    // // Move to three blocks on the right
    // StartIntake();
    // chassis.moveToPoint(-26.066, 19.266, 3000, {.minSpeed=65, .earlyExitRange=15});
    // chassis.moveToPoint(-16.066,25.266, 3000, {.maxSpeed=40});
    // chassis.waitUntilDone();

    // // Move to matchloader
    // chassis.turnToHeading(325, 700);
    // chassis.waitUntilDone();
    // Matchloader.extend();
    // chassis.moveToPoint(-45, 46.4, 1000);
    // chassis.turnToHeading(270, 1000);
    // chassis.moveToPoint(-71, 46.4, 1400, {.maxSpeed=65});
    // pros::delay(1200);

    // // Move to right long goal
    // chassis.moveToPose(-29, 47.5, 270, 1000, {.forwards=false});
    // chassis.waitUntilDone();
    // Matchloader.retract();
    // StartScoring(true);
    // pros::delay(2400);
    // Wing.extend();
    // chassis.moveToPoint(-51, 47.5, 1500);
    // chassis.turnToHeading(205, 500, {.minSpeed=50, .earlyExitRange=5});
    // chassis.moveToPose(-29.5, 55.7, 270, 1000, {.forwards=false, .minSpeed=50, .earlyExitRange=7});
    // Wing.retract();
    // chassis.moveToPoint(-10, 56, 10000, {.forwards=false, .maxSpeed=50});
}