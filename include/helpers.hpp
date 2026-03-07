#include "goal_type.hpp"

void colourSort();
void StartIntake();
void StartOuttake(bool scoring = false);
void StopIntake();
void StartScoring(GoalType goalType = GoalType::LONG_GOAL);
void StopScoring();

int GetFrontDistanceMeasurement();
bool IsFrontDistanceConfident();
int GetLeftDistanceMeasurement();
bool IsLeftDistanceConfident();
int GetRightDistanceMeasurement();
bool IsRightDistanceConfident();