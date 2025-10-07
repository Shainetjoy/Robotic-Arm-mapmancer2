// Joystick 1 → Servo1, Servo2/3
int xAxis1, yAxis1; 

// Joystick 2 → Servo4
int xAxis2;         

// Joystick 3 → Car control
int carX, carY;

void setup() {
  Serial.begin(9600);  // match baud with receiver
}

void loop() {
  // --- Joystick 1 (Servos 1,2,3) ---
  xAxis1 = analogRead(A0); 
  yAxis1 = analogRead(A1);

  int angleX1 = map(xAxis1, 0, 1023, 0, 180);
  int angleY1 = map(yAxis1, 0, 1023, 0, 180);

  // --- Joystick 2 (Servo 4) ---
  xAxis2 = analogRead(A2);
  int angleX2 = map(xAxis2, 0, 1023, 0, 180);

  // --- Joystick 3 (Car control) ---
  // NOTE: X controls forward/backward, Y controls left/right
  carX = analogRead(A3);  // forward/backward
  carY = analogRead(A4);  // turning

  int carXscaled = carX / 4;   // 0–1023 → 0–255
  int carYscaled = carY / 4;

  // --- Send all values ---
  Serial.write(255);         // Start marker
  Serial.write(angleX1);     // Servo1
  Serial.write(angleY1);     // Servo2/3
  Serial.write(angleX2);     // Servo4
  Serial.write(carXscaled);  // Car forward/backward
  Serial.write(carYscaled);  // Car turning

  delay(20);                 // ~50 Hz update rate
}
