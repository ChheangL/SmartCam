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

bool get_status(const char* var){
  Firebase.RTDB.getInt(fbdo, "/test/"+var.c_str());
  return fbdo.to<bool>();
}
bool send_imgage(unsigned int counter){
    if (Firebase.ready()){
    Serial.print("Uploading picture... ");
    const char* filePath = FILE_PHOTO + char(counter)+EXTENSION;
    //MIME type should be valid to avoid the download problem.
    //The file systems for flash and SD/SDMMC can be changed in FirebaseFS.h.
    if (Firebase.Storage.upload(&fbdo, STORAGE_BUCKET_ID /* Firebase Storage bucket id */, FILE_PHOTO+".jpg" /* path to local file */, mem_storage_type_flash /* memory storage type, mem_storage_type_flash and mem_storage_type_sd */, filePath /* path of remote file stored in the bucket */, "image/jpeg" /* mime type */)){
      Serial.printf("\nDownload URL: %s\n", fbdo.downloadURL().c_str());
    }
    else{
      Serial.println(fbdo.errorReason());
    }
    counter ++;
    return 
  }
}
