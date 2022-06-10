void initservo(){
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    servoUpDown.setPeriodHertz(50);   // standard 50 hz servo
    servoUpDown.attach(servoPin1, 1000, 2000); // attaches the servo on pin 18 to the servo object
    servoClose.setPeriodHertz(50);   // standard 50 hz servo
    servoClose.attach(servoPin2, 1000, 2000); // attaches the servo on pin 18 to the servo object
    servoRotate.setPeriodHertz(50);   // standard 50 hz servo
    servoRotate.attach(servoPin3, 1000, 2000); // attaches the servo on pin 18 to the servo object

    pinMode(servoPin1, OUTPUT);
    pinMode(servoPin2, OUTPUT);
    pinMode(servoPin3, OUTPUT);

    flagxservo=0;
    flagxservo90=0;

    Serial.println("Servo is ready to use");
}

// for servo 1
// direction true for CW, false for CCW
// for CW velocity 0,1,2,3 for 90,60,30,0
// for CCW velocity 0,1,2,3 for 90,120,150,180
void servo1cont(bool direct, int velocity){
  static int velocitytoservo;
  velocitytoservo = 90 - velocity*30;
  if(direct){
    servoUpDown.write(velocitytoservo);
    Serial.println("Servo1 speed:");
    Serial.print(velocitytoservo);
  }
  if(!direct){
    velocitytoservo = 180 - velocitytoservo;
    servoUpDown.write(velocitytoservo);
    Serial.println("Servo1 speed:");
    Serial.print(velocitytoservo);
  }
}
// servo stop
void servo1stop(){
  servoUpDown.write(90);
}

// for servo 2
// direction true for CW, false for CCW
// for CW velocity 0,1,2,3 for 86, 91, 96, 101
// for CCW velocity 0,1,2,3 for 86,81,76,71
void servo2cont(bool direct, int velocity){
  int velocitytoservo;
  velocitytoservo = 90 - velocity*30;
  if(direct){
    servoClose.write(80);
    Serial.println("Servo2 speed:");
    Serial.print(velocitytoservo);
    
  }
  if(!direct){
    velocitytoservo = 180 - velocitytoservo;
    servoClose.write(100);
    Serial.println("Servo2 speed:");
    Serial.print(velocitytoservo);
  }
}

// servo stop
void servo2stop(){
  servoClose.write(90);
}
