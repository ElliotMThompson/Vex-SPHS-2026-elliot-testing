#include "scoring.h"
#include "main.h"

// Scoring mechanism up/down motor
pros::Motor scoringMech(8);

// Scoring flex wheel motor
pros::Motor scoringWheelMotor(9);

int scoringMechSpeed = 80;
int scoringWheelsSpeed = 45;

// false = flex wheels move one direction
// true = flex wheels move the other direction
bool scoringDirection = true;

void scoringSetup() {
    scoringMech.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void scoringMechUp() {
    scoringMech.move(scoringMechSpeed);
}

void scoringMechDown() {
    scoringMech.move(-scoringMechSpeed);
}

void scoringMechStop() {
    scoringMech.move(0);
}

// Used by Eva's profile
void scoringWheels() {
    if (scoringDirection == false) {
        scoringWheelMotor.move(scoringWheelsSpeed);
    }
    else {
        scoringWheelMotor.move(-scoringWheelsSpeed);
    }
}

// Used by Ansh's profile
void scoringWheelsAccept() {
    scoringWheelMotor.move(-scoringWheelsSpeed);
}

// Used by Ansh's profile
void scoringWheelsReject() {
    scoringWheelMotor.move(scoringWheelsSpeed);
}

void scoringWheelsStop() {
    scoringWheelMotor.move(0);
}

void changeScoringDirection() {
    scoringDirection = !scoringDirection;
}