// KONDISI JALAN RBOT
enum Motion {
    MAJU,
    MUNDUR,
    KIRI,
    KANAN,
    PUTAR_KANAN,
    PUTAR_KIRI,
    SERONG_KANAN_DEPAN,
    SERONG_KIRI_DEPAN,
    SERONG_KANAN_BELAKANG,
    SERONG_KIRI_BELAKANG,
    BALIK_KANAN,
    BALIK_KIRI,
    STOP
  };

Motion _currentMotion = STOP;

void initPS() {
  Ps3.attachOnConnect(onConnect);
//  Ps3.attach(notify);
  Ps3.begin("02:02:02:02:02:02");
  Serial.print("Ready.");
}

void readJoystickLeft() {
  lX = constrain(X_LEFT_DATA, -127, 127);
  lY = constrain(Y_LEFT_DATA, -127, 127);
  float rad = atan2(lY, lX);
  angleLeft = rad * TO_DEG;
  //if (angle < 0) {
    //angle = map(angle, -179, -1, 181, 359);
  //}
  powerLeft = sqrt(lX * lX + lY * lY);
  speedLimitLeft = constrain(powerLeft, 0, 127); // NILAI TERKECIL DARI POWER DI JOYSTIVCK (SUDUT 90 DEG) = 127
  speedFromJoystickLeft = map(speedLimitLeft, 0, 127, 0, 200); // MAP POWER JOYSTICK KE RPM MOTOR
}

void readJoystickRight() {
  rX = constrain(X_RIGHT_DATA, -127, 127);
  rY = constrain(Y_RIGHT_DATA, -127, 127);
  float rad = atan2(rY, rX);
  angleRight = rad * TO_DEG;
  powerRight = sqrt(rX * rX + rY * rY);
  speedLimitRight = constrain(powerRight, 0, 127); // NILAI TERKECIL DARI POWER DI JOYSTIVCK (SUDUT 90 DEG) = 127
  speedFromJoystickRight = map(speedLimitRight, 0, 127, 0, 200); // MAP POWER JOYSTICK KE RPM MOTOR
}

// EVENT BUAT RODA
void wheelEvent() {
  readJoystickLeft();
  readJoystickRight();
    
  if ((Y_LEFT_DATA > -15 && Y_LEFT_DATA < 15) && (X_LEFT_DATA < 15 && X_LEFT_DATA > -15) &&
      (Y_RIGHT_DATA >- 15 && Y_RIGHT_DATA < 15) && (X_RIGHT_DATA < 15 && X_RIGHT_DATA > -15)) {
    _currentMotion = STOP;
    
  } else {
    if (Y_RIGHT_DATA < -20 || Y_RIGHT_DATA > 20 || X_RIGHT_DATA > 20 || X_RIGHT_DATA < -20) {
      if (angleRight >= 0 && angleRight < 90) {
        _currentMotion = SERONG_KANAN_BELAKANG;
      }
      if (angleRight >= 90 && angleRight < 180) {
        _currentMotion = SERONG_KIRI_BELAKANG;
      }
      if (angleRight >= -180 && angleRight < -90) {
        _currentMotion = SERONG_KIRI_DEPAN;
      }
      if (angleRight >= -90 && angleRight < 0) {
        _currentMotion = SERONG_KANAN_DEPAN;
      }
    } else {
      if (angleLeft >= 45 && angleLeft < 135) {
        _currentMotion = MUNDUR;
      }
      if (angleLeft >= -135 && angleLeft < -45) {
        _currentMotion = MAJU;
      }
      if ((angleLeft >= -45 && angleLeft < 0) || (angleLeft >= 0 && angleLeft < 45)) {
        _currentMotion = KANAN;
      }
      if ((angleLeft < -135 && angleLeft >= -180) || (angleLeft <= 180 && angleLeft >= 135)) {
        _currentMotion = KIRI;
      }
    }
  }
 
  if (R1_LONG_PRESS) {
    _currentMotion = PUTAR_KANAN;
  }
  if (L1_LONG_PRESS) {
    _currentMotion = PUTAR_KIRI;
  }
  if (R2_PRESSED) {
    _currentMotion = BALIK_KANAN;
  }
  if (L2_PRESSED) {
    _currentMotion = BALIK_KIRI;
  }
  if (R1_RELEASE) {
    _currentMotion = STOP;
  }
  if (L1_RELEASE) {
    _currentMotion = STOP;
  }
}

// EVENT BUAT SERVO
void servoEvent() {
    if( Ps3.event.button_down.triangle ){
        //Serial.println("Started pressing the triangle button");
        Serial.println("servo vertikal ke atas");                
        servo1cont(false,2);
        delayMicroseconds(50);
    }
    
    if( Ps3.event.button_up.triangle ){
        //Serial.println("Released the triangle button");
        Serial.println("servo vertikal stop");    
        servo1stop();
        delayMicroseconds(50);
    }

    // tombol x servo vertikal CCW
    if( Ps3.event.button_down.cross ){
        //Serial.println("Started pressing the cross button");
        //delay(250);
        Serial.println("servo vertikal turun");       
        servo1cont(true,2);
        delayMicroseconds(50);
    }
    if( Ps3.event.button_up.cross ){
        //Serial.println("Released the cross button");
        //servo2stop();
        Serial.println("servo stop");     
        servo1stop();
        delayMicroseconds(50);
    }

    
    // tombol kotak for servo horizontal buka
    if( Ps3.event.button_down.square ){
        //Serial.println("Started pressing the square button");
        Serial.println("servo horizontal ke buka");
        servo2cont(false,2);
        delayMicroseconds(50);
    }
    if( Ps3.event.button_up.square ){
        Serial.println("servo horizontal stop");
        servo2stop();
        delayMicroseconds(50);
    }
    
    // tombol bulet for servo horizontal tutup
    if( Ps3.event.button_down.circle ){
        //Serial.println("Started pressing the circle button");
        Serial.println("servo horizontal ke tutup");   
        servo2cont(true,2);
        delayMicroseconds(50);
    }
    if( Ps3.event.button_up.circle ){
        //Serial.println("Released the circle button");
        //delay(250);
        Serial.println("servo horizontal stop");
        servo2stop();
        delayMicroseconds(50);
    }

    // tombol pad kanan for servo90
    if( Ps3.event.button_down.right ){
        if(flagxservo90==0){
          Serial.println("servo 90 derajat, flagservo:");
          Serial.print(flagxservo90);
          
          servoRotate.write(150);
          flagxservo90=1;
          //delay(250);
        }
        else if(flagxservo90==1){
          Serial.println("servo 0 derajat, flagservo:");
          Serial.print(flagxservo90);
          
          servoRotate.write(0);
          flagxservo90=0;
        }
        delay(50);
    }
    if( Ps3.event.button_up.right ){
        Serial.println("Released the right button");
        delay(50);
    }

    // tombol atas bawah buat atur speed motor
    // tombol atas for speed up
    if( Ps3.event.button_down.up ){
      toggle = true;
      delayMicroseconds(50);
    }
    if( Ps3.event.button_up.up ){
      toggle = false;
      delayMicroseconds(50);
    }
}

void notify() {
  if (Y_LEFT + X_LEFT > 2) {
    readJoystickLeft();
    Serial.print("Moved the left stick:");
    Serial.print(" x="); Serial.print(lX, DEC);
    Serial.print(" y="); Serial.print(lY, DEC);
    Serial.print("   "); Serial.print(angleLeft);
    Serial.print("   "); Serial.print(speedLimitLeft);
    Serial.print("   "); Serial.print(speedFromJoystickLeft);
    Serial.print("   "); Serial.print(powerLeft);
    Serial.println();
  }
  if (R1_LONG_PRESS) {
    Serial.println("R1 PRESSED");
  }
  if (L1_LONG_PRESS) {
    Serial.println("L1 PRESSED");
  }
  if (R1_RELEASE) {
    Serial.println("R1 RELEASE");
  }
  if (L1_RELEASE) {
    Serial.println("L1 RELEASE");
  }
}

void onConnect() {
  Serial.println("Connected!.");
}
