#ifndef CONSTANTS
#define CONSTANTS
#define PI 3.14159265359
#define FASTLED_ALLOW_INTERRUPTS 0   //FASTLED SERIAL INTERRUPTS ALLOWED TO ZERO
#define NUM_LEDS 16                 //NUM OF LEDS IN CHAIN                       
#define DATA_PIN 39                 //DATA PIN 5 (GPIO D5)                         
CRGB leds[NUM_LEDS];


//turret constants:
double turretkP = 0.0;
double turretkI = 0.0;
double turretkD = 0.0;

int LEDCounter = 0;

enum STATE {
  START,
  NORMAL,
  INTAKING,
  SHUTTLE,
  SHOOTING,
  ENDGAME,
};

#endif
