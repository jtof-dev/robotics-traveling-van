#include <PID_v1.h>

// setting up the physical pins
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
PID pid(&angle, &output, &setPoint, Kp, Ki, Kd, DIRECT)

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


// function to set motor speed, pos numbers to move forward and neg numbers to move backward
void setMotors(int speed) {
  if (speed > 0) {
    analogWrite(leftMotorIn1, speed);
    digitalWrite(leftMotorIn2, LOW);

    analogWrite(rightMotorIn1, speed);
    digitalWrite(rightMotorIn2, LOW);

    Serial.print("forward - speed: ");
    Serial.println(speed);
  } else if (speed < 0) {
    digitalWrite(leftMotorIn1, LOW);
    analogWrite(leftMotorIn2, abs(speed));

    digitalWrite(rightMotorIn1, LOW);
    analogWrite(rightMotorIn2, abs(speed));

    Serial.print("reverse - speed: ");
    Serial.println(abs(speed));
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


void loop() {
  // int potValue = analogRead(potPin);
  // Serial.print("\npotentiometer value: ");
  // Serial.println(potValue);

  angle = map(analogRead(potPin), 0, 1023, -900, 900) / 10.0;
  Serial.print("\nangle: ")
  Serial.println(angle)

  pid.Compute();

  delay(100);
}
