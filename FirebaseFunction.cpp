#include "FirebaseFunction.h"
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <DHT.h>

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);


//#include <time.h>
 FirebaseData fbdo;
 FirebaseAuth auth;
 FirebaseConfig config;
bool FirebaseStatus = false;

const char* photo_file = "/data/photo";
const char* extension = ".jpg";

void updateAliveStatus(){
  if(!get_status("CamStatus")){
    Firebase.RTDB.setBool(&fbdo, "test/CamStatus", true);
  }
}

void startDHT(){
    dht_sensor.begin();
    Serial.println("dht sucess");
}

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
  Firebase.RTDB.allowMultipleRequests(true);
  digitalWrite(4,!FirebaseStatus); //Turn Off Flash Ligh
  return FirebaseStatus;
}

void sendDHT_Data(){
  dht_sensor.begin();
  float humi  = dht_sensor.readHumidity();
  float tempC = dht_sensor.readTemperature();
  Serial.println("Humid: "+ String(humi)+"temp: "+String(tempC));
  if ( isnan(tempC) || isnan(humi)) {
   humi = 0.0;
   tempC = 0.0;
  }
  if(!Firebase.RTDB.setFloat(&fbdo, "test/Humidity", humi) ||!Firebase.RTDB.setFloat(&fbdo, "test/Temperature", tempC)){
    Serial.println(fbdo.errorReason());
  }
}

bool get_status(const char* var){
  if (Firebase.RTDB.getBool(&fbdo, "/test/"+String(var))){
    return fbdo.to<bool>();
  }else{
    Serial.println(fbdo.errorReason());
    return false;
  }
}

bool get_trigger(){
  bool trigger = get_status("Trigger");
  if(trigger){
      Firebase.RTDB.setBool(&fbdo, "/test/Trigger",false);
  }
  return trigger;
}

bool sendImage(unsigned int counter){
    
    if (Firebase.ready()){
    Serial.print("Uploading picture... ");
    //time_t t = Firebase.getCurrentTime();
    //const char *str=ctime(&t);
    //snprintf(str, sizeof str, "%d,%02d,%02d_%02d:%02d:%02d",year(t),month(t),day(t),hour(t),minute(t),second(t));
    const char* filePath = (String(photo_file) + String(counter)+String(extension)).c_str();
    Serial.printf(filePath);
    //MIME type should be valid to avoid the download problem.
    //The file systems for flash and SD/SDMMC can be changed in FirebaseFS.h.
    if (Firebase.Storage.upload(&fbdo, STORAGE_BUCKET_ID /* Firebase Storage bucket id */, FILE_PHOTO /* path to local file */, mem_storage_type_flash /* memory storage type, mem_storage_type_flash and mem_storage_type_sd */, filePath /* path of remote file stored in the bucket */, "image/jpeg" /* mime type */)){
      Serial.printf("\nDownload URL: %s\n", fbdo.downloadURL().c_str());
      Firebase.RTDB.setInt(&fbdo, "test/count", counter);      
    }
    else{
      Serial.println(fbdo.errorReason());
      //Firebase.RTDB.end(&fbdo);
      return false;
    }
    return true;
  }
}
