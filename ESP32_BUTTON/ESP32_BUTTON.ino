#define BUTTON 23

void setup() {
  pinMode(BUTTON,INPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(BUTTON);
  Serial.println(buttonState);
  delay(300);
}
