const int POTENTIOMETER_PIN = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("Potentiometer reader initialized. Turn the knob to see values change.");
}

void loop() {
  int sensorValue = 0;

  sensorValue = analogRead(POTENTIOMETER_PIN);
  Serial.print("Analog Value: ");
  Serial.println(sensorValue);

  delay(100);
}
