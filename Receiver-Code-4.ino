#include <Servo.h>

// --- Servo objects ---
Servo servoX1;   // Joystick1 X
Servo servoY1;   // Joystick1 Y
Servo servoY2;   // Joystick1 Y opposite
Servo servoX2;   // Joystick2 X

// --- Motor driver pins (L298N) ---
#define ENA 5   // Left motor speed (PWM)
#define IN1 6
#define IN2 7
#define ENB 9   // Right motor speed (PWM)
#define IN3 10
#define IN4 11

// --- Variables ---
int angleX1, angleY1, angleX2;
int carX, carY;

void setup() {
  Serial.begin(9600);

  // Attach servos
  servoX1.attach(3);
  servoY1.attach(4);
  servoY2.attach(8);
  servoX2.attach(12);

  // Setup motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Stop motors at start
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  if (Serial.available() >= 6) { // marker + 5 values
    int marker = Serial.read();
    if (marker == 255) {
      angleX1 = Serial.read();   // Servo1
      angleY1 = Serial.read();   // Servo2/3
      angleX2 = Serial.read();   // Servo4
      carX    = Serial.read();   // Car forward/back
      carY    = Serial.read();   // Car turning

      // --- Servo control ---
      servoX1.write(angleX1);
      servoY1.write(angleY1);
      servoY2.write(180 - angleY1);
      servoX2.write(angleX2);

      // --- Car control ---
      driveCar(carX, carY);
    }
  }
}

// --- Car drive function ---
void driveCar(int xVal, int yVal) {
  int deadzone = 15;
  int speedLeft = 0, speedRight = 0;

  // Forward / backward (using X axis)
  if (xVal > 127 + deadzone) {
    int speed = map(xVal, 128, 255, 0, 255);
    speedLeft = speed;
    speedRight = speed;

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

  } else if (xVal < 127 - deadzone) {
    int speed = map(xVal, 126, 0, 0, 255);
    speedLeft = speed;
    speedRight = speed;

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

  } else {
    // Stop if inside dead-zone
    speedLeft = 0;
    speedRight = 0;
  }

  // Turning adjustment (using Y axis)
  if (yVal > 127 + deadzone) {  // Right turn
    int adjust = map(yVal, 128, 255, 0, speedLeft);
    speedLeft = speedLeft;
    speedRight = max(0, speedRight - adjust);

  } else if (yVal < 127 - deadzone) { // Left turn
    int adjust = map(yVal, 126, 0, 0, speedRight);
    speedRight = speedRight;
    speedLeft = max(0, speedLeft - adjust);
  }

  // Apply motor speeds
  analogWrite(ENA, speedLeft);
  analogWrite(ENB, speedRight);
}
