#include <PID_v1.h>

// setting up the physical pins
// for the motor pins, they have to be PWM pins
const int potPin = A0;
const int leftMotorIn1 = 3;
const int leftMotorIn2 = 5;
const int rightMotorIn1 = 6;
const int rightMotorIn2 = 9;

double output, scaleFactor;
double setPoint = 0;

// very preliminary values for Kp, Ki, and Kd. will require lots of tinkering
double Kp = 10.0;
double Ki = 0.1;
double Kd = 0.5;

double angle;
double motorCommand;

// the PID controller expects an angle input, so my calculated angle will work as the input
PID pid(&angle, &output, &setPoint, Kp, Ki, Kd, DIRECT);


// function to set motor speed using PWM values, pos numbers to move forward and neg numbers to move backward
void setMotors() {
  // the output from the PID controller is between 0 and 255, so the direction is chosen based on whether angle is pos or neg
  if (angle > 0) {
    analogWrite(leftMotorIn1, output);
    digitalWrite(leftMotorIn2, LOW);

    analogWrite(rightMotorIn1, output);
    digitalWrite(rightMotorIn2, LOW);

    Serial.print("forward - PWM value: ");
    Serial.println(output);
  } else if (angle < 0) {
    digitalWrite(leftMotorIn1, LOW);
    analogWrite(leftMotorIn2, output);

    digitalWrite(rightMotorIn1, LOW);
    analogWrite(rightMotorIn2, output);

    Serial.print("reverse - PWM value: ");
    Serial.println(output);
  } else {
    stopMotors();
  }
}


void stopMotors() {
  digitalWrite(leftMotorIn1, LOW);
  digitalWrite(leftMotorIn2, LOW);

  digitalWrite(rightMotorIn1, LOW);
  digitalWrite(rightMotorIn2, LOW);
  
  Serial.println("motors stopped");
}


// the setup function that initializes pins and starts holding the brakes
void setup() {
  Serial.begin(9600);

  pinMode(leftMotorIn1, OUTPUT);
  pinMode(leftMotorIn2, OUTPUT);
  pinMode(rightMotorIn1, OUTPUT);
  pinMode(rightMotorIn2, OUTPUT);

  stopMotors();

  Serial.println("robot cart controller initialized");
}


void loop() {
  angle = map(analogRead(potPin), 0, 1023, -900, 900) / 10.0;
  Serial.print("angle: ");
  Serial.println(angle);

  // throw in the angle and get out a value between 0 and 255 (by default). the arduino by default only sends 8-bit PWM values (0 - 255)
  pid.Compute();
  
  setMotors();

  delay(100);
}
