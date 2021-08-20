#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "Home Network";
const char *password = "Idonthinkyoushouldbedoingthis";
int Hour;
int Pin1;
int Pin2;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 19800);

void setup(){
  Serial.begin(115200);
  pinMode(D2, OUTPUT);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D8, INPUT_PULLUP);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void WiFiTime(){
  timeClient.update();
  Hour = timeClient.getHours();
}

void MQ(){
  digitalWrite(D2, HIGH);
  delay(3600000);
  digitalWrite(D2, LOW);
  delay(3600000);
}

void MO(){
  Pin2 = digitalRead(D8);
  if (Pin2 == 0){
    digitalWrite(D2, HIGH);
  }
  else{
    digitalWrite(D2, LOW);
  }
}
void loop() {
  WiFiTime();
  delay(1000);
  
  switch (Hour){

  case 7 ... 16:
  MO();
break;

  default:
  Pin1 = digitalRead(D3);
  if(Pin1 == 0){
    MQ();
  }
  break;
  }
}
