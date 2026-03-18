#include "helpers.hpp"
#include "pros/rtos.hpp"
#include "robot.hpp"
#include "goal_type.hpp"
#include "auton.h"
#include <cmath>

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
    releaseOuttakeOverride();
}

void StartOuttake(bool scoring)
{
    if (scoring)
    {
        Second_Stage_Intake.move(-300);
        First_Stage_Intake.move(-300);
    }
    else {
        Second_Stage_Intake.move(-600);
        First_Stage_Intake.move(-600);
    }
    
    releaseOuttakeOverride();
}

void StopIntake()
{
    First_Stage_Intake.brake();
    Second_Stage_Intake.brake();
    releaseOuttakeOverride();
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

namespace {
    constexpr double kMmPerInch = 25.4;
    constexpr double kFieldMinIn = -72.0;
    constexpr double kFieldMaxIn = 72.0;
    constexpr double kRobotHalfWidthIn = 7.0;
    constexpr double kRobotHalfLengthIn = 8.0;
    constexpr double kHeadingOffsetDegrees = 90.0;

    enum CardinalDirection {
        POS_X = 0,
        POS_Y = 1,
        NEG_X = 2,
        NEG_Y = 3
    };

    double mmToInches(double mm) {
        return mm / kMmPerInch;
    }

    double normalizeDegrees(double angleDegrees) {
        double out = std::fmod(angleDegrees, 360.0);
        if (out < 0) out += 360.0;
        return out;
    }

    int getNearestCardinal(double headingDegrees) {
        int cardinal = static_cast<int>(std::lround(headingDegrees / 90.0)) % 4;
        if (cardinal < 0) cardinal += 4;
        return cardinal;
    }

    void applyDistanceToPose(lemlib::Pose& pose, int wallDirection, double distanceInches, double robotHalfExtentInches) {
        if (wallDirection == POS_X) {
            pose.x = kFieldMaxIn - (distanceInches + robotHalfExtentInches);
        } else if (wallDirection == NEG_X) {
            pose.x = kFieldMinIn + (distanceInches + robotHalfExtentInches);
        } else if (wallDirection == POS_Y) {
            pose.y = kFieldMaxIn - (distanceInches + robotHalfExtentInches);
        } else {
            pose.y = kFieldMinIn + (distanceInches + robotHalfExtentInches);
        }
    }
}

void UpdatePose(bool useRight, bool useLeft, bool useFront)
{
    lemlib::Pose pose = chassis.getPose();

    const double headingDegrees = normalizeDegrees(pose.theta + kHeadingOffsetDegrees);
    const int frontDirection = getNearestCardinal(headingDegrees);

    if (useFront) {
        const int frontMeasurementMm = GetFrontDistanceMeasurement();
        if (frontMeasurementMm >= 0) {
            const double distanceInches = mmToInches(static_cast<double>(frontMeasurementMm));
            applyDistanceToPose(pose, frontDirection, distanceInches, kRobotHalfLengthIn);
        }
    }

    if (useLeft) {
        const int leftMeasurementMm = GetLeftDistanceMeasurement();
        if (leftMeasurementMm >= 0) {
            const double distanceInches = mmToInches(static_cast<double>(leftMeasurementMm));
            const int leftDirection = (frontDirection + 1) % 4;
            applyDistanceToPose(pose, leftDirection, distanceInches, kRobotHalfWidthIn);
        }
    }

    if (useRight) {
        const int rightMeasurementMm = GetRightDistanceMeasurement();
        if (rightMeasurementMm >= 0) {
            const double distanceInches = mmToInches(static_cast<double>(rightMeasurementMm));
            const int rightDirection = (frontDirection + 3) % 4;
            applyDistanceToPose(pose, rightDirection, distanceInches, kRobotHalfWidthIn);
        }
    }

    chassis.setPose(pose.x, pose.y, pose.theta);
}