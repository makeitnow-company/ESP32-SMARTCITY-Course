#define WATERSENSOR 36

void setup(){
  Serial.begin(9600);
}

void loop(){
  int water_value = analogRead(WATERSENSOR);
  Serial.println(water_value);
  delay(300);
}
