#include <FastLED.h>
#include "Alfredo_NoU3.h"
#include "PestoLink-Receive.h"
#include "Constants.h"

NoU_Motor frontLeftMotor(8);
NoU_Motor frontRightMotor(2);
NoU_Motor rearLeftMotor(3);
NoU_Motor rearRightMotor(4);
NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMotor, &rearLeftMotor, &rearRightMotor);

NoU_Motor spintake(1);
NoU_Motor kicker(6);
NoU_Motor flywheelLeft(7);
NoU_Motor flywheelRight(5);

NoU_Servo intakePivot(5);
NoU_Servo intakePivot2(1);
NoU_Servo turret(2);
NoU_Servo hoodLeft(3);
NoU_Servo hoodRight(4);

STATE robotState;
ALLIANCE alliance;  
INTAKESTATE intakeState;

void setup() {
  NoU3.begin();
  NoU3.calibrateIMUs();
  PestoLink.begin("SturgSON");
  xTaskCreatePinnedToCore(task, "task", 4096, NULL, 2, NULL, 1);
  Serial.begin(9600);

  robotState = START;
  current_time = millis();
  previous_time = current_time;

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.setBrightness(20);
  FastLED.clear();
  FastLED.show();
}

void setLEDS() {
  int timeDifference = current_time - previous_time;
  if(robotState == START) {
    if (alliance == RED) 
      for(int i = 0; i < 16; i++) 
        leds[i] = CRGB::Red;
    if (alliance == BLUE) 
      for(int i = 0; i < 16; i++) 
        leds[i] = CRGB::Blue;
  }
  else if(robotState == SHUTTLE) {
    for(int i = 0; i < 16; i++) 
      leds[i] = CRGB::Orange;
  }
  else if(robotState == NORMAL) {
    for(int i = 0; i < 16; i++)
      leds[i] = CRGB::Yellow;
  }
  // else if(robotState == SHOOTING) {
  //   if (timeDifference > 250) 
  //     leds[i] = CRGB::Black;
  //   if(timeDifference > 500) {
  //     leds[i] = CRGB::Green;
  //     previous_time = current_time;
  //   }
  // }
  // else if(robotState == INTAKING) {
  //   if (timeDifference > 250) 
  //     leds[i] = CRGB::Black;
  //   if(timeDifference > 500) {
  //     leds[i] = CRGB::Green;
  //     previous_time = current_time;
  //   }
  // }
  FastLED.show();
}
void controls() {
}

void loop() {
  //controls();

      float batteryVoltage = NoU3.getBatteryVoltage();
    PestoLink.printBatteryVoltage(batteryVoltage);


    int yaw=roll*(PI/180);
    while(yaw>360){
        yaw-=360;
    }
    while(yaw<0){
        yaw+=360;
    }
    yaw = (yaw>90-MOE && yaw<90+MOE) ? yaw = 90 :
        (yaw>180-MOE && yaw<180+MOE) ? yaw = 180 :
        (yaw>270-MOE && yaw<270+MOE) ? yaw = 270 :
        (yaw>360-MOE || yaw<MOE) ? yaw = 360 :
        yaw;


  //SHOOTER
  if(PestoLink.buttonHeld(7)) {
    flywheelLeft.set(currentLeftFlywheel);
    flywheelRight.set(currentRightFlywheel);
    kicker.set(1);
    spintake.set(1);
  } else if(PestoLink.buttonHeld(rightBumper)) { //pass
    turretAngleCurrent =  (int)(roll + 180) % 360;
    hoodLeftCurrent = HOOD_MAX;
    hoodRightCurrent = HOOD_MAX;
    currentLeftFlywheel = PASS_SPEED;
    currentRightFlywheel = PASS_SPEED;
    kicker.set(1);
    spintake.set(1);
  }else  if(PestoLink.buttonHeld(leftTrigger)) {
    if(intakeState == UP) {
      intakeState = DOWN;
      intakePivot.write(intakeState);
    }
    spintake.set(1);
    kicker.set(-1);
  }  else{
    kicker.set(0);
    spintake.set(0);
  }

  //RIGHT TRENCH
  if(PestoLink.buttonHeld(buttonB)) {
    if(yaw == 360) usePreset(rightTrench);
    if(yaw == 270) usePreset(RTrenchLeft);
    if(yaw == 180) usePreset(RTrenchBack);
    if(yaw == 90) usePreset (RTrenchRight);
  }

  //LEFT TRENCH
  if(PestoLink.buttonHeld(buttonX)) {
    if(yaw == 360) usePreset(leftTrench);
    if(yaw == 270) usePreset(LTrenchLeft);
    if(yaw == 180) usePreset(LTrenchBack);
    if(yaw == 90) usePreset (LTrenchRight);
  }

  //UNDER HUB
  if(PestoLink.buttonHeld(buttonY)) {
    if(yaw == 360) usePreset(hub);
    if(yaw == 270) usePreset(hubLeft);
    if(yaw == 180) usePreset(hubBack);
    if(yaw == 90) usePreset (hubRight);
  }

  if(PestoLink.keyHeld(Key::Numpad1)) {
    if(yaw == 360) usePreset(depotCorner);
    if(yaw == 270) usePreset(depotLeft);
    if(yaw == 180) usePreset(depotBack);
    if(yaw == 90) usePreset (depotRight);
  }

  if(PestoLink.keyHeld(Key::Numpad2)) {
    if(yaw == 360) usePreset(tower);
    if(yaw == 270) usePreset(towerLeft);
    if(yaw == 180) usePreset(towerBack);
    if(yaw == 90) usePreset (towerRight);
  }

  if(PestoLink.keyHeld(Key::Numpad3)) {
    if(yaw == 360) usePreset(outpostCorner);
    if(yaw == 270) usePreset(outpostLeft);
    if(yaw == 180) usePreset(outpostBack);
    if(yaw == 90) usePreset (outpostRight);
  }



  //FLATTEN HOOD FOR TRENCH
  if(PestoLink.buttonHeld(leftBumper)) {
    hoodRightCurrent = HOOD_FLAT;
    hoodLeftCurrent = HOOD_FLAT;
  }

    if(PestoLink.buttonHeld(buttonA)) {
    intakeState = UP;
    intakePivot.write(intakeState);
  }

}

void task(void* pvParameters) {
  while (true) {
    delay(10);
    heading = NoU3.yaw * angular_scale;
    roll = NoU3.roll * angular_scale;
    pitch = NoU3.pitch * angular_scale;
    float yVelocity = -PestoLink.getAxis(1);
    float xVelocity = PestoLink.getAxis(0);
    float rotation = -PestoLink.getAxis(2);

    // Rotate joystick vector to be robot-centric
    float cosA = cos(roll);
    float sinA = sin(roll);

    float xField = xVelocity * cosA + yVelocity * sinA;
    float yField = -xVelocity * sinA + yVelocity * cosA;

    //set motor power
    drivetrain.holonomicDrive(xField, yField, rotation);
    turret.write(turretAngleCurrent);
    hoodLeft.write(hoodLeftCurrent);
    hoodRight.write(hoodRightCurrent);
    intakePivot2.write((intakeState - 180) * -1);
    
    setLEDS();
  }
}