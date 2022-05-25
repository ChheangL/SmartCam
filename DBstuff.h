#ifndef DBSTUFF_H
#define DBSTUFF_H

#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

bool startFirebase();
bool readBool(String path);
int readInt(String path);



#endif
