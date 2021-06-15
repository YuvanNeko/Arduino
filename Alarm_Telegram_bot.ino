#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid     = "";
const char *password = "";

const int dt = 1000;
const unsigned long d = 60000;
const String ID = String(your id);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, your offset);

#define TELEGRAM_BOT_TOKEN "your token"

WiFiClientSecure client;
UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);

int delayBetweenChecks = 1000;
unsigned long lastTimeChecked;

bool AlarmState = true;

void setup() {
  Serial.begin(115200);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  timeClient.begin();
  delay(100);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  if(WiFi.status() == WL_CONNECTED){
    Serial.print("Connected");
  }

  client.setInsecure();
  bot.longPoll = 60;
}

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    if(bot.messages[i].chat_id.equals(ID)){
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
      Serial.print("Call back button pressed with text: ");
      Serial.println(text);

      if (text == F("Arm")) {
        if (AlarmState == false){
          AlarmState = true;
          bot.sendMessage(chat_id, "Your alarm has been armed!");
        }
        else{
          bot.sendMessage(chat_id, "Your alarm has been already armed!");
        }
      } if (text == F("Disarm")) {
        if(AlarmState == true){;
          AlarmState = false;
          bot.sendMessage(chat_id, "Your alarm has been disarmed!");
        }
        else{
          bot.sendMessage(chat_id, "Your alarm has already been disarmed!");
        }
      }

       if(text == F("Uptime")){
          bot.sendMessage(chat_id, "Your up time is :");
          bot.sendMessage(chat_id, String((millis()/d)));
          bot.sendMessage(chat_id, "minutes.");
        }

        else if (text == "Alarm Status"){
          if (AlarmState == true){
            bot.sendMessage(chat_id, "Your alarm is armed and ready to wake you up in the morning :)");
          }
          else{
            bot.sendMessage(chat_id, "Your alarm is not armed.");
          }
        }
        
      else{
        String chat_id = String(bot.messages[i].chat_id);
        String text = bot.messages[i].text;

      if (text == F("/options")) {
        String keyboardJson;
        keyboardJson = F("[[{ \"text\" : \"Arm\", \"callback_data\" : \"Arm\" },{ \"text\" : \"Disarm\", \"callback_data\" : \"Disarm\" }, { \"text\" : \"Uptime\", \"callback_data\" : \"Uptime\" }],");
        keyboardJson += F("[{ \"text\" : \"Alarm Status\", \"callback_data\" : \"Alarm Status\" }]]");
        bot.sendMessageWithInlineKeyboard(chat_id, "Alarm", "", keyboardJson);
      }
      if (text == F("/start")) {

        bot.sendMessage(chat_id, "Welcome to Cookie's Alarm system.\n Please press /options to proceed.", "Markdown");
      }
    }  
  }
  else{
    String chat_id = String(bot.messages[i].chat_id);
    bot.sendMessage(chat_id, "You are not Cookie, are you?, This incident will be reported to the owner of me :)");
    bot.sendMessage(ID, chat_id);
    bot.sendMessage(ID, "Has tried to use your service.");
  }
 }
}
void tele(){
        if (millis() > lastTimeChecked + delayBetweenChecks)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    
    if (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
    }

    lastTimeChecked = millis();
    }
    }

void alarm(){
 int i = 0;
  
        digitalWrite(D4, LOW);
        delay(dt);
        digitalWrite(D4, HIGH);
        delay(dt);
  }
void loop() {
      digitalWrite(D5, LOW);
      timeClient.update();
      int hr = timeClient.getHours();
      if(hr >= 6 && hr <= 8){
        if (AlarmState == true){
           for(int i = 0; i <= 15; i++){
        alarm();
      }
    }
      }
    for(int j = 0; j <= 5; j++){
      tele();
      delay(350);
    } 
  }
