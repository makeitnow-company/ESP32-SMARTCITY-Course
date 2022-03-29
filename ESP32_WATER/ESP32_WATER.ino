#define WATERSENSOR 36

void setup(){
  Serial.begin(9600);
}

void loop(){
  int cds_value = analogRead(WATERSENSOR);
  Serial.println(cds_value);
  delay(300);
}
