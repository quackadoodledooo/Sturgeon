#include <FastLED.h>
#include <Alfredo_NoU3.h>
#include <PestoLink-Receive.h>
#include "Constants.h"
#include "PID.h"

PID turretPID(turretkP, turretkI, turretkD, -1, 1);

NoU_Motor frontLeftMotor(1);
NoU_Motor frontRightMotor(2);
NoU_Motor rearLeftMotor(3);
NoU_Motor rearRightMotor(4);
NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMotor, &rearLeftMotor, &rearRightMotor);

NoU_Motor spindexer(5);
NoU_Motor turret(6);
NoU_Motor intakeWheels(7);
NoU_Motor shooter(8);

NoU_Servo intakePivot(1);
NoU_Servo hood(2);
NoU_Servo climber(3);

STATE robotState;

void setup() {
  NoU3.begin();
  NoU3.calibrateIMUs();
  PestoLink.begin("Sturgeon");
  turret.beginEncoder();
  xTaskCreatePinnedToCore(taskUpdateTurret, "taskUpdateTurret", 4096, NULL, 2, NULL, 1);
  robotState = START;
}

void setLEDS() {
    if(LEDCounter > 7) {
      LEDCounter = 0;
      for(int i = 0; i < 16; i++) {
        leds[i] = CRGB::Black;
      }
    }
    if(robotState == START) {
      leds[LEDCounter] = CRGB::Green;
      leds[LEDCounter + 8] = CRGB::Green;
    }
    else if(robotState == SHUTTLE) {
      leds[LEDCounter] = CRGB::Green;
      leds[LEDCounter + 8] = CRGB::Green;
    }
    else if(robotState == SHOOTING) {
      leds[LEDCounter] = CRGB::Green;
      leds[LEDCounter + 8] = CRGB::Green;
    }
    else if(robotState == INTAKING) {
      leds[LEDCounter] = CRGB::Green;
      leds[LEDCounter + 8] = CRGB::Green;
    }
    else if(robotState == NORMAL) {
      for(int i = 0; i < 16; i++) leds[i] = CRGB::Yellow;
    }
    if(LEDCounter > 0 && (LEDCounter + 8) > 8) {
      leds[LEDCounter -1] = CRGB::Black;
      leds[LEDCounter + 7] = CRGB::Black;
    }
  LEDCounter++;
  FastLED.show();
}

void loop() {
  
}

void taskUpdateTurret(void* pvParameters) {
  while (true) {

  }
}