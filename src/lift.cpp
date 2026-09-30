 // gives file access to the lift and main files
# include "lift.h"
# include "main.h"
# include "opcontrol.h"
# include "robotConfigs.h"
# include "intake.h"

// two motors for the lift
pros::MotorGroup liftMotors({16, -20}, pros::MotorGears::green);

// speed of the lift
int liftSpeed = 40;

// motors for lift always hold until a button is pressed to change it (idk if needed)
void liftSetup() {
    liftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

// three lift commands
void liftUp() {
    liftMotors.move(liftSpeed);
}

void liftDown() {
    liftMotors.move(-liftSpeed);
}

// stops the lift
void liftStop() {
    liftMotors.move(0);
}