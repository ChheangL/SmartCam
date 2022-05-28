#include"init.h"
#include <Arduino.h>
#include "FirebaseFunction.h"
#include "captureImage.h"

//Add max number of picutre
//Add return to 0 for count

void setup() {
  pinMode(4,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,INPUT);
  digitalWrite(12,LOW);
  
  Serial.begin(115200);
  //---------------------------- Initalization -------------------------------------------
  initialization();
  
  startFirebase();

  initCamera();
  //--------------------------- Setup Complete ---------------------------------------------
}
int timer = 0 ;
bool Read = 0;
unsigned int c = 0;
unsigned int previousT =   millis();
bool trigger = false;
bool BuzzerOn = true;
bool FlashOn = true;

void loop(){
  Read = digitalRead(13);
  trigger = get_trigger();
  BuzzerOn = get_status("Buzzer");
  FlashOn = get_status("Flash");
  digitalWrite(12,(Read || trigger) && BuzzerOn);
  digitalWrite(4,(Read|| trigger) && FlashOn);
  if (Read || trigger &&(millis()-previousT > 2000)){
    
    capturePhotoSaveSpiffs();
    bool sendImageFailed = false;
    digitalWrite(12,false);
    digitalWrite(4,false);
    for (int i=0; i<5 && !sendImageFailed && checkPhoto(SPIFFS);i++ ){
      sendImageFailed = sendImage(c);
    }
    c++;
    if(c > 50){
      c=0;
    }
    previousT = millis();
  }
  Serial.println(Read);
  delay(1000);
}
