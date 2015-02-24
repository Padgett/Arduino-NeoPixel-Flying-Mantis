// Functions for the Flying Mantis project

// Check our switch for fire
boolean check_switch() {
  int buttonState = digitalRead(FIRESWITCHPIN);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    return true;  
  } else {
    return false;
  }
}

void fire_show() {
  randomCyclePalette(body, firecolor, firecolorcount, 1, 15);
  randomCyclePalette(arms, firecolor, firecolorcount, 1, 15);
  randomCyclePalette(head, firecolor, firecolorcount, 1, 15);
  randomCyclePalette(wingleg, firecolor, firecolorcount, 1, 15);
}

// Fill the dots one after the other with a color
void colorWipe(Adafruit_NeoPixel &strip, uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(Adafruit_NeoPixel &strip, uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(strip, (i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// This could use some cleanup
void rainbowPalette(Adafruit_NeoPixel &strip, uint32_t c[], int count, int cycles, int wait) {
  int j, ci = 0;

  for(j=0; j<cycles; j++) {
    for(uint16_t k=0; k<strip.numPixels(); k++) {
      for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, c[ci]);
        ci++;
        if (ci >= count) {
          ci = 0;
        }
      }
      strip.show();
      delay(wait);
      ci++;
      if (ci >= count) {
        ci = 0;
      }
    }
  }
}

void randomCyclePalette(Adafruit_NeoPixel &strip, uint32_t c[], int count, int cycles, int wait) {
  int j;

  for(j=0; j<cycles; j++) {
    for(uint16_t i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, c[random(count)]);
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(Adafruit_NeoPixel &strip, uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(strip, ((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(Adafruit_NeoPixel &strip, uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(Adafruit_NeoPixel &strip, uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel(strip, (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// fade_up - fade up to the given color
void fade_up(Adafruit_NeoPixel &strip, int num_steps, int wait, int R, int G, int B) {
  uint8_t i;
  uint16_t j;
  
  for (i=0; i<num_steps; i++) {
    for(j=0; j<strip.numPixels(); j++) {
       strip.setPixelColor(j, strip.Color(R * i / num_steps, G * i / num_steps, B * i / num_steps));
    }  
  strip.show();
  delay(wait);
  }  
} // fade_up

// clearstrip - set strip to black
void clearstrip(Adafruit_NeoPixel &strip) {
  for(uint16_t j=0; j<strip.numPixels(); j++) {
    strip.setPixelColor(j, 0);
  }
  strip.show();
} // clearstrip

// cycle
void cycle(Adafruit_NeoPixel &strip, uint32_t c[], int count, int cycles, int wait) {
  uint8_t cs, i;
  
  for (cs=0;cs<cycles;cs++) {
    for (i=0;i<count;i++) {
      for(uint16_t j=0; j<strip.numPixels(); j++) {
         strip.setPixelColor(j, c[i]);
      }
      strip.show();
      delay(wait);
    }
  }
} // cycle

// sparks - Random sparks - just one LED on at a time!
void sparks (Adafruit_NeoPixel &strip, uint32_t c[], int count, int cycles, int wait) {
  int j;
  uint16_t i;
  
  //Clear the strip first
  clearstrip(strip);
  
  for(j=0;j<cycles;j++) {
    i = random(strip.numPixels());
    strip.setPixelColor(i, color[random(count)]);
    strip.show();
    delay(wait);
    strip.setPixelColor(i, 0);
    strip.show();
  }
} //sparks

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel &strip, byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
