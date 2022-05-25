#ifndef FIREBASEFUNCTION_H
#define FIREBASEFUNCTION_H



#define API_KEY "AIzaSyDr7ZHyxr3Afc81oouiyQUY_i7cx90LMmg"
#define DATABASE_URL "https://smartcamera-188a6-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define STORAGE_BUCKET_ID "gs://smartcamera-188a6.appspot.com/"
#define USER_EMAIL "lychheang008@gmail.com"
#define USER_PASSWORD "123456"

bool startFirebase();
bool sendImage();
bool getBuzzer_status();
bool getFlash_status();

#endif
