#include <Arduino.h>
#include <PID_v1.h>

// setting up the physical pins
// for the motor pins, they have to be PWM pins
const int potPin = A0;
const int encoderPinA = 2;
const int encoderPinB = 3;
const int leftMotorIn1 = 5;
const int leftMotorIn2 = 6;
// const int rightMotorIn1 = 6;
// const int rightMotorIn2 = 9;

double output;
double mappedOutput;
double scaleFactor;
// use this variable to set what angle the pot reads while the pendulum is perfectly balanced
const double setPoint = -6.0;
const double mappedBound = 70;

// define constants for the encoder
const int countsPerRevolution = 520 * 4.0;
int maxDistanceMM = 12.f * 25.4f;
volatile long encoderCount = 0;
long robotDistanceMM = 0;
// int isRobotWithinMaxDistance = 1;

int motorSerial = 0;

// define constants for correlating distance and encoder values
const float wheelDiameterMM = 65.0;
const float wheelCircumferenceMM = PI * wheelDiameterMM;
const float mmPerCount = wheelCircumferenceMM / countsPerRevolution;

// very preliminary values for Kp, Ki, and Kd. will require lots of tinkering
const double Kp = 15.0;
const double Ki = 0.1;
const double Kd = 0.5;

double angle;
double motorCommand;

// the PID controller expects an angle input, so my calculated angle will work as the input
PID pid(&angle, &output, &setPoint, Kp, Ki, Kd, REVERSE);


// function to set motor speed using PWM values, pos numbers to move forward and neg numbers to move backward
void setMotors() {
  // the output from the PID controller is between 0 and 255, so the direction is chosen based on whether angle is pos or neg
  if (mappedOutput > 0) {
    analogWrite(leftMotorIn1, mappedOutput);
    digitalWrite(leftMotorIn2, LOW);

    // analogWrite(rightMotorIn1, mappedOutput);
    // digitalWrite(rightMotorIn2, LOW);

    // Serial.print("forward - PWM value: ");
    // Serial.println(output);
  } else if (mappedOutput < 0) {
    digitalWrite(leftMotorIn1, LOW);
    analogWrite(leftMotorIn2, abs(mappedOutput));

    // digitalWrite(rightMotorIn1, LOW);
    // analogWrite(rightMotorIn2, mappedOutput);

    // Serial.print("reverse - PWM value: ");
    // Serial.println(output);
  } else {
    coastMotors();
  }
}


void stopMotors() {
  digitalWrite(leftMotorIn1, HIGH);
  digitalWrite(leftMotorIn2, HIGH);

  // digitalWrite(rightMotorIn1, HIGH);
  // digitalWrite(rightMotorIn2, HIGH);

  if (motorSerial == 0) {
    motorSerial = 1;
    Serial.println("motors braking");
  }
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

    angle = map(analogRead(potPin), 0, 1023, -900, 900) / 10.0;
    Serial.print("angle: ");
    Serial.println(angle);

  if (fabs(robotDistanceMM) < maxDistanceMM) {

    if (abs(angle - setPoint) > 55) {
      stopMotors();
      maxDistanceMM = 0;
      Serial.println("pendulum tipped past 45deg");
    }

    // throw in the angle and get out a value between 0 and 255 (by default). the arduino by default only sends 8-bit PWM values (0 - 255)
    pid.Compute();

    // Serial.print("PID controller output: ");
    // Serial.println(output);
    // Serial.print("\n");

    Serial.print("distance travelled: ");
    Serial.println(robotDistanceMM);
  
    // map the output range onto [70, 255] 
    // if (output > setPoint) {
    //   mappedOutput = map(output, setPoint, 255, mappedBound, 255);
    // } 
    // else if (output < setPoint) {
    //   mappedOutput = map(output, -255, setPoint, -255, -mappedBound);
    // }
    
    // if (abs(output) < 5) {
    //   mappedOutput = 0;
    // }

    Serial.print("mapped output PWM value: ");
    Serial.println(mappedOutput);
    Serial.print("\n\n");
    // snap low values to 0 to avoid extra oscillations
    if (abs(output) < abs(setPoint) + 2) {
      mappedOutput = 0;
    };

    setMotors();
  } else {
    stopMotors();
    delay(2000);
  }
}
