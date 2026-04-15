#include "goal_type.hpp"
#include "lemlib/pose.hpp"

void colourSort();
void outtakeTask();
void startOuttakeTask();
void setOuttakeOverride(bool override);
void overrideOuttake(int voltage);
void releaseOuttakeOverride();

void StartIntake();
void StartOuttake(bool scoring = false);
void StopIntake();
void StartScoring(GoalType goalType = GoalType::LONG_GOAL, bool slow = false);
void StopScoring();

int GetFrontDistanceMeasurement();
bool IsFrontDistanceConfident();
int GetLeftDistanceMeasurement();
bool IsLeftDistanceConfident();
int GetRightDistanceMeasurement();
bool IsRightDistanceConfident();

void UpdatePose(bool useRight, bool useLeft, bool useFront);

void TestClearParkZone();
void ClearParkZone(lemlib::Pose pose, int initHeading);