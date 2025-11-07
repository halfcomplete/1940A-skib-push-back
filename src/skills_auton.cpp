#include "skills_auton.h"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "robot.hpp"

void skills_auton() {
    // Bottom_Roller.move(-12000);
    // Top_Roller.move(12000);
    // Switcheroo.retract();
    // chassis.setPose(-62.87, 15.447, 180);
    // pros::delay(200);
    // chassis.moveToPoint(-62.87, -8.335, 3000);

    chassis.setPose(45.65, 16.9, 0);
    Bottom_Roller.move(-12000);
    Top_Roller.move(12000);
    Switcheroo.retract();
    float firstMatchloaderY = 47.4;
    // Move to matchloader
    chassis.moveToPose(42.5, firstMatchloaderY, 0, 1000);
    chassis.turnToHeading(90, 1000);
    chassis.waitUntilDone();

    // Collect blocks from matchloader
    Matchloader.extend();
    chassis.moveToPose(55.5, firstMatchloaderY, 90, 1500,{.maxSpeed = 70});
    for (int i = 0; i < 7; i++) {
        chassis.moveToPoint(57, firstMatchloaderY, 450, {.minSpeed = 100});
        chassis.moveToPoint(55.2, firstMatchloaderY, 450);
    }
    chassis.moveToPoint(57.75, firstMatchloaderY, 450, {.minSpeed = 100});
    pros::delay(500);
    chassis.moveToPoint(55.2, firstMatchloaderY, 450);

    // Move to Long goal
    chassis.waitUntilDone();
    chassis.moveToPoint(50.5, firstMatchloaderY, 2000);
    chassis.waitUntilDone();
    Matchloader.retract();
    pros::delay(100);
    chassis.turnToHeading(280, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(29.3, firstMatchloaderY + 0.8, 2000);
    chassis.waitUntilDone();

    // Score all 7 blocks in the long goal
    Switcheroo.extend();
    Bottom_Roller.move(-11000);
    Top_Roller.move(11000);
    Inside_Roller.move(-11000);
    pros::delay(4700);

    // Reverse slightly
    chassis.moveToPoint(51.5, firstMatchloaderY, 1500, {.forwards = false});
    chassis.waitUntilDone();
    Switcheroo.toggle();
    chassis.turnToHeading(225, 70, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE});
    Top_Roller.move(12000);

    // Intake 4 more blocks
    chassis.moveToPose(13, 14, 225, 3000, {.maxSpeed = 60});
    chassis.waitUntilDone();

    // Go back to the front of the long goal
    chassis.moveToPoint(45.5, firstMatchloaderY, 1000, {.forwards = false});
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToHeading(270, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE});
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.moveToPose(28.4, firstMatchloaderY - 4.2, 270, 1800, {.maxSpeed = 70});
    chassis.waitUntilDone();

    // Score all 4 blocks in the long goal
    Switcheroo.extend();
    Bottom_Roller.move(-12000);
    Top_Roller.move(12000);
    Inside_Roller.move(-12000);
    pros::delay(2900);
    Switcheroo.toggle();

    // Move back
    chassis.moveToPoint(38, firstMatchloaderY,  1000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToHeading(0, 1000);
    Top_Roller.move(0);
    Inside_Roller.move(0);
    Bottom_Roller.move(0);

    // // SETUP FROM CORNER ================================================
    // Bottom_Roller.move(-12000);
    // Top_Roller.move(12000);
    // Inside_Roller.move(0);
    // Switcheroo.retract();

    // chassis.setPose(lemlib::Pose(42.67, -64, 0));

    float secondMatchloaderY = -55.4;
    // ======== OTHER CORNER ========
    // Move back to other corner
    chassis.moveToPose(38, secondMatchloaderY, 0, 5000, {.forwards = false});
    chassis.turnToHeading(90, 1000);
    chassis.waitUntilDone();

    // Collect blocks from matchloader
    Matchloader.extend();
    Bottom_Roller.move(-12000);
    Top_Roller.move(12000);
    chassis.moveToPose(52, secondMatchloaderY, 90, 1500,{.maxSpeed = 70});
    for (int i = 0; i < 7; i++) {
        chassis.moveToPoint(56, secondMatchloaderY, 450, {.minSpeed = 100});
        chassis.moveToPoint(51.7, secondMatchloaderY, 450);
    }
    chassis.moveToPoint(55, secondMatchloaderY, 450, {.minSpeed = 100});
    pros::delay(400);
    chassis.moveToPoint(52, secondMatchloaderY, 450);

    // Move to Long goal
    chassis.waitUntilDone();
    chassis.moveToPoint(49.7, secondMatchloaderY, 1000);
    chassis.waitUntilDone();
    Matchloader.retract();
    pros::delay(100);
    chassis.moveToPose(22, secondMatchloaderY + 0.3, 90, 1000);
    chassis.waitUntilDone();
    pros::delay(200);

    // Score all 6 blocks in the long goal
    Switcheroo.extend();
    Bottom_Roller.move(-12000);
    Top_Roller.move(12000);
    Inside_Roller.move(-12000);
    pros::delay(4400);

    Switcheroo.toggle();

    // Reverse slightly
    chassis.moveToPoint(47, secondMatchloaderY, 2000, {.forwards = false});
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.turnToHeading(315, 70, {.direction = lemlib::AngularDirection::CW_CLOCKWISE});
    Top_Roller.move(12000);

    // Intake 4 more blocks
    Inside_Roller.move(0);
    chassis.moveToPoint(10, -24, 3000, {.maxSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(200);

    // Go back to the front of the long goal
    chassis.moveToPoint(44, secondMatchloaderY + 0.45, 1000, {.forwards = false});
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToHeading(270, 1000, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE});
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.moveToPose(22, secondMatchloaderY - 0.35, 270, 1000);
    chassis.waitUntilDone();
    pros::delay(200);

    // Score all 4 blocks in the long goal
    Switcheroo.extend();
    Bottom_Roller.move(-12000);
    Top_Roller.move(12000);
    Inside_Roller.move(-12000);
    pros::delay(3000);
    Switcheroo.toggle();

    // // SETUP FOR PARK ======================================================================
    // chassis.setPose(lemlib::Pose(26, -46.3, 270));
    // Bottom_Roller.move(-12000);
    // Top_Roller.move(12000);
    // Inside_Roller.move(-12000);
    // Switcheroo.extend();

    // Park and clear park zone
    ODOM_Lift.extend();
    Bottom_Roller.move(12000);
    chassis.moveToPoint(49, secondMatchloaderY, 1200, {.forwards = false, .minSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToHeading(217, 1000);
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.moveToPoint(68.5, 8.8, 15000, {.minSpeed = 85});
    right_mg.move_velocity(450);
};