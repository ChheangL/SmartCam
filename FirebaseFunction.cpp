#include "FirebaseFunction.h"
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
 FirebaseData fbdo;
 FirebaseAuth auth;
 FirebaseConfig config;
bool FirebaseStatus = false;

bool startFirebase(){
  digitalWrite(4,HIGH);
    /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  uint8_t previousT =millis()/100;
  while(!FirebaseStatus){
    if(millis()-previousT*100>= 1000){
      FirebaseStatus = Firebase.RTDB.setBool(&fbdo, "test/CamStatus", true);
      previousT = millis()/100;
    }
    
  }
  digitalWrite(4,!FirebaseStatus); //Turn Off Flash Ligh
  return FirebaseStatus;
}
