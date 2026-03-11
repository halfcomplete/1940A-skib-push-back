#include "helpers.hpp"
#include "pros/rtos.hpp"
#include "robot.hpp"
#include "goal_type.hpp"
#include "auton.h"

void colourSort() {
    // pros::Task sortTask([&]()->void {
    //     while (true) {
    //         if (SkIbIdI_oPtIcAl.get_hue() > 90 && SkIbIdI_oPtIcAl.get_proximity() > 128) {
    //             Trapdoor.retract();
    //             pros::delay(50);
    //             Trapdoor.extend();
    //         }

    //         pros::delay(10);
    //     }
    // });
}


void StartIntake()
{
    First_Stage_Intake.move(600);
    Second_Stage_Intake.move(600);
}

void StartOuttake(bool scoring)
{
    Second_Stage_Intake.move(-600);
    First_Stage_Intake.move(-600);
}

void StopIntake()
{
    First_Stage_Intake.brake();
    Second_Stage_Intake.brake();
}

/// @brief Start scoring by starting the intake and scoring mech.
/// @param auton 
/// @param goalType The type of goal we are scoring in.
void StartScoring(GoalType goalType)
{
    if (goalType == HIGH_GOAL)
    {
        StartIntake();
        overrideOuttake(600);
    }
    else if (goalType == LOW_GOAL)
    {
        StartOuttake(true);
        overrideOuttake(600);
    }
    else 
    {
        StartIntake();
        overrideOuttake(-600);
        Outtake_Lift.extend();
    }
}

void StopScoring()
{
    Outtake_Lift.retract();
    releaseOuttakeOverride();
}

/// @return The distance measurement from the front sensor in mm. Returns -1 if no object is detected or if the confidence is not above 50.
int GetFrontDistanceMeasurement()
{
    int distance = Front_Sensor.get();
    if (!IsFrontDistanceConfident() || distance == 9999)
        return -1;
    return distance;
}

bool IsFrontDistanceConfident()
{
    return Front_Sensor.get_confidence() > 50;
}

/// @return The distance measurement from the left sensor in mm. Returns -1 if no object is detected or if the confidence is not above 50.
int GetLeftDistanceMeasurement()
{
    int distance = Left_Sensor.get();
    if (!IsLeftDistanceConfident() || distance == 9999)
        return -1;
    return distance;
}

bool IsLeftDistanceConfident()
{
    return Left_Sensor.get_confidence() > 50;
}

/// @return The distance measurement from the right sensor in mm. Returns -1 if no object is detected or if the confidence is not above 50.
int GetRightDistanceMeasurement()
{
    int distance = Right_Sensor.get();
    if (!IsRightDistanceConfident() || distance == 9999)
        return -1;
    return distance;
}

bool IsRightDistanceConfident()
{
    return Right_Sensor.get_confidence() > 40;
}