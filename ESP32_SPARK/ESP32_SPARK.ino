#define SPARKSENSOR 33

void setup(){
  pinMode(SPARKSENSOR, INPUT);
  Serial.begin(9600);
}

void loop(){
  if(digitalRead(SPARKSENSOR)){
    Serial.println("FIRE");
    delay(300);
  }
}
