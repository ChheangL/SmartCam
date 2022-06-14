#include"init.h"
#include <Arduino.h>
#include "FirebaseFunction.h"
#include "captureImage.h"

//Add max number of picutre
//Add return to 0 for count
#define uS_TO_S_FACTOR 1000000        /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 2              /* Time ESP32 will go to sleep for 5 minutes (in seconds) */


void setup() {
  pinMode(4,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(15,INPUT);
  digitalWrite(2,LOW);
  
  Serial.begin(115200);
  //---------------------------- Initalization -------------------------------------------
  initialization();
  
  startFirebase();

  startDHT();

  initCamera();
  //--------------------------- Setup Complete ---------------------------------------------
}
int timer = 0 ;
bool Read = 0;
RTC_DATA_ATTR unsigned int c = 0;
unsigned int previousT =   millis();
bool trigger = false;
bool BuzzerOn = true;
bool FlashOn = true;
bool lockMode = true;

void loop(){
  Read = digitalRead(15);
  if(Read ||(millis() - previousT >= 1000)){
  trigger = get_trigger();
  lockMode = get_status("lockMode");
  updateAliveStatus();
  sendDHT_Data();
  if(trigger || lockMode){
    
    //Serial.println(Read);
    //Serial.println(trigger);
    if (Read || trigger){
        BuzzerOn = get_status("Buzzer");
        FlashOn = get_status("Flash");
        digitalWrite(2,(Read || trigger) && BuzzerOn);
        digitalWrite(4,(Read|| trigger) && FlashOn);  
      capturePhotoSaveSpiffs();
      //bool sendImageFailed = false;
      digitalWrite(4,false);
  
      //for (int i=0; i<5 && !sendImageFailed;i++ ){
      //  sendImageFailed = 
      sendImage(c);
      //  delay(5000);
      //}
      
      
      c++;
      if(c > 50){
        c=0;
      }
//      esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR); //go to sleep
//      Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
//      Serial.println("Going to sleep as normal now.");
//      esp_deep_sleep_start();
      
      digitalWrite(2,0);
    }
  }
  previousT = millis();
  }
}
