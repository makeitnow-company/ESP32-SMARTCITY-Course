#define SHOCKSENSOR 32

void setup(){
  pinMode(SHOCKSENSOR, INPUT);
  Serial.begin(9600);
}

void loop(){
  if(digitalRead(SHOCKSENSOR)){
    Serial.println("충격감지");
    delay(300);
  }
}
