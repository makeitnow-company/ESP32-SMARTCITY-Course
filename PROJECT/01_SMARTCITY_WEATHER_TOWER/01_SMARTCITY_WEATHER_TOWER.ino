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

#define CDS 39
#define WATER 36

BlynkTimer timer;

boolean rain;

void weatherEvent()
{  
  int cds_value = analogRead(CDS);
  int water_value = analogRead(WATER);
  if(water_value > 2000){
    rain = true;
  }else{
    rain = false;
  }
  Blynk.virtualWrite(V5, cds_value/1000);
  Blynk.virtualWrite(V6, rain);
}


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(200L, weatherEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}
