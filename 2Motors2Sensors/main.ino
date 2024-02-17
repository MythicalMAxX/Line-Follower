// Motor pin definitions
#define MOTOR_LEFT_PIN 2
#define MOTOR_RIGHT_PIN 3

// Sensor pin definitions
#define SENSOR_LEFT_PIN A0
#define SENSOR_RIGHT_PIN A1

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
  pinMode(SENSOR_RIGHT_PIN, INPUT);
}

void loop() {
  // Read sensor values
  int sensorLeft = analogRead(SENSOR_LEFT_PIN);
  int sensorRight = analogRead(SENSOR_RIGHT_PIN);

  // Calculate error
  int error = sensorLeft - sensorRight;

  // Adjust motor speeds based on error
  int leftSpeed, rightSpeed;
  if (error > 0) {
    // If sensorLeft detects more light (meaning it's away from the line), turn right
    leftSpeed = MOTOR_SPEED;
    rightSpeed = MOTOR_SPEED - abs(error);
  } else if (error < 0) {
    // If sensorRight detects more light (meaning it's away from the line), turn left
    leftSpeed = MOTOR_SPEED - abs(error);
    rightSpeed = MOTOR_SPEED;
  } else {
    // If both sensors detect similar light levels, move straight
    leftSpeed = MOTOR_SPEED;
    rightSpeed = MOTOR_SPEED;
  }

  // Apply motor speeds
  analogWrite(MOTOR_LEFT_PIN, constrain(leftSpeed, 0, 255));
  analogWrite(MOTOR_RIGHT_PIN, constrain(rightSpeed, 0, 255));
}
