#define LED_RED 4
#define LED_YELLOW 5
#define LED_GREEN 12 

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

void loop() {
  digitalWrite(LED_RED,HIGH);
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_GREEN,LOW);
  delay(1000);
  digitalWrite(LED_RED,LOW);
  digitalWrite(LED_YELLOW,HIGH);
  digitalWrite(LED_GREEN,LOW);
  delay(1000);
  digitalWrite(LED_RED,LOW);
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_GREEN,HIGH);
  delay(1000);
}
