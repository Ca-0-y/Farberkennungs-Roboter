#include <Arduino.h>

int RED = 1;
int GREEN = 1;
int YELLOW = 1;
const int Red_LED = 0;
const int Green_LED = 2;
const int Yellow_LED = 15;

void setup(){
    pinMode(Red_LED, OUTPUT);
    digitalWrite(Red_LED, LOW);
    pinMode(Green_LED, OUTPUT);
    pinMode(Yellow_LED, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    if (RED == 1){
        digitalWrite(Red_LED, HIGH);
        delay(100);
        digitalWrite(Red_LED, LOW);
        delay(100);
        RED = 0;
    }
    if (GREEN == 1){
        digitalWrite(Green_LED, HIGH);
        delay(300);
        digitalWrite(Green_LED, LOW);
        delay(100);
        GREEN = 0;
    }
    if (YELLOW == 1){
        digitalWrite(Yellow_LED, HIGH);
        delay(600);
        digitalWrite(Yellow_LED, LOW);
        delay(100);
        YELLOW = 0;
    }
}