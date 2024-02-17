// Motor pin definitions
#define MOTOR_LEFT_PIN 2
#define MOTOR_RIGHT_PIN 3

// Sensor pin definition
#define SENSOR_PIN A0

// Sensor threshold
#define LINE_THRESHOLD 700 // Adjust as needed

// Motor speed
#define MOTOR_SPEED 200 // Adjust as needed

void setup() {
  // Set motor pins as output
  pinMode(MOTOR_LEFT_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_PIN, OUTPUT);
  
  // Set sensor pin as input
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  // Read sensor value
  int sensorValue = analogRead(SENSOR_PIN);

  // Calculate error
  int error = sensorValue - LINE_THRESHOLD;

  // Adjust motor speeds based on error
  int leftSpeed, rightSpeed;
  if (error > 0) {
    // If sensor detects the line, move straight
    leftSpeed = MOTOR_SPEED;
    rightSpeed = MOTOR_SPEED;
  } else {
    // If sensor does not detect the line, turn based on the error
    leftSpeed = MOTOR_SPEED - abs(error); // Decrease left motor speed
    rightSpeed = MOTOR_SPEED + abs(error); // Increase right motor speed
  }

  // Apply motor speeds
  analogWrite(MOTOR_LEFT_PIN, constrain(leftSpeed, 0, 255));
  analogWrite(MOTOR_RIGHT_PIN, constrain(rightSpeed, 0, 255));
}
