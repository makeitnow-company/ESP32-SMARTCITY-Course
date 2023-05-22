#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "********"
#define BLYNK_DEVICE_NAME "********"
#define BLYNK_AUTH_TOKEN "*********"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "WiFi 이름을 입력해 주세요";
char pass[] = "WiFi 비밀번호를 입력해 주세요";

#define BTN_SECURITY_MODE 23 //보안 모드 전환 버튼
#define BTN_ADMIN_CHECK 27 //관리자 확인 버튼
#define HALLSENSOR 15
#define PROXSENSOR 34

#define DHTPIN 14        
#define DHTTYPE DHT11   

#define DUST_LED_PIN 13
#define DUST_MEASURE_PIN 35 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C

BlynkTimer timer;
DHT dht(DHTPIN, DHTTYPE);                
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int voMeasured;
float calcVoltage, dustDensity, temp, humidity;

boolean securityMode;
boolean doorOpen;
boolean windowOpen;
boolean adminCheck;

void securityEvent()
{  
  if(!digitalRead(HALLSENSOR)){
     windowOpen = true;
  }

  if(analogRead(PROXSENSOR) > 4000){
    doorOpen = true;
  }

  if(digitalRead(BTN_SECURITY_MODE)){
    securityMode = !securityMode;
    windowOpen = false;
    doorOpen = false;
  }

  if(securityMode){
    if(windowOpen){
      Blynk.virtualWrite(V2, "창문 침입 감지");    
    }else if(doorOpen){
      Blynk.virtualWrite(V1, "출입문 침입 감지");    
    }else{
      Blynk.virtualWrite(V2, "창문 보안 작동중");    
      Blynk.virtualWrite(V1, "출입문 보안 작동중");    
    }
  }else{
      Blynk.virtualWrite(V1, "출입문 보안 해제 해제중"); 
      Blynk.virtualWrite(V2, "창문 보안 해제중"); 
  }
  
  if(digitalRead(BTN_ADMIN_CHECK)){
    windowOpen = false;
    doorOpen = false;
  }
}

void dht11Event()
{  
  temp = dht.readTemperature();
  humidity = dht.readHumidity();      
  Blynk.virtualWrite(V7, temp);
  Blynk.virtualWrite(V8, humidity);
}

void dustEvent(){
  digitalWrite(DUST_LED_PIN, LOW);
  delayMicroseconds(280);
  voMeasured = analogRead(DUST_MEASURE_PIN);
  delayMicroseconds(40);
  digitalWrite(DUST_LED_PIN, HIGH);
  delayMicroseconds(9680);
  calcVoltage = voMeasured * (3.3 / 4095);
  dustDensity = 170 * calcVoltage - 0.1;
  Blynk.virtualWrite(V9, dustDensity);
}

void displayOLED(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("HUMI:");
  display.print(humidity);
  display.setCursor(0,15);
  display.print("TEMP:");
  display.print(temp);
  display.setCursor(0,30);
  display.print("DUST:");
  display.print(dustDensity);
  display.display();
}

void setup()
{
  Serial.begin(9600);
   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  dht.begin();        
  pinMode(DUST_LED_PIN, OUTPUT);
  pinMode(HALLSENSOR, INPUT);
  pinMode(BTN_SECURITY_MODE, INPUT);
  pinMode(BTN_ADMIN_CHECK, INPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(200L, securityEvent);
  timer.setInterval(1000L, dht11Event);
  timer.setInterval(1000L, dustEvent);
  timer.setInterval(500L, displayOLED);

  display.setTextSize(2);
  display.setTextColor(WHITE,0);
}

void loop()
{
  Blynk.run();
  timer.run();
}