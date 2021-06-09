#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>

const char *ssid     = "Home Network Extended";
const char *password = "Idonthinkyoushouldbedoingthis";
const char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int dt = 1000;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 19800);

void setup(){
  Serial.begin(115200);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, LOW);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    digitalWrite(D5, HIGH);
    delay ( 500 );
    Serial.print ( "." );
    digitalWrite(D5, LOW);
    delay( 500 );  
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
  digitalWrite(D5, LOW);
  int hr = timeClient.getHours();
  if(hr >= 6 && hr <= 8){
   alarm();
  }
    else{
    printime();
   }
}
