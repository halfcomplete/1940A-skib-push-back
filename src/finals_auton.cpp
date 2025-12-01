#include "finals_auton.h"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "robot.hpp"
#include "helpers.hpp"

void finals_right_auton()
{
    chassis.setPose(-48.599, -13, 180);
    StartIntake();
    Matchloader.extend();
    chassis.moveToPoint(-48.599, -47, 1500);
    chassis.waitUntilDone();

    // Move to matchloader
    chassis.turnToHeading(270, 700);
    chassis.waitUntilDone();
    chassis.moveToPoint(-73, -47, 1400);
    pros::delay(1400);

    // Move to right long goal
    chassis.moveToPose(-30.614, -48, 270, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring();
    pros::delay(1300);
    chassis.moveToPoint(-44, -48, 1000);
    chassis.waitUntilDone();
    StartIntake();


    // Move to 3 blocks on the right
    chassis.moveToPoint(-13, -7, 5000, {.maxSpeed=30});
    chassis.waitUntilDone();

    // Move back to long goal
    chassis.moveToPoint(-49, -44, 1000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-25, -44.5, 1000, {.forwards=false});
    chassis.waitUntilDone();
    StartScoring();
}

void finals_left_auton()
{
    chassis.setPose(-48.599, 15.328, 0);
    StartIntake();
    Matchloader.extend();
    chassis.moveToPoint(-48.599, 47, 1500);
    chassis.waitUntilDone();

    // Move to matchloader
    chassis.turnToHeading(270, 700);
    chassis.waitUntilDone();
    chassis.moveToPoint(-73, 47, 1400);
    pros::delay(1400);

    // Move to left long goal
    chassis.moveToPose(-30.614, 48, 270, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring();
    pros::delay(1300);
    chassis.moveToPoint(-44, 48, 1000);
    chassis.waitUntilDone();
    StartIntake();


    // Move to 3 blocks on the left
    chassis.moveToPoint(-13, 7, 5000, {.maxSpeed=50});
    chassis.waitUntilDone();

    // Move back to long goal
    chassis.moveToPoint(-49, 44, 1000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-20, 44, 1000, {.forwards=false});
    chassis.waitUntilDone();
    StartScoring();
}