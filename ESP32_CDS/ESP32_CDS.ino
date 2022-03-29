#define CDS 39

void setup(){
  Serial.begin(9600);
}

void loop(){
  int cds_value = analogRead(CDS);
  Serial.println(cds_value);
  delay(300);
}
