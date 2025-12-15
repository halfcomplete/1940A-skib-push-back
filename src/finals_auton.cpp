#include "finals_auton.h"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "robot.hpp"
#include "helpers.hpp"

void finals_right_auton()
{
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-46.818, -13.547, 90);

    // Move to three blocks on the right
    StartIntake();
    chassis.moveToPoint(-26.066, -19.266, 3000, {.minSpeed=65, .earlyExitRange=15});
    chassis.moveToPoint(-16.066, -25.266, 3000, {.maxSpeed=40});
    chassis.waitUntilDone();

    // Move to matchloader
    chassis.turnToHeading(215, 700);
    chassis.waitUntilDone();
    Matchloader.extend();
    chassis.moveToPoint(-45, -46.5, 1000);
    chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(-71, -46.5, 1400, {.maxSpeed=65});
    pros::delay(1200);

    // Move to right long goal
    chassis.moveToPose(-30.614, -47, 270, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring(true);
    pros::delay(2400);
    Wing.extend();
    chassis.moveToPoint(-51, -47, 1500);
    chassis.turnToHeading(225, 500, {.minSpeed=50, .earlyExitRange=5});
    chassis.moveToPose(-29.5, -39.3, 270, 1000, {.forwards=false, .minSpeed=50, .earlyExitRange=7});
    Wing.retract();
    chassis.moveToPoint(-14, -39.3, 10000, {.forwards=false, .maxSpeed=50});
}

void finals_left_auton()
{
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-46.818, 13.547, 90);

    // Move to three blocks on the right
    StartIntake();
    chassis.moveToPoint(-26.066, 19.266, 3000, {.minSpeed=65, .earlyExitRange=15});
    chassis.moveToPoint(-16.066,25.266, 3000, {.maxSpeed=40});
    chassis.waitUntilDone();

    // Move to matchloader
    chassis.turnToHeading(325, 700);
    chassis.waitUntilDone();
    Matchloader.extend();
    chassis.moveToPoint(-45, 49.2, 1000);
    chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(-71, 49.2, 1400, {.maxSpeed=65});
    pros::delay(1200);

    // Move to right long goal
    chassis.moveToPose(-29, 50, 270, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring(true);
    pros::delay(2400);
    Wing.extend();
    chassis.moveToPoint(-51, 50, 1500);
    chassis.turnToHeading(225, 500, {.minSpeed=50, .earlyExitRange=5});
    chassis.moveToPose(-29.5, 57.6, 270, 1000, {.forwards=false, .minSpeed=50, .earlyExitRange=7});
    Wing.retract();
    chassis.moveToPoint(-10, 57.5, 10000, {.forwards=false, .maxSpeed=50});
}