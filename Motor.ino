void initOmniwheel(){
  motorInit();
  leftForwardInit();
  leftBackwardInit();
  rightBackwardInit();
  rightForwardInit();
}

void motorInit() {
  pinMode(LF_A, OUTPUT);
  pinMode(LF_B, OUTPUT);
  pinMode(LB_A, OUTPUT);
  pinMode(LB_A, OUTPUT);
  pinMode(RF_A, OUTPUT);
  pinMode(RF_B, OUTPUT);
  pinMode(RB_A, OUTPUT);
  pinMode(RB_A, OUTPUT);
}

void leftForwardInit() {
  ledcSetup(LF_PWM[0], freq, resolution);
  ledcSetup(LF_PWM[1], freq, resolution);
  ledcAttachPin(LF_A, LF_PWM[0]);
  ledcAttachPin(LF_B, LF_PWM[1]);
  Serial.println("Omni left forward is ready!");
}

void leftBackwardInit() {
  ledcSetup(LB_PWM[0], freq, resolution);
  ledcSetup(LB_PWM[1], freq, resolution);
  ledcAttachPin(LB_A, LB_PWM[0]);
  ledcAttachPin(LB_B, LB_PWM[1]);
  Serial.println("Omni left backward is ready!");
}

void rightForwardInit() {
  ledcSetup(RF_PWM[0], freq, resolution);
  ledcSetup(RF_PWM[1], freq, resolution);
  ledcAttachPin(RF_A, RF_PWM[0]);
  ledcAttachPin(RF_B, RF_PWM[1]);
  Serial.println("Omni right forward is ready!");
}

void rightBackwardInit() {
  ledcSetup(RB_PWM[0], freq, resolution);
  ledcSetup(RB_PWM[1], freq, resolution);
  ledcAttachPin(RB_A, RB_PWM[0]);
  ledcAttachPin(RB_B, RB_PWM[1]);
  Serial.println("Omni right backward is ready!");
}

void runLeftForward(bool clockwise, int velocity) {
  if (clockwise) {
    ledcWrite(LF_PWM[0],velocity);
    ledcWrite(LF_PWM[1], 0);
  }
  if (!clockwise) {
    ledcWrite(LF_PWM[0],0);
    ledcWrite(LF_PWM[1], velocity);
  }
}

void runLeftBackward(bool clockwise, int velocity) {
  if (clockwise) {
    ledcWrite(LB_PWM[0],velocity);
    ledcWrite(LB_PWM[1], 0);
  }
  if (!clockwise) {
    ledcWrite(LB_PWM[0],0);
    ledcWrite(LB_PWM[1], velocity);
  }
}

void runRightForward(bool clockwise, int velocity) {
  if (clockwise) {
    ledcWrite(RF_PWM[0],velocity);
    ledcWrite(RF_PWM[1], 0);
  }
  if (!clockwise) {
    ledcWrite(RF_PWM[0],0);
    ledcWrite(RF_PWM[1], velocity);
  }
}

void runRightBackward(bool clockwise, int velocity) {
  if (clockwise) {
    ledcWrite(RB_PWM[0],velocity);
    ledcWrite(RB_PWM[1], 0);
  }
  if (!clockwise) {
    ledcWrite(RB_PWM[0],0);
    ledcWrite(RB_PWM[1], velocity);
  }
}

// FUNGSI BUAT STOP MOTOR (OPSIONAL)
void stopWheel(int RPWM, int LPWM) {
  ledcWrite(RPWM, 0);
  ledcWrite(LPWM, 0);
}

void runWheel() {
  switch (_currentMotion) {
    case MAJU:
      Serial.println("Maju");
      forward();
      break;
    case MUNDUR:
      backward();
      Serial.println("Mundur");
      break;
    case KANAN:
      turnRight();
      Serial.println("Geser Kanan");
      break;
    case KIRI:
      turnLeft();
      Serial.println("Geser Kiri");
      break;
    case SERONG_KANAN_DEPAN:
      frontRight();
      Serial.println("Serong Kanan Depan");
      break;
    case SERONG_KANAN_BELAKANG:
      Serial.println("Serong Kanan Belakang");
      backRight();
      break;
    case SERONG_KIRI_BELAKANG:
      Serial.println("Serong Kiri Belakang");
      backLeft();
      break;
    case SERONG_KIRI_DEPAN:
      Serial.println("Serong Kiri Depan");
      frontLeft();
      break;
    case PUTAR_KANAN:
      rotateRight(dutyCycle[0]);
      Serial.println("Putar Kanan");
      break;
    case PUTAR_KIRI:
      rotateLeft(dutyCycle[0]);
      Serial.println("Putar Kiri");
      break;
    case BALIK_KANAN:
      rotateRight(dutyCycle[1]);
      delay(552.80);
      _currentMotion = STOP;
      break;
    case BALIK_KIRI:
      rotateLeft(dutyCycle[1]);
      delay(552.80);
      _currentMotion = STOP;
    case STOP:
      stopped();
//      Serial.println("Stop");
      break;
  }
}

void forward() {
  runLeftForward(true, speedFromJoystickLeft);
  runLeftBackward(true, speedFromJoystickLeft);
  runRightForward(false, speedFromJoystickLeft);
  runRightBackward(false, speedFromJoystickLeft);
}
  
void backward() {
  runLeftForward(false, speedFromJoystickLeft);
  runLeftBackward(false, speedFromJoystickLeft);
  runRightForward(true, speedFromJoystickLeft);
  runRightBackward(true, speedFromJoystickLeft);
}
  
void turnLeft() {
  runLeftForward(false, speedFromJoystickLeft);
  runLeftBackward(true, speedFromJoystickLeft);
  runRightForward(false, speedFromJoystickLeft);
  runRightBackward(true, speedFromJoystickLeft);
}
  
void turnRight() {
  runLeftForward(true, speedFromJoystickLeft);
  runLeftBackward(false, speedFromJoystickLeft);
  runRightForward(true, speedFromJoystickLeft);
  runRightBackward(false, speedFromJoystickLeft);
}
  
void rotateRight(int velocity) {
  runLeftForward(true, velocity);
  runLeftBackward(true, velocity);
  runRightForward(true, velocity);
  runRightBackward(true, velocity);
}
  
void rotateLeft(int velocity) {
  runLeftForward(false, velocity);
  runLeftBackward(false, velocity);
  runRightForward(false, velocity);
  runRightBackward(false, velocity);
}
  
void frontRight() { 
  runLeftForward(true, speedFromJoystickRight);
  stopWheel(LB_PWM[0], LB_PWM[1]);
  stopWheel(RF_PWM[0], RF_PWM[1]);
  runRightBackward(false, speedFromJoystickRight);
}
  
void backLeft() {
  runLeftForward(false, speedFromJoystickRight);
  stopWheel(LB_PWM[0], LB_PWM[1]);
  stopWheel(RF_PWM[0], RF_PWM[1]);
  runRightBackward(true, speedFromJoystickRight);
}
  
void frontLeft() {
  runLeftBackward(true, speedFromJoystickRight);
  runRightForward(false, speedFromJoystickRight);
  stopWheel(LF_PWM[0], LF_PWM[1]);
  stopWheel(RB_PWM[0], RB_PWM[1]);
}
  
void backRight() {
  runLeftBackward(false, speedFromJoystickRight);
  runRightForward(true, speedFromJoystickRight);
  stopWheel(LF_PWM[0], LF_PWM[1]);
  stopWheel(RB_PWM[0], RB_PWM[1]);
}
  
void stopped() {
  stopWheel(LF_PWM[0], LF_PWM[1]);
  stopWheel(RB_PWM[0], RB_PWM[1]);
  stopWheel(LB_PWM[0], LB_PWM[1]);
  stopWheel(RF_PWM[0], RF_PWM[1]);
}
