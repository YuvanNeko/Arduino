#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char *ssid     = "Home Network Extended";
const char *password = "Idonthinkyoushouldbedoingthis";

#define TELEGRAM_BOT_TOKEN "1738735467:AAHMehIT-6QuyUHAbxrTrObKp-_0xRCX3pY"

WiFiClientSecure client;
UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);

int delayBetweenChecks = 1000;
unsigned long lastTimeChecked;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  client.setInsecure();
  bot.longPoll = 60;
}

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String text = bot.messages[i].text;
      Serial.print("Call back button pressed with text: ");
      Serial.println(text);

      if (text == F("ON")) {
        digitalWrite(D4, HIGH);
      } else if (text == F("OFF")) {
        digitalWrite(D4, LOW);
      } 
      else{
        String chat_id = String(bot.messages[i].chat_id);
      String text = bot.messages[i].text;

      if (text == F("/options")) {
        String keyboardJson;
        keyboardJson = F("[[{ \"text\" : \"ON\", \"callback_data\" : \"ON\" },{ \"text\" : \"OFF\", \"callback_data\" : \"OFF\" }]]");
        bot.sendMessageWithInlineKeyboard(chat_id, "LED Control", "", keyboardJson);
      }
      if (text == F("/start")) {

        bot.sendMessage(chat_id, "/options : returns the inline keyboard\n", "Markdown");
      }
    }  
  }
}


void loop() {
  if (millis() > lastTimeChecked + delayBetweenChecks)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    if (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
    }lastTimeChecked = millis();
    }
  }
