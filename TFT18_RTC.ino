/**  DS1307 RTC Module Demo for use with SPI LCD 180 * 120
     Sainsmart (ITDB18SP) with UTFT Library .. Pinout ....
     Joseph R. Unik - 11/2/2013
     
     PINS - SDA, SCL, CS, RST, RS
     PINS - 11   10   9   12   8
**/

#include <UTFT.h>
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>

extern uint8_t SevenSegNumFont[];
extern uint8_t SmallFont[];
extern uint8_t BigFont[];

int d;
int led = 13;
String dayOfWeek;

UTFT myGLCD(ITDB18SP,11,10,9,12,8);
// PINS - SDA, SCL, CS, RST, RS

void setup()
{
  pinMode(led, OUTPUT);
  
  myGLCD.InitLCD();
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.clrScr();
  myGLCD.fillScr(0, 0, 0);
}

void loop()
{
  tmElements_t tm;

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillCircle(80, 50, 3);              // erase second colon char
  myGLCD.fillCircle(80, 70, 3);
  
  digitalWrite(led, LOW);                    // second led off
  
  delay(500);
  
  if (RTC.read(tm)) 
  {
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.setColor(255, 0, 0);
    char buffer[16];
    myGLCD.setFont(SevenSegNumFont);
    sprintf(buffer, "%02d", (tm.Hour));      // print time in seven seg font
    myGLCD.print(buffer, 4, 40);
    sprintf(buffer, "%02d", (tm.Minute));
    myGLCD.print(buffer, 89, 40);
    
    myGLCD.fillCircle(80, 50, 3);            // draw second colon char
    myGLCD.fillCircle(80, 70, 3);
    digitalWrite(led, HIGH);                 // second led oN
    
    myGLCD.setFont(BigFont);
    sprintf(buffer, "%02d/%02d/%4d", (tm.Month), (tm.Day), (tmYearToCalendar(tm.Year)));
    myGLCD.setColor(255, 255, 255);
    myGLCD.print(buffer, CENTER, 110);
    
    d = weekday();
    printDayOfWeek();
    myGLCD.print(dayOfWeek, CENTER, 0);
    
    delay(500);
  } 
}

void printDayOfWeek()
{
  switch(d)
  {
     case 0:
     dayOfWeek = "Monday";
     break;
     
     case 1:
     dayOfWeek = "Tuesday";
     break;
    
     case 2:
     dayOfWeek = "Wednesday";
     break;
     
     case 3:
     dayOfWeek = "Thursday";
     break;
     
     case 4:
     dayOfWeek = "Friday";
     break;
    
     case 5:
     dayOfWeek = "Saturday";
     break;    
     
     case 6:
     dayOfWeek = "Sunday";
     break;
  }
}
