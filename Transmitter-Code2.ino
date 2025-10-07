int xAxis, yAxis;

void setup() {
  Serial.begin(9600);  // Bluetooth baud rate
}

void loop() {
  xAxis = analogRead(A0);                     // Joystick X-axis
  yAxis = analogRead(A1);                     // Joystick Y-axis

  int angleX = map(xAxis, 0, 1023, 0, 180);   // Servo angle 0–180
  int angleY = map(yAxis, 0, 1023, 0, 180);

  Serial.write(255);      // Start marker (helps sync receiver)
  Serial.write(angleX);   // Send X value
  Serial.write(angleY);   // Send Y value

  delay(20);              // 50 updates per second
}
this code is working 