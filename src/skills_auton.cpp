#include "skills_auton.h"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "robot.hpp"
#include "helpers.hpp"

void skills_auton() {
    chassis.setPose(-48.599, -15.328, 180);
    StartIntake();
    // Matchloader.extend();
    chassis.moveToPoint(-48.599, -46.9, 1500);
    chassis.waitUntilDone();

    // Move to matchloader
    chassis.turnToHeading(270, 1000);
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(-55.8, -46.9, 3000, {.maxSpeed=20});
    chassis.turnToHeading(270, 1500);
    pros::delay(10000);
    // chassis.moveToPoint(-71, -48.5, 1000);
    // chassis.moveToPoint(-85, -48.5, 2000);

    // Move back slightly
    chassis.moveToPoint(-50, -48.5, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();

    // Move to the side
    chassis.turnToHeading(180, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-50, -62.8, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1000);
    chassis.waitUntilDone();

    float secondMatchloaderY = -57;

    // Move to the front of the long goal
    chassis.moveToPoint(33, -63, 2000);
    chassis.waitUntilDone();
    chassis.turnToHeading(0, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(33, secondMatchloaderY + 1, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1500);
    chassis.waitUntilDone();
    chassis.moveToPoint(12, secondMatchloaderY + 1, 1000, {.forwards=false});
    chassis.waitUntilDone();
    StartScoring(true);
    Matchloader.extend();
    pros::delay(4000);
    StopScoring();

    // Move to the other matchloader
    Matchloader.extend();
    StartIntake();
    Matchloader.extend();
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(75, secondMatchloaderY + 1.2, 3500, {.minSpeed=75});
    chassis.waitUntilDone();

    // Move to the long goal and score
    chassis.moveToPoint(24.6, secondMatchloaderY + 1, 1500, {.forwards=false, .maxSpeed=60});
    Matchloader.retract();
    chassis.waitUntilDone();
    StartScoring(true);
    pros::delay(4000);
    StopScoring();

    chassis.moveToPoint(41, secondMatchloaderY + 0.8, 1500);
    chassis.turnToHeading(0, 1000);

    float thirdMatchloaderY = 40;

    chassis.moveToPoint(42, thirdMatchloaderY, 4000, {.maxSpeed=80});

    // Move to third matchloader
    chassis.turnToHeading(90, 1000);
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(80, thirdMatchloaderY, 4000, {.minSpeed=90});

    chassis.waitUntilDone();

    Matchloader.retract();

    // Move back slightly
    chassis.moveToPoint(50, 48.5, 1000, {.forwards=false});
    chassis.waitUntilDone();

    // Move to the side
    chassis.turnToHeading(0, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(50, thirdMatchloaderY + 20, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();

    float fourthMatchloaderY = 53;

    // Move to the front of the long goal
    chassis.moveToPoint(-36, 65.5, 2000);
    chassis.waitUntilDone();
    chassis.turnToHeading(180, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-36, fourthMatchloaderY, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-12, fourthMatchloaderY, 1400, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.extend();
    StartScoring(true);
    Matchloader.extend();
    pros::delay(4000);
    StopScoring();

    // Move to the other matchloader
    StartIntake();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);

    chassis.moveToPoint(-75, fourthMatchloaderY + 1.67, 4000, {.minSpeed=90});
    chassis.waitUntilDone();
    
    // Move to the long goal and score
    chassis.moveToPoint(-27, fourthMatchloaderY, 1500, {.forwards=false, .maxSpeed=60});
    Matchloader.retract();
    chassis.waitUntilDone();
    StartScoring(true);
    pros::delay(4000);
    StopScoring();

    // Move to park zone and clear it
}