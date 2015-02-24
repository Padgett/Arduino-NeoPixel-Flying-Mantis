// Requires Adafruit's Neopixel Library
#include <Adafruit_NeoPixel.h>

// Our Fire Switch
#define FIRESWITCHPIN 12

//Setup our Body section
#define BODYPIN 3
#define BODYLEN 890 // 890
#define BODYBRIGHTNESS 64 // 1/4 Brightness

//Setup our Arm Section
#define ARMPIN 5
#define ARMLEN 150
#define ARMBRIGHTNESS 64 // 1/4 Brightness

//Setup our Head Section
#define HEADPIN 7
#define HEADLEN 60
#define HEADBRIGHTNESS 255 // Full Brightness

//Setup our Wing and Leg Section
#define WINGLEGPIN 9
#define WINGLEGLEN 150
#define WINGLEGBRIGHTNESS 128 // 1/2 Brightness

Adafruit_NeoPixel body = Adafruit_NeoPixel(BODYLEN, BODYPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel arms = Adafruit_NeoPixel(ARMLEN, ARMPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel head = Adafruit_NeoPixel(HEADLEN, HEADPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wingleg = Adafruit_NeoPixel(WINGLEGLEN, WINGLEGPIN, NEO_GRB + NEO_KHZ800);

uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
int      colorswitch = 0, // First color selection
         colorcount = 5,
         firecolorcount = 9,
         i;
         
uint32_t color[]  = {0x464E1D, 0x6D6359, 0xBFB9A1, 0x141411, 0x948F58}; // Our Color Palette
uint32_t firecolor[]  = {0x000000, 0x990000, 0xFF2206, 0xFF4800, 0xFF7500, 0xFF8000, 0x000000, 0xAA0000, 0xFF0000}; // Our Fire Color Palette
uint32_t prevTime;

void setup() {
  pinMode(FIRESWITCHPIN, INPUT);
  
  // Initialize all pixels to our first color
  body.begin();
  body.setBrightness(BODYBRIGHTNESS);
  fade_up(body, 150, 20, 255, 255, 255);
  
  arms.begin();
  arms.setBrightness(ARMBRIGHTNESS);
  for (int i=0; i < arms.numPixels(); i++) {
    arms.setPixelColor(i, 0xFFFFFF);
  }
  arms.show();
  
  head.begin();
  head.setBrightness(HEADBRIGHTNESS);
  for (int i=0; i < head.numPixels(); i++) {
    head.setPixelColor(i, 0xFFFFFF);
  }
  head.show();
  
  wingleg.begin();
  wingleg.setBrightness(WINGLEGBRIGHTNESS);
  for (int i=0; i < wingleg.numPixels(); i++) {
    wingleg.setPixelColor(i, 0xFFFFFF);
  }
  wingleg.show();
  
  //delay(10000); //Hold for 10 seconds
}

void loop() {
  if (check_switch()) {
    fade_up(body, 50, 30, 255, 0, 0);
    fade_up(arms, 50, 30, 255, 0, 0);
    fade_up(head, 50, 30, 255, 0, 0);
    fade_up(wingleg, 50, 30, 255, 0, 0);
    while (check_switch()) {
      fire_show();
    }
  } /* else {
    clearstrip(body);
  }
*/ 

  // Test
  //randomCyclePalette(body, color, colorcount, 50, 110);
  //rainbowPalette(body, color, colorcount, 1, 100);
  
  //rainbowPalette(body, color, colorcount, 1, 100);
  rainbowPalette(arms, color, colorcount, 2, 100);
  rainbowPalette(head, color, colorcount, 5, 100);
  rainbowPalette(wingleg, color, colorcount, 2, 100);

  // Sparks
  for (i=0;i<=2000;i++) {
    sparks(body, color, colorcount, 1, 10);
    sparks(arms, color, colorcount, 1, 10);
    sparks(head, color, colorcount, 1, 10);
    sparks(wingleg, color, colorcount, 1, 10);
  }

  // Random Cycle
  for (i=0;i<=2000;i++) {
    randomCyclePalette(body, color, colorcount, 1, 30);
    randomCyclePalette(arms, color, colorcount, 1, 30);
    randomCyclePalette(head, color, colorcount, 1, 30);
    randomCyclePalette(wingleg, color, colorcount, 1, 30);
  }

  //colorWipe(body, body.Color(255, 0, 0), 50); // Red
  //colorWipe(body, body.Color(0, 255, 0), 50); // Green
  //colorWipe(body, body.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  //theaterChase(wing, wing.Color(127, 127, 127), 50); // White
  //theaterChase(wing, wing.Color(127,   0,   0), 50); // Red
  //theaterChase(wing, wing.Color(  0,   0, 127), 50); // Blue

  //fade_up(body, 50, 50, 255, 255, 0);
  //rainbow(body, 20);
  //rainbowCycle(body, 20);
  //theaterChaseRainbow(body, 50);
}
