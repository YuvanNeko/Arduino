#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>
#include <Wire.h>
#include "DS3231.h"

File myFile;

#define ONE_WIRE_BUS 7

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DS3231 Clock;

boolean Century = false;
boolean PM = false;
float temp1;
float temp2;
void setup () {

    Wire.begin();
    Serial.begin(57600);
    pinMode(9, INPUT_PULLUP);
    pinMode(4, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    Serial.print("Initializing SD card...");
    pinMode(10, OUTPUT);

    if (!SD.begin(10)) {
      Serial.println("initialization failed!");
      return;
    }
    Serial.println("initialization done.");
      sensors.begin();
}


void loop () {

    delay(1000);   

int YT_sec, YT_min, YT_hr, YT_yr, YT_mt, YT_dt;

YT_sec = Clock.getSecond();

if (YT_sec==0) {
YT_min = Clock.getMinute();
YT_hr = Clock.getHour(Century, PM);
YT_yr = Clock.getYear();
YT_mt = Clock.getMonth(Century);
YT_dt = Clock.getDate();
sensors.requestTemperatures();
myFile = SD.open("tempread.txt", FILE_WRITE);
if (myFile) {
  myFile.print(YT_dt); 
  myFile.print('/');
  myFile.print(YT_mt);
  myFile.print('/');
  myFile.print(YT_yr);
  myFile.print(' ');
  myFile.print(YT_hr);
  myFile.print(':');
  myFile.print(YT_min);
  myFile.print(':');
  myFile.print(YT_sec);  
  myFile.print(',');
  myFile.print(sensors.getTempCByIndex(0));
  myFile.print(',');
  myFile.println(sensors.getTempCByIndex(1));
  myFile.close();
  temp1 = (sensors.getTempCByIndex(0));
  temp2 = (sensors.getTempCByIndex(1));
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
  Serial.println(YT_sec); 
  Serial.println(temp1);
  Serial.println(temp2);
  Serial.println("card write successful");
  int buttonVal = digitalRead(9);
  if((temp1 >= 35.00 || temp1 <= 28.00) && buttonVal == 0){
    if(YT_hr >= 6 && YT_hr <= 7){
    digitalWrite(6, LOW);
    delay(1000);
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>
#include <Wire.h>
#include "DS3231.h"

File myFile;

#define ONE_WIRE_BUS 7

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DS3231 Clock;

boolean Century = false;
boolean PM = false;
float temp1;
float temp2;
void setup () {

    Wire.begin();
    Serial.begin(57600);
    pinMode(9, INPUT_PULLUP);
    pinMode(4, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    Serial.print("Initializing SD card...");
    pinMode(10, OUTPUT);

    if (!SD.begin(10)) {
      Serial.println("initialization failed!");
      return;
    }
    Serial.println("initialization done.");
      sensors.begin();
}


void loop () {

    delay(1000);   

int YT_sec, YT_min, YT_hr, YT_yr, YT_mt, YT_dt;

YT_sec = Clock.getSecond();

if (YT_sec==0) {
YT_min = Clock.getMinute();
YT_hr = Clock.getHour(Century, PM);
YT_yr = Clock.getYear();
YT_mt = Clock.getMonth(Century);
YT_dt = Clock.getDate();
sensors.requestTemperatures();
myFile = SD.open("tempread.txt", FILE_WRITE);
if (myFile) {
  myFile.print(YT_dt); 
  myFile.print('/');
  myFile.print(YT_mt);
  myFile.print('/');
  myFile.print(YT_yr);
  myFile.print(' ');
  myFile.print(YT_hr);
  myFile.print(':');
  myFile.print(YT_min);
  myFile.print(':');
  myFile.print(YT_sec);  
  myFile.print(',');
  myFile.print(sensors.getTempCByIndex(0));
  myFile.print(',');
  myFile.println(sensors.getTempCByIndex(1));
  myFile.close();
  temp1 = (sensors.getTempCByIndex(0));
  temp2 = (sensors.getTempCByIndex(1));
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
  Serial.println(YT_sec); 
  Serial.println(temp1);
  Serial.println(temp2);
  Serial.println("card write successful");
  int buttonVal = digitalRead(9);
  if((temp1 >= 35.00 || temp1 <= 28.00) && buttonVal == 0){
    if(YT_hr >= 6 && YT_hr <= 7){
    digitalWrite(6, LOW);
    delay(1000);
    digitalWrite(6, HIGH);
    }
  }
  if(temp2 >= 35.00){
    digitalWrite(4, HIGH);
    delay(1000);
    digitalWrite(4, LOW);
  }
   if(temp2 <= 28.00){
    digitalWrite(3, HIGH);
    delay(1000);
    digitalWrite(3, LOW);
  }
} else {
  Serial.println("error opening tempread.txt");
}

}

}
    digitalWrite(6, HIGH);
    }
  }
  if(temp2 >= 35.00){
    digitalWrite(4, HIGH);
    delay(1000);
    digitalWrite(4, LOW);
  }
   if(temp2 <= 28.00){
    digitalWrite(3, HIGH);
    delay(1000);
    digitalWrite(3, LOW);
  }
} else {
  Serial.println("error opening tempread.txt");
}

}

}
