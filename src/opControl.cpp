#include "main.h"
#include "opcontrol.h"
#include "robotConfigs.h"
#include "lift.h"
#include "intake.h"
#include "scoring.h"

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain

);

pros::Controller controller(pros::E_CONTROLLER_MASTER);

DriverMode driverMode = PRACTICE; // default driver mode is practice

bool practiceSkills = false; // Allows practice driver to switch between competition and skills driver profiles WITHOUT changing the Current Mode

// ==============================
// Competition driver profile
// ==============================

void competitionDriver() {

        // Drive Controls
        int leftY = controller.get_analog(
            pros::E_CONTROLLER_ANALOG_LEFT_Y
        );

        int rightX = controller.get_analog(
            pros::E_CONTROLLER_ANALOG_RIGHT_X
        );

        chassis.curvature(leftY, rightX);

        // Lift Controls
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
            liftUp();
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
            liftDown();
        }
        else {
            liftStop();
        }

        // Intake Controls
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intakeAccept();
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intakeReject();
        }
        else {
            intakeStop();
        }

        // Scoring Flex Wheel Controls
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            scoringAccept();
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            scoringReject();
        }
        else {
            scoringWheelsStop();
        }

        // Scoring Mechanism Flip
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            changeScoringDirection();
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            scoringFlip();
        }
        else {
            scoringFlipStop();
        }

        // Delay to prevent overloading the controller
        pros::delay(25);

}

// ==============================
// Skills driver profile
// ==============================

void skillsDriver() {

        // Drivetrain Controls
        int leftY = controller.get_analog(
            pros::E_CONTROLLER_ANALOG_LEFT_Y
        );

        int rightX = controller.get_analog(
            pros::E_CONTROLLER_ANALOG_RIGHT_X
        );

        chassis.curvature(leftY, rightX);

        // Lift Controls
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            liftUp();
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            liftDown();
        }
        else {
            liftStop();
        }

        //intake Controls
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            intakeAccept();
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intakeReject();
        }
        else {
            intakeStop();
        }

        // Scoring Flex Wheel Controls
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
            scoringAccept();
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
            scoringReject();
        }
        else {
            scoringWheelsStop();
        }

        // Scoring Mechanism Flip
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            changeScoringDirection();
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            scoringFlip();
        }
        else {
            scoringFlipStop();
        }

        // Delay to prevent overloading the controller
        pros::delay(25);

}

// ==============================
// Practice driver profile
// ==============================

void practiceDriver() {

    // X+A = Competition Driver 
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)
     && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {

        practiceSkills = false;
        
        controller.rumble(".-");
        pros::delay(500);
    }

    // X+B = Skills Driver
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) 
    && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {

        practiceSkills = true;

        controller.rumble("-...");
        pros::delay(500);
    }

    // Run Whichever driver profile is selected
    if (practiceSkills == false) {
        competitionDriver();
    } 
    else {
        skillsDriver();
    } 
}