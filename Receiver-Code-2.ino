#include <Servo.h>

Servo servoX;   // Joystick X
Servo servoY1;  // Joystick Y (normal)
Servo servoY2;  // Joystick Y (opposite)

int angleX, angleY;

void setup() {
  Serial.begin(9600);
  servoX.attach(9);     // Servo for X-axis
  servoY1.attach(10);   // Y1 normal
  servoY2.attach(11);   // Y2 opposite
}

void loop() {
  if (Serial.available() >= 3) {
    int marker = Serial.read();
    if (marker == 255) {
      angleX = Serial.read();
      angleY = Serial.read();

      servoX.write(angleX);          // X-axis control
      servoY1.write(angleY);         // Normal Y
      servoY2.write(180 - angleY);   // Opposite Y
    }
  }
}
