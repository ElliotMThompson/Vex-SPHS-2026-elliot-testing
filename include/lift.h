#include "main.h"
#include "lemlib/api.hpp"
#pragma once

// four lift commands
void liftSetup(); // holds position when stopped
void liftUp(); // move up
void liftDown(); // move down
void liftStop(); // lift brakes and holds position

// lift position commands for scoring macro
double getLiftPosition();
void resetLiftPosition();