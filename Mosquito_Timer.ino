#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "Your SSID";
const char *password = "Your password";
const char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String Week;
int Hour;
int Minute;
int Second;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, Youroffset);

void setup(){
  Serial.begin(115200);
  pinMode(D2, OUTPUT);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void WiFiTime(){
  timeClient.update();
  Week = daysOfTheWeek[timeClient.getDay()];
  Hour = timeClient.getHours();
  Minute = timeClient.getMinutes();
  Second = timeClient.getSeconds();
}
void loop() {
  WiFiTime();
  delay(1000);
  
  switch (Hour){

  case 7 ... 17:
  delay(1000);
  Serial.print(Week); 
  Serial.print(', ');
  Serial.print(Hour);
  Serial.print(':');
  Serial.print(Minute);
  Serial.print(':');
  Serial.print(Second);
break;

  default:
  digitalWrite(D2, HIGH);
  delay(3600000);
  digitalWrite(D2, LOW);
  delay(3600000);
  break;
  }
}
