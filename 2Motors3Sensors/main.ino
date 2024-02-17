// Motor pin definitions
#define MOTOR_LEFT_PIN 2
#define MOTOR_RIGHT_PIN 3

// Sensor pin definitions
#define SENSOR_LEFT_PIN A0
#define SENSOR_CENTER_PIN A1
#define SENSOR_RIGHT_PIN A2

// Sensor threshold
#define LINE_THRESHOLD 700 // Adjust as needed

// Motor speed
#define MOTOR_SPEED 200 // Adjust as needed

void setup() {
  // Set motor pins as output
  pinMode(MOTOR_LEFT_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_PIN, OUTPUT);
  
  // Set sensor pins as input
  pinMode(SENSOR_LEFT_PIN, INPUT);
  pinMode(SENSOR_CENTER_PIN, INPUT);
  pinMode(SENSOR_RIGHT_PIN, INPUT);
}

void loop() {
  // Read sensor values
  int sensorLeft = analogRead(SENSOR_LEFT_PIN);
  int sensorCenter = analogRead(SENSOR_CENTER_PIN);
  int sensorRight = analogRead(SENSOR_RIGHT_PIN);

  // Calculate error
  int error = sensorCenter - LINE_THRESHOLD;

  // Adjust motor speeds based on error
  int leftSpeed, rightSpeed;
  if (error > 0) {
    // If the center sensor detects the line, move straight
    leftSpeed = MOTOR_SPEED;
    rightSpeed = MOTOR_SPEED;
  } else {
    // If the center sensor doesn't detect the line, use the left and right sensors to adjust direction
    if (sensorLeft > LINE_THRESHOLD) {
      // Turn left
      leftSpeed = 0;
      rightSpeed = MOTOR_SPEED;
    } else if (sensorRight > LINE_THRESHOLD) {
      // Turn right
      leftSpeed = MOTOR_SPEED;
      rightSpeed = 0;
    } else {
      // If none of the sensors detect the line, stop
      leftSpeed = 0;
      rightSpeed = 0;
    }
  }

  // Apply motor speeds
  analogWrite(MOTOR_LEFT_PIN, leftSpeed);
  analogWrite(MOTOR_RIGHT_PIN, rightSpeed);
}
