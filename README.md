#Farberkennungs-Roboter

## Overview

### Description of Project

The software is for programming a line follower that can recognize colors. When recognizing black and white, the motors move alternately at different speeds to follow the line. When colors are detected, the motors rotate at the same speed and the color order is detected. Depending on the color order, the loudspeaker plays sounds, the LEDs light up or the motors rotate for a certain time.

## Parts Sourcing

### Description of Parts needed for Project

1.  Get ESP32 Dev Module here: https://www.az-delivery.de/products/esp32-developmentboard
2.  Get HC-SR04 here: https://eckstein-shop.de/HC-SR04AbstandsmessungUltraschallUltrasonicSensorModule
3.  Get L293DNE here: https://www.mouser.de/ProductDetail/Texas-Instruments/L293DNE?qs=ZA235jQDfbp%2Fp7f5ThcsUA%3D%3D
4.  Get DC geared motors here: 2x https://www.roboter-bausatz.de/p/roboter-auto-reifen-inkl.-getriebemotor-1-48
5.  Get SK6812 here: https://eckstein-shop.de/OPSCO10xRGBALEDwithICSK6812SMD50504PINSK6812RGBA-10
6.  Get VEML6040 here: https://www.mouser.de/ProductDetail/Vishay-Semiconductors/VEML6040A3OG?qs=uWNRbsI0ZdO85N24FCwIew%3D%3D

## 3D Printing

### Description of files and production workflow

1.  The 3D models are designed to be shielded from extraneous light, as the color sensor is very sensitive to lighting conditions

## Hardware

### Description of files and production workflow

1.  The circuit diagram shows the wiring of the individual components on a breadboard

## Software

### Program installation

1.  install [PlatformIO](https://platformio.org)
2.  Open Project
3.  install [MicroBlocks](https://microblocks.fun/download) or use it online
4.  Open Project



