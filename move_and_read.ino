int ENABLE_PIN = 8;
int M1_STEP_PIN = 2;
int M1_DIR_PIN = 5;
int M2_STEP_PIN = 3;
int M2_DIR_PIN = 6;

// Distance Sensor Pin
int analogPin = A2;

// Variables
int sensorValue = 0;
float voltage = 0.0;

void setup() {
  // Initialize serial communication for sensor readings
  Serial.begin(9600);
  // Configure stepper motor pins as outputs
  pinMode(M1_STEP_PIN, OUTPUT);
  pinMode(M1_DIR_PIN, OUTPUT);
  pinMode(M2_STEP_PIN, OUTPUT);
  pinMode(M2_DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(analogPin, INPUT);
  
  // Enable the stepper drivers (LOW typically enables)
  digitalWrite(ENABLE_PIN, LOW);
  Serial.println("System Ready - Stepper + Distance Sensor");
  Serial.println("Step, Voltage, Raw Value");
}

void loop() {
  // Set direction forward
  digitalWrite(M1_DIR_PIN, LOW);

  // Rotate forward 200 steps (one full rotation for most steppers)
  for (int i = 0; i < 100; i++) {
    // Step both motors
    digitalWrite(M1_STEP_PIN, HIGH);
    delay(50);
    digitalWrite(M1_STEP_PIN, LOW);
    delay(50);
    // Take distance reading every 10 steps
    readAndPrintDistance();
  }

  delay(100);

  // Set direction reverse
  digitalWrite(M1_DIR_PIN, HIGH);
  
  // Rotate backward 200 steps
  for (int i = 0; i < 100; i++) {
    // Step both motors
    digitalWrite(M1_STEP_PIN, HIGH);
    delay(50);
    digitalWrite(M1_STEP_PIN, LOW);
    delay(50);
    readAndPrintDistance();
  }

}

// Function to read sensor and print data
void readAndPrintDistance() {
  sensorValue = analogRead(analogPin);
  voltage = (sensorValue * 5.0) / 1023.0;   // (Digital back to analog: what was the voltage)

  // Print formatted data to serial monitor
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 5);
  Serial.print(" V | Raw: ");
  Serial.println(sensorValue);
}
