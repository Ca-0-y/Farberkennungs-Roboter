#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <HCSR04.h>
#include <L293.h>

#include "Buzzer.h"
#include "Wire.h"
#include "veml6040.h"

#define triggerPin 4  // HC_SR04_TRIGGER_PIN
#define echoPin 35    // HC_SR04_ECHO_PIN
#define LED_RED 0
#define LED_GREEN 2
#define LED_YELLOW 15
#define PIEZO 16
#define SK6812 23
#define NUMPIXELS 1   // Number of Pixels
#define DELAYVAL 500  // Time (in milliseconds) to pause between pixels
#define VEML_SCL 22
#define VEML_SDA 21
#define forwardPinA 26  // L293_1A
#define reversePinA 27  // L293_2A
#define speedPinA 14    // L293_1_2EN
#define forwardPinB 25  // L293_3A
#define reversePinB 33  // L293_4A
#define speedPinB 32    // L293_3_4EN
#define use_standalone

/*Farbsensor*/
VEML6040 RGBWSensor;
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

/*SK6812*/
Adafruit_NeoPixel pixels(NUMPIXELS, SK6812, NEO_GRBW);

/*Motortreiber*/
#ifdef use_standalone

// make a new istance of the L293 library and call it "motor"
// then show what are the pins used to control speed, to tell the motor to go forward and to tell the motor to go reverse
L293 motorA(speedPinA, forwardPinA, reversePinA);
L293 motorB(speedPinB, forwardPinB, reversePinB);

#else

// if you using the twoWire version of the library only one pin is required to tell the direction
// the forwardPin can do the job of the directionPin in this case
L293_twoWire motor(speedPin, forwardPin);

#endif

/*Farbsensor*/
int raw_red;
int raw_green;
int raw_blue;
int raw_white;
//int ColorRed = 0;
//int ColorGreen = 0;
//int ColorBlue = 0;
//int ColorYellow = 0;
//int ColorWhite = 0;
//int ColorBlack = 0;
int color;
int colors [3] = {0, 0, 0};
int colorIndex = 0;

/*Motortreiber*/
int MotorIsRunning;

/*Ultraschallsensor*/
float temperature = 15;
double maxDistance = 10.00;

/*Buzzer*/
Buzzer::Melody_t myMelody1{
    .nbNotes = 3,
    .duration = {800, 400, 800},
    .frequency = {C5_NOTE_FREQ, A4_NOTE_FREQ, B4_NOTE_FREQ}};
Buzzer::Melody_t myMelody2{
    .nbNotes = 6,
    .duration = {400, 600, 400, 600, 400, 600},
    .frequency = {A4_NOTE_FREQ, C4_NOTE_FREQ, A4_NOTE_FREQ, C4_NOTE_FREQ, A4_NOTE_FREQ, C4_NOTE_FREQ}};
Buzzer::Melody_t myMelody3{
    .nbNotes = 3,
    .duration = {400, 400, 800},
    .frequency = {D4_NOTE_FREQ, E4_NOTE_FREQ, G4_NOTE_FREQ}};
Buzzer myBuzzer;

void sk6812() {
    pixels.clear();  // Set all pixel colors to 'off'

    // The first NeoPixel in a strand is #0, second is 1, all the way up
    // to the count of pixels minus one.
    for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(255, 255, 0, 0));

        pixels.show();  // Send the updated pixel colors to the hardware.

        delay(DELAYVAL);  // Pause before next pass through loop
    }
}

void ENGINE_CONDITION() {
    if (MotorIsRunning == 0) {
        motorA.forward(90);
        motorB.forward(90);
    }
    if (MotorIsRunning == 1) {
        motorA.forward(90);
        motorB.stop();
    }
    if (MotorIsRunning == 2) {
        motorA.stop();
        motorB.forward(90);
    }
    if(MotorIsRunning == 3){
        motorA.stop();
        motorB.stop();
    }
    if (MotorIsRunning == 4){
        for( int i = 0; i < 3; i++){
            motorA.forward(90);
            motorB.forward(90);
            delay(1000);
            motorA.stop();
            motorB.stop();
            delay(100);
            motorA.back(90);
            motorB.back(90);
            delay(1000);
            motorA.stop();
            motorB.stop();
        }
    }
}

void GET_DISTANCE() {
    double* distances = HCSR04.measureDistanceCm(temperature);
    if (*(distances) <= maxDistance) {
        MotorIsRunning = 3;
    }
    else{
      MotorIsRunning = 0;
    }
}

void COLOR_CODE(){

  Serial.println("Current colors:");

  for (int i = 0; i <3; i++) {
    Serial.printf("%d, ", colors[i]);
  }
  Serial.println();

  if(colorIndex == 3){
    colorIndex = 0;
    colors[0] = 0;
    colors[1] = 0;
    colors[2] = 0;
  }
  if(colorIndex == 0){
    colors[colorIndex] = color;
    colorIndex++;
    Serial.println("color1");
    
  }
  else if(color != colors[colorIndex-1]){
    colors[colorIndex] = color;
    colorIndex++;
    Serial.println("color2");
  }/*
  for(int i = 0; i<1; i++){
    if(colors[i] = 1){
        if(colors[i+1] = 2){
            if(colors[i+2] = 1){
              MotorIsRunning = 4;
            }
            if(colors[i+2] = 3){
                //????????????????????????????
            }
        }
        if(colors[i+1] = 3){
            if(colors[i+2] = 1){
              for(i = 0; i<3; i++){ 
                digitalWrite(LED_GREEN, HIGH);
                delay(300);
                digitalWrite(LED_GREEN, LOW);
                digitalWrite(LED_RED, HIGH);
                delay(300);
                digitalWrite(LED_RED, LOW);
                digitalWrite(LED_YELLOW, HIGH);
                delay(300);
                digitalWrite(LED_YELLOW, LOW);
              }
            }
            if(colors[i+2] = 2){
                MotorIsRunning = 3;
                //Geruchssensor!!!!!!!!!!!!!!
            }
        }
    }
    if(colors[i] = 2){
        if(colors[i+1] = 1){
            if(colors[i+2] = 2){
                myBuzzer.setMelody(&myMelody1);
                myBuzzer.step();
            }
            if(colors[i+2] = 3){
                myBuzzer.setMelody(&myMelody2);
                myBuzzer.step();
            }
        }
        if(colors[i+1] = 3){
            if(colors[i+2] = 1){
                myBuzzer.setMelody(&myMelody3);
                myBuzzer.step();
            }
            if(colors[i+2] = 2){
                
            }
        }
    }
    if(colors[i] = 3){
        if(colors[i+1] = 2){
            if(colors[i+2] = 1){

            }
            if(colors[i+2] = 3){

            }
        }
        if(colors[i+1] = 1){
            if(colors[i+2] = 3){

            }
            if(colors[i+2] = 2){
                MotorIsRunning = 3;
                delay(3000);
            }
        }
    }
  }*/
}

void setup() {
    Serial.begin(9600);
    Wire.begin();
    if (!RGBWSensor.begin()) {
        Serial.println("ERROR: couldn't detect the sensor");
        while (1) {
        }
    }
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif
    // END of Trinket-specific code.
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    digitalWrite(LED_RED, LOW);
    pixels.begin();

    /*
     * init RGBW sensor with:
     *  - 320ms integration time
     *  - auto mode
     *  - color sensor enable
     */

    RGBWSensor.setConfiguration(VEML6040_IT_320MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
    sk6812();
    HCSR04.begin(triggerPin, echoPin);
    myBuzzer.init(PIEZO);
    
}

void loop() {

    GET_DISTANCE();

  if(MotorIsRunning != 3){  
    raw_red = RGBWSensor.getRed() / 255;
    raw_green = RGBWSensor.getGreen() / 255;
    raw_blue = RGBWSensor.getBlue() / 255;
    raw_white = RGBWSensor.getWhite() / 255;

    // Serial.print(" CCT: ");
    // Serial.print(RGBWSensor.getCCT());
    // Serial.print(" AL: ");
    // Serial.println(RGBWSensor.getAmbientLight());

     //Serial.println(raw_red);
    // Serial.println(raw_green);
    // Serial.println(raw_blue);
     //Serial.println(raw_white);

    if ((27 <= raw_red) & (raw_red <= 29) & (44 <= raw_white) & (raw_white <= 47)) {
        color = 2;
        digitalWrite(LED_GREEN, HIGH);
        Serial.print("Color Sensor found: Green\n");
        
    } else {
        /// ColorGreen = 0;
        digitalWrite(LED_GREEN, LOW);
    }
    if ((29 <= raw_red) & (raw_red <= 33) & (48 <= raw_white) & (raw_white <= 55)) {
        // ColorBlue = 1;
        Serial.print("Color Sensor found: Blue\n");
     
    } else {
        // ColorBlue = 0;
    }
    if ((59 <= raw_red) & (raw_red <= 69) & (67 <= raw_white) & (raw_white <= 75)) {
        digitalWrite(LED_RED, HIGH);
        color = 1;
        Serial.print("Color Sensor found: Red\n");
       
    } else {
        // ColorRed = 0;
        digitalWrite(LED_RED, LOW);
    }
    if ((86 <= raw_red) & (raw_red <= 88) & (106 <= raw_white) & (raw_white <= 115)) {
        digitalWrite(LED_YELLOW, HIGH);
        color = 3;
        Serial.print("Color Sensor found: Yellow\n");
    } else {
        // ColorYellow = 0;
        digitalWrite(LED_YELLOW, LOW);
    }
    if ((88 <= raw_red) & (raw_red <= 92) & (120 <= raw_white) & (raw_white <= 128)) {
        
        Serial.print("Color Sensor found: White\n");
        if (MotorIsRunning == 2 | MotorIsRunning == 0) {
            MotorIsRunning = 1;
        }
    }
    if ((22 <= raw_red) & (raw_red <= 25) & (36 <= raw_white) & (raw_white <= 39)) {
        
        Serial.print("Color Sensor found: Black\n");
        if (MotorIsRunning == 1 | MotorIsRunning == 0) {
            MotorIsRunning = 2;
        }
    } 
    COLOR_CODE();
    ENGINE_CONDITION();
  }
  
  
}