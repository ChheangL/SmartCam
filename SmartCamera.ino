#include <WiFi.h>
#include"init.h"
#include"SPIFFS.h"
// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";


void setup() {

  
  Serial.begin(115200);
  //---------------------------- Initalization -------------------------------------------
  SPIFFS.begin(true);

  if (!connectToWifi(readFile("/ssid.txt").c_str(),readFile("/password.txt").c_str())){
    Serial.print("Setting AP (Access Point)…");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    WiFi.softAP(ssid, password);
  
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    bool Wifistatus = false;
    int previous_time = 0;
    while(!Wifistatus){
      int current_time = millis();
      if(current_time - previous_time >= 3000){
        Wifistatus = startServer();
        Serial.println(Wifistatus);
        previous_time = current_time;
      }
    }
    WiFi.softAPdisconnect(true);
  }
  endServer();
  Serial.println("Connect to Wifi Success fully");
  //--------------------------- Setup Complete ---------------------------------------------
}

void loop(){
  
}
