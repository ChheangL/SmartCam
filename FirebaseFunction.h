#ifndef FIREBASEFUNCTION_H
#define FIREBASEFUNCTION_H



#define API_KEY "AIzaSyDNE_baNdoY1RaQtWiG_esWYr4e8aOFHKo"
#define DATABASE_URL "https://smartcamus-default-rtdb.firebaseio.com/"
#define STORAGE_BUCKET_ID "smartcamus.appspot.com"
#define USER_EMAIL "lychheang008@gmail.com"
#define USER_PASSWORD "123456"
#define FILE_PHOTO "/data/photo.jpg"

#define DHT_SENSOR_PIN  14 
#define DHT_SENSOR_TYPE DHT22


void startDHT();
bool startFirebase();
bool sendImage(unsigned int counter);
bool get_status(const char* var);
bool get_trigger();
void updateAliveStatus();
void sendDHT_Data();

#endif
