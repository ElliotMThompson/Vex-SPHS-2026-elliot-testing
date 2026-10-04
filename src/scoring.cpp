#include "scoring.h"
#include "main.h"

// Scoring mechanism up/down motor
pros::Motor scoringMech(8);

// Scoring flex wheel motor
pros::Motor scoringWheelMotor(9);

int scoringMechSpeed = 80;
// The idea is the take scoringMechFalsePosition and instead of having
// scoring mech motor change, change it idtead.
// and move the scoring mech motor to match it at the snaped values
int scoringMechAngleSnap = 7.5;
int scoringMechAngleChange = 5;
int scoringMechFalsePosition = getScoringMechPosition();
//
int scoringWheelsSpeed = 45;

// false = flex wheels move one direction
// true = flex wheels move the other direction
bool scoringDirection = true;

void scoringSetup() {
    scoringMech.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    resetScoringMechPosition();
}

void scoringMechUp() {
    scoringMechFalsePosition += scoringMechAngleChange;
    int scoringMechFalsePositionSnapped = round(scoringMechFalsePosition / scoringMechAngleSnap) * scoringMechAngleSnap;
    scoringMech.moveAbsolute(scoringMechFalsePositionSnapped, scoringMechSpeed);
}

void scoringMechDown() {
    scoringMechFalsePosition -= scoringMechAngleChange;
    int scoringMechFalsePositionSnapped = round(scoringMechFalsePosition / scoringMechAngleSnap) * scoringMechAngleSnap;
    scoringMech.moveAbsolute(scoringMechFalsePositionSnapped, scoringMechSpeed);
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

// gets the current scoring mechanism position
double getScoringMechPosition() {
    return scoringMech.get_position();
}

// makes the current scoring mechanism position 0
void resetScoringMechPosition() {
    scoringMech.tare_position();
}
