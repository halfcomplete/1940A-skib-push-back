#pragma once
#include "auton_type.h"

void auton(AutonType autonToRun);
void run();
void init(int x, int y, int h);
int get_heading(int base);
void Left_7B_1G_MF();
void Left_7B_2G_LF();
void Right_7B_2G();
void Right_7B_1G();
void TestPidTurn();
void TestPidMove();
void raygoon_righ_tauton();
void Right_Solo_AWP();
void MotorMoveTest();

// Outtake task control
void startOuttakeTask();
void setOuttakeOverride(bool override);
void overrideOuttake(int voltage);
void releaseOuttakeOverride();