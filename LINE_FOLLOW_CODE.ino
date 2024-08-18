#define IR_SENSOR_RIGHT  7
#define IR_SENSOR_LEFT  10
#define IR_SENSOR_MID 8
#define MOTOR_SPEED  150
const int GLED = 2;
const int RLED = 3;
const int laser = 13;

// Right motor pins
int rightMotorPin1 = 9;
int rightMotorPin2 = 11;

// Left motor pins
int leftMotorPin1 = 5;
int leftMotorPin2 = 6;

void setup() {
  TCCR0B = TCCR0B & B11111000 | B00000010; // Set timer for PWM

  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(laser, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  pinMode(IR_SENSOR_MID, INPUT);

  // Initialize motor and LED states
  rotateMotor(0, 0);
  digitalWrite(GLED, LOW);
  digitalWrite(RLED, HIGH);
  digitalWrite(laser, LOW);
}

void loop() {
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);
  int midIRSensorValue = digitalRead(IR_SENSOR_MID);

  if (midIRSensorValue == LOW) {
    // Stop both motors
    rotateMotor(0, 0);
  } else {
    // If none of the sensors detects a black line, go straight
    if (rightIRSensorValue == LOW && leftIRSensorValue == LOW) {
      rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
    }
    // If right sensor detects a black line, turn right
    else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW) {
      rotateMotor(-MOTOR_SPEED, -MOTOR_SPEED);
    }
    // If left sensor detects a black line, turn left
    else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH) {
      rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
    }
    // If both sensors detect a black line, stop
    else {
      rotateMotor(0, 0);
    }
  }

  // Control GLED and RLED based on whether any motor is moving
  bool motorsMoving = (digitalRead(leftMotorPin1) == HIGH || digitalRead(leftMotorPin2) == HIGH ||
                       digitalRead(rightMotorPin1) == HIGH || digitalRead(rightMotorPin2) == HIGH);
  
  if (motorsMoving) {
    digitalWrite(GLED, HIGH); // Turn GLED ON
    digitalWrite(RLED, LOW);  // Turn RLED OFF
    digitalWrite(laser, HIGH); // Turn laser ON
  } else {
    digitalWrite(GLED, LOW);  // Turn GLED OFF
    digitalWrite(RLED, HIGH); // Turn RLED ON
    digitalWrite(laser, LOW); // Turn laser OFF
  }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  // Control right motor
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else if (rightMotorSpeed > 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  // Control left motor
  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }
}
