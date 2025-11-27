#include "finals_auton.h"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "robot.hpp"

void finals_right_auton()
{
    chassis.setPose(45.65, 16.9, 0);
    Conveyer.move(-12000);
    Top_Roller.move(12000);
    Trapdoor.retract();

    // Move to matchloader
    chassis.moveToPose(42.5, 46.9, 0, 1000);
    chassis.turnToHeading(90, 1000);
    chassis.waitUntilDone();

    // Collect blocks from matchloader
    Matchloader.extend();
    chassis.moveToPose(55.5, 47.3, 90, 1500);
    for (int i = 0; i < 2; i++) {
        chassis.moveToPoint(57.8, 47.3, 450, {.minSpeed = 100});
        chassis.moveToPoint(55.5, 47.3, 450, {.minSpeed = 100});
    }

    // Move to Long goal
    chassis.waitUntilDone();
    chassis.moveToPoint(50.5, 47.5, 2000);
    chassis.waitUntilDone();
    Matchloader.retract();
    pros::delay(100);
    chassis.moveToPose(29.3, 47.5, 270, 2000);
    chassis.waitUntilDone();

    // Score all 4 blocks in the long goal
    Trapdoor.extend();
    Conveyer.move(-12000);
    pros::delay(2800);
    // Inside_Roller.move_velocity(0);
    pros::delay(100);

    // Reverse slightly
    chassis.moveToPoint(51.5, 47.3, 1500, {.forwards = false});
    chassis.waitUntilDone();
    Trapdoor.toggle();
    chassis.turnToHeading(225, 70, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE});
    Top_Roller.move(12000);

    // Intake 3 more blocks
    chassis.moveToPose(15, 15, 225, 3000, {.maxSpeed = 60});
    chassis.waitUntilDone();

    // Go back to the front of the long goal
    chassis.moveToPoint(45.5, 45, 1000, {.forwards = false});
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToHeading(270, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE});
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.moveToPose(28.7, 42, 270, 1800, {.maxSpeed = 70});
    chassis.waitUntilDone();

    // Score all 4 blocks in the long goal
    Trapdoor.extend();
    Conveyer.move(-12000);
    Top_Roller.move(12000);
    // Inside_Roller.move(-12000);
}

void finals_left_auton()
{
    chassis.setPose(46.768, -21, 270);
    Conveyer.move(-12000);
    Top_Roller.move(12000);
    Trapdoor.retract();

    // Intake 4 more blocks
    // Inside_Roller.move(0);
    chassis.moveToPoint(20.729, -26.561, 3000, {.maxSpeed = 40});
    chassis.waitUntilDone();
    pros::delay(400);

    // Move to matchloader
    chassis.moveToPoint(48, -47, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1000);
    chassis.waitUntilDone();

    // Collect blocks from matchloader
    Matchloader.extend();
    chassis.moveToPose(55, -47, 90, 1500,{.maxSpeed = 70});
    for (int i = 0; i < 3; i++) {
        chassis.moveToPoint(58.5, -47, 450, {.minSpeed = 100});
        chassis.moveToPoint(55.2, -47, 450);
    }

    // Move to Long goal
    chassis.waitUntilDone();
    chassis.moveToPoint(51.5, -46.7, 1000);
    chassis.waitUntilDone();
    Matchloader.retract();
    pros::delay(100);
    chassis.moveToPose(26.67, -47.567, 90, 1000);
    chassis.waitUntilDone();
    pros::delay(300);

    // Score all 7 blocks in the long goal
    Trapdoor.extend();
    Conveyer.move(-12000);
    Top_Roller.move(12000);
    // Inside_Roller.move(-12000);
    pros::delay(4000);

    // // Reverse slightly
    // chassis.moveToPoint(47, -46.35, 2000, {.forwards = false});
    // chassis.waitUntilDone();
    // pros::delay(1300);
    // chassis.turnToHeading(315, 70, {.direction = lemlib::AngularDirection::CW_CLOCKWISE});
    // Top_Roller.move(12000);

    // // Go back to the front of the long goal
    // chassis.moveToPoint(45.5, -46.4, 1000, {.forwards = false});
    // chassis.waitUntilDone();
    // pros::delay(100);
    // chassis.turnToHeading(270, 1000, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE});
    // chassis.waitUntilDone();
    // pros::delay(200);
    // chassis.moveToPose(26, -46.5, 270, 1000);
    // chassis.waitUntilDone();
    // pros::delay(300);

    // // Score all 4 blocks in the long goal
    // Switcheroo.extend();
    // Bottom_Roller.move(-12000);
    // Top_Roller.move(12000);
    // Inside_Roller.move(-12000);
    // pros::delay(3200);
    // Switcheroo.toggle();
}