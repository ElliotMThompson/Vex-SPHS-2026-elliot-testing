#include "scoring.h"
#include "main.h"

// Scoring flex wheel motor
pros::Motor scoringWheels(8);

// Scoring mechanism flip motor
pros::Motor scoringFlipMotor(9);

int scoringSpeed = 100;
int scoringFlipSpeed = 80;

// false = move toward resting position
// true = move toward scoring/perpendicular position
bool scoringDirection = true;

void scoringSetup() {
    scoringFlipMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void scoringAccept() {
    scoringWheels.move(scoringSpeed);
}

void scoringReject() {
    scoringWheels.move(-scoringSpeed);
}

void scoringWheelsStop() {
    scoringWheels.move(0);
}

void scoringFlip() {
    if (scoringDirection == false) {
        scoringFlipMotor.move(scoringFlipSpeed);
    }
    else {
        scoringFlipMotor.move(-scoringFlipSpeed);
    }
}

void scoringFlipStop() {
    scoringFlipMotor.move(0);
}

void changeScoringDirection() {
    scoringDirection = !scoringDirection;
}