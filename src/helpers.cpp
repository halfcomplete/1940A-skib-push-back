#include "helpers.hpp"
#include "pros/rtos.hpp"
#include "robot.hpp"

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
    // Inside_Roller.brake();
    First_Stage_Intake.move(12000);
    Second_Stage_Intake.brake();
}

void StartOuttake(bool lowGoal)
{
    if (lowGoal)
        First_Stage_Intake.move(-600);
    else
        First_Stage_Intake.move(-100);
    Second_Stage_Intake.move(600);
}

void StopIntake()
{
    // Inside_Roller.brake();
    First_Stage_Intake.brake();
}

void StartScoring(bool auton, bool highGoal)
{
    First_Stage_Intake.move(600);
    if (highGoal)
    {
        Second_Stage_Intake.move(-64);
        First_Stage_Intake.move(100);
    }
    else if (auton)
    {
        Second_Stage_Intake.move(-69);
    }
    else {
        Second_Stage_Intake.move(-600);
    }
}

void StopScoring()
{
    Second_Stage_Intake.brake();
    Outtake_Lift.retract();
}

void GetFrontDistanceMeasurement()
{

}