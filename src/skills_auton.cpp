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
    Matchloader.extend();
    chassis.waitUntilDone();

    // Move to matchloader
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-62, -48, 1000);
    for (int i = 0; i < 2; i++)
    {
        chassis.moveToPoint(-65, -48, 1000, {.minSpeed=62});
        chassis.waitUntilDone();
        chassis.moveToPoint(-61, -48, 600, {.forwards=false});
        chassis.waitUntilDone();
    }

    // Move back slightly
    chassis.moveToPoint(-52, -48, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();

    // Move to the side
    chassis.turnToHeading(180, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-54, -61.2, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1000);
    chassis.waitUntilDone();

    float secondMatchloaderY = -52.7;

    // Move to the front of the long goal
    chassis.moveToPoint(43, -61.67, 2000);
    chassis.waitUntilDone();
    chassis.turnToHeading(0, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(43, secondMatchloaderY, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1500);
    chassis.moveToPoint(12, secondMatchloaderY, 1000, {.forwards=false});
    chassis.waitUntilDone();
    StartIntake();
    StartScoring(true);
    Matchloader.extend();
    pros::delay(2500);
    StopScoring();

    // Move to the other matchloader
    Matchloader.extend();
    StartIntake();
    Matchloader.extend();
    chassis.moveToPoint(74, secondMatchloaderY + 2, 3300, {.maxSpeed=60});
    chassis.waitUntilDone();
    chassis.waitUntilDone();

    // Move to the long goal and score
    chassis.moveToPoint(23, secondMatchloaderY, 1500, {.forwards=false, .maxSpeed=60});
    Matchloader.retract();
    chassis.waitUntilDone();
    StartScoring(true);
    pros::delay(2500);
    StopScoring();

    chassis.moveToPoint(43, secondMatchloaderY + 0.8, 1500);
    chassis.turnToHeading(0, 1000);

    float thirdMatchloaderY = 43.4;

    chassis.moveToPoint(43, thirdMatchloaderY, 4000, {.maxSpeed=80});

    // Move to third matchloader
    chassis.turnToHeading(90, 1000);
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(61, thirdMatchloaderY, 4000);
    chassis.waitUntilDone();
    chassis.moveToPoint(71, thirdMatchloaderY, 3000, {.maxSpeed=60});
    chassis.waitUntilDone();

    // Move back slightly
    chassis.moveToPoint(55, 48.5, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();

    // Move to the side
    chassis.turnToHeading(0, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(50, 58.2, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();

    float fourthMatchloaderY = 54.3;

    // Move to the front of the long goal
    chassis.moveToPoint(-40, 58.2, 4000);
    chassis.waitUntilDone();
    chassis.turnToHeading(180, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-40, fourthMatchloaderY, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-12, fourthMatchloaderY - 1.1, 1400, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.extend();
    StartScoring(true);
    Matchloader.extend();
    pros::delay(4000);
    StopScoring();

    // Move to the other matchloader
    StartIntake();
    chassis.waitUntilDone();

    chassis.moveToPoint(-75, fourthMatchloaderY - 2, 4000, {.maxSpeed=60});
    chassis.waitUntilDone();
    
    // Move to the long goal and score
    chassis.moveToPoint(-12, fourthMatchloaderY, 1500, {.forwards=false, .maxSpeed=60});
    Matchloader.retract();
    chassis.waitUntilDone();
    StartScoring(true);
    pros::delay(1800);
    StopScoring();

    // Move to park zone and clear it
    chassis.moveToPoint(-36, fourthMatchloaderY, 1500);
    StartIntake();
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(-36, 5.7, 5000, {.maxSpeed=60});
    chassis.turnToHeading(270, 1000);
    chassis.moveToPose(-75, 5.7, 270, 10000, {.minSpeed=127});
}