// Motor pin definitions
#define MOTOR_FL_PIN 2 // Front-left motor
#define MOTOR_FR_PIN 3 // Front-right motor
#define MOTOR_BL_PIN 4 // Back-left motor
#define MOTOR_BR_PIN 5 // Back-right motor

// Sensor pin definition
#define SENSOR_PIN A0

// Sensor threshold
#define LINE_THRESHOLD 700 // Adjust as needed

// Motor speed
#define MOTOR_SPEED 200 // Adjust as needed

void setup() {
  // Set motor pins as output
  pinMode(MOTOR_FL_PIN, OUTPUT);
  pinMode(MOTOR_FR_PIN, OUTPUT);
  pinMode(MOTOR_BL_PIN, OUTPUT);
  pinMode(MOTOR_BR_PIN, OUTPUT);

  // Set sensor pin as input
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  // Read sensor value
  int sensorValue = analogRead(SENSOR_PIN);

  // Calculate error
  int error = sensorValue - LINE_THRESHOLD;

  // Adjust motor speeds based on error
  int leftSpeed = MOTOR_SPEED + error;
  int rightSpeed = MOTOR_SPEED - error;

  // Apply motor speeds
  // Front motors
  analogWrite(MOTOR_FL_PIN, constrain(leftSpeed, 0, 255));
  analogWrite(MOTOR_FR_PIN, constrain(rightSpeed, 0, 255));
  // Back motors
  analogWrite(MOTOR_BL_PIN, constrain(leftSpeed, 0, 255));
  analogWrite(MOTOR_BR_PIN, constrain(rightSpeed, 0, 255));
  
  // Delay for stability
  delay(10);
}
