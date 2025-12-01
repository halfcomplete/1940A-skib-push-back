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
    Conveyer.move(600);
    Top_Roller.brake();
}

void StartOuttake()
{
    Conveyer.move(-600);
    Top_Roller.move(600);
}

void StopIntake()
{
    // Inside_Roller.brake();
    Top_Roller.brake();
    Conveyer.brake();
}

void StartScoring()
{
    Conveyer.move(600);
    Top_Roller.move(-600);
}