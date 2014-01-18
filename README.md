Neopixel_Clock_Calendar
=======================

An RTC based clock and perpetual calendar using NeoPixel Ring for time display and a bi-color LED matrix as a perpetual month-view calendar.    

* __RTC__ - [ChronoDot](http://docs.macetech.com/doku.php/chronodot_v2.0 "MaceTech's ChronoDot webpage")     
* __MCU__ - [Arduino Pro Mini 328](http://arduino.cc/en/Main/ArduinoBoardProMini "Pro Mini page on Arduino.cc")    
* __Clock Display__ - [NeoPixel Ring](http://www.adafruit.com/products/1463 "NeoPixel product page on Adafruit.com")
_\* Though I would probably use the [12 pixel](http://www.adafruit.com/products/1643 "12 pixel version on Adafruit.com") or [24-pixel](http://www.adafruit.com/products/1586 "24 pixel version on Adafruit.com") version, which were not yet available, if building this today._     
* __LED Matrix__ - [CSM57281EG](http://www.alldatasheet.com/datasheet-pdf/pdf/286248/CHINASEMI/CSM-57281EG.html "CSM57281EG Datasheet")      
_\* Any 5x7 bicolor LED matrix should work. But, pinouts will likely be different; be sure to check datasheet!_     
* __Matrix Driver__ - Adafruit 16x8 LED Matrix Driver Backpack - [HT16K33 Breakout](http://www.adafruit.com/products/1427 "LED Driver product page on Adafruit.com") _\* Pretty cool little chip! Handles up to 16x8 (or 8x8 bicolor) LED matrix AND up 13x3 key/button matrix on same pins by converting between ouput/input/high-impedance states._

![ChronoDot](https://github.com/1ChicagoDave/Neopixel_Clock_Calendar/blob/master/Images/ChronoDotV2.1_1x1.jpg?raw=true "ChronoDot V2.1")![Arduino Pro Mini 328](https://github.com/1ChicagoDave/Neopixel_Clock_Calendar/blob/master/Images/ArduinoProMini328_1x1.jpg?raw=true "Arduino Pro Mini 328")      
![NeoPixel Ring](https://github.com/1ChicagoDave/Neopixel_Clock_Calendar/blob/master/Images/NeoPixelRing16_1x1.jpg?raw=true "NeoPixel Ring")![5x7 LED bicolor matrix](https://github.com/1ChicagoDave/Neopixel_Clock_Calendar/blob/master/Images/5x7LEDmatrix_1x1.jpg?raw=true "5x7 LED bicolor matrix")![HT16K33 LED backpack](https://github.com/1ChicagoDave/Neopixel_Clock_Calendar/blob/master/Images/HT16K33_LED_Backpack_1x1.jpg?raw=true "Adafruit HT16K33 LED backpack")
