#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <ESP8266Firebase.h>

const char* ssid = "UNITY";
const char* password = "basnayake";
#define REFERENCE_URL "testsending-data-default-rtdb.firebaseio.com"

Firebase firebase(REFERENCE_URL);

const int MAX_PLANETS = 10; 
String planetNames[MAX_PLANETS];
String raValues[MAX_PLANETS];
String decValues[MAX_PLANETS];
int planetCount = 0;
String Planet_needed;

int findIndex(const String array[], int arraySize, const String &targetValue) {
  for (int i = 0; i < arraySize; ++i) {
    if (array[i] == targetValue) {
      return i;  
    }
  }
  return -1;  
}

void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
}

void readFirebaseData() {
  if (WiFi.status() == WL_CONNECTED) {
    Planet_needed = firebase.getString("/Planet");
    // Process Firebase data here
  }
}

void fetchDataFromAPI() {
  if (WiFi.status() == WL_CONNECTED) {
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    
    if (https.begin(*client, "https://api.visibleplanets.dev/v3?latitude=7.4818&longitude=80.3609&showCoords=true&aboveHorizon=false")) {
      int httpCode = https.GET();
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          DynamicJsonDocument doc(4096);
          deserializeJson(doc, payload);
          JsonArray data = doc["data"];

          for (JsonObject planet : data) {
            String name = planet["name"];
            JsonObject ra = planet["rightAscension"];
            JsonObject dec = planet["declination"];
            
            int raHours = ra["hours"];
            int raMinutes = ra["minutes"];
            float raSeconds = ra["seconds"];
            bool raNegative = ra["negative"];
            
            int decDegrees = dec["degrees"];
            int decArcMinutes = dec["arcminutes"];
            float decArcSeconds = dec["arcseconds"];
            bool decNegative = dec["negative"];

            planetNames[planetCount] = name;
            raValues[planetCount] = String(raNegative ? "-" : "") + String(raHours) + "h " + String(raMinutes) + "m " + String(raSeconds) + "s";
            decValues[planetCount] = String(decNegative ? "-" : "") + String(decDegrees) + "° " + String(decArcMinutes) + "' " + String(decArcSeconds) + "\"";
            
            planetCount++;
            if (planetCount >= MAX_PLANETS) {
              break;
            }
          }
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();

  connectToWiFi();
}

void loop() {
  fetchDataFromAPI();
  readFirebaseData();
  
  Serial.println(Planet_needed + " : RA: " + String(raValues[findIndex(planetNames, MAX_PLANETS, Planet_needed)]) + " : DEC:" + String(decValues[findIndex(planetNames, MAX_PLANETS, Planet_needed)]));
  Serial.println();
  Serial.println("Waiting 1S before the next round...");
  delay(1000);

}