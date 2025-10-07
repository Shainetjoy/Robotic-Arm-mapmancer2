#include <Servo.h>

Servo servoX1;   // Joystick1 X
Servo servoY1;   // Joystick1 Y
Servo servoY2;   // Joystick1 Y opposite
Servo servoX2;   // Joystick2 X

int angleX1, angleY1, angleX2;

void setup() {
  Serial.begin(9600);
  servoX1.attach(9);
  servoY1.attach(10);
  servoY2.attach(11);
  servoX2.attach(12);   // New servo pin
}

void loop() {
  if (Serial.available() >= 4) { // marker + 3 data bytes
    int marker = Serial.read();
    if (marker == 255) {
      angleX1 = Serial.read();
      angleY1 = Serial.read();
      angleX2 = Serial.read();

      servoX1.write(angleX1);
      servoY1.write(angleY1);
      servoY2.write(180 - angleY1); // opposite movement
      servoX2.write(angleX2);       // controlled by joystick2
    }
  }
}
