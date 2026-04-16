#include "robot.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/optical.hpp"

// Outtake control - when true, other code is controlling outtake
bool outtakeOverride = false;

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

pros::MotorGroup left_mg({-13, -12, -11});    
pros::MotorGroup right_mg({14, 15, 16});

lemlib::Drivetrain drivetrain(&left_mg, &right_mg,
                              14, // track width in inches
                              lemlib:: Omniwheel:: NEW_325, // Wheel configuration
                              450, // RPM
                              2 // Drift was 2  0.5
);

pros::Imu imu(2); 

pros::Rotation verticalRotation(1); 

lemlib::TrackingWheel vertical_tracking_wheel(&verticalRotation, lemlib::Omniwheel::NEW_2, 0);


lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);


// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              55, // derivative gain (kD)
                                              0.9, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              300, // large error range timeout, in milliseconds
                                              10 // maximum acceleration (slew) - smooths out sudden lurches
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2.3, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              15, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              200, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

pros::Motor First_Stage_Intake(18, pros::v5::MotorGears::blue);
pros::Motor Second_Stage_Intake(-17, pros::v5::MotorGears::green);
pros::Motor Outtake(-10, pros::v5::MotorGears::green);

pros::adi::Pneumatics Outtake_Lift({22, 'f'}, false);            // Starts retracted, extends when the ADI port is high
pros::adi::Pneumatics Intake_Lift({22, 'g'}, false);
pros::adi::Pneumatics Matchloader({22, 'h'}, false);
pros::adi::Pneumatics Wing({22, 'e'}, false);

// Distance Sensors
pros::Distance Front_Sensor(5);
pros::Distance Right_Sensor(4);
pros::Distance Left_Sensor(21);