// Constants for PID control
#define KP 1.0 // Proportional gain
#define KD 0.1 // Derivative gain
#define KI 0.01 // Integral gain

// Define sensor pins
#define LEFT_SENSOR_PIN A0
#define CENTER_SENSOR_PIN A1
#define RIGHT_SENSOR_PIN A2
#define LEFT_OUTER_SENSOR_PIN A3
#define RIGHT_OUTER_SENSOR_PIN A4

// Define motor control pins
#define MOTOR_FL_PIN 2
#define MOTOR_FR_PIN 3
#define MOTOR_BL_PIN 4
#define MOTOR_BR_PIN 5

// Define target position (center of the line)
#define TARGET_POSITION 512 // Assuming analog sensor values range from 0 to 1023

// Variables for PID control
float error = 0;
float lastError = 0;
float integral = 0;
float derivative = 0;

// Variables for motor speeds
int motorFLSpeed = 0;
int motorFRSpeed = 0;
int motorBLSpeed = 0;
int motorBRSpeed = 0;

void setup() {
  // Initialize sensor pins as input
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(CENTER_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);
  pinMode(LEFT_OUTER_SENSOR_PIN, INPUT);
  pinMode(RIGHT_OUTER_SENSOR_PIN, INPUT);

  // Initialize motor pins as output
  pinMode(MOTOR_FL_PIN, OUTPUT);
  pinMode(MOTOR_FR_PIN, OUTPUT);
  pinMode(MOTOR_BL_PIN, OUTPUT);
  pinMode(MOTOR_BR_PIN, OUTPUT);
}

void loop() {
  // Read sensor values
  int leftSensor = analogRead(LEFT_SENSOR_PIN);
  int centerSensor = analogRead(CENTER_SENSOR_PIN);
  int rightSensor = analogRead(RIGHT_SENSOR_PIN);
  int leftOuterSensor = analogRead(LEFT_OUTER_SENSOR_PIN);
  int rightOuterSensor = analogRead(RIGHT_OUTER_SENSOR_PIN);

  // Calculate error (distance from the target position)
  error = (leftSensor * -2) + (leftOuterSensor * -1) + (centerSensor * 0) + (rightSensor * 1) + (rightOuterSensor * 2);

  // Update integral and derivative
  integral += error;
  derivative = error - lastError;
  lastError = error;

  // Calculate PID control output
  float output = (KP * error) + (KI * integral) + (KD * derivative);

  // Adjust motor speeds based on PID output
  motorFLSpeed = 255 - output;
  motorFRSpeed = 255 + output;
  motorBLSpeed = 255 - output;
  motorBRSpeed = 255 + output;

  // Ensure motor speeds are within limits
  motorFLSpeed = constrain(motorFLSpeed, 0, 255);
  motorFRSpeed = constrain(motorFRSpeed, 0, 255);
  motorBLSpeed = constrain(motorBLSpeed, 0, 255);
  motorBRSpeed = constrain(motorBRSpeed, 0, 255);

  // Apply motor speeds
  analogWrite(MOTOR_FL_PIN, motorFLSpeed);
  analogWrite(MOTOR_FR_PIN, motorFRSpeed);
  analogWrite(MOTOR_BL_PIN, motorBLSpeed);
  analogWrite(MOTOR_BR_PIN, motorBRSpeed);
}
