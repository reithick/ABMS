int current = A0;
int senstivity = 185;
int adcvalue = 0;
int offsetvoltage = 2500;
double voltage = 0;
double ecurrent = 0;


void setup() {
  Serial.begin(9600);

}

void loop() {
  adcvalue = analogRead(current);
  voltage = (adcvalue / 1024.0) * 5000;
  ecurrent = ((voltage - offsetvoltage) / senstivity);
  Serial.println("adc=");
  Serial.println(adcvalue);
  Serial.println("\nvoltage=");
  Serial.println(voltage);
  Serial.println("\necurrent=");
  Serial.println(ecurrent);
}
