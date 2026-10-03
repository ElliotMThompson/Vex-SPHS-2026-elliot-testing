#pragma once

void scoringSetup();

void scoringMechUp();
void scoringMechDown();
void scoringMechStop();

void scoringWheels();
void scoringWheelsAccept();
void scoringWheelsReject();
void scoringWheelsStop();

void changeScoringDirection();

// scoring mechanism position commands for scoring macro
double getScoringMechPosition();
void resetScoringMechPosition();