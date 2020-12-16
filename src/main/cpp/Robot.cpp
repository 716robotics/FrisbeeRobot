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
  }

void Robot::RobotPeriodic() {}

void Robot::TeleopInit() {
  compressor.Start();
}

void Robot::TeleopPeriodic() {
  drive.TankDrive(leftDriveStick.GetX(), rightDriveStick.GetX(), true);
  drive.ArcadeDrive(xbox.GetX(xbox.kRightHand), xbox.GetY(xbox.kRightHand), true);
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {
  drive.TankDrive(leftDriveStick.GetX(), rightDriveStick.GetX(), true);
  if (xbox.GetXButtonPressed()) {Load=!Load;}
  if (xbox.GetYButtonPressed()) {Shoot=!Shoot;}
  shooterLoad.Set(float(Load));
  shooters.Set(float(Shoot)*SHOOTPOWER);
  if (xbox.GetAButton()) {shootPusher.Set(shootPusher.kReverse);}
  else {shootPusher.Set(shootPusher.kForward); }
  if (xbox.GetTriggerAxis(xbox.kRightHand)>0.8) {shootAngle.Set(shootAngle.kForward);}
  if (xbox.GetTriggerAxis(xbox.kLeftHand)>0.8) {shootAngle.Set(shootAngle.kReverse);}
}

int Robot::ColorSensor(){
  frc::Color detectedColor = colorSensor0.GetColor();
  frc::Color detectedColor = colorSensor1.GetColor();
  int Color = 0;
  double C_red = detctedColor.red * 255;
  double C_green = detectedColor.green * 255;
  double C_blue = detectedColor.blue * 255;
  if (((C_red > C_green) && (C_green > C_blue)) || ((C_green > C_red) && (C_red > C_blue))) Color = 1; //red
  if ((C_green > C_blue) && (C_blue > C_red)){
    if ((C_green - C_blue) > 40) Color = 2; //green
    else Color = 3; //blue
  }
  if ((C_blue > C_green) && (C_green > C_red)) Color = 3; //blue
  if (((C_green > C_red) && (C_red > C_blue)) & (C_green >= 138)) Color = 4; //yellow
  double proximity0 = colorSensor0.GetProximity(); // The closest reading is 2047 and furthest is 0
  double proximity1 = colorSensor1.GetProximity();
  frc::SmartDashboard::PutNumber("Proximity0", proximity0);
  frc::SmartDashboard::PutNumber("Proximity1", proximity1);
  frc::SmartDashboard::PutNumber("Red", (detectedColor.red * 255));
  frc::SmartDashboard::PutNumber("Green", (detectedColor.green * 255));
  frc::SmartDashboard::PutNumber("Blue", (detectedColor.blue * 255));
  frc::SmartDashboard::PutNumbet("Color", Color);
  if (proximity > 400) frc::SmartDashboard::PutString("Color Status", "OK");
  else {
    frc::SmartDashboard::PutString("Color Status", "Not Close Enough"); 
    C_color = 0;
  }
  frc::SmartDashboard::PutNumber("Color Detected", C_color);
  return C_color;
}

//---Don't touch Below This Comment---
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
