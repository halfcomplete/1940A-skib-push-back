#include "skills_auton.h"
//#include "lemlib/asset.hpp"
#include "goal_type.hpp"
#include "lemlib/chassis/chassis.hpp"
//#include "lemlib/pose.hpp"
#include "robot.hpp"
#include "helpers.hpp"
float firstMatchloaderY = -47;//-49.5
float secondMatchloaderY = -54.5; //-55.5
float thirdMatchloaderY = 41; //41.1
float fourthMatchloaderY = 50;
float r_side_y = -66;
// x=65.6, y=17.7 if clearing first park zone first
void skills_auton() {
    startOuttakeTask();
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    Wing.extend();
    // chassis.setPose(-48.599, -18.1, 180);
    chassis.setPose(-58.6, -3.8, 270);
    first_clear();
    high_goal();
    first_corner();
    second_corner();
    second_clear();
    third_corner();
    fourth_corner();
    final_park();
}

void first_clear()
{
    ClearParkZone(chassis.getPose(), 270);
    chassis.waitUntilDone();
}

void high_goal()
{
    StopIntake();
    chassis.moveToPoint(-26.7, 19, 3000, {.maxSpeed=90});
    
    chassis.turnToHeading(315, 1000);
    // StopIntake();
    // StartScoring(GoalType::LONG_GOAL);
    // pros::delay(40);
    // StopIntake();
    // StopScoring();
    // overrideOuttake(-25);
    chassis.waitUntilDone();
    chassis.moveToPoint(-7.7, 0.5, 1000, {.forwards=false});
    chassis.waitUntilDone();
    overrideOuttake(12000);
    pros::delay(200);
    
    StartScoring(GoalType::HIGH_GOAL, false);
    pros::delay(2300);
    StopScoring();
    StopIntake();
    chassis.moveToPoint(-20.1, 17.4, 1000);
    chassis.waitUntilDone();
}

void first_corner()
{
    // Matchloader.extend();
    chassis.turnToPoint(-44, firstMatchloaderY, 1000, {.maxSpeed=80});
    chassis.waitUntilDone();
    StartScoring(LONG_GOAL);
    chassis.moveToPoint(-44, firstMatchloaderY, 1500);
    Matchloader.extend();
    chassis.waitUntilDone();
    StopScoring();
    StartIntake();

    // Move to matchloader
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-73, firstMatchloaderY-1.6, 2000);
    chassis.waitUntilDone();

    // Move back slightly
    chassis.moveToPoint(-53, firstMatchloaderY-1.6, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();

    // Move to the side
    chassis.turnToHeading(295, 1000, {.minSpeed=1, .earlyExitRange=1});
    chassis.waitUntilDone();
    chassis.moveToPoint(-35, r_side_y, 1000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();
}

void second_corner()
{
    // Move to the front of the long goal
    chassis.moveToPoint(39, r_side_y, 2500, {.forwards=false, .maxSpeed=110});
    chassis.waitUntilDone();
    UpdatePose(false, true, false);
    chassis.turnToHeading(180, 1000, {.minSpeed=1, .earlyExitRange=1});
    chassis.waitUntilDone();
    chassis.moveToPoint(39, secondMatchloaderY, 1000, {.forwards=false, .minSpeed=1, .earlyExitRange=1});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1500, {.maxSpeed=80});
    chassis.moveToPoint(12, secondMatchloaderY, 1000, {.forwards=false});
    chassis.waitUntilDone();
    StartIntake();
    StartScoring(GoalType::LONG_GOAL);
    Matchloader.extend();
    pros::delay(1600);
    StopScoring();

    // Move to the matchloader
    Matchloader.extend();
    StartIntake();
    chassis.moveToPoint(52, secondMatchloaderY, 2000, {.minSpeed=80, .earlyExitRange=6});
    chassis.moveToPoint(70, secondMatchloaderY-0.5, 2300, {.maxSpeed=40});
    chassis.waitUntilDone();

    // Move to the long goal and score
    chassis.moveToPoint(21, secondMatchloaderY, 1500, {.forwards=false, .maxSpeed=70});

    chassis.waitUntilDone();
    Matchloader.retract();
    StopIntake();
    pros::delay(10);
    StartScoring(GoalType::LONG_GOAL);
    pros::delay(1600);
    StopScoring();

    chassis.moveToPoint(40, secondMatchloaderY +1, 1500);
    chassis.waitUntilDone();
    chassis.turnToHeading(0, 1000);
}

void second_clear()
{

}

void third_corner()
{
    chassis.moveToPoint(40, thirdMatchloaderY-10, 4000, {.minSpeed=70, .earlyExitRange=10});
    chassis.moveToPoint(40, thirdMatchloaderY, 4000, {.maxSpeed=100});


    // Move to third matchloader
    chassis.turnToHeading(90, 1000, {.maxSpeed=80});
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(49, thirdMatchloaderY+1.1, 2000, {.minSpeed=80, .earlyExitRange=6});
    chassis.moveToPoint(80, thirdMatchloaderY+1.1, 2300, {.maxSpeed=80});
    chassis.waitUntilDone();

    // Move back slightly
    chassis.moveToPoint(45, thirdMatchloaderY, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();

    // Move to the side
    chassis.turnToHeading(120, 1000, {.minSpeed=1, .earlyExitRange=1});
    chassis.waitUntilDone();
    chassis.moveToPoint(40, 64.5, 1000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1000, {.maxSpeed=80});
    chassis.waitUntilDone();
}

void fourth_corner()
{
    // Move to the front of the long goal
    chassis.moveToPoint(-41, 63, 2500, {.forwards=false, .maxSpeed=110});
    chassis.waitUntilDone();
    UpdatePose(false, true, false);
    chassis.turnToHeading(0, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-41, fourthMatchloaderY, 1000, {.forwards=false, .maxSpeed=80});
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-12, fourthMatchloaderY, 800, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.extend();
    StartScoring(GoalType::LONG_GOAL);
    Matchloader.extend();
    pros::delay(1600);
    StopScoring();

    // Move to the other matchloader
    StartIntake();
    chassis.waitUntilDone();
    chassis.moveToPoint(-54, fourthMatchloaderY-1, 2000, {.minSpeed=80, .earlyExitRange=6});
    chassis.moveToPoint(-80, fourthMatchloaderY-2, 2200, {.maxSpeed=60});
    chassis.waitUntilDone();

    // Move to the long goal and score
    chassis.moveToPoint(-12, fourthMatchloaderY, 1200, {.forwards=false, .maxSpeed=80});
    Matchloader.retract();
    chassis.waitUntilDone();
    StopScoring();
    pros::delay(10);
    StartScoring(GoalType::LONG_GOAL);
    pros::delay(1600);
}

void final_park()
{
    // Move to park zone and clear it
    chassis.moveToPoint(-51, fourthMatchloaderY,1500);
    chassis.waitUntilDone();
    StartScoring(GoalType::LONG_GOAL);
    // chassis.turnToHeading(180, 1000);
    // chassis.moveToPoint(-24, 1.4, 4000);
    // chassis.turnToHeading(272, 800);
    // chassis.waitUntilDone();
    // chassis.moveToPoint(-90, 1.4, 3000,{.minSpeed=127, .earlyExitRange=1});
    // chassis.turnToHeading(270, 400);
    // chassis.turnToHeading(260, 400);
    // chassis.turnToHeading(280, 400);
    // chassis.turnToHeading(260, 400);
    // idea: go into the park zone from the side
}