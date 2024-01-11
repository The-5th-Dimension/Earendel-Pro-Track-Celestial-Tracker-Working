#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <ESP8266Firebase.h>
#include <vector>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const char* ssid = "UNITY";
const char* password = "basnayake";
#define REFERENCE_URL "testsending-data-default-rtdb.firebaseio.com"

Firebase firebase(REFERENCE_URL);

const int MAX_PLANETS = 10; 
std::vector<String> planetNames;
std::vector<String> raValues;
std::vector<String> decValues;

const int numberOfPlanets = 10; // Assuming 10 planets in our solar system

// Define an array of strings for planet names with moons
const String planetsWithMoon[numberOfPlanets] = {
  "Sun",
  "Moon",
  "Mercury",
  "Venus",
  "Mars",
  "Jupiter",
  "Saturn",
  "Uranus",
  "Neptune"
};

String Planet_needed;
String Star_data;

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
  lcd.setCursor(0,0);
  lcd.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    lcd.print('.');
    delay(1000);
  }
  lcd.clear();
  Serial.println();
}

void readFirebaseVariableData() {
  if (WiFi.status() == WL_CONNECTED) {
    unsigned long startTime = millis();

    Planet_needed = firebase.getString("/Planet");
    // Process Firebase data here

    unsigned long endTime = millis();
    Serial.println("Firebase Reading Time: " + String(endTime - startTime) + " ms");
    lcd.setCursor(0,0);
    lcd.print("F:" + String(endTime - startTime) + "ms");
  }
}

void readFirebaseStarData() {
  if (WiFi.status() == WL_CONNECTED) {
    unsigned long startTime = millis();

    Star_data = firebase.getString("/" + Planet_needed);
    // Process Firebase data here

    unsigned long endTime = millis();
    lcd.setCursor(10,0);
    lcd.print("S:" + String(endTime - startTime) + "ms");
    Serial.println("Firebase Star Reading Time: " + String(endTime - startTime) + " ms");
  }
}

void fetchDataFromAPI() {
  if (WiFi.status() == WL_CONNECTED) {
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;

    unsigned long startTime = millis();

    if (https.begin(*client, "https://api.visibleplanets.dev/v3?latitude=7.4818&longitude=80.3609&showCoords=true&aboveHorizon=false")) {
      int httpCode = https.GET();
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          // Serial.print(payload);
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

            planetNames.push_back(name);
            // Serial.print(name);
            raValues.push_back(String(raNegative ? "-" : "") + String(raHours) + "h " + String(raMinutes) + "m " + String(raSeconds) + "s");
            decValues.push_back(String(decNegative ? "-" : "") + String(decDegrees) + "° " + String(decArcMinutes) + "' " + String(decArcSeconds) + "\"");
          
          }
        }
      } else {
        Serial.printf("[https] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      unsigned long endTime = millis();
      Serial.println("HTTP Fetching Time: " + String(endTime - startTime) + " ms");
      lcd.setCursor(10,0);
      lcd.print("H: " + String(endTime - startTime) + "ms");

      https.end();
    } else {
      Serial.printf("[https] Unable to connect\n");
    }
  }
}

void setup() {

  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();

  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();

  connectToWiFi();
}

void loop() {
  readFirebaseVariableData();

  // Check if the desired planet is in the array
  bool planetFound = false;
  for (int i = 0; i < numberOfPlanets; i++) {
    if (Planet_needed.equals(planetsWithMoon[i])) {
      planetFound = true;
      break; // Exit the loop once the planet is found
    }
  }

  // If the planet is found, fetch data from the API; otherwise, delay and then read from Firebase
  if (planetFound) {
    fetchDataFromAPI();

    int index = findIndex(planetNames, Planet_needed);
    if (index != -1) {
      Serial.println(Planet_needed + " : RA: " + raValues[index] + " : DEC:" + decValues[index]);
      lcd.setCursor(0,1);
      lcd.print("              ");
      lcd.setCursor(0,1);
      lcd.print(Planet_needed + ":");
      lcd.setCursor(0,2);
      lcd.print( "RA: " + String(raValues[index]) );
      lcd.setCursor(0,3);
      lcd.print( "DEC: " + String(decValues[index]) );
    } else {
      Serial.println("Planet not found!");
    }

  } else {
    readFirebaseStarData();

    Serial.println(Planet_needed + ": " + Star_data);
    lcd.setCursor(0,1);
    lcd.print("              ");
    lcd.setCursor(0,1);
    lcd.print(Planet_needed + ":");
    lcd.setCursor(0,2);
    lcd.print(Star_data.substring(0, 10));
    lcd.setCursor(0,3);
    lcd.print(Star_data.substring(11));
    
  }
  
  Serial.println();
  // Serial.println("Waiting 1S before the next round...");
  // delay(1000);
}
