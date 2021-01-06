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
  frc::XboxController xbox{3};
  frc::Jaguar lDrive0{PWMCHANNELDRIVEL0};
  frc::Jaguar lDrive1{PWMCHANNELDRIVEL1};
  frc::Jaguar rDrive0{PWMCHANNELDRIVER0};
  frc::Jaguar rDrive1{PWMCHANNELDRIVER1};
  frc::SpeedControllerGroup lDrive{lDrive0, lDrive1};
  frc::SpeedControllerGroup rDrive{rDrive0, rDrive1};
  frc::DifferentialDrive drive{lDrive, rDrive};
  frc::Compressor compressor;
  frc::DoubleSolenoid shootPusher{PCMSHOOTPUSHERR, PCMSHOOTPUSHERL};
  frc::DoubleSolenoid shootAngle{PCMSHOOTANGLER, PCMSHOOTANGLEL};
  frc::Jaguar shooterLoad{PVMSHOOTERLOAD};
  frc::Jaguar shooter1{PVMSHOOTER1};
  frc::Jaguar shooter2{PVMSHOOTER2};
  frc::SpeedControllerGroup shooters{shooter1, shooter2};
  static constexpr auto i2cPort0 = frc::I2C::Port::kOnboard;
  static constexpr auto i2cPort1 = frc::I2C::Port::kMXP;
  rev::ColorSensorV3 colorSensor0{i2cPort0};
  rev::ColorSensorV3 colorSensor1{i2cPort1};
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  double ColorSensorGet(int,int);
  bool Load=false;
  bool Shoot=false;

 private:
  frc::SendableChooser<std::string> CM_chooser;
  const std::string kControlMapDefault = "Classic";
  const std::string kControlMapLowPersonel = "Xbox Only";
  frc::SendableChooser<std::string> SF_chooser;
  const std::string kSafteyNone = "None - Only Team Members";
  const std::string kSafteyDrDm = "Driver Has Deadman";
  const std::string kSafteyOpDm = "Operator Has Deadman";
};
