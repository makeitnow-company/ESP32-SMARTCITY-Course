#include <Adafruit_NeoPixel.h>

#define PIN 19
#define NUMPIXELS 9

Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

void setup() {
  pixels.begin();
}

void loop() {
  for(int i=0; i<NUMPIXELS; i+=2) { 
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
  }
  for(int i=1; i<NUMPIXELS; i+=2){
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
  }
  pixels.show();
}
