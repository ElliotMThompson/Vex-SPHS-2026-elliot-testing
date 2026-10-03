#include "scoringMacro.h"
#include "lift.h"
#include "scoring.h"

// Scoring Macro Settings

// Turn entire macro on/off
bool scoringMacroEnabled = true;

// How far the cascade moves before scoring mech starts
double macroLiftStartScoringPosition = 50;

// Final cascade position
double macroLiftTargetPosition = 150;

// Final scoring mechanism position
double macroScoringTargetPosition = 100;
// How long the scoring wheels accept during the scoring macro
int macroScoringWheelsTime = 750;
// How close the motors need to be to count as finished
double macroPositionTolerance = 5;


// Scoring Macro State

enum ScoringMacroState {
    MACRO_IDLE,
    MACRO_RAISING_LIFT,
    MACRO_RAISING_BOTH,
    MACRO_RETURNING
};

ScoringMacroState scoringMacroState = MACRO_IDLE;

// false = robot is in resting setup
// true = robot is in scoring setup
bool scoringPositionActive = false;
// Remembers when the scoring wheels started running
uint32_t scoringWheelsStartTime = 0;

// Start Macro

void startScoringMacro() {

    if (scoringMacroEnabled == false) {
        return;
    }

    // If currently resting, move to scoring position
    if (scoringPositionActive == false) {

        scoringPositionActive = true;
        scoringMacroState = MACRO_RAISING_LIFT;
    }

    // If currently in scoring position, return everything
    else {

        scoringPositionActive = false;
        scoringMacroState = MACRO_RETURNING;
    }
}


// Update Macro

void updateScoringMacro() {

    // Nothing to do
    if (scoringMacroState == MACRO_IDLE) {
        return;
    }


    // Step 1: Raise Cascade

    if (scoringMacroState == MACRO_RAISING_LIFT) {

        liftUp();
        scoringMechStop();

        // Cascade has cleared enough for scoring mech to start
        if (getLiftPosition() >= macroLiftStartScoringPosition) {
            scoringWheelsStartTime = pros::millis();
            scoringMacroState = MACRO_RAISING_BOTH;
        }
    }


    // Step 2 Raise Both

    else if (scoringMacroState == MACRO_RAISING_BOTH) {

        // Keep moving cascade until target
        if (getLiftPosition() < macroLiftTargetPosition) {
            liftUp();
        }
        else {
            liftStop();
        }

        // Move scoring mechanism until target
        if (getScoringMechPosition() < macroScoringTargetPosition) {
            scoringMechUp();
        }
        else {
            scoringMechStop();
        }

        // Keep scoring wheels accepting for the adjustable amount of time
        if (pros::millis() - scoringWheelsStartTime < macroScoringWheelsTime) {
            scoringWheelsAccept();
        }
        else {
            scoringWheelsStop();
        }

        // Both reached their targets
        if (
            getLiftPosition() >=
                macroLiftTargetPosition - macroPositionTolerance
            &&
            getScoringMechPosition() >=
                macroScoringTargetPosition - macroPositionTolerance
        ) {
            liftStop();
            scoringMechStop();
            scoringWheelsStop();

            scoringMacroState = MACRO_IDLE;
        }
    }


    // Return Everything to Rest

    else if (scoringMacroState == MACRO_RETURNING) {

        scoringWheelsStop();

        // Return cascade to 0
        if (getLiftPosition() > macroPositionTolerance) {
            liftDown();
        }
        else {
            liftStop();
        }

        // Return scoring mechanism to 0
        if (getScoringMechPosition() > macroPositionTolerance) {
            scoringMechDown();
        }
        else {
            scoringMechStop();
        }

        // Both are back at resting position
        if (
            getLiftPosition() <= macroPositionTolerance
            &&
            getScoringMechPosition() <= macroPositionTolerance
        ) {
            liftStop();
            scoringMechStop();

            scoringMacroState = MACRO_IDLE;
        }
    }
}


// Macro Statuses

bool isScoringMacroRunning() {
    return scoringMacroState != MACRO_IDLE;
}

bool isScoringPositionActive() {
    return scoringPositionActive;
}