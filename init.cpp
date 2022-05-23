
//Code based from https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
//for making text field and SPIFFS save
#include "init.h"

AsyncWebServer server(80);


String readFile( const char * path){
  File file = SPIFFS.open(path, FILE_READ);
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  file.close();
  Serial.println(fileContent);
  return fileContent;
}

void writeFile(const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = SPIFFS.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}

//Sending The HTML page and store the SSID and passworld from user
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
    <title>ESP Input Form</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        h1{
            flex: content;
            text-align: center;
            margin: auto;
            border: 3px solid green;
            flex-shrink: 2;
            font-family:'Courier New', Courier, monospace;
        }
        .Description{
            color:blue;
            font-family: 'Courier New', Courier, monospace;
            font-size: medium;
        }
        input{
            background-color: bisque;
        }
    </style>
    </head><body>
    <h1>Setting up Your WIFI</h1>
    <form action="/get">
        <p class="Description">Enter your Router WIFI and password for the camera</p>
      <p>SSID: <input type="text" name="input1"></p>
      <p>PASSWORD: <input type="text" name="input2"></p>
      <p><input type="submit" value="Submit"></p>
      
    </form><br>
    </form>
  </body></html>)rawliteral";

bool connectToWifi(const char* ssid, const char* password){
  int i =0;
  WiFi.begin(ssid, password);
  int previous_time=0;
  while (WiFi.status() != WL_CONNECTED) {
    int current_times = millis();
    if (current_times - previous_time >= 1000){
      Serial.println("Connecting to WiFi..");
      if(i>4){
        return false;
      }
      i++;
      previous_time = current_times;
    }
   }
// Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  return true;
}

bool wifiStatus = false;

bool startServer(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200,"text/html",index_html);
  });
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
    String ssid;
    String password;
    ssid = request->getParam("input1")->value();
    password = request->getParam("input2")->value();
    writeFile("/ssid.txt",ssid.c_str());
    writeFile("/password.txt",password.c_str());
    request->send_P(200,"text/html","ESP32 is trying to connect please wait 10 second and return to home page<br><a href=\"/\">Return To Home Page </a>");
    if (connectToWifi(ssid.c_str(),password.c_str())){
      wifiStatus = true;
    }
  });
  server.begin();
  return wifiStatus;
}
void endServer(){
  server.end();
}