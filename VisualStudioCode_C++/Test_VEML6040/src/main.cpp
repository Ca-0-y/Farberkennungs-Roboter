/*

The MIT License (MIT)

Copyright (c) 2015 thewknd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "Arduino.h"
#include "Wire.h"
#include "veml6040.h"

VEML6040 RGBWSensor;
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 23 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
#define RED_LED 0
int raw_red;
int raw_green;
int raw_blue;
int raw_white;
int RED = 0;
int GREEN = 0;
int BLUE = 0;
int YELLOW = 0;
int WHITE = 0;
int BLACK = 0;


void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  if(!RGBWSensor.begin()) {
    Serial.println("ERROR: couldn't detect the sensor");
    while(1){}
  }
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.
pinMode(RED_LED, OUTPUT);
digitalWrite(RED_LED, LOW);
  pixels.begin();

 
 

  /*
   * init RGBW sensor with: 
   *  - 320ms integration time
   *  - auto mode
   *  - color sensor enable
   */
    
	RGBWSensor.setConfiguration(VEML6040_IT_320MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
	
  delay(1500);
  Serial.println("Vishay VEML6040 RGBW color sensor auto mode example");
  Serial.println("CCT: Correlated color temperature in \260K");
  Serial.println("AL: Ambient light in lux");
  delay(1500);
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 255, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
 
  raw_red = RGBWSensor.getRed()/255;  
  raw_green = RGBWSensor.getGreen()/255;  
  raw_blue = RGBWSensor.getBlue()/255;  
  raw_white = RGBWSensor.getWhite()/255; 

 if ((59 <= raw_red) & (raw_red <= 69) & (67 <= raw_white) & (raw_white <= 75)) {
  RED = 1;
  Serial.print("Color Sensor found: Red\n");
  }
 if ((27 <= raw_red) & (raw_red <= 29) & (44 <= raw_white) & (raw_white <= 47)) {
  GREEN = 1;
  Serial.print("Color Sensor found: Green\n");
  }
 if ((29 <= raw_red) & (raw_red <= 33) & (48 <= raw_white) & (raw_white <= 55)) {
  BLUE = 1;
  Serial.print("Color Sensor found: Blue\n");
  }
 if ((86 <= raw_red) & (raw_red <= 88) & (106 <= raw_white) & (raw_white <= 115)) {
  YELLOW = 1;
  Serial.print("Color Sensor found: Yellow\n");
  }
 if ((22 <= raw_red) & (raw_red <= 25) & (36 <= raw_white) & (raw_white <= 39)) {
  BLACK = 1;
  Serial.print("Color Sensor found: Black\n");
  }
 if ((88 <= raw_red) & (raw_red <= 92) & (120 <= raw_white) & (raw_white <= 128)) {
  WHITE = 1;
  Serial.print("Color Sensor found: White\n");
 }
  delay(3000);
}