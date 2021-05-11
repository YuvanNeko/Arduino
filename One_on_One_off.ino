#include <Wire.h>
#include "DS3231.h"
DS3231 Clock;

boolean Century = false;
boolean PM = false;

void setup () 
{
  Wire.begin();
  Serial.begin(57600);
  pinMode (3, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (13, OUTPUT);
  pinMode (12, OUTPUT);
}
void resetPins(){
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
}
void loop ()
{
  loop:
  resetPins();
  int YT_sec, YT_min, YT_hr, YT_yr, YT_mt, YT_dt;

YT_sec = Clock.getSecond();
YT_min = Clock.getMinute();
YT_hr = Clock.getHour(Century, PM);
YT_yr = Clock.getYear();
YT_mt = Clock.getMonth(Century);
YT_dt = Clock.getDate();

switch (YT_hr){

  case 7 ... 17:
  delay(1000);
  Serial.print(YT_dt); 
  Serial.print('/');
  Serial.print(YT_mt);
  Serial.print('/');
  Serial.print(YT_yr);
  Serial.print(' ');
  Serial.print(YT_hr);
  Serial.print(':');
  Serial.print(YT_min);
  Serial.print(':');
  Serial.print(YT_sec);
  Serial.print(' ');
  Serial.println(Clock.getTemperature());    
break;
default :
  digitalWrite(7, HIGH);
  delay(3000);
  digitalWrite(7, LOW);
  digitalWrite(5, HIGH);
  delay(3000);
  digitalWrite(5, LOW);
  digitalWrite(3, HIGH);
  delay(3000);
  if (YT_hr >= 7 && YT_hr <= 17){
    goto loop;
  }
  digitalWrite(3, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(7, HIGH);
  delay(3600000);
   if (YT_hr >= 7 && YT_hr <= 17){
    goto loop;
  }
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(7, LOW);
  digitalWrite(5, HIGH);
  delay(3600000);
   if (YT_hr >= 7 && YT_hr <= 17){
    goto loop;
  }
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(3, HIGH);
  delay(3600000);
   if (YT_hr >= 7 && YT_hr <= 17){
    goto loop;
  }
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);
  delay(3600000);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  if (YT_hr >= 7 && YT_hr <= 17){
    goto loop;
  }
  break;
}
}
