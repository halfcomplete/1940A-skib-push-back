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
#include "pid_tests.h"

void outtakeTask() {
    while (true) {
        if (!outtakeOverride) {
            Outtake.move_velocity(-30);
        }
        pros::delay(20);
    }
}

void startOuttakeTask() {
    pros::Task outtake_task(outtakeTask, "Outtake Task");
}

void setOuttakeOverride(bool override) {
    outtakeOverride = override;
}

void overrideOuttake(int voltage) {
    outtakeOverride = true;
    Outtake.move_velocity(voltage);
}

void releaseOuttakeOverride() {
    outtakeOverride = false;
}

void auton(AutonType autonToRun) {
    switch (autonToRun) {
        case AutonType::PID_MOVE_TEST_24:
            // TestPidMove(48);
            chassis.setPose(-48.482, 17.8, 0);
            break;
        case AutonType::PID_MOVE_TEST_48:
            TestPidMove(24);
            break;
        case AutonType::PID_TURN_TEST_90:
            TestPidTurn(90);
            break;
        case AutonType::PID_TURN_TEST_180:
            TestPidTurn(180);
            break;
        case AutonType::L_9B_1G:
            Left_9B_1G();
            break;
        case AutonType::L_7B_2G:
            Left_7B_2G();
            break;
        case AutonType::R_7B_2G:
            Right_7B_2G();
            break;
        case AutonType::R_9B_1G:
            Right_9B_1G();
            break;
        case AutonType::L_4B_1G:
            throw std::runtime_error("L_4B_1G Auton not implemented");
            break;
        case AutonType::R_4B_1G:
            throw std::runtime_error("R_4B_1G Auton not implemented");
            break;
        case AutonType::SOLO_AWP:
            Right_Solo_AWP();
            break;
        case AutonType::SKILLS:
            skills_auton();
            break;
    }
};

void Left_7B_2G_MF()
{
    startOuttakeTask();
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-46.818, 13.547, 90);

    // Move to three blocks on the left
    StartIntake();
    chassis.moveToPoint(-27, 21, 4000, {.minSpeed=60, .earlyExitRange=1});
    chassis.waitUntilDone();
    Matchloader.extend();
    chassis.moveToPoint(-14, 25, 3000, {.maxSpeed=30});
    chassis.waitUntilDone();
    chassis.moveToPoint(-20.5, 20.5, 2000, {.forwards=false, .maxSpeed=45});


    // Score in high goal
    chassis.turnToHeading(315, 2000);
    chassis.waitUntilDone();
    Matchloader.retract();
    chassis.moveToPoint(-7, 8.3, 1000, {.forwards=false, .maxSpeed=40});
    chassis.waitUntilDone();
    StartScoring(GoalType::HIGH_GOAL);
    pros::delay(2000);
    StopScoring();

    return;

    // Move to matchloader
    chassis.moveToPoint(-47, 48, 1500, {.maxSpeed=60});
    StartIntake();
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToHeading(270, 1000);
    Matchloader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(-73, 48, 1700, {.maxSpeed=45});

    // Score in long goal
    Wing.extend();
    chassis.moveToPoint(-30, 48, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring(GoalType::LONG_GOAL);
    pros::delay(1200);
    chassis.moveToPoint(-43, 52, 1000);
    chassis.turnToHeading(225, 1000);
    chassis.moveToPose(-24.7, 52, 270, 1000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-14, 52, 1000, {.forwards=false});
    pros::delay(80);
    Wing.retract();
}

void Left_9B_1G()
{
    startOuttakeTask();
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-44.518, 13.547, 90);
    Wing.extend();

    // Move to three blocks on the left
    StartIntake();
    chassis.moveToPoint(-26.066, 19.266, 3000, {.minSpeed=80, .earlyExitRange=13});
    chassis.moveToPoint(-16.066, 25.266, 3000, {.maxSpeed=53});
    pros::delay(800);
    Matchloader.extend();
    
    chassis.waitUntilDone();
    Matchloader.retract();

    // Move to two blocks under the long goal
    chassis.turnToHeading(55, 1000, {.minSpeed=60, .earlyExitRange=1});
    chassis.waitUntilDone();
    chassis.moveToPoint(-3.7, 39, 1100, {.maxSpeed=60});
    chassis.turnToHeading(19, 1000);
    pros::delay(400);
    Matchloader.extend();
    
    chassis.moveToPoint(-13, 33, 1000, {.forwards=false, .minSpeed=70});
    pros::delay(200);
    Matchloader.retract();
    chassis.moveToPoint(-5, 40.4, 1100, {.maxSpeed=50});
    chassis.moveToPoint(-16.066, 28, 2000, {.forwards=false, .minSpeed=80});

    // Move to right long goal
    chassis.turnToHeading(330, 700);
    chassis.waitUntilDone();
    Matchloader.retract();
    float y = 49.5;
    chassis.moveToPoint(-36, y, 1000, {.maxSpeed=90});
    chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(-19, y, 630, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-16, y, 1000, {.forwards=false, .maxSpeed=60});
    StartScoring();
    // chassis.setPose(-21.33, y, chassis.getPose().theta);
    pros::delay(1600);

    // Move to matchloader
    Matchloader.extend();
    StartIntake();
    chassis.moveToPoint(-46, y, 1700, {.minSpeed=65, .earlyExitRange=5});
    chassis.moveToPoint(-76, y, 1000, {.maxSpeed=60});

    // Move to right long goal
    chassis.moveToPose(-19, y, 270, 3000, {.forwards=false, .minSpeed=60});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring();
    pros::delay(1400);
    StopScoring();
    chassis.moveToPoint(-30, y-1, 2000, {.maxSpeed=110});
    chassis.moveToPoint(-16, y-1, 1000, {.forwards=false, .minSpeed=90 });
}


void Left_7B_2G()
{
    startOuttakeTask();
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-48.482, 17.8, 0);

    Wing.extend();

    // Move to matchloader
    chassis.moveToPoint(-48.482, 50.7, 1500, {.maxSpeed=90});
    StartIntake();
    chassis.turnToHeading(270, 1000, {.maxSpeed=80});
    Matchloader.extend();
    chassis.moveToPoint(-65, 50.7, 1100, {.maxSpeed=60});
    
    // Move to long goal and score
    chassis.moveToPoint(-30, 50.5, 1000, {.forwards=false, .minSpeed=90, .earlyExitRange=7});
    chassis.moveToPoint(-26, 50.5, 1000, {.forwards=false, .maxSpeed=50});
    chassis.waitUntilDone();
    StartScoring(GoalType::LONG_GOAL);
    Matchloader.retract();
    pros::delay(1000);
    StopScoring();

    // Move to three blocks
    chassis.moveToPoint(-46, 48, 1000);
    chassis.waitUntilDone();
    StartIntake();
    chassis.turnToHeading(135, 800, {.maxSpeed=90});
    chassis.moveToPoint(-25.5, 28, 2000, {.minSpeed=90, .earlyExitRange=10.5});
    chassis.waitUntilDone();
    Matchloader.extend();
    chassis.moveToPoint(-22, 24, 3000, {.maxSpeed=40});
    chassis.waitUntilDone();

    // Turn around and score in the middle high goal
    chassis.turnToHeading(315, 750);
    
    chassis.moveToPoint(-1, 3, 600, {.forwards=false, .maxSpeed=60});
    
    pros::delay(490);
    StartOuttake();
    overrideOuttake(90);
    pros::delay(170);
    StopIntake();
    Matchloader.retract();
    StartScoring(GoalType::HIGH_GOAL);
    pros::delay(1450);
    StopScoring();

    // Move to the long goal and wing
    Wing.extend();
    chassis.moveToPoint(-37, 56, 2000, {.maxSpeed=110});
    chassis.turnToHeading(225, 1000, {.maxSpeed=80});
    chassis.moveToPoint(-28, 60, 1000, {.forwards=false });
    chassis.turnToHeading(270, 600);
    chassis.moveToPoint(-10, 60, 1000, {.forwards=false, .minSpeed=80});
}
// void Right_7B_2G()
// {
//     startOuttakeTask();
//     right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     chassis.setPose(-48.482, -17.8, 180);

//     Wing.extend();

//     // Move to matchloader
//     chassis.moveToPoint(-48.482, -48.7, 1500, {.maxSpeed=90});
//     StartIntake();
//     chassis.turnToHeading(270, 1000, {.maxSpeed=80});
//     Matchloader.extend();
//     chassis.moveToPoint(-65, -48.7, 2500, {.maxSpeed=60});
    
//     // Move to long goal and score
//     chassis.moveToPoint(-30, -50.5, 1000, {.forwards=false, .minSpeed=90, .earlyExitRange=7});
//     chassis.moveToPoint(-26, -50.5, 1000, {.forwards=false, .maxSpeed=50});
//     chassis.waitUntilDone();
//     StartScoring(GoalType::LONG_GOAL);
//     Matchloader.retract();
//     pros::delay(800);
//     StopScoring();

//     // Move to three blocks
//     chassis.moveToPoint(-46, -48, 1000);
//     pros::delay(300);
//     StartScoring();
//     chassis.waitUntilDone();
//     chassis.turnToHeading(45, 800, {.maxSpeed=90});
//     chassis.moveToPoint(-25.5, -28, 2000, {.minSpeed=90, .earlyExitRange=9.5});
//     chassis.waitUntilDone();
//     StopScoring();
//     Matchloader.extend();
//     chassis.moveToPoint(-22, -24, 3000, {.maxSpeed=50});
//     chassis.waitUntilDone();
//     Matchloader.retract();
    
//     chassis.moveToPoint(-5.6, -7.1, 600, {.maxSpeed=60});
//     chassis.waitUntilDone();
//     StartOuttake(true);
//     overrideOuttake(200);
//     pros::delay(1600);
//     Matchloader.retract();
//     StopIntake();
//     StopScoring();

//     // Move to the long goal and wing
//     Wing.extend();
//     chassis.moveToPoint(-37, -36.7, 2000, {.forwards=false, .maxSpeed=110});
//     chassis.turnToHeading(275, 1000, {.maxSpeed=80});
//     chassis.moveToPoint(-10, -36.7, 1000, {.forwards=false, .minSpeed=50});
// }
void Right_7B_2G()
{
    startOuttakeTask();
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-48.482, -17.8, 180);

    Wing.extend();

    // Move to matchloader
    chassis.moveToPoint(-48.482, -48.7, 1500, {.maxSpeed=90});
    StartIntake();
    chassis.turnToHeading(270, 1000, {.maxSpeed=80});
    Matchloader.extend();
    chassis.moveToPoint(-65, -48.7, 1000, {.maxSpeed=60});
    
    // Move to long goal and score
    chassis.moveToPoint(-30, -50.5, 1000, {.forwards=false, .minSpeed=90, .earlyExitRange=7});
    chassis.moveToPoint(-26, -50.5, 1000, {.forwards=false, .maxSpeed=50});
    chassis.waitUntilDone();
    StartScoring(GoalType::LONG_GOAL);
    Matchloader.retract();
    pros::delay(1000);
    StopScoring();

    // Move to three blocks
    chassis.moveToPoint(-46, -48, 1000);
    chassis.waitUntilDone();
    StartIntake();
    chassis.turnToHeading(45, 800, {.maxSpeed=90});
    chassis.moveToPoint(-25.5, -28, 2000, {.minSpeed=90, .earlyExitRange=9.5});
    chassis.waitUntilDone();
    Matchloader.extend();
    chassis.moveToPoint(-22, -24, 3000, {.maxSpeed=50});
    chassis.waitUntilDone();
    Matchloader.retract();
    
    chassis.moveToPoint(-5, -6, 600, {.maxSpeed=60});
    chassis.waitUntilDone();
    StartScoring(GoalType::LOW_GOAL);
    overrideOuttake(200);
    pros::delay(1600);
    Matchloader.retract();
    StopIntake();
    StopScoring();

    // Move to the long goal and wing
    Wing.extend();
    chassis.moveToPoint(-37, -35.7, 2000, {.forwards=false, .maxSpeed=110});
    chassis.turnToHeading(275, 1000, {.maxSpeed=80});
    chassis.moveToPoint(-10, -35.7, 1000, {.forwards=false, .minSpeed=50});
}

void Right_9B_1G()
{
    startOuttakeTask();
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-44.518, -13.547, 90);
    Wing.extend();

    // Move to three blocks on the left
    StartIntake();
    chassis.moveToPoint(-26.066, -19.266, 3000, {.minSpeed=80, .earlyExitRange=15});
    chassis.moveToPoint(-16.066, -25.266, 3000, {.maxSpeed=43});
    chassis.waitUntilDone();

    // Move to two blocks under the long goal
    chassis.turnToHeading( 125, 1000, {.minSpeed=60, .earlyExitRange=1});
    chassis.waitUntilDone();
    chassis.moveToPoint(-6, -30, 1100);
    chassis.turnToHeading(159, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-4.5, -39, 1100, {.maxSpeed=60, .minSpeed=5, .earlyExitRange=1});
    pros::delay(320);
    Matchloader.extend();
    pros::delay(450);
    chassis.moveToPoint(-16.066, -22, 2000, {.forwards=false, .minSpeed=80});

    // Move to right long goal
    Wing.retract();
    chassis.turnToHeading(150, 700);
    chassis.waitUntilDone();
    Matchloader.retract();
    chassis.moveToPoint(-42, -48.28, 3500, {.maxSpeed=60});
    chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(-19, -51.5, 630, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-13, -51.5, 1000, {.forwards=false, .maxSpeed=60});
    StartScoring();
    chassis.setPose(-21.33, -51.5, chassis.getPose().theta);
    pros::delay(1600);

    // Move to matchloader
    Matchloader.extend();
    StartIntake();
    chassis.moveToPoint(-46, -51, 1700, {.minSpeed=65, .earlyExitRange=7});
    chassis.moveToPoint(-81, -51, 1200, {.maxSpeed=30});

    // Move to right long goal
    chassis.moveToPose(-19, -51.5, 270, 3000, {.forwards=false, .minSpeed=60});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring();
    pros::delay(1000);
    StopScoring();
    chassis.moveToPoint(-30, -51.5, 2000, {.maxSpeed=110});
    chassis.moveToPoint(-16, -51.5, 1000, {.forwards=false, .minSpeed=90 });
}




void TestPidTurn()
{
    chassis.setPose(0, 0, 0);
    pros::delay(100);
    chassis.turnToHeading(90, 10000);
}

void TestPidMove()
{
    chassis.setPose(0, 0, 0);
    pros::delay(100);
    chassis.moveToPose(0, 48, 0, 10000);
}

void raygoon_righ_tauton() {
    chassis.setPose(-48.599, -15.328, 180);
    StartIntake();
    Matchloader.extend();
    chassis.moveToPoint(-48.599, -49, 1500);
    chassis.waitUntilDone();

    // Move to matchloader
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(-69, -47, 1400);
    chassis.waitUntilDone();
    pros::delay(800);

    // Move to right long goal
    chassis.moveToPose(-30.614, -50, 270, 1000, {.forwards=false, .earlyExitRange=1});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring(GoalType::LONG_GOAL);
    pros::delay(1000);
    chassis.moveToPoint(-44, -49, 1000);
    chassis.waitUntilDone();
    StartIntake();


    // Move to 3 blocks on the right
    chassis.moveToPoint(-24, -27, 1500);
    chassis.waitUntilDone();
}

void MotorMoveTest() {
    First_Stage_Intake.move(700);
}


void Right_Solo_AWP() {
    chassis.setPose(-48.599, -15.328, 180);
    StartIntake();
    Matchloader.extend();
    float firstY = -48.8;
    chassis.moveToPoint(-48.599, firstY, 1500,  {.minSpeed=2, .earlyExitRange=1});
    
    // Move to matchloader
    chassis.turnToHeading(270, 700, {.minSpeed=2, .earlyExitRange=1});
    StartIntake();
    chassis.moveToPoint(-75, firstY - 1.7, 900, {.minSpeed=100});
    chassis.waitUntilDone();

    // Move to right long goal
    chassis.moveToPose(-25, firstY, 270, 1000, {.forwards=false, .minSpeed=85, .earlyExitRange=1});
    chassis.waitUntilDone();
    StartScoring(GoalType::LONG_GOAL);
    Matchloader.retract();
    pros::delay(900);
    StopScoring();
    chassis.waitUntilDone();
    chassis.swingToPoint(-22, -26, lemlib::DriveSide::RIGHT, 2000, {.minSpeed=30, .earlyExitRange=1});
    chassis.waitUntilDone();
    StartIntake();

    float bx = -16;
    // Move to 3 blocks on the right
    chassis.moveToPoint(bx, -29, 3000, {.minSpeed=55, .earlyExitRange=1});
    pros::delay(400);
    Matchloader.extend();
    chassis.waitUntilDone();
    pros::delay(100);
    Matchloader.retract();
    chassis.turnToHeading(0, 1000, {.minSpeed=2, .earlyExitRange=1});

    
    // Move to 3 blocks on the left
    StartIntake();    
    chassis.moveToPoint(-bx, 18, 2300, {.minSpeed=55,  .earlyExitRange=1});
    pros::delay(700);
    Matchloader.extend();
    chassis.waitUntilDone();
    pros::delay(100);
    float y = 46.5;

    // Move to left long goal and score
    chassis.turnToHeading(290, 1000);
    chassis.moveToPose(-35, y, 270, 1000, {.lead=0.3});
    chassis.moveToPoint(-25, y, 1000, {.forwards=false, .minSpeed=90, .earlyExitRange=5});
    chassis.moveToPoint(-20, y, 300, {.forwards=false, .maxSpeed=50});
    chassis.waitUntilDone();
    StartScoring(GoalType::LONG_GOAL);
    pros::delay(1000);
    StopScoring();

    // Move to matchloader on the left
    chassis.moveToPoint(-58, y+1, 1000, {.minSpeed=100, .earlyExitRange=5});
    chassis.moveToPoint(-75, y+1, 650, {.maxSpeed=60});

    // Score in high goal
    chassis.moveToPoint(-45, y, 1000, {.forwards=false, .minSpeed=4, .earlyExitRange=1});
    chassis.turnToHeading(315, 1000, {.minSpeed=3, .earlyExitRange=1});
    chassis.moveToPoint(-4, 2, 1000, {.forwards=false, .minSpeed=40, .earlyExitRange=1});
    StartScoring(GoalType::HIGH_GOAL);
}
