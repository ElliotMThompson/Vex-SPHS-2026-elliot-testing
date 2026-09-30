# include "lift.h"
# include "main.h"
# include "opcontrol.h"
# include "robotConfigs.h"
# include "intake.h"

pros::MotorGroup intake_motors({20, -15}, pros::MotorGears::green);

// speed of the intake
int intakeSpeed = 100;

//lift initializer
void intakeSetup() {
    intake_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void intakeAccept() {
    intake_motors.move(intakeSpeed);
}

void intakeReject() {
    intake_motors.move(-intakeSpeed);
}

void intakeStop() {
    intake_motors.move(0);
}

