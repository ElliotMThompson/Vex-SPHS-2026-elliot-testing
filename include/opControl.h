#ifndef _PROS_OP_CONTROL_H_
#define _PROS_OP_CONTROL_H_
#include "main.h"
#include "lemlib/api.hpp"
#pragma once

void driverControl();

// Driver profiles
void competitionDriver();
void skillsDriver();
void practiceDriver();

extern pros::Controller controller;

enum DriverMode {
    COMPETITION,
    SKILLS,
    PRACTICE
};

extern DriverMode driverMode;

#endif