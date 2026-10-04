#include "scoringMacro.h"
#include "lift.h"
#include "scoring.h"

// Scoring Macro Settings

// Turn entire macro on/off
bool scoringMacroEnabled = true;

// How far the cascade moves before scoring mech starts
double macroLiftStartScoringPosition = 450;

// Final cascade position
double macroLiftTargetPosition = 580;

// Final scoring mechanism position
double macroScoringTargetPosition = 600;
// How long the scoring wheels accept during the scoring macro
int macroScoringWheelsTime = 750;
// How close the motors need to be to count as finished
double macroPositionTolerance = 25;

// Maximum amount of time the scoring macro can run
int macroSafetyTimeout = 3000;


// Scoring Macro State

enum ScoringMacroState {
    MACRO_IDLE,
    MACRO_RAISING_LIFT,
    MACRO_RAISING_BOTH,
    MACRO_RETURNING_LIFT,
    MACRO_RETURNING_SCORING
};

ScoringMacroState scoringMacroState = MACRO_IDLE;

// false = robot is in resting setup
// true = robot is in scoring setup
bool scoringPositionActive = false;
// Remembers when the scoring wheels started running
uint32_t scoringWheelsStartTime = 0;
// Remembers when the scoring macro started running
uint32_t scoringMacroStartTime = 0;
// Remembers if the last macro movement timed out
bool scoringMacroTimedOut = false;
// Remembers which direction the macro was moving before timeout
bool scoringMacroTimedOutGoingUp = false;

// Start Macro

void startScoringMacro() {

    if (scoringMacroEnabled == false) {
        return;
    }

    // Start safety timer
    scoringMacroStartTime = pros::millis();

    // Retry the same movement if the last macro timed out
    if (scoringMacroTimedOut == true) {

        scoringMacroTimedOut = false;

        if (scoringMacroTimedOutGoingUp == true) {

            scoringPositionActive = true;

            // If cascade already cleared the starting position, continue both
            if (getLiftPosition() >= macroLiftStartScoringPosition) {
                scoringWheelsStartTime = pros::millis();
                scoringMacroState = MACRO_RAISING_BOTH;
            }
            else {
                scoringMacroState = MACRO_RAISING_LIFT;
            }
        }

        else {

            scoringPositionActive = false;

            // If cascade is already at the bottom, continue lowering scoring mech
            if (getLiftPosition() <= macroPositionTolerance) {
                scoringMacroState = MACRO_RETURNING_SCORING;
            }
            else {
                scoringMacroState = MACRO_RETURNING_LIFT;
            }
        }

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
        scoringMacroState = MACRO_RETURNING_LIFT;
    }
}


// Update Macro

void updateScoringMacro() {

    // Nothing to do
    if (scoringMacroState == MACRO_IDLE) {
        return;
    }

    // Stop everything if the macro has been running for too long
    if (pros::millis() - scoringMacroStartTime >= macroSafetyTimeout) {

        if (
            scoringMacroState == MACRO_RAISING_LIFT
            ||
            scoringMacroState == MACRO_RAISING_BOTH
        ) {
            scoringMacroTimedOutGoingUp = true;
        }
        else {
            scoringMacroTimedOutGoingUp = false;
        }

        scoringMacroTimedOut = true;

        liftStop();
        scoringMechStop();
        scoringWheelsStop();

        scoringMacroState = MACRO_IDLE;
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

    else if (scoringMacroState == MACRO_RETURNING_LIFT) {

        scoringWheelsStop();

        // Return cascade to 0
        if (getLiftPosition() > macroPositionTolerance) {
            liftDown();
            scoringMechStop();
        }
        else {
            liftStop();
            scoringMechStop();

            scoringMacroState = MACRO_RETURNING_SCORING;
        }
    }

    else if (scoringMacroState == MACRO_RETURNING_SCORING) {

        scoringWheelsStop();
        liftStop();

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