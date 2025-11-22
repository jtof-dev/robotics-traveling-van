#include <Arduino.h>
#include <PID_v1.h>

// setting up the physical pins
// for the motor pins, they have to be PWM pins
const int potPin = A0;
const int encoderPinA = A1;
const int encoderPinB = A2;
const int leftMotorIn1 = 3;
const int leftMotorIn2 = 5;
// const int rightMotorIn1 = 6;
// const int rightMotorIn2 = 9;

double output, scaleFactor;
double setPoint = 0;

// define constants for the encoder
const int countsPerRevolution = 520 * 4.0;
const int maxDistanceMM = 457;
volatile long encoderCount = 0;
long robotDistanceMM = 0;
// int isRobotWithinMaxDistance = 1;

// define constants for correlating distance and encoder values
const float wheelDiameterMM = 65.0;
const float wheelCircumferenceMM = PI * wheelCircumferenceMM;
const float mmPerCount = wheelCircumferenceMM / countsPerRevolution;

// very preliminary values for Kp, Ki, and Kd. will require lots of tinkering
double Kp = 4.9;
double Ki = 0.1;
double Kd = 0.4;

double angle;
double motorCommand;

// the PID controller expects an angle input, so my calculated angle will work as the input
PID pid(&angle, &output, &setPoint, Kp, Ki, Kd, REVERSE);


// function to set motor speed using PWM values, pos numbers to move forward and neg numbers to move backward
void setMotors() {
  // the output from the PID controller is between 0 and 255, so the direction is chosen based on whether angle is pos or neg
  if (output > 0) {
    analogWrite(leftMotorIn1, abs(output));
    digitalWrite(leftMotorIn2, LOW);

    // analogWrite(rightMotorIn1, abs(output));
    // digitalWrite(rightMotorIn2, LOW);

    Serial.print("forward - PWM value: ");
    Serial.println(output);
  } else if (output < 0) {
    digitalWrite(leftMotorIn1, LOW);
    analogWrite(leftMotorIn2, abs(output));

    // digitalWrite(rightMotorIn1, LOW);
    // analogWrite(rightMotorIn2, abs(output));

    Serial.print("reverse - PWM value: ");
    Serial.println(output);
  } else {
    stopMotors();
  }
}


void stopMotors() {
  digitalWrite(leftMotorIn1, HIGH);
  digitalWrite(leftMotorIn2, HIGH);

  // digitalWrite(rightMotorIn1, HIGH);
  // digitalWrite(rightMotorIn2, HIGH);
  
  Serial.println("motors braking");
}


// this funciton probably won't be used, but the function exists in the motor driver so I mapped it here
void coastMotors() {
  digitalWrite(leftMotorIn1, LOW);
  digitalWrite(leftMotorIn2, LOW);

  // digitalWrite(rightMotorIn1, LOW);
  // digitalWrite(rightMotorIn2, LOW);

  Serial.println("motors coasting");
}


// two interrupt functions for faster encoder reading
void isr_encoderDirectionA() {
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    encoderCount--;
  } else {
    encoderCount++;
  }
}


void isr_encoderDirectionB() {
  if (digitalRead(encoderPinB) == digitalRead(encoderPinA)) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}


float getDistanceTraveledMM() {
  cli();
  long currentCount = encoderCount;
  sei();

  return (float)currentCount * mmPerCount;
}


// the setup function that initializes pins and starts holding the brakes
void setup() {
  Serial.begin(9600);

  pinMode(leftMotorIn1, OUTPUT);
  pinMode(leftMotorIn2, OUTPUT);
  // pinMode(rightMotorIn1, OUTPUT);
  // pinMode(rightMotorIn2, OUTPUT);

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), isr_encoderDirectionA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), isr_encoderDirectionB, CHANGE);

  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-255, 255);

  stopMotors();

  Serial.println("robot cart controller initialized");
}


void loop() {
  robotDistanceMM = getDistanceTraveledMM();

  if (fabs(robotDistanceMM < maxDistanceMM)) {
    angle = map(analogRead(potPin), 0, 1023, -900, 900) / 10.0;
    Serial.print("angle: ");
    Serial.println(angle);

    // throw in the angle and get out a value between 0 and 255 (by default). the arduino by default only sends 8-bit PWM values (0 - 255)
    pid.Compute();

    Serial.print("PID controller output: ");
    Serial.println(output);
  
    // now, check if the robot is within a certain distance of the max distance and add some extra motor power if so (for future)
    
    // possibly, multiply or divide the output by a constant since four motor drivers are reading from the same pins
    // output = output / 4;

    setMotors();

    delay(500);
  } else {
    stopMotors();
    delay(2000);
  }
}
