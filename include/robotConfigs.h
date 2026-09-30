#ifndef _PROS_ROBOT_CONFIGS_H_
#define _PROS_ROBOT_CONFIGS_H_
#include "main.h"
#include "lemlib/api.hpp"
#pragma once

//Drivetrain motor groups
extern pros::MotorGroup left_motor_group;
extern pros::MotorGroup right_motor_group;
extern lemlib::Chassis chassis;
extern lemlib::ExpoDriveCurve throttle_curve;
extern lemlib::ExpoDriveCurve steer_curve;

//bot motors
//add motors as needed 

#endif