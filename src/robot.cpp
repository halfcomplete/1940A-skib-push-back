#include "robot.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/optical.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

pros::MotorGroup left_mg({-10, 9, -8});    
pros::MotorGroup right_mg({7, -21, 6});

lemlib::Drivetrain drivetrain(&left_mg, &right_mg,
                              13.25, // track width in inches
                              lemlib:: Omniwheel:: NEW_4, // Wheel configuration
                              400, // RPM
                              2 // Drift was 2  0.5
);

pros::Imu imu(2); 

pros::Rotation horizontalRotation(20); 
pros::Rotation verticallRotation(11); 

lemlib::TrackingWheel horizontal_tracking_wheel(&horizontalRotation, lemlib::Omniwheel::NEW_2, -4);
lemlib::TrackingWheel vertical_tracking_wheel(&verticallRotation, lemlib::Omniwheel::NEW_2, 0);


lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);


// lateral PID controller
lemlib::ControllerSettings lateral_controller(10.95, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              125, // derivative gain (kD)
                                              3.6, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(4.549, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              32, // derivative gain (kD)
                                              9, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              1, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);


pros::Motor Conveyer(4, pros::v5::MotorGears::blue);
pros::Motor Top_Roller(5, pros::v5::MotorGears::blue);


pros::adi::Pneumatics Double_Park({22, 'f'}, false);            // Starts retracted, extends when the ADI port is high
pros::adi::Pneumatics Trapdoor({22, 'g'}, false);
pros::adi::Pneumatics Matchloader({22, 'e'}, false);
pros::adi::Pneumatics Wing({22,'h'},false);

pros::Optical SkIbIdI_oPtIcAl(2);