// Define motor control pins
#define MOTOR_FL_PIN 2 // Front-left motor
#define MOTOR_FR_PIN 3 // Front-right motor
#define MOTOR_BL_PIN 4 // Back-left motor
#define MOTOR_BR_PIN 5 // Back-right motor

// Define sensor pins
#define SENSOR_FL_PIN A0 // Front-left sensor
#define SENSOR_FR_PIN A1 // Front-right sensor
#define SENSOR_BL_PIN A2 // Back-left sensor
#define SENSOR_BR_PIN A3 // Back-right sensor

// Thresholds for sensor readings
#define LINE_THRESHOLD 500 // Adjust as needed

void setup() {
  // Set motor control pins as output
  pinMode(MOTOR_FL_PIN, OUTPUT);
  pinMode(MOTOR_FR_PIN, OUTPUT);
  pinMode(MOTOR_BL_PIN, OUTPUT);
  pinMode(MOTOR_BR_PIN, OUTPUT);

  // Set sensor pins as input
  pinMode(SENSOR_FL_PIN, INPUT);
  pinMode(SENSOR_FR_PIN, INPUT);
  pinMode(SENSOR_BL_PIN, INPUT);
  pinMode(SENSOR_BR_PIN, INPUT);
}

void loop() {
  // Read sensor values
  int sensorFL = analogRead(SENSOR_FL_PIN);
  int sensorFR = analogRead(SENSOR_FR_PIN);
  int sensorBL = analogRead(SENSOR_BL_PIN);
  int sensorBR = analogRead(SENSOR_BR_PIN);

  // Line-following logic
  if (sensorFL > LINE_THRESHOLD && sensorFR > LINE_THRESHOLD) {
    // Move forward
    moveForward();
  } else if (sensorFL > LINE_THRESHOLD && sensorFR < LINE_THRESHOLD) {
    // Turn right
    turnRight();
  } else if (sensorFL < LINE_THRESHOLD && sensorFR > LINE_THRESHOLD) {
    // Turn left
    turnLeft();
  } else {
    // Stop
    stopMotors();
  }
}

// Function to move forward
void moveForward() {
  digitalWrite(MOTOR_FL_PIN, HIGH);
  digitalWrite(MOTOR_FR_PIN, HIGH);
  digitalWrite(MOTOR_BL_PIN, HIGH);
  digitalWrite(MOTOR_BR_PIN, HIGH);
}

// Function to turn left
void turnLeft() {
  digitalWrite(MOTOR_FL_PIN, LOW);
  digitalWrite(MOTOR_FR_PIN, HIGH);
  digitalWrite(MOTOR_BL_PIN, HIGH);
  digitalWrite(MOTOR_BR_PIN, LOW);
}

// Function to turn right
void turnRight() {
  digitalWrite(MOTOR_FL_PIN, HIGH);
  digitalWrite(MOTOR_FR_PIN, LOW);
  digitalWrite(MOTOR_BL_PIN, LOW);
  digitalWrite(MOTOR_BR_PIN, HIGH);
}

// Function to stop
void stopMotors() {
  digitalWrite(MOTOR_FL_PIN, LOW);
  digitalWrite(MOTOR_FR_PIN, LOW);
  digitalWrite(MOTOR_BL_PIN, LOW);
  digitalWrite(MOTOR_BR_PIN, LOW);
}
