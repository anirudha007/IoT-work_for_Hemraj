int vout_pin = A0;
int vref_pin = A1;
void setup() {
  Serial.begin(9600);
}

void loop() {
  float readVoltage = analogRead(vout_pin);
  float readVoltage_1 = analogRead(vref_pin);
  float Vout = (readVoltage * 5 ) / 1023;
  float Vref = (readVoltage_1 * 5 ) / 1023;
  float current = (Vout-Vref)*160;
  Serial.println(current);
  // Serial.println(analogRead(A2));
  delay(1000);
}
