#include "helpers.hpp"
#include "pros/rtos.hpp"
#include "robot.hpp"

void colourSort() {
    pros::Task sortTask([&]()->void {
        while (true) {
            if (SkIbIdI_oPtIcAl.get_hue() > 90 && SkIbIdI_oPtIcAl.get_proximity() > 128) {
                Trapdoor.retract();
                pros::delay(50);
                Trapdoor.extend();
            }

            pros::delay(10);
        }
    });
}


void StartIntake()
{
    // Inside_Roller.brake();
    Conveyer.move(12000);
    Top_Roller.brake();
}

void StartOuttake(bool lowGoal)
{
    if (lowGoal)
        Conveyer.move(-600);
    else
        Conveyer.move(-100);
    Top_Roller.move(600);
}

void StopIntake()
{
    // Inside_Roller.brake();
    Conveyer.brake();
}

void StartScoring(bool auton, bool highGoal)
{
    Conveyer.move(600);
    if (highGoal)
    {
        Trapdoor.extend();
        Top_Roller.move(-76);
        Conveyer.move(100);
    }
    else if (auton)
    {
        Top_Roller.move(-74);
    }
    else {
        Top_Roller.move(-600);
    }
}

void StopScoring()
{
    Top_Roller.brake();
    Trapdoor.retract();
}