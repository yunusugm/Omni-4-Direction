//? JOYSTICK EVENT YANG DIPAKAI
#define R1_LONG_PRESS (Ps3.data.button.r1) //R1 DITEKAN MAKA DATA > 0 == TRUE
#define L1_LONG_PRESS (Ps3.data.button.l1)
#define R2_PRESSED    (Ps3.event.button_down.r2)
#define L2_PRESSED    (Ps3.event.button_down.l2)
#define R1_RELEASE    (Ps3.event.button_up.r1)
#define L1_RELEASE    (Ps3.event.button_up.l1)
#define R2_RELEASE    (Ps3.event.button_up.r2)
#define Y_LEFT        (abs(Ps3.event.analog_changed.stick.ly))
#define X_LEFT        (abs(Ps3.event.analog_changed.stick.lx))
#define Y_RIGHT       (abs(Ps3.event.analog_changed.stick.ry))
#define X_RIGHT       (abs(Ps3.event.analog_changed.stick.rx))
#define TRIANGLE_LONG_PRESS (Ps3.data.button.triangle)
#define CROSS_LONG_PRESS    (Ps3.data.button.cross)
#define CIRCLE_LONG_PRESS   (Ps3.data.button.circle)
#define SQUARE_LONG_PRESS   (Ps3.data.button.square)

//? DATA FROM JOYSTICK
#define X_LEFT_DATA   (Ps3.data.analog.stick.lx)
#define Y_LEFT_DATA   (Ps3.data.analog.stick.ly)
#define X_RIGHT_DATA  (Ps3.data.analog.stick.rx)
#define Y_RIGHT_DATA  (Ps3.data.analog.stick.ry)

//? JOYSTICK VAR
#define TO_DEG 57.29577951308
int battery = 0;
float angleLeft, angleRight;
float powerLeft, powerRight;
float speedLimitLeft, speedLimitRight;
int speedFromJoystickLeft, speedFromJoystickRight; 
int rX, rY, lX, lY;

// MOTOR PIN DAN CHANNEL DAN ENCODER
const byte LF_A = 25; const byte LF_B = 26; // KIRI DEPAN
int LF_PWM[] = {4, 5};
int LF_ENC[] = {21, 19};
const byte LB_A = 32; const byte LB_B = 33; // KIRI BELAKANG
int LB_PWM[] = {10, 11};
int LB_ENC[] = {23, 22};
const byte RF_A = 17; const byte RF_B = 15; // KANAN DEPAN
int RF_PWM[] = {12, 13};
int RF_ENC[] = {35, 34};
const byte RB_A = 18; const byte RB_B = 13; // KANAN BELAKANG
int RB_PWM[] = {14, 15};
int RB_ENC[] = {16, 4}; 

// CONFIG ESP KE MOTOR
const int freq = 5000;
const int resolution = 8;
int dutyCycle[] = {100, 225}; // long rotate, 180 rotate

// SERVO
const byte servoPin1 = 27;
const byte servoPin2 = 14;
const byte servoPin3 = 12;

Servo servoUpDown;
Servo servoClose;
Servo servoRotate;

static int flagxservo;
static int flagxservo90;

bool flagspeed;
bool toggle;
