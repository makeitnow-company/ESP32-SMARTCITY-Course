#define DUST_LED_PIN 13
#define DUST_MEASURE_PIN 35 

void setup()
{
  Serial.begin(9600);
  pinMode(DUST_LED_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(DUST_LED_PIN, LOW);
  delayMicroseconds(280);
  int voMeasured = analogRead(DUST_MEASURE_PIN);
  delayMicroseconds(40);
  digitalWrite(DUST_LED_PIN, HIGH);
  delayMicroseconds(9680);
  float calcVoltage = voMeasured * (3.3 / 4095);
  float dustDensity = 170 * calcVoltage - 0.1;
  if(dustDensity<=0) dustDensity = 0;
  Serial.print("dust : ");
  Serial.print(dustDensity);
  Serial.println("ug/m3");
}
