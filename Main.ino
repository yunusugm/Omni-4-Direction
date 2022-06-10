#include <Ps3Controller.h>
#include <ESP32Servo.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  initPS();
  initOmniwheel();
  initservo();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!Ps3.isConnected()) {
    return;
  }
  wheelEvent();
  servoEvent();
  runWheel();
}
