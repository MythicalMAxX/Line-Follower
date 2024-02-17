// Motor pin definitions
#define MOTOR_LEFT_PIN 2
#define MOTOR_RIGHT_PIN 3

// Sensor pin definitions
#define SENSOR_LEFT_PIN A0
#define SENSOR_RIGHT_PIN A1

// PID constants
#define KP 0.1 // Proportional gain
#define KI 0.01 // Integral gain
#define KD 0.05 // Derivative gain

// Setpoint (desired position)
#define SETPOINT 512 // Middle of the sensor range

// Motor speed limits
#define MIN_SPEED 0
#define MAX_SPEED 255

// PID variables
double errorSum = 0; // Integral of the error
int lastError = 0; // Previous error
int baseSpeed = 150; // Base speed for both motors

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
  int error = SETPOINT - (sensorLeft + sensorRight) / 2;

  // Calculate PID terms
  double proportional = KP * error;
  errorSum += error;
  double integral = KI * errorSum;
  double derivative = KD * (error - lastError);
  lastError = error;

  // Calculate motor speeds
  int leftSpeed = baseSpeed + proportional + integral + derivative;
  int rightSpeed = baseSpeed - proportional - integral - derivative;

  // Apply speed limits
  leftSpeed = constrain(leftSpeed, MIN_SPEED, MAX_SPEED);
  rightSpeed = constrain(rightSpeed, MIN_SPEED, MAX_SPEED);

  // Apply motor speeds
  analogWrite(MOTOR_LEFT_PIN, leftSpeed);
  analogWrite(MOTOR_RIGHT_PIN, rightSpeed);
}
