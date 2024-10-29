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



using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
controller pen(primary);
motor left1(PORT11, ratio6_1,true);
motor left2(PORT12, ratio6_1,true );
motor left3top(PORT19, ratio6_1,true);
motor right1(PORT3, ratio6_1,false );
motor right2(PORT2, ratio6_1,false );
motor right3top(PORT5, ratio6_1,false );
motor_group DriveA(left1,left2,left3top);
motor_group DriveB(right1,right2,right3top);
motor lift(PORT1, ratio18_1,false );
pneumatics rod(Brain.ThreeWirePort.A);
motor intake(PORT4, ratio36_1,false);
rotation sensor(PORT4);
inertial imu(PORT1);

tao::DifferentialDrivetrain chassis(left_drive, right_drive, imu, {
	.drive_gains = { 4.24, 0, 0.06 },
	.turn_gains = { 0.82, 0.003, 0.0875 },
	.drive_tolerance = 0.7,
	.turn_tolerance = 0.34,
	.lookahead_distance = 10.3,
	.track_width = 13.75,
	.wheel_diameter = 3.25,
	.gearing = (36.0 / 48.0),
}, tao::Logger(std::cout, tao::Logger::Level::DEBUG));
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
    DriveA.setVelocity(pen.Axis3.position(), pct);
    DriveB.setVelocity(pen.Axis2.position(), pct);
    DriveA.spin(forward);
    DriveB.spin(forward);
    if (pen.ButtonR2.pressing())  {
      intake.spin(reverse);
    }else if (pen.ButtonR1.pressing())  {
      intake.spin(forward);
    }else {intake.stop();}
    
    
    
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
   pen.ButtonL1.pressed([]() {
   rod.set(!rod);
   });
  intake.setVelocity(100, pct);
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

