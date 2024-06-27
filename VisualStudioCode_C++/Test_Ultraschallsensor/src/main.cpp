#include <Arduino.h>
#include <HCSR04.h>

byte triggerPin = 4;
byte echoPin = 35;

void setup () {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
}

void loop () {
  float temperature = 15;
  
  double* distances = HCSR04.measureDistanceCm(temperature);
  
  Serial.print("Distance: ");
  Serial.print(distances[0]);
  Serial.println(" cm");
  
  Serial.println("---");
  delay(250);
}




