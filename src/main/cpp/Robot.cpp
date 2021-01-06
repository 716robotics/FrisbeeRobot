//FRC Team 716 Frisbee Robot Code

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  CM_chooser.SetDefaultOption(kControlMapDefault, kControlMapDefault);
  CM_chooser.AddOption(kControlMapLowPersonel, kControlMapLowPersonel);
  frc::SmartDashboard::PutData("Control Mapping", &CM_chooser);
  SF_chooser.SetDefaultOption(kSafteyNone, kSafteyNone);
  SF_chooser.AddOption(kSafteyDrDm, kSafteyDrDm);
  SF_chooser.AddOption(kSafteyOpDm, kSafteyOpDm);
  frc::SmartDashboard::PutData("E-Stop Behavior", &SF_chooser);
  compressor.Start();
  }

void Robot::RobotPeriodic() {}

void Robot::TeleopInit() {

}

void Robot::TeleopPeriodic() {
  if (CM_chooser.GetSelected() == kControlMapLowPersonel){
    drive.ArcadeDrive(xbox.GetX(xbox.kRightHand), xbox.GetY(xbox.kRightHand), true);
  }
  else {drive.TankDrive(leftDriveStick.GetY(), rightDriveStick.GetY(), true);
  }

}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {
  drive.TankDrive(leftDriveStick.GetY(), rightDriveStick.GetY(), true);
  if (xbox.GetXButtonPressed()) {Load=!Load;}
  if (xbox.GetYButtonPressed()) {Shoot=!Shoot;}
  shooterLoad.Set(float(Load));
  shooters.Set(float(Shoot)*SHOOTPOWER);
  if (xbox.GetAButton()) {shootPusher.Set(shootPusher.kReverse);}
  else {shootPusher.Set(shootPusher.kForward); }
  if (xbox.GetTriggerAxis(xbox.kRightHand)>0.8) {shootAngle.Set(shootAngle.kForward);}
  if (xbox.GetTriggerAxis(xbox.kLeftHand)>0.8) {shootAngle.Set(shootAngle.kReverse);}
}

double Robot::ColorSensorGet(int sensor, int mode = 0){
  if (mode == 0){ //return proximity of given sensor
  double proximity0 = colorSensor0.GetProximity(); // The closest reading is 2047 and furthest is 0
  double proximity1 = colorSensor1.GetProximity();
  frc::SmartDashboard::PutNumber("Proximity0", proximity0);
  frc::SmartDashboard::PutNumber("Proximity1", proximity1);
  if (sensor == 0){return proximity0;}
  if (sensor == 1){return proximity1;}
}
  if (mode == 1){ //return color data (not yet used or really fleshed out)
  frc::Color detectedColor = colorSensor0.GetColor();
  return 0; //temporary to suppress compiler warnings
  }
}

//---Don't touch Below This Comment---
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
