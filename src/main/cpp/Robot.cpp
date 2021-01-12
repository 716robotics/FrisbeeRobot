//FRC Team 716 Frisbee Robot Code

#include "Robot.h"
#include <iostream>

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
    RunFrisbee(1);
  }
  else {drive.TankDrive(leftDriveStick.GetY(), rightDriveStick.GetY(), true);
  RunFrisbee(1);
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

void Robot::RunFrisbee(int mode){
  //if (!deadman) {ss = ss_stop;} not yet implimented
  if (xbox.GetY(xbox.kRightHand) > 0.7) {shootAngle.Set(shootAngle.kForward);}
  if (xbox.GetY(xbox.kRightHand) < -0.7) {shootAngle.Set(shootAngle.kReverse);}
  switch(ss)
  {
    case ss_reload:
    shootCheck = 0;
    frc::SmartDashboard::PutString("Shooter Status", "Reloading");
      if (slidereturn.Get()){shootCheck++; //checks if shootpusher has returned to where it should be
        shootPusher.Set(shootPusher.kOff);}
      else {shootPusher.Set(shootPusher.kReverse);
        break;}
      if (ColorSensorGet(1,0) >= FRISBEEDETECTED){ //check if frisbee present in shooter
        shootCheck ++;
        shooterLoad.Set(0);
        break;}
      else{
        if (ColorSensorGet(0,0) >= FRISBEEDETECTED || xbox.GetXButton()){ //check if fris. avail for reload
          shooterLoad.Set(1);}
          else{frc::SmartDashboard::PutString("Shooter Status", "Out of Ammo!");
          Shoot = false;
          shooter1.Set(0);
          shooter2.Set(0);
          shooterLoad.Set(1);
          shootTimer.Stop();
          shootTimer.Reset();
          break;}}
        if (shootCheck == 2) {ss = ss_shoot;}
        break;
      case ss_shoot:
        if (ColorSensorGet(1,0) < FRISBEEDETECTED && slidereturn.Get()){ //check if frisbee present in shooter
          ss = ss_reload;
          break;}
        if(xbox.GetTriggerAxis(xbox.kRightHand) >= 90){Shoot = true;}
        if(Shoot){
          frc::SmartDashboard::PutString("Shooter Status", "Shooting");
          shooter1.Set(SHOOTPOWER);
          shooter2.Set(SHOOTPOWER);
          if(Shoot != lastshoot){shootTimer.Start();}
          if (shootTimer.Get() >= 3){shootPusher.Set(shootPusher.kForward);
          slideTimer.Start();}
          if (slideTimer.Get() > 3){shootPusher.Set(shootPusher.kReverse);
          slideTimer.Stop();
          slideTimer.Reset();}}
          break;

      case ss_stop:
          Shoot = false;
          shooter1.Set(0);
          shooter2.Set(0);
          shooterLoad.Set(0);
          shootTimer.Stop();
          shootTimer.Reset();
          slideTimer.Stop();
          slideTimer.Reset();
          shootPusher.Set(shootPusher.kOff);
          shootAngle.Set(shootAngle.kOff);
          frc::SmartDashboard::PutString("Shooter Status", "Halted");
          //if(deadman) {ss = ss_reload;}
          break;
      }
lastshoot = Shoot;
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
  }
  return 0;
}

//---Don't touch Below This Comment---
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
