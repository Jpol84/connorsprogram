/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       polja                                                     */
/*    Created:      8/14/2024, 11:06:49 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <vector>

const std::vector<Vector2> PATH = {tao::Vector2(0, 0), tao::Vector2(10, 10), tao::Vector2(20, 0)};
chassis.follow_path(PATH);

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
controller controller1(primary);
motor left1(PORT8, ratio6_1,true);
motor left2(PORT7, ratio6_1,true );
motor left3top(PORT19, ratio6_1,false);
motor right1(PORT2, ratio6_1,false );
motor right2(PORT3, ratio6_1,false );
motor right3top(PORT1, ratio6_1,true );
motor_group DriveA(left1,left2,left3top);
motor_group DriveB(right1,right2,right3top);
motor intake(PORT20, ratio18_1,false );
pneumatics rod(Brain.ThreeWirePort.A);
motor lift(PORT9, ratio36_1, true);


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  tao:: vector2 point(24,24);
  chassis.turn_to(point);
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  
  // User control code here, inside the loop
  while (1) {
    DriveA.setVelocity(controller1.Axis3.position(), pct);
    DriveB.setVelocity(controller1.Axis2.position(), pct);
    DriveA.spin(forward);
    DriveB.spin(forward);
    if (controller1.ButtonR2.pressing() ) {
      intake.spin(reverse);
    }else if (controller1.ButtonR1.pressing() ) {
      intake.spin(forward);
    }else {intake.stop();}
    intake.setVelocity(100, pct);
    if(controller1.ButtonL1.pressing() ) {
      rod.set(true);
    }else {rod.set(false);}
    if (controller1.ButtonDown.pressing() ) {
      Lift.spin(forward);
    }else if (controller1.ButtonUp.pressing() ) {
      Lift.spin(reverse);
    }else {Lift.stop();}
    Lift.setVelocity(100, pct);
     
    
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }

}
//
// Main will set up the competition functions and callbacks.
//
int main() {
  controller1.ButtonA.pressed([]() {
   rod.set(!rod);
  });

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(20, msec);
  }
}

