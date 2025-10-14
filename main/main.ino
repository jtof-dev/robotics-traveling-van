const int POTENTIOMETER_PIN = A0;

const int LEFT_MOTOR_IN1 = 3;
const int LEFT_MOTOR_IN2 = 5;
const int RIGHT_MOTOR_IN1 = 6;
const int RIGHT_MOTOR_IN2 = 9;

const int DEAD_ZONE_LOW = 492;
const int DEAD_ZONE_HIGH = 532;


void setup() {
  Serial.begin(9600);
  Serial.println("Robot Cart Controller Initialized");

  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);

  stopMotors();
}


void loop() {
  int potValue = analogRead(POTENTIOMETER_PIN);

  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);

  delay(100);
}


void setMotors(int speed) {
  if (speed > 0) {
    analogWrite(LEFT_MOTOR_IN1, speed);
    digitalWrite(LEFT_MOTOR_IN2, LOW);
    analogWrite(RIGHT_MOTOR_IN1, speed);
    digitalWrite(RIGHT_MOTOR_IN2, LOW);
    Serial.print("Forward - Speed: ");
    Serial.println(speed);
    
  } else if (speed < 0) {
    digitalWrite(LEFT_MOTOR_IN1, LOW);
    analogWrite(LEFT_MOTOR_IN2, abs(speed));
    digitalWrite(RIGHT_MOTOR_IN1, LOW);
    analogWrite(RIGHT_MOTOR_IN2, abs(speed));
    Serial.print("Reverse - Speed: ");
    Serial.println(abs(speed));
    
  } else {
    stopMotors();
  }
}


/**
 * @brief Stops all motors by setting both control pins LOW (brake).
 */
void stopMotors() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
  Serial.println("Motors Stopped");
}

