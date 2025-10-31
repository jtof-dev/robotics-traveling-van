const int POTENTIOMETER_PIN = A0;

const int LEFT_MOTOR_IN1 = 3;
const int LEFT_MOTOR_IN2 = 5;
const int RIGHT_MOTOR_IN1 = 6;
const int RIGHT_MOTOR_IN2 = 9;

void setup() {
  Serial.begin(9600);
  Serial.println("robot cart controller initialized");

  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);

  stopMotors();
}


void loop() {
  int potValue = analogRead(POTENTIOMETER_PIN);
  Serial.print("potentiometer value: ");
  Serial.println(potValue);

  // here, take the pot value and input into PID_v1.h
  // looks like it will take lots of tinkering to get right

  delay(100);
}


// function to set motor speed, pos numbers to move forward and neg numbers to move backward
void setMotors(int speed) {
  if (speed > 0) {
    analogWrite(LEFT_MOTOR_IN1, speed);
    digitalWrite(LEFT_MOTOR_IN2, LOW);
    analogWrite(RIGHT_MOTOR_IN1, speed);
    digitalWrite(RIGHT_MOTOR_IN2, LOW);
    Serial.print("forward - speed: ");
    Serial.println(speed);
    
  } else if (speed < 0) {
    digitalWrite(LEFT_MOTOR_IN1, LOW);
    analogWrite(LEFT_MOTOR_IN2, abs(speed));
    digitalWrite(RIGHT_MOTOR_IN1, LOW);
    analogWrite(RIGHT_MOTOR_IN2, abs(speed));
    Serial.print("reverse - speed: ");
    Serial.println(abs(speed));
    
  } else {
    stopMotors();
  }
}


void stopMotors() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
  Serial.println("motors stopped");
}
