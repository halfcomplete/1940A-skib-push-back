#include "skills_auton.h"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "robot.hpp"
#include "helpers.hpp"

void skills_auton() {
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-46.818, -15.547, 180);
    chassis.moveToPoint(-46, -48.8, 1000);
    chassis.turnToHeading(270, 1000);
    Matchloader.extend();
    StartIntake();
    chassis.moveToPoint(-73, -48.8, 5000, {.maxSpeed=60});
    chassis.waitUntilDone();
    chassis.moveToPoint(-27, -50, 1000, {.forwards=false});
    chassis.waitUntilDone();
    StartScoring(true);
    pros::delay(3000);

    chassis.moveToPoint(-50, -48.8, 1000);
    Matchloader.retract();

    // Move to three blocks on the right
    StartIntake();
    chassis.turnToHeading(45, 1000);
    chassis.moveToPoint(-22.066, -17.266, 5000, {.maxSpeed=45});
    chassis.waitUntilDone();

    // Move to long goal
    chassis.moveToPoint(-46, -48.4, 1000, {.forwards=false, .maxSpeed=60});
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(-27, -48.4, 1400, {.forwards=false, .maxSpeed=60});
    StartScoring(true);
    pros::delay(3000);

    // ==== OTHER CORNER ====
    // Move to left long goal
    chassis.moveToPoint(-50, -47.5, 1000);
    chassis.turnToHeading(0, 1000);
    chassis.moveToPoint(-53.7, 47.5, 6000, {.maxSpeed=70});
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();
    Matchloader.extend();

    // Move to matchloader
    StartIntake();
    chassis.moveToPoint(-80, 46.4, 5000, {.maxSpeed=65});
    chassis.waitUntilDone();
    pros::delay(3000);

    // Move to right long goal
    chassis.moveToPose(-29, 47.5, 270, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring(true);
    pros::delay(4000);
    Matchloader.retract();
    chassis.waitUntilDone();
    chassis.moveToPoint(-60, 47.5, 1000);

    // Move to three blocks on the left
    StartIntake();
    chassis.turnToHeading(135, 1000);
    chassis.moveToPoint(-24, 17.266, 4000, {.maxSpeed=45});
    chassis.waitUntilDone();

    // Move to left long goal
    chassis.moveToPoint(-29, 48.5, 1000, {.forwards=false, .maxSpeed=60});
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring(true);
    pros::delay(4000);
    Matchloader.retract();
    chassis.moveToPoint(-58, 48.5, 1000);

    // Move to parking zone and park
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(-36, 0, 4000, {.minSpeed=40});
    pros::delay(200);
    chassis.turnToHeading(270, 800);
    chassis.waitUntilDone();
    chassis.moveToPoint(-90, 0, 2000,{.minSpeed=127, .earlyExitRange=1});
    chassis.turnToHeading(270, 400);
    chassis.turnToHeading(260, 400);
    chassis.turnToHeading(280, 400);
    chassis.turnToHeading(260, 400);
}

// #include "skills_auton.h"
// #include "lemlib/asset.hpp"
// #include "lemlib/chassis/chassis.hpp"
// #include "lemlib/pose.hpp"
// #include "robot.hpp"
// #include "helpers.hpp"

// void skills_auton() {
//     chassis.setPose(-48.599, -15.328, 180);
//     StartIntake();
//     // Matchloader.extend();
//     chassis.moveToPoint(-48.599, -45.9, 1500);
//     Matchloader.extend();
//     chassis.waitUntilDone();

//     // Move to matchloader
//     chassis.turnToHeading(270, 1000);
//     chassis.waitUntilDone();
//     chassis.moveToPoint(-62, -46.9, 1000, {.maxSpeed=60});
//     for (int i = 0; i < 2; i++)
//     {
//         chassis.moveToPoint(-65, -47, 1500, {.minSpeed=45});
//         chassis.waitUntilDone();
//         chassis.moveToPoint(-61, -46, 600, {.forwards=false});
//         chassis.waitUntilDone();
//     }


//     // Move back slightly
//      Top_Roller.move_relative(-90, 100);
//     chassis.moveToPoint(-52, -48, 1000, {.forwards=false});
//     chassis.waitUntilDone();
//     Matchloader.retract();

//     // Move to the side
//     chassis.turnToHeading(180, 1000);
//     chassis.waitUntilDone();
//     chassis.moveToPoint(-54, -59.2, 1000);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(95, 1000);
//     chassis.waitUntilDone();

//     float secondMatchloaderY = -49;

//     // Move to the front of the long goal
//     chassis.moveToPoint(43, -61.67, 2500, {.maxSpeed=80});
//     chassis.waitUntilDone();
//     chassis.turnToHeading(0, 1000);
//     chassis.waitUntilDone();
//     chassis.moveToPoint(41, secondMatchloaderY, 1000);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(90, 1500);
//     chassis.moveToPoint(12, secondMatchloaderY, 1000, {.forwards=false});
//     chassis.waitUntilDone();
//     StartIntake();
//     StartScoring(true);
//     Matchloader.extend();
//     pros::delay(2500);
//     StopScoring();

//     // Move to the other matchloader
//     Matchloader.extend();
//     StartIntake();
//     Matchloader.extend();
//     chassis.moveToPoint(70, secondMatchloaderY+2 , 3300, {.maxSpeed=50});
//     chassis.moveToPoint(69.5, secondMatchloaderY+2, 500 );
//     chassis.waitUntilDone();
//     Top_Roller.move_relative(-90, 100);
//     chassis.waitUntilDone();

//     // Move to the long goal and score
//     chassis.moveToPoint(21, secondMatchloaderY, 1500, {.forwards=false, .maxSpeed=60});
//     Matchloader.retract();
//     chassis.waitUntilDone();
//     StartScoring(true);
//     pros::delay(2800);
//     StopScoring();

//     chassis.moveToPoint(43, secondMatchloaderY +1, 1500);
//     chassis.turnToHeading(0, 1000);

//     float thirdMatchloaderY = 48;

//     chassis.moveToPoint(41, 48, 4000, {.maxSpeed=80});

//     // Move to third matchloader
//     chassis.turnToHeading(90, 1000);
//     Matchloader.extend();
//     chassis.waitUntilDone();
//     chassis.moveToPoint(66, thirdMatchloaderY, 2500, {.maxSpeed=50});
//     chassis.waitUntilDone();
//     chassis.moveToPoint(73, thirdMatchloaderY+1, 2500, {.maxSpeed=50});
//     chassis.waitUntilDone();
//     Top_Roller.move_relative(-90, 100);

//     // Move back slightly
//     chassis.moveToPoint(53, 48.5, 1000, {.forwards=false});
//     chassis.waitUntilDone();
//     Matchloader.retract();

//     // Move to the side
//     chassis.turnToHeading(0, 1000);
//     chassis.waitUntilDone();
//     chassis.moveToPoint(50, 64.5, 1000);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(280, 1000);
//     chassis.waitUntilDone();

//     float fourthMatchloaderY = 52;

//     // Move to the front of the long goal
//     chassis.moveToPoint(-40, 66.5, 2500, {.maxSpeed=80});
//     chassis.waitUntilDone();
//     chassis.turnToHeading(180, 1000);
//     chassis.waitUntilDone();
//     chassis.moveToPoint(-40, 52, 1000);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(270, 500);
//     chassis.waitUntilDone();
//     chassis.moveToPoint(-12, fourthMatchloaderY+3 , 1400, {.forwards=false});
//     chassis.waitUntilDone();
//     Matchloader.extend();
//     StartScoring(true);
//     Matchloader.extend();
//     pros::delay(2500);
//     StopScoring();

//     // Move to the other matchloader
//     StartIntake();
//     chassis.waitUntilDone();
//     chassis.moveToPoint(-80, fourthMatchloaderY+2, 4000, {.maxSpeed=50});
//     chassis.waitUntilDone();
//     Top_Roller.move_relative(-90, 100);
    
//     // Move to the long goal and score
//     chassis.moveToPoint(-12, fourthMatchloaderY, 1500, {.forwards=false, .maxSpeed=60});
//     Matchloader.retract();
//     chassis.waitUntilDone();
//     StartScoring(true);
//     pros::delay(1900);

//     // Move to park zone and clear it
//     chassis.moveToPoint(-38, fourthMatchloaderY,1500);
//     chassis.waitUntilDone();
//     StartScoring();
//     chassis.turnToHeading(180, 1000);
//     chassis.moveToPoint(-36, 5, 4000, {.minSpeed=40});
//     pros::delay(200);
//     chassis.turnToHeading(270, 800);
//     chassis.waitUntilDone();
//     chassis.moveToPoint(-90, 8, 2000,{.minSpeed=127, .earlyExitRange=1});
//     chassis.turnToHeading(270, 400);
//     chassis.turnToHeading(260, 400);
//     chassis.turnToHeading(280, 400);
//     chassis.turnToHeading(260, 400);
// }