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
            Outtake.move_velocity(-50);
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
            TestPidMove(72);
            break;
        case AutonType::PID_TURN_TEST_90:
            TestPidTurn(90);
            break;
        case AutonType::PID_TURN_TEST_180:
            TestPidTurn(180);
            break;
        case AutonType::L_7B_1G_MF:
            Left_7B_1G_MF();
            break;
        case AutonType::L_7B_2G_LF:
            Left_7B_2G_LF();
            break;
        case AutonType::R_7B_2G:
            Right_7B_2G();
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

void Left_7B_1G_MF()
{
    startOuttakeTask();
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-44.518, 13.547, 90);
    Wing.extend();

    // Move to three blocks on the left
    StartIntake();
    chassis.moveToPoint(-26.066, 19.266, 3000, {.minSpeed=80, .earlyExitRange=13});
    chassis.moveToPoint(-16.066, 25.266, 3000, {.maxSpeed=43});
    chassis.waitUntilDone();

    // Move to two blocks under the long goal
    chassis.turnToHeading(55, 1000, {.minSpeed=60, .earlyExitRange=1});
    chassis.waitUntilDone();
    chassis.moveToPoint(-6, 30, 1100);
    chassis.turnToHeading(21, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-5.2, 40.5, 1100, {.maxSpeed=60});
    pros::delay(320);
    Matchloader.extend();
    pros::delay(450);
    chassis.moveToPoint(-16.066, 28, 2000, {.forwards=false, .minSpeed=80});

    // Move to right long goal
    chassis.turnToHeading(330, 700);
    chassis.waitUntilDone();
    Matchloader.retract();

    chassis.moveToPoint(-36, 49.28, 1000, {.maxSpeed=90});
    chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(-19, 49.28, 630, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-16, 49.28, 1000, {.forwards=false, .maxSpeed=60});
    StartScoring();
    chassis.setPose(-21.33, 49.28, chassis.getPose().theta);
    pros::delay(1600);

    // Move to matchloader
    Matchloader.extend();
    StartIntake();
    chassis.moveToPoint(-46, 49, 1700, {.minSpeed=65, .earlyExitRange=9});
    chassis.moveToPoint(-76, 49, 1100, {.maxSpeed=30});

    // Move to right long goal
    chassis.moveToPose(-19, 49.28, 270, 3000, {.forwards=false, .minSpeed=60});
    chassis.waitUntilDone();
    Matchloader.retract();
    StartScoring();
    pros::delay(1000);
    chassis.moveToPoint(-30, 49.28, 2000, {.maxSpeed=110});
    chassis.moveToPoint(-16, 49.28, 1000, {.forwards=false, .minSpeed=90 });
}


void Left_7B_2G_LF()
{
    startOuttakeTask();
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-48.482, 17.8, 0);

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
    chassis.moveToPoint(-25.5, 28, 2000, {.minSpeed=90, .earlyExitRange=9.5});
    chassis.waitUntilDone();
    Matchloader.extend();
    chassis.moveToPoint(-22, 24, 3000, {.maxSpeed=50});
    chassis.waitUntilDone();

    // Turn around and score in the middle high goal
    chassis.turnToHeading(315, 750);
    
    chassis.moveToPoint(-2, 6, 600, {.forwards=false, .maxSpeed=60});
    
    pros::delay(300);
    StartOuttake();
    pros::delay(200);
    StopIntake();
    Matchloader.retract();
    StartScoring(GoalType::HIGH_GOAL);
    pros::delay(1200);
    StopScoring();

    // Move to the long goal and wing
    Wing.extend();
    chassis.moveToPoint(-37, 56, 2000, {.maxSpeed=110});
    chassis.turnToHeading(225, 1000, {.maxSpeed=80});
    chassis.moveToPoint(-28, 62, 1000, {.forwards=false });
    chassis.turnToHeading(270, 600);
    chassis.moveToPoint(-19, 62, 1000, {.forwards=false, .minSpeed=50});
}

void Right_7B_2G()
{
    startOuttakeTask();
    right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-48.482, -17.8, 180);

    // Move to matchloader
    chassis.moveToPoint(-48.482, -50.7, 1500, {.maxSpeed=90});
    StartIntake();
    chassis.turnToHeading(270, 1000, {.maxSpeed=80});
    Matchloader.extend();
    chassis.moveToPoint(-65, -50.7, 1100, {.maxSpeed=60});
    
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
    
    chassis.moveToPoint(-4, -7, 600, {.maxSpeed=60});
    chassis.waitUntilDone();
    StartOuttake();
    pros::delay(1600);
    Matchloader.retract();
    StopIntake();

    // Move to the long goal and wing
    Wing.extend();
    chassis.moveToPoint(-37, -39, 2000, {.forwards=false, .maxSpeed=110});
    chassis.turnToHeading(270, 1000, {.maxSpeed=80});
    chassis.moveToPoint(-19, -39, 1000, {.forwards=false, .minSpeed=50});
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
    chassis.moveToPoint(-48.599, firstY, 1500);
    
    // Move to matchloader
    chassis.turnToHeading(270, 700, {.minSpeed=60});
    StartIntake();
    chassis.moveToPoint(-75, firstY, 1600, {.minSpeed=150});
    chassis.waitUntilDone();

    // Move to right long goal
    chassis.moveToPose(-25, firstY - 1.2, 270, 1000, {.forwards=false, .minSpeed=85});
    chassis.waitUntilDone();
    StartScoring(GoalType::LONG_GOAL);
    Matchloader.retract();
    pros::delay(1700);
    chassis.setPose(-30.9, -51.1, 270);
    chassis.waitUntilDone();
    chassis.moveToPoint(-40, -50.6, 1000, {.minSpeed=80, .earlyExitRange=1});
    chassis.turnToPoint(-27, -27, 1000, {.minSpeed=90});
    chassis.waitUntilDone();
    StartIntake();


    // Move to 3 blocks on the right
    chassis.moveToPoint(-24, -27, 1500, {.minSpeed=90, .earlyExitRange=21.7});
    chassis.moveToPoint(-22, -26, 3000, {.maxSpeed=30});
    chassis.waitUntilDone();
    
    // Move to 3 blocks on the left
    StartIntake();
    chassis.turnToPoint(-24, 4, 1000, {.minSpeed=80, .earlyExitRange=2});
    chassis.moveToPoint(-24, 4, 1000, {.minSpeed=80, .earlyExitRange=3.4}); 
    chassis.moveToPoint(-24, 22, 1800, {.maxSpeed=30});
    chassis.waitUntilDone();

    // Score in high goal
    chassis.moveToPoint(-12.2, 12.8, 1500, {.forwards=false, .maxSpeed=50});
    chassis.waitUntilDone();
    chassis.turnToHeading(315, 1000, {.maxSpeed=60});
    chassis.waitUntilDone();
    StartScoring(GoalType::HIGH_GOAL);
    pros::delay(700);
    StopScoring();

    // Move to matchloader on the left
    float y = 41;

    // Score in left long goal
    chassis.turnToPoint(-38, y, 1000);
    chassis.moveToPose(-38, y, 270, 1000, {.minSpeed=70});
    chassis.moveToPose(-30.436, y, 270, 930, {.forwards=false, .minSpeed=80});
    pros::delay(50);
    StartScoring(GoalType::LONG_GOAL);
}
