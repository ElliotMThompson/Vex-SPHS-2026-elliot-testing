#include "main.h"
#include "lemlib/api.hpp"
#pragma once

void intakeSetup(); // holds position when stopped
void intakeAccept(); // accepts the pin/+cup
void intakeReject(); // rejects the pin/+cup
void intakeStop(); // stops the intake