/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "uglyIncludes.h"

class Robot : public frc::TimedRobot {
  frc::Joystick leftDriveStick{0};
  frc::Joystick rightDriveStick{1};
  frc::Jaguar lDrive1{PWMCHANNELDRIVEL1};
  frc::Jaguar lDrive2{PWMCHANNELDRIVEL2};
  frc::Jaguar rDrive1{PWMCHANNELDRIVER1};
  frc::Jaguar rDrive2{PWMCHANNELDRIVER2};
  frc::SpeedControllerGroup lDrive{lDrive1, lDrive2};
  frc::SpeedControllerGroup rDrive{rDrive1, rDrive2};
  frc::DifferentialDrive drive{lDrive, rDrive};
  frc::Compressor compressor;
  frc::DoubleSolenoid shootPusher{PCMSHOOTPUSHERR, PCMSHOOTPUSHERL};
  frc::DoubleSolenoid shootAngle{PCMSHOOTANGLER, PCMSHOOTANGLEL};
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> CM_chooser;
  const std::string kControlMapDefault = "Classic";
  const std::string kControlMapLowPersonel = "Xbox Only";
  frc::SendableChooser<std::string> SF_chooser;
  const std::string kSafteyNone = "None - Only Team Members";
  const std::string kSafteyDrDm = "Driver Has Deadman";
  const std::string kSafteyOpDm = "Operator Has Deadman";
};
