/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "uglyIncludes.h"

class Robot : public frc::TimedRobot {
  frc::XboxController xbox{2};
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
  frc::DigitalInput slidereturn{DIOSLIDERETURN};
  frc::Timer shootTimer;
  frc::Timer slideTimer;
  enum ShooterState {
    ss_stop,
    ss_reload,
    ss_shoot
  };
  ShooterState ss = ss_reload;
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  void RunFrisbee();
  double ColorSensorGet(int,int);
  bool Load = false; //for testing only
  bool Shoot = false;
  int shootCheck = 0;
  int NoFrisbeeCount = 0; //this is a count of how many cycles the systems goes without seeing a frisbee with EITHER sensor
  
};
