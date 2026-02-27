#include "../include/main.h"
#include "lemlib/api.hpp"

extern pros::Controller master;
extern pros::Controller partner;

extern pros::MotorGroup left_mg;    
extern pros::MotorGroup right_mg;

extern lemlib::Drivetrain drivetrain;

extern pros::Imu imu;

//extern pros:: Rotation horizontalRotation;
//extern pros:: Rotation verticallRotation;

extern lemlib::TrackingWheel horizontalTrackingWheel;

extern lemlib::TrackingWheel verticalTrackingWheel;

extern lemlib::OdomSensors sensors;

extern lemlib::ControllerSettings lateral_controller;

extern lemlib::ControllerSettings angular_controller;

extern lemlib::Chassis chassis;

extern pros::Motor First_Stage_Intake;
extern pros::Motor Second_Stage_Intake;
extern pros::Motor Outtake;

extern pros::adi::Pneumatics Outtake_Lift;
extern pros::adi::Pneumatics Intake_Lift;
extern pros::adi::Pneumatics Matchloader;
extern pros::adi::Pneumatics Wing;

// Distance Sensors
extern pros::Distance Front_Sensor;
extern pros::Distance Right_Sensor;
extern pros::Distance Left_Sensor;