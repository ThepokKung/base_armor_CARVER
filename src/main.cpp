#include <Arduino.h>
#include <FastLED.h>

// Deinfine variables
#define NUM_LEDS 126
#define DATA_PIN 16

CRGB leds[NUM_LEDS]; // Array to hold the LED data
// put function declarations here:


void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:

  fill_solid(leds, NUM_LEDS, CRGB::Red); // Fill the LEDs with red color
}

// put function definitions here:
void setled(){
  
}
