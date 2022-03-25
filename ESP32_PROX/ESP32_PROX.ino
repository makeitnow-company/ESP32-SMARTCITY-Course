#define PROXSENSOR 34

void setup(){
  Serial.begin(9600);
}

void loop(){
  int value = analogRead(PROXSENSOR);
  Serial.println(value);
  delay(300);
}
