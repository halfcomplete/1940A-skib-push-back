#include "skills_auton.h"
//#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
//#include "lemlib/pose.hpp"
#include "robot.hpp"
#include "helpers.hpp"

void skills_auton() {
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-48.599, -18.1, 180);
    StartIntake();
    // Matchloader.extend();
    float first_matchloader_y = -50;
    chassis.moveToPoint(-48.599, first_matchloader_y, 1500);
    Matchloader.extend();
    chassis.waitUntilDone();

    // Move to matchloader
    chassis.turnToHeading(270, 1000, {.maxSpeed=80});
    chassis.waitUntilDone();
    chassis.moveToPoint(-72, first_matchloader_y, 2000, {.maxSpeed=60});
    chassis.waitUntilDone();
    chassis.moveToPoint(-53.5, first_matchloader_y, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-72, first_matchloader_y, 1000, {.maxSpeed=60});
    chassis.waitUntilDone();

    // Move back slightly
    chassis.moveToPoint(-48, first_matchloader_y, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();

    // Move to the side
    chassis.turnToHeading(180, 1000, {.maxSpeed=65});
    chassis.waitUntilDone();
    float r_side_y = -67;
    chassis.moveToPoint(-54, r_side_y, 1000, {.maxSpeed=50});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1000, {.maxSpeed=45});
    chassis.waitUntilDone();

    float secondMatchloaderY = -55;

    // Move to the front of the long goal
    chassis.moveToPoint(43, r_side_y, 2500, {.maxSpeed=90});
    chassis.waitUntilDone();
    UpdatePose(true, false, false);
    chassis.turnToHeading(0, 1000, {.maxSpeed=80});
    chassis.waitUntilDone();
    chassis.moveToPoint(41, secondMatchloaderY, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1500, {.maxSpeed=80});
    chassis.moveToPoint(12, secondMatchloaderY, 1000, {.forwards=false});
    chassis.waitUntilDone();
    StartIntake();
    StartScoring(GoalType::LONG_GOAL);
    Matchloader.extend();
    pros::delay(2500);
    StopScoring();

    // Move to the matchloader
    Matchloader.extend();
    pros::delay(200);
    Matchloader.extend();
    StartIntake();
    chassis.moveToPoint(70, secondMatchloaderY-1 , 3300, {.maxSpeed=50});
    chassis.moveToPoint(69.5, secondMatchloaderY-1, 500 );
    chassis.waitUntilDone();

    // Move to the long goal and score
    chassis.moveToPoint(21, secondMatchloaderY, 1500, {.forwards=false, .maxSpeed=60});

    

    Matchloader.retract();
    chassis.waitUntilDone();
    StopIntake();
    pros::delay(200);
    StartScoring(GoalType::LONG_GOAL);
    pros::delay(2800);
    StopScoring();

    chassis.moveToPoint(38, secondMatchloaderY +1, 1500);
    chassis.waitUntilDone();
    chassis.turnToHeading(0, 1000, {.maxSpeed=80});

    float thirdMatchloaderY = 42;


    chassis.moveToPoint(50, thirdMatchloaderY, 4000, {.maxSpeed=80});


    // Move to third matchloader
    chassis.turnToHeading(90, 1000, {.maxSpeed=80});
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(66, thirdMatchloaderY +0.4, 2500, {.maxSpeed=50});
    chassis.waitUntilDone();
    chassis.moveToPoint(75, thirdMatchloaderY+1.1, 2500, {.maxSpeed=70});
    chassis.waitUntilDone();

    // Move back slightly
    chassis.moveToPoint(53, 48.5, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();
    StopScoring();

    // Move to the side
    chassis.turnToHeading(0, 1000, {.maxSpeed=80});
    chassis.waitUntilDone();
    chassis.moveToPoint(50, 64.5, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000, {.maxSpeed=80});
    chassis.waitUntilDone();

    float fourthMatchloaderY = 50;

    // Move to the front of the long goal
    chassis.moveToPoint(-40, 64, 2500, {.maxSpeed=80});
    chassis.waitUntilDone();
    UpdatePose(true, false, false);
    chassis.turnToHeading(180, 1000, {.maxSpeed=80});
    chassis.waitUntilDone();
    chassis.moveToPoint(-40, fourthMatchloaderY, 1000, {.maxSpeed=80});
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500, {.maxSpeed=80});
    chassis.waitUntilDone();
    chassis.moveToPoint(-12, fourthMatchloaderY, 1400, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.extend();
    StartScoring(GoalType::LONG_GOAL);
    Matchloader.extend();
    pros::delay(2500);
    StopScoring();

    // Move to the other matchloader
    StartIntake();
    chassis.waitUntilDone();
    chassis.moveToPoint(-80, fourthMatchloaderY+0.5, 4000, {.maxSpeed=50});
    chassis.waitUntilDone();
    
    // Move to the long goal and score
    chassis.moveToPoint(-12, fourthMatchloaderY, 1500, {.forwards=false, .maxSpeed=60});
    Matchloader.retract();
    chassis.waitUntilDone();
    StopScoring();
    pros::delay(200);
    StartScoring(GoalType::LONG_GOAL);
    pros::delay(1900);

    // Move to park zone and clear it
    chassis.moveToPoint(-38, fourthMatchloaderY,1500);
    chassis.waitUntilDone();
    StartScoring(GoalType::LONG_GOAL);
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(-36, 3.2, 4000, {.maxSpeed=50});
    pros::delay(200);
    chassis.turnToHeading(270, 800, {.maxSpeed=50});
    chassis.waitUntilDone();
    chassis.moveToPoint(-25, 3.2, 1000, {.forwards=false, .maxSpeed=70});
    chassis.waitUntilDone();
    chassis.moveToPoint(-90, 3.2, 3000,{.minSpeed=127, .earlyExitRange=1});
    chassis.turnToHeading(270, 400);
    chassis.turnToHeading(260, 400);
    chassis.turnToHeading(280, 400);
    chassis.turnToHeading(260, 400);
}