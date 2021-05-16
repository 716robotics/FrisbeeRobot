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

void Robot::RobotPeriodic() {
  frc::SmartDashboard::PutBoolean("slide", slidereturn.Get());
  frc::SmartDashboard::PutNumber("Proximity0", colorSensor0.GetProximity());
  frc::SmartDashboard::PutNumber("Proximity1", colorSensor1.GetProximity());
  frc::SmartDashboard::PutNumber("shoot timer", shootTimer.Get());
  frc::SmartDashboard::PutNumber("No Frisbee",NoFrisbeeCount);
}

void Robot::TeleopInit() {
shootPusher.Set(shootPusher.kForward);
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
  std::cout << ss << std::endl;
  switch(ss)
  {
    case ss_reload:
    shootCheck = 0;
    frc::SmartDashboard::PutString("Shooter Status", "Reloading");
      if (!slidereturn.Get()){shootCheck++;} //checks if shootpusher has returned to where it should be
      else {shootPusher.Set(shootPusher.kForward);
        break;}
      if (ColorSensorGet(0,0) >= FRISBEEDETECTED){ //check if frisbee present in shooter
        shootCheck ++;
        shooterLoad.Set(0);
        //NoFrisbeeCount = 0;
        if (shootCheck == 2) {ss = ss_shoot;
        break;}}
      else{
        if (ColorSensorGet(1,0) >= FRISBEEDETECTED || xbox.GetXButton()){ //check if fris. avail for reload
          shooterLoad.Set(1);
          //NoFrisbeeCount = 0;
          }
          else{frc::SmartDashboard::PutString("Shooter Status", "Out of Ammo!");
          //Shoot = false;
          NoFrisbeeCount ++;
          shooter1.Set(0);
          shooter2.Set(0);
          shooterLoad.Set(0);
          //shootTimer.Stop();
          //shootTimer.Reset();
          break;}}
        break;
      case ss_shoot:
        if (ColorSensorGet(1,0) >= FRISBEEDETECTED && (!slidereturn.Get()) && ColorSensorGet(0,0) < FRISBEEDETECTED){ //check if frisbee present in shooter
          ss = ss_reload;
          break;}
        frc::SmartDashboard::PutBoolean("Shoot", Shoot);
        if(xbox.GetTriggerAxis(xbox.kLeftHand) > 0.3){Shoot = false;}
        else if(xbox.GetTriggerAxis(xbox.kRightHand) > 0.3){Shoot = true;}
        if (Shoot){
          shooter1.Set(SHOOTPOWER);
          shooter2.Set(SHOOTPOWER);
          shootTimer.Start(); //harmless if called when already running
          if (shootTimer.Get() >= 1 && shootTimer.Get() <= 2){shootPusher.Set(shootPusher.kReverse);}
          else if (shootTimer.Get() > 2){
          shootTimer.Stop();
          shooter1.Set(0);
          shooter2.Set(0);
          shootPusher.Set(shootPusher.kForward);
          shootTimer.Reset();
          }}
          else {frc::SmartDashboard::PutString("Shooter Status", "Shooting");}
          break;

      case ss_stop:
          //Shoot = false; TEMPORARY
          shooter1.Set(0);
          shooter2.Set(0);
          shooterLoad.Set(0);
          //shootTimer.Stop();
          //shootTimer.Reset();
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
