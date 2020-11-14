/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include "Tunables.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

class Robot : public frc::TimedRobot {
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
