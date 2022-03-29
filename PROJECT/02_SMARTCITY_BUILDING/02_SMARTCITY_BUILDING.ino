#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPLdbqVFzI7"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "nlSZTq9JuG-sI5-qmhxIsTkXEheM42oQ"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KT_GiGA_2G_makeitnow";
char pass[] = "makeitnow1";

#define BTN_ADMIN_CHECK 27 //관리자 확인 버튼

#define SHOCKSENSOR 32
#define SPARKSENSOR 33
#define BUZZER 18     

int freq = 5000;
int buzzerChannel=0;
int resolution = 8;

BlynkTimer timer;

boolean fireDetect;
boolean shockDetect;
boolean adminCheck;

void disasterEvent(){
  if(digitalRead(SPARKSENSOR)){
    fireDetect = true;
  }

  if(digitalRead(SHOCKSENSOR)){
    shockDetect = true;
  }
  
  if(fireDetect){
     Blynk.virtualWrite(V3, "화재 감지");    
  }else if(shockDetect){
     Blynk.virtualWrite(V4, "지진 감지");    
  }else{
     Blynk.virtualWrite(V3, "재난 감지 작동 중");
     Blynk.virtualWrite(V4, "재난 감지 작동 중");
  }

  if(fireDetect || shockDetect){
     ledcWriteTone(buzzerChannel, 500);
  }else{
     ledcWriteTone(buzzerChannel, 0);
  }
  
  if(digitalRead(BTN_ADMIN_CHECK)){
    shockDetect = false;
    fireDetect = false;
  }
}

void setup()
{
  Serial.begin(9600);
  ledcSetup(buzzerChannel,freq,resolution);
  ledcAttachPin(BUZZER,buzzerChannel);
  pinMode(SPARKSENSOR, INPUT);
  pinMode(SHOCKSENSOR, INPUT);
  pinMode(BTN_ADMIN_CHECK, INPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(200L, disasterEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}
