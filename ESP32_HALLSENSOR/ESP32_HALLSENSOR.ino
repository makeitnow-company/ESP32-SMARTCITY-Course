#define HALLSENSOR 15

void setup() {
  pinMode(HALLSENSOR,INPUT);
  Serial.begin(9600);
}

void loop() {
  if(!digitalRead(HALLSENSOR)){
    Serial.println("자성감지");
    delay(300);
  }
}
