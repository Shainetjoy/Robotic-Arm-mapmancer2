#include <Servo.h>

Servo myServo;
int angle;

void setup() {
  Serial.begin(9600);   // Must match transmitter baud
  myServo.attach(9);    // Servo signal pin
}

void loop() {
  if (Serial.available()) {
    angle = Serial.read();   // Read joystick value from Bluetooth
    myServo.write(angle);    // Move servo accordingly
  }
}
