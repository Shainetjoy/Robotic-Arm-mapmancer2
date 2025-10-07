int xAxis1, yAxis1; // Joystick 1
int xAxis2;         // Joystick 2

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Joystick 1
  xAxis1 = analogRead(A0); 
  yAxis1 = analogRead(A1);

  int angleX1 = map(xAxis1, 0, 1023, 0, 180);
  int angleY1 = map(yAxis1, 0, 1023, 0, 180);

  // Joystick 2
  xAxis2 = analogRead(A2);
  int angleX2 = map(xAxis2, 0, 1023, 0, 180);

  // Send all 3 angles over Bluetooth
  Serial.write(255);       // Start marker
  Serial.write(angleX1);   // Servo1 X
  Serial.write(angleY1);   // Servo2/3 Y
  Serial.write(angleX2);   // Servo4 X
  delay(20);
}
