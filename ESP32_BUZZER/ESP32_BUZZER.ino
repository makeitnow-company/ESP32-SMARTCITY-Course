#define BUZZER 18

int freq = 5000;
int buzzerChannel =0;
int resolution = 8;

void setup(){
  Serial.begin(9600);
  ledcSetup(buzzerChannel,freq,resolution);
  ledcAttachPin(BUZZER, buzzerChannel);
}

void loop(){
  for (int i=480; i<=700; i++){
    Serial.println("UP");
    ledcWriteTone(buzzerChannel, i);
    delay(9);
  }
  
  for (int i=700; i>=480; i--){
    Serial.println("DOWN");
    ledcWriteTone(buzzerChannel, i);
    delay(9);
  }
}
