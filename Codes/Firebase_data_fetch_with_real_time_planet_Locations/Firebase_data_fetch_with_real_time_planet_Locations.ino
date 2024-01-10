#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <ESP8266Firebase.h>
#include <vector>

const char* ssid = "UNITY";
const char* password = "basnayake";
#define REFERENCE_URL "testsending-data-default-rtdb.firebaseio.com"

Firebase firebase(REFERENCE_URL);

const int MAX_PLANETS = 10; 
std::vector<String> planetNames;
std::vector<String> raValues;
std::vector<String> decValues;

String Planet_needed;

int findIndex(const std::vector<String>& array, const String &targetValue) {
  auto it = std::find(array.begin(), array.end(), targetValue);
  if (it != array.end()) {
    return std::distance(array.begin(), it);
  }
  return -1;  
}


void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(100);
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
          Serial.print(payload);
          DynamicJsonDocument doc(4096);
          deserializeJson(doc, payload);
          JsonArray data = doc["Sun"];

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

            planetNames.push_back(name);
            Serial.print(name);
            raValues.push_back(String(raNegative ? "-" : "") + String(raHours) + "h " + String(raMinutes) + "m " + String(raSeconds) + "s");
            decValues.push_back(String(decNegative ? "-" : "") + String(decDegrees) + "° " + String(decArcMinutes) + "' " + String(decArcSeconds) + "\"");
            
            if (planetNames.size() >= MAX_PLANETS) {
              break;
            }
          }
        }
      } else {
        Serial.printf("[https] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    } else {
      Serial.printf("[https] Unable to connect\n");
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
  // readFirebaseData();
  
  int index = findIndex(planetNames, Planet_needed);
  if (index != -1) {
    Serial.println(Planet_needed + " : RA: " + raValues[index] + " : DEC:" + decValues[index]);
  } else {
    Serial.println("Planet not found!");
  }
  Serial.println();
  Serial.println("Waiting 1S before the next round...");
  delay(1000);
}

