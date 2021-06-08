#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>

const char *ssid     = "your ssid";
const char *password = "your password";
const char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int dt = 1000;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 19800);

void setup(){
  Serial.begin(115200);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );  
  }

  timeClient.begin();
}

void alarm(){
  digitalWrite(D4, LOW);
  delay(dt);
  digitalWrite(D4, HIGH);
  delay(dt);
}
void printime(){
  timeClient.update();
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  Serial.println(WiFi.localIP());
  delay(dt);
}
void loop() {
  int hr = timeClient.getHours();
  if(hr >= 6 && hr <= 8){
   alarm();
  }
    else{
    printime();
   }
}
