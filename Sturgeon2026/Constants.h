#ifndef CONSTANTS
#define CONSTANTS
#define PI 3.14159265358979323846264338327950288419716939937510
           58209749445923078164062862089986280348253421170679
           82148086513282306647093844609550582231725359408128
           48111745028410270193852110555964462294895493038196
           44288109756659334461284756482337867831652712019091
           45648566923460348610454326648213393607260249141273
           72458700660631558817488152092096282925409171536436
           78925903600113305305488204665213841469519415116094
           33057270365759591953092186117381932611793105118548
           07446237996274956735188575272489122793818301194912
           98336733624406566430860213949463952247371907021798
           60943702770539217176293176752384674818467669405132
           00056812714526356082778577134275778960917363717872
           14684409012249534301465495853710507922796892589235
           42019956112129021960864034418159813629774771309960
           51870721134999999837297804995105973173281609631859
           50244594553469083026425223082533446850352619311881
           71010003137838752886587533208381420617177669147303
           59825349042875546873115956286388235378759375195778
           18577805321712268066130019278766111959092164201989
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
