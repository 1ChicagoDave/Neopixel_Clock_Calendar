Neopixel_Clock_Calendar
=======================

An RTC based clock and perpetual calendar using NeoPixel Ring for time display and a bi-color LED matrix as a perpetual month-view calendar.     

### Hardware -

* __RTC__ - [ChronoDot](http://docs.macetech.com/doku.php/chronodot_v2.0 "MaceTech's ChronoDot webpage")     
* __MCU__ - [Arduino Pro Mini 328](http://arduino.cc/en/Main/ArduinoBoardProMini "Pro Mini page on Arduino.cc")    
* __Clock Display__ - [NeoPixel Ring](http://www.adafruit.com/products/1463 "NeoPixel product page on Adafruit.com")      
_\* Though I would probably use the [12 pixel](http://www.adafruit.com/products/1643 "12 pixel version on Adafruit.com") or [24-pixel](http://www.adafruit.com/products/1586 "24 pixel version on Adafruit.com") version, which were not yet available, if building this today._     
* __LED Matrix__ - [CSM57281EG](http://www.alldatasheet.com/datasheet-pdf/pdf/286248/CHINASEMI/CSM-57281EG.html "CSM57281EG Datasheet")      
_\* Any 5x7 bicolor LED matrix should work. But, pinouts will likely be different; be sure to check datasheet!_     
* __Matrix Driver__ - Adafruit [HT16K33 Breakout](http://www.adafruit.com/products/1427 "LED Driver product page on Adafruit.com")       
_\* Pretty cool little chip! It can drive up to a 16x8 (or 8x8 bicolor) LED matrix with PWM brightness control AND simultaneously scan up a 13x3 key/button matrix on the same pins by quickly converting pin states (ouput/input/high-impedance)._       

### External Libraries - 

* [__Time__](http://playground.arduino.cc/Code/time "Arduino Playground page for "Time") - [_also here_](http://www.pjrc.com/teensy/td_libs_Time.html "Time Library page at PJRC.com")    
* [__RTClib__](https://github.com/adafruit/RTClib "Adafruit's GitHub repo for RTClib by JeeLabs") - [_also here_](https://github.com/jcw/rtclib "JeeLabs GitHub repo for RTClib")     
* [__Adafruit\_NeoPixel__](https://github.com/adafruit/Adafruit_NeoPixel "Adafruit Github repo - latest version of NeoPixel library")      
* [__Adafruit\_LEDBackpack__](https://github.com/adafruit/Adafruit-LED-Backpack-Library "Adafruit GitHub repo - for using LED matrix driver")     
* [__Adafrui\_GFX__](https://github.com/adafruit/Adafruit-GFX-Library "Adafruit GitHub repo - Core graphics library for displays, providing a common set of graphics primitives (points, lines, circles, etc.)")

_Libraries referenced in code are included in the `Source` folder. Links to original library sources \(above) are provided to credit the authors, and provide simple access to updates & documentation._


![ChronoDot](https://github.com/1ChicagoDave/Neopixel_Clock_Calendar/blob/master/Images/ChronoDotV2.1_1x1.jpg?raw=true "ChronoDot V2.1")![Arduino Pro Mini 328](https://github.com/1ChicagoDave/Neopixel_Clock_Calendar/blob/master/Images/ArduinoProMini328_1x1.jpg?raw=true "Arduino Pro Mini 328")      
![NeoPixel Ring](https://github.com/1ChicagoDave/Neopixel_Clock_Calendar/blob/master/Images/NeoPixelRing16_1x1.jpg?raw=true "NeoPixel Ring")![5x7 LED bicolor matrix](https://github.com/1ChicagoDave/Neopixel_Clock_Calendar/blob/master/Images/5x7LEDmatrix_1x1.jpg?raw=true "5x7 LED bicolor matrix")![HT16K33 LED backpack](https://github.com/1ChicagoDave/Neopixel_Clock_Calendar/blob/master/Images/HT16K33_LED_Backpack_1x1.jpg?raw=true "Adafruit HT16K33 LED backpack")
