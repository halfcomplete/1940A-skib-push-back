#include "skills_auton.h"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "robot.hpp"
#include "helpers.hpp"

void skills_auton() {
    chassis.setPose(-48.599, -15.328, 180);
    StartIntake();
    Matchloader.extend();
    chassis.moveToPoint(-48.599, -48, 1500);
    chassis.waitUntilDone();

    // Move to matchloader
    chassis.turnToHeading(270, 1000);
    Matchloader.extend();
    chassis.waitUntilDone();

    for (int i = 0; i < 5; i++) {
        chassis.moveToPoint(-60, -48, 1400, {.minSpeed=80});
        pros::delay(400);
        chassis.moveToPoint(-67, -48, 500);
        pros::delay(500);
    }

    Matchloader.retract();

    // Move back slightly
    chassis.moveToPoint(-50, -48, 1000, {.forwards=false});
    chassis.waitUntilDone();

    // Move to the side
    chassis.turnToHeading(180, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-50, -63, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1000);
    chassis.waitUntilDone();

    int secondMatchloaderY = -57.5;

    // Move to the front of the long goal
    chassis.moveToPoint(43, -66, 2000);
    chassis.waitUntilDone();
    chassis.turnToHeading(0, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(43, secondMatchloaderY, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1500);
    chassis.waitUntilDone();
    chassis.moveToPoint(18, secondMatchloaderY, 1000, {.forwards=false});
    chassis.waitUntilDone();
    StartScoring();
    pros::delay(3000);
    StopScoring();

    // Move to the other matchloader
    StartIntake();
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(61, secondMatchloaderY + 0.5, 1400, {.minSpeed=65});
    chassis.waitUntilDone();

    for (int i = 0; i < 5; i++)
    {
        chassis.moveToPoint(61, secondMatchloaderY + 0.5, 1400);
        chassis.waitUntilDone();
        pros::delay(400);
        chassis.moveToPoint(67, secondMatchloaderY + 0.5, 500);
        chassis.waitUntilDone();
        pros::delay(500);
    }

    // Move to the long goal and score
    chassis.moveToPoint(27, secondMatchloaderY, 1500, {.forwards=false, .maxSpeed=60});
    Matchloader.retract();
    chassis.waitUntilDone();
    StartScoring();
    pros::delay(3000);
    StopScoring();
}