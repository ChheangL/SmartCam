#include <WiFi.h>
#include"init.h"
#include"SPIFFS.h"
#include "DBstuff.h"

// Replace with your network credentials


void setup() {
  pinMode(4,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,INPUT);
  digitalWrite(12,LOW);
  
  Serial.begin(115200);
  //---------------------------- Initalization -------------------------------------------
  initialization();
  startFirebase();

  //--------------------------- Setup Complete ---------------------------------------------
}

int timer = 0 ;
bool Read = 0;
void loop(){
  Read = digitalRead(13);
  digitalWrite(12,Read);
  digitalWrite(4,Read);
  Serial.println(Read);
  delay(1000);
}
