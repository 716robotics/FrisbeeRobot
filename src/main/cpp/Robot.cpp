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

void Robot::TestPeriodic() {}

//Don't touch Below This Comment
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
