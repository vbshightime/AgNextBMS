#include"sht31.h"
#include<ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

const char *WiFiSSID = "Agnextsn_compass";
const char *WiFiPass = "Agnext0419";
AsyncWebServer server(80);

static float tempC = 0.0;
static float tempF = 0.0;
static float humid = 0.0;

 String PAGE2 = 
     "<!DOCTYPE html>"
     "<html>"
     "<head>"
     "<meta charset=\"utf-8\">"
     "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0\">"
     "<title> My first HTML page</title>"
     "</head>"
     "<body style= \"background-color:#EDEEF2\">"
     "<h1 style= \"color:blue\">Temperature and Humidity</h1>"
     "<h3 style= \"font-family:verdana; color:blue\">Temperature in Celcius:</h3>"
     "<p style=\"font-size:160%; font-family:Lucida Console\">"+String(tempC,1)+
     "</p>"
     "<h3 style= \"font-family:verdana; color:blue\">Temperature in Fahrenheit:</h3>"
     "<p style=\"font-size:160%; font-family:Lucida Console\">"+String(tempF,1)+
     "</p>"
     "<h3 style= \"font-family:verdana; color:blue\">Humidity:</h3>"
     "<p style=\"font-size:160%; font-family:Lucida Console\">"+String(humid,1)+
     "</p>"
     "</body>"
     "</html>";
     
void setup(){
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Starting I2C Communication");
  oneShotLow();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", PAGE2);
  });
  server.begin();

  reconnectWiFi();
  }

 void loop(){
   delay(500);
   i2Cinit();
   tempC = readTempC();
   tempF = readtempF();
   humid = readHumidity();

  } 

 void reconnectWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();        
  delay(400);
  WiFi.begin(WiFiSSID,WiFiPass);
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED)
  {   
      delay(500);
      Serial.print(".");
      if(counter == 100){
          ESP.restart();
        }
        counter++;  
  }
  Serial.println(WiFi.localIP());
} 
