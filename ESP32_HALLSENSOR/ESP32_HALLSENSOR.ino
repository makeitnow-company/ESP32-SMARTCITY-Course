#define HALLSENSOR 15

void setup() {
  pinMode(HALLSENSOR,INPUT);
  Serial.begin(9600);
}

void loop() {
  if(!digitalRead(HALL_SENSOR)){
    Serial.println("자성감지");
    delay(300);
  }
}
