int xAxis;

void setup() {
  Serial.begin(9600); // Default HC-05 baud
}

void loop() {
  xAxis = analogRead(A0);                     // Read joystick
  int angle = map(xAxis, 0, 1023, 0, 180);    // Map to servo angle
  Serial.write(angle);                        // Send via Bluetooth
  delay(20);                                  // ~50Hz updates
}
