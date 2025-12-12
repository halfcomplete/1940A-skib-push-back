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
    chassis.moveToPoint(-62, -49, 1000, {.maxSpeed=60});
    for (int i = 0; i < 2; i++)
    {
        chassis.moveToPoint(-65, -49, 1500, {.minSpeed=45});
        chassis.waitUntilDone();
        chassis.moveToPoint(-61, -49, 600, {.forwards=false});
        chassis.waitUntilDone();
    }
    pros::delay(1000);

    // Move back slightly
     Top_Roller.move_relative(-90, 100);
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

    float secondMatchloaderY = -49;

    // Move to the front of the long goal
    chassis.moveToPoint(43, -61.67, 2500, {.maxSpeed=80});
    chassis.waitUntilDone();
    chassis.turnToHeading(0, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(41, secondMatchloaderY, 1000);
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
    chassis.moveToPoint(70, secondMatchloaderY , 3300, {.maxSpeed=50});
    chassis.moveToPoint(69.5, secondMatchloaderY, 500 );
    chassis.waitUntilDone();
    Top_Roller.move_relative(-90, 100);
    chassis.waitUntilDone();

    // Move to the long goal and score
    chassis.moveToPoint(21, secondMatchloaderY, 1500, {.forwards=false, .maxSpeed=60});
    Matchloader.retract();
    chassis.waitUntilDone();
    StartScoring(true);
    pros::delay(2800);
    StopScoring();

    chassis.moveToPoint(43, secondMatchloaderY +1, 1500);
    chassis.turnToHeading(0, 1000);

    float thirdMatchloaderY = 48;

    chassis.moveToPoint(41, 48, 4000, {.maxSpeed=80});

    // Move to third matchloader
    chassis.turnToHeading(90, 1000);
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(66, thirdMatchloaderY, 4000, {.maxSpeed=50});
    chassis.waitUntilDone();
    chassis.moveToPoint(74, thirdMatchloaderY, 3000, {.maxSpeed=40});
    chassis.waitUntilDone();
    Top_Roller.move_relative(-90, 100);

    // Move back slightly
    chassis.moveToPoint(53, 48.5, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();

    // Move to the side
    chassis.turnToHeading(0, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(50, 63, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();

    float fourthMatchloaderY = 50;

    // Move to the front of the long goal
    chassis.moveToPoint(-40, 62, 2500, {.maxSpeed=65});
    chassis.waitUntilDone();
    chassis.turnToHeading(180, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-40, 47, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-12, fourthMatchloaderY , 1400, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.extend();
    StartScoring(true);
    Matchloader.extend();
    pros::delay(4000);
    StopScoring();

    // Move to the other matchloader
    StartIntake();
    chassis.waitUntilDone();

    chassis.moveToPoint(-80, fourthMatchloaderY +2, 4000, {.maxSpeed=50});
    chassis.waitUntilDone();
    Top_Roller.move_relative(-90, 100);
    
    // Move to the long goal and score
    chassis.moveToPoint(-12, fourthMatchloaderY, 1500, {.forwards=false, .maxSpeed=60});
    Matchloader.retract();
    chassis.waitUntilDone();
    StartScoring(true);
    pros::delay(1800);
    StopScoring();

    // Move to park zone and clear it
    chassis.moveToPoint(-38, fourthMatchloaderY,1500);
    chassis.waitUntilDone();
    StartIntake();
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(-36, 0, 5000, {.maxSpeed=60});
    chassis.turnToHeading(270, 1000);
    chassis.moveToPose(-75, 5.7, 270, 10000, {.minSpeed=127});
}