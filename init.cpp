
//Code based from https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
//for making text field and SPIFFS save
#include "init.h"



void initialization(){
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    ESP.restart();
  }
  else {
    delay(500);
    Serial.println("SPIFFS mounted successfully");
  }
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  digitalWrite(4,HIGH);
  bool res;
   res = wm.autoConnect("AutoConnectAP","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }
  digitalWrite(4,LOW); //Signaling Finish Setting up
}
