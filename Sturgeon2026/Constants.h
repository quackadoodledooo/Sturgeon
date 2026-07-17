#ifndef CONSTANTS
#define CONSTANTS
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989
#define FASTLED_ALLOW_INTERRUPTS 0   //FASTLED SERIAL INTERRUPTS ALLOWED TO ZERO
#define NUM_LEDS 16                 //NUM OF LEDS IN CHAIN                       
#define DATA_PIN 39                 //DATA PIN 5 (GPIO D5)                         
CRGB leds[NUM_LEDS];

const double PASS_SPEED = 1; //REDUCE IF PASSING TOO FAR
//USE JOSHUAS SERVO TESTER TO FIND ACTUAL VALUE FOR THESE TWO.
const int HOOD_FLAT = 80;
const int HOOD_MAX = 180;
const int MOE = 5;

unsigned long current_time;
unsigned long previous_time;
double currentLeftFlywheel;
double currentRightFlywheel;
double heading;
double pitch;
double roll;
int hoodLeftCurrent;
int hoodRightCurrent;
int turretAngleCurrent;

//The gyroscope sensor is by default precise, but not accurate. This is fixable by adjusting the angular scale factor.
//Tuning procedure:
//Rotate the robot in place 5 times. Use the Serial printout to read the current gyro angle in Radians, we will call this "measured_angle".
//measured_angle should be nearly 31.416 which is 5*2*pi. Update measured_angle below to complete the tuning process.
float measured_angle = 27.562;
float angular_scale = (5.0 * 2.0 * PI) / measured_angle;

struct Preset
{
  double turretAngle;
  double leftHood;
  double rightHood;
  double leftFlywheel;
  double rightFlywheel;
};

Preset hub;
Preset hubLeft;
Preset hubRight;
Preset hubBack;
Preset tower;
Preset towerLeft;
Preset towerRight;
Preset towerBack;
Preset depotCorner;
Preset depotLeft;
Preset depotRight;
Preset depotBack;
Preset outpostCorner;
Preset outpostLeft;
Preset outpostRight;
Preset outpostBack;
Preset leftTrench;
Preset LTrenchLeft;
Preset LTrenchRight;
Preset LTrenchBack;
Preset rightTrench;
Preset RTrenchLeft;
Preset RTrenchRight;
Preset RTrenchBack;

void setPresets() {
  //USE JOSHUAS SERVO TESTER TO FIND VALUES
  hub.turretAngle = 0;
  hub.leftHood = 0;
  hub.rightHood = 0;
  hub.leftFlywheel = 0;
  hub.rightFlywheel = 0;
}

void usePreset(Preset preset) {
  turretAngleCurrent = preset.turretAngle;
  currentLeftFlywheel = preset.leftFlywheel;
  currentRightFlywheel = preset.rightFlywheel;
  hoodLeftCurrent = preset.leftHood;
  hoodRightCurrent = preset.rightHood;
}

enum INTAKESTATE { //CHANGE THESE NUMBERS TO ACTUAL SERVO VALUES FOR UP AND DOWN
  UP = 10,
  DOWN = 85
};

enum ALLIANCE {
  RED,
  BLUE
};


enum STATE {
  START,
  NORMAL,
  SHUTTLE,
  SCORING,
};

//CHANGE THESE BASED OFF CONTROLLER, THESE ARE FOR XBOX
const int buttonA = 0;
const int buttonB = 1;
const int buttonX = 2;
const int buttonY = 3;
const int leftBumper = 4;
const int rightBumper = 5; 
const int leftTrigger = 6;
const int rightTrigger = 7;
const int leftMain = 8;
const int rightMain = 9;
const int leftStick = 10;
const int rightStick = 11;
const int upDPad = 12;
const int downDPad = 13;
const int leftDPad = 14;
const int rightDPad = 15;

#endif
