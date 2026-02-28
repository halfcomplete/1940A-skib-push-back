#include "auton.h"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robot.hpp"
#include "skills_auton.h"
#include "finals_auton.h"
#include "helpers.hpp"
#include "auton_type.h"

void TestPidTurn(int angle)
{
    chassis.setPose(0, 0, 0);
    pros::delay(100);
    chassis.turnToHeading(angle, 10000);
}

void TestPidMove(int distance)
{
    chassis.setPose(0, 0, 0);
    pros::delay(100);
    chassis.moveToPose(0, distance, 0, 10000);
}