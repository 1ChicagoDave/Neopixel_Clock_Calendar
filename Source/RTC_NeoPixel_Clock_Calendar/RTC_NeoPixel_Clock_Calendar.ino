
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <RTClib.h>
#include <Time.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

  uint16_t twlve1;    // these are for the twelve oclock indicator .....testing an idea
  uint16_t twlve2;

#define debug true  // Turn on/off serial monitor

const int brightLevel = 80;
#define PIN 6  // Pin NeoPixel Ring is on
// You can set this to whichever digital pin is convenient for you

//  Initialize NeoPixels!  -- How many LEDS....etc...etc....
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

RTC_DS1307 RTC;

// Set clock variables - 
// set your timezone
// EX:  (ET = -4), (CST = -5), (MT = -6), (PST = -7)
const int TimeZone = 0;    // (CST = UTC - 5)

int secondDot = 0;
int minuteDot = 0;
int hourDot = 0;
int dayDot;
byte dayX;
byte dayY;

//  Array for changing twelve o'clock indicator throughout the day - once per hour

const uint32_t twelve[]= { 
  0x390070, 0x3b0087, 0x410082, 0x550091, 0x6e3191, 0x843191, 0x9a3165, 0xc65d4f, 0xdc734f, 0xdc9f4f, 0xf2cb4f, 0xAAAA00, 
  0xBCAA12, 0xCEAA24, 0xE0A136, 0xE09848, 0xE0865A, 0xE0746C, 0xE96B7E, 0xD74F90, 0xD734BD, 0xD734E1, 0x700058, 0x530070 };  


// Which LEDS are what part of clock face -
const int clock[13][2]= {
  {
    0,15                                              }  // 0 / 12
  ,
  {
    14,14                                              }  // 1
  ,
  {
    13,13                                              }  // 2
  ,
  {
    12,11                                              }  // 3
  ,
  {
    10,10                                              }  // 4
  ,
  {
    9,9                                              }  // 5
  ,
  {
    8,7                                              }  // 6
  ,
  {
    6,6                                              }  // 7
  ,
  {
    5,5                                              }  // 8
  ,
  {
    4,3                                              }  // 9
  ,
  {
    2,2                                              }  // 10
  ,
  {
    1,1                                              }  // 11
  ,
  {
    0,15                                              }  // 12

};

static uint8_t __attribute__ ((progmem)) sunday30_bmp[]={
  0xFF, 0xFF, 0xFF, 0xFF, 0xC0};
static uint8_t __attribute__ ((progmem)) tuesday31_bmp[]={
  0x3f, 0xFF, 0xFF, 0xFF, 0xF8};
static uint8_t __attribute__ ((progmem)) friday30_bmp[]={
  0x7, 0xFF, 0xFF, 0xFF, 0xFE};
static uint8_t __attribute__ ((progmem)) sunday31_bmp[]={
  0xFF, 0xFF, 0xFF, 0xFF, 0xE0};

void setup()  
{

#ifdef degug
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out    -  Leave commented out to ensure better/faster timing of clock & display
  Serial.begin(57600);
#endif
  Wire.begin();
  RTC.begin();
  strip.begin();
  matrix.begin(0x70);  // pass in the address
  matrix.setBrightness(2);
  delay(1000);

  if (! RTC.isrunning())
  {
    Serial.println("RTC is NOT running!");
    // Sets RTC to date time this sketch was compiled
    RTC.adjust(DateTime(__DATE__,__TIME__));
  }

  // strip.show(); // Initialize all pixels to 'off'
  //    Runs through colors - "Se;f Test / Initialization"
  colorWipe(255, 20);    // GREEN
  colorWipe(0xFFF000, 20);      // YELLOW
  colorWipe(0x0000FF, 20);        // BLUE
  colorWipe(0x000000, 20);          // CLEAR

}    // End void setup()

/****************************************************/

uint32_t timer = millis();

void loop()                     // run over and over again
{
 // twlve1 = map(timer,0,1000, 0, 15);    // these are for the twelve oclock indicator .....testing an idea
  //twlve2 = map(timer,0,1000, 15, 0);


  DateTime now = RTC.now();

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 1 seconds, print out the current stats
  // also helps appearance of second pixel flashing every second
  if (millis() - timer > 1000) 
  { 
    timer = millis(); // reset the timer

    /*
    // Uncomment if you want to watch serial monitor
     
     Serial.print("\nTime: ");
     Serial.print(GPS.hour + 19, DEC); // TimeZone change!
     Serial.print(':');
     Serial.print(GPS.minute, DEC); 
     Serial.print(':');
     Serial.print(GPS.seconds, DEC); 
     Serial.print('.');
     Serial.println(GPS.milliseconds);
     */


    // Set Arduino clock using the time.h library
    setTimeClock();
    delay(10);
    // We turn it back on at beginning of loop again
    // delay(30);
    // initNeoPixels();
#ifdef debug
    digitalClockDisplay();
#endif
    setSecond();
    setBackground();
    setHour();
    setMinute();

    setDayDot();
    
    //  Decide which month to display
    switch (month())
    {
      case 9:
      showSeptember2013();
      break;
      
      case 10:
      showOctober2013();
      break;
      
      case 11:
      showNovember2013();
      break;
      
      case 12:
      showDecember2013();
      break;
     
    }      // end MONTH SWITCH CASE
  }

}

/**********************************************/

void setTimeClock()
{

  DateTime now = RTC.now();
  int clockHour = now.hour();
  // adjust for timezone setting
  if (now.hour() <= abs(TimeZone))
  {
    clockHour = ((now.hour() + (12 + TimeZone)));
  }
  else if ((now.hour() > abs(TimeZone)) && (now.hour() <= (12 + abs(TimeZone))))
  {
    clockHour = (now.hour() + TimeZone);
  }
  else if (now.hour() > (12 + abs(TimeZone)))
  {
    clockHour = (now.hour() - (12 + abs(TimeZone)));
  }
  // use time.h lbrary to set Arduino's timeclock
  setTime(clockHour , now.minute(), now.second(), now.day(), now.month(), now.year());
  delay(10); 
}

/***************************************************/

void setBackground()
{
  int c = (brightLevel / 8);
  // Set the Clock Face" however we feel. I used two YELLOW lights to mark 12 o'clock for simplicity & personal taste
  // I left in commented code for 3,6, & 9 o'clock dial positions for you
  for(uint16_t i=0; i<16; i++) 
  {
    // Start with a clean slate!
    strip.setPixelColor(i, 0,0,0);  // sets background to blank - clears all LEDs
  }
  // twelve o'clock position
  strip.setPixelColor((clock[12][0]),c,c,0);
  strip.setPixelColor((clock[12][1]),c,c,0);

  // three o'clock position
  // strip.setPixelColor((clock[3][0]),0,c,c);
  // strip.setPixelColor((clock[3][1]),0,c,c);

  // six o'clock position
 //  strip.setPixelColor((clock[6][0]),c,c,0);
 //  strip.setPixelColor((clock[6][1]),c,c,0);

  // nine o'clock position
   // strip.setPixelColor((clock[9][0]),0,c,c);
   // strip.setPixelColor((clock[9][1]),0,c,c);

  strip.show();  // Light 'em up!
  delay(10);
  /*
  twlve1++;
  if(twlve1 == 100) twlve1 = 30;
  twlve2--;
  if(twlve2 == 30) twlve2 = 100;
  */
}  // end setBackground


/*************************************************/

void setHour()
{
  int c = (brightLevel / 4);
  hourDot = hour();
  strip.setPixelColor((clock[hourDot][0]), 0,0,c);
  strip.setPixelColor((clock[hourDot][1]), 0,0,c);

  strip.show();
  delay(10);
}  // end setHour()

/**************************************************/
void setMinute()
{
  int c = (brightLevel / 4);
  // convert 60 possible minutes to groups of five for our usage - (Relies on fabulous integer math!)
  int clockMinute = minute();
  minuteDot = (clockMinute / 5);

  uint32_t minColor = strip.Color(0,c,0);
  uint32_t hourColor = strip.getPixelColor(hourDot);
  uint32_t blend = ((hourColor + minColor)/4);

  // blink Minute dot number of minutes out of five minute "group"
  // blink 0 times on the "zero" - ( 0, 5, 10, 15, 20, etc...)
  // blinks once on the "ones" - ( 1, 6, 11, 16, 21, etc....)
  // blinks twice on the "twos" - ( 2, 7, 12, 17, 22, etc....)
  // See a pattern here??   :)
  if ((minute()%5) !=0)
  {
    if (minuteDot == hourDot)
    {
      for ( int i = 1; i <= ((minute() %5 )); i++)
      {
        // change color to whatever you'd like!
        // I'm using a dim green here
        strip.setPixelColor((clock[minuteDot][0]), blend);
        strip.setPixelColor((clock[minuteDot][1]), blend);
        strip.show();
        delay(50);
        // and clear!
        strip.setPixelColor((clock[minuteDot][0]), 0,0,0);
        strip.setPixelColor((clock[minuteDot][1]), 0,0,0);
        strip.show();
        delay(120);
      }
    }
    else
    {
      for ( int i = 1; i <= ((minute() %5 )); i++)
      {
        // change color to whatever you'd like!
        // I'm using a dim green here
        strip.setPixelColor((clock[minuteDot][0]), minColor);
        strip.setPixelColor((clock[minuteDot][1]), minColor);
        strip.show();
        delay(50);
        // and clear!
        strip.setPixelColor((clock[minuteDot][0]), 0,0,0);
        strip.setPixelColor((clock[minuteDot][1]), 0,0,0);
        strip.show();
        delay(120);
      }
    }
  }
  // Then...after the blinks to indicate exact minutes, this "holds" the light steady until the next second-cycle
  // I've kept this color the same as the one above...slightly dimmer.
  strip.setPixelColor((clock[minuteDot][0]), minColor);
  strip.setPixelColor((clock[minuteDot][1]), minColor);
  strip.show();
  delay(10);


}  // end setMinute()

/********************************************/

void setSecond()
{
  int c = (brightLevel / 4);

  // more integer math to split 60 possible seconds into 12 possible dial locations
  int clockSecond = second();
  secondDot = (clockSecond / 5);
  uint32_t secColor = strip.Color(c,0,0);
  uint32_t minColor = strip.getPixelColor(minuteDot);
  uint32_t hourColor = strip.getPixelColor(hourDot);
  uint32_t twelveColor = strip.getPixelColor((clock[12][0]));

  uint32_t blendMin = (secColor + minColor);
  uint32_t blendHour = (secColor + hourColor);
  uint32_t blendTwelve = (secColor + twelveColor);


  // Blink the secondPixel every second & Update seconds variable if necessary

  // Something I was playing with - it "races" the second indicator from 12 o'clock to the
  // current position every second. Kind of neat, but "wastes time"   :)
  //"Race" to second position
  for ( int i = 1; i<= (secondDot); i++)
  {
    if (i == minuteDot)
    {      
      strip.setPixelColor((clock[i][0]), blendMin);
      strip.setPixelColor((clock[i][1]), blendMin);   
      strip.show();
      delay(15);
      strip.setPixelColor((clock[i][0]), minColor);
      strip.setPixelColor((clock[i][1]), minColor);
      strip.show();
      delay(15);
    }
    else if (i == hourDot)
    {      
      strip.setPixelColor((clock[i][0]), blendHour);
      strip.setPixelColor((clock[i][1]), blendHour);   
      strip.show();
      delay(15);
      strip.setPixelColor((clock[i][0]), hourColor);
      strip.setPixelColor((clock[i][1]), hourColor);
      strip.show();
      delay(15);
    }
    else if (i == 12)
    {      
      strip.setPixelColor((clock[i][0]), blendTwelve);
      strip.setPixelColor((clock[i][1]), blendTwelve);   
      strip.show();
      delay(15);
      strip.setPixelColor((clock[i][0]), twelveColor);
      strip.setPixelColor((clock[i][1]), twelveColor);
      strip.show();
      delay(15);
    }    
    else  
    {
      strip.setPixelColor((clock[i][0]), secColor);
      strip.setPixelColor((clock[i][1]), secColor);
      strip.show();
      delay(15);
      strip.setPixelColor((clock[i][0]), 0,0,0);
      strip.setPixelColor((clock[i][1]), 0,0,0);
      strip.show();
      delay(15);
    }


  }


  // Blinks once every second (or so) to indcate times position within the current minute
  strip.setPixelColor((clock[secondDot][0]), c,0,0);    // Turn on
  strip.setPixelColor((clock[secondDot][1]), c,0,0);    // Turn on
  strip.show();
  delay(10);
  //  strip.setPixelColor((clock[secondDot][0]), 0,0,0);    // Turn off - only flash/blink in seconds position
  //  strip.setPixelColor((clock[secondDot][1]), 0,0,0);    // Turn off - only flash/blink in seconds position
  /// strip.show();
  //delay(10);

}  // end setSecond()



void initNeoPixels()
{

  // a simple colorWipe-type of indicator that we commented out way aboave
  for (int i =0; i < 16 ; i++)
  {
    strip.setPixelColor(i, 0,0,0);
    strip.show();
    delay(10);
    strip.setPixelColor(i, 55,0,5);
    strip.show();
  }    // end for 
}    // end initNeoPixels()

void digitalClockDisplay()
{
  // we commented this out above also. It writes the time to serial monitor for debugging, etc...

  // Turn on Serial...
  Serial.begin(115200);
  // digital clock display of the time
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(" ");
  // ....and Date
  /*
  Serial.print(day());
   Serial.print(" ");
   Serial.print(month());
   Serial.print(" ");
   Serial.print(year()); 
   Serial.print(); 
   */
  // Carriage return / newline
  Serial.println(" ");
  // turn Serial off again... so timers work correctly!
  Serial.end();

}


//    ** BORRROWED from ADAFRUIT EXAMPLE CODE!!
void colorWipe(uint32_t c, uint8_t wait) 
{
  for( uint16_t i=0; i<16; i++) 
  {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


/********************* BEGIN SHOW MONTHS *********************/
void showSeptember2013()
{
  dayDot = LED_RED;
  // September 2013
  matrix.clear();
  matrix.drawBitmap(0, 0, sunday30_bmp, 7, 5, LED_GREEN);
  matrix.drawLine(0,0, 0,4, LED_OFF); 
  matrix.drawLine(6,0, 6,3, LED_OFF); 
  matrix.drawLine(0,0, 0,4, LED_YELLOW); 
  matrix.drawLine(6,0, 6,3, LED_YELLOW);  
  matrix.drawPixel(dayX,dayY, LED_OFF);
  matrix.drawPixel(dayX,dayY, dayDot);
  matrix.writeDisplay();

}
void showOctober2013()
{
  dayDot = LED_RED;
  // October 2013
  matrix.clear();
  matrix.drawBitmap(0, 0, tuesday31_bmp, 7, 5, LED_GREEN);
  matrix.drawLine(0,0, 0,4, LED_OFF); 
  matrix.drawLine(6,0, 6,3, LED_OFF); 
  matrix.drawLine(0,0, 0,4, LED_YELLOW); 
  matrix.drawLine(6,0, 6,3, LED_YELLOW);  
  matrix.drawPixel(dayX,dayY, LED_OFF);
  matrix.drawPixel(dayX,dayY, dayDot);
  matrix.writeDisplay();

}

void showNovember2013()
{
  dayDot = LED_RED;
  // November 2013
  matrix.clear();
  matrix.drawBitmap(0, 0, friday30_bmp, 7, 5, LED_GREEN);
  matrix.drawLine(0,0, 0,4, LED_OFF); 
  matrix.drawLine(6,0, 6,3, LED_OFF); 
  matrix.drawLine(0,0, 0,4, LED_YELLOW); 
  matrix.drawLine(6,0, 6,3, LED_YELLOW);  
  matrix.drawPixel(dayX,dayY, LED_OFF);
  matrix.drawPixel(dayX,dayY, dayDot);
  matrix.writeDisplay();

}

void showDecember2013()
{
  dayDot = LED_RED;
  // Decemeber 2013
  matrix.clear();
  matrix.drawBitmap(0, 0, sunday31_bmp, 7, 5, LED_GREEN);
  matrix.drawLine(0,0, 0,4, LED_OFF); 
  matrix.drawLine(6,0, 6,3, LED_OFF); 
  matrix.drawLine(0,0, 0,4, LED_YELLOW); 
  matrix.drawLine(6,0, 6,3, LED_YELLOW);  
  matrix.drawPixel(dayX,dayY, LED_OFF);
  matrix.drawPixel(dayX,dayY, dayDot);
  matrix.writeDisplay(); 

}

/***************** END SHOW MONTHS ***********************/

void setDayDot()
// determine where to place the indicator for TODAY on LED matrix
// We need both X and Y axis - ZERO INDEXED!!  Sunday = 0
{

#ifdef debug
  Serial.print("Weekday:  ");
  Serial.println(weekday());
  Serial.print("Day:  ");
  Serial.println(day());
  delay(20);
#endif
  // This gives us our X-Axis
  dayX = weekday() - 1;      // weekday() returns Sunday as 1

    // Y-axis is a little more complicated. We have to determine which week of the month it is
  // between 0-5 (up to six weeks per month!) and use it as our Y-Axis value.
  int firstWeekdayOfMonth = weekday() - (day()%7) + 1;    // This has problems when the date IS a multiple of 7
  if (firstWeekdayOfMonth = 8) firstWeekdayOfMonth = 1;    // THIS corrects the above issue!

  // First, figure out which date is the LAST day in the FIRST week of the month
  int firstWeekEnds = 8 - firstWeekdayOfMonth;    // EX: the 1st is Thurs -- weekday() == 5.... 8 - 5 = 3.... Last day of first week is Sat the 3rd.

  int weekOne = firstWeekEnds;
  int weekTwo = weekOne + 7;
  int weekThree = weekTwo + 7;
  int weekFour = weekThree + 7;
  int weekFive = weekFour + 7;
  int weekSix = weekFive + 7;

#ifdef debug
  Serial.print("FirstWeekdayOfMonth:  ");
  Serial.println(firstWeekdayOfMonth);
  Serial.print("weekOne:  ");
  Serial.println(weekOne);
  Serial.print("weekTwo:  ");
  Serial.println(weekTwo); 
  Serial.print("weekThree:  ");
  Serial.println(weekThree);
  Serial.print("weekFour:  ");
  Serial.println(weekFour);
  Serial.print("weekFive:  ");
  Serial.println(weekFive);
  Serial.print("weekSix:  ");
  Serial.println(weekSix);
  delay(20);
#endif


  int today = day();

  if (today <= weekOne)  dayY = 0;
  if((today <= weekTwo) && (today > weekOne))  dayY = 1;
  if((today <= weekThree) && (today > weekTwo))  dayY = 2;
  if((today <= weekFour) && (today > weekThree))  dayY = 3;
  if((today <= weekFive) && (today > weekFour))  dayY = 4;
  if((today <= weekSix) && (today > weekFive))  dayY = 5;

#ifdef debug
  Serial.print("dayY:  ");
  Serial.print(dayY);
#endif
}







