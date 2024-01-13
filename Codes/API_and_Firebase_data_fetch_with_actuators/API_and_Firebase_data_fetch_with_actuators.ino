#include <Arduino.h>
#include "WiFiManager.h"
#include "FirebaseManager.h"
#include "HTTPManager.h"
#include "ServoManager.h"
#include "LCDManager.h"

ServoManager Zaxis;
LiquidCrystal_I2C lcd(0x27, 20, 4);

const char* ssid = "UNITY";
const char* password = "basnayake";
#define REFERENCE_URL "earendeldata-default-rtdb.asia-southeast1.firebasedatabase.app"

FirebaseManager firebase(REFERENCE_URL);

WiFiManager Wireless(ssid, password, lcd);

HTTPManager HTTPmanager;

const int MAX_PLANETS = 10;
String planetNames[MAX_PLANETS];
String raValues[MAX_PLANETS];
String decValues[MAX_PLANETS];

const int numberOfPlanets = 10;
const String planetsWithMoon[numberOfPlanets] = {
  "Sun", "Moon", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"
};

String Planet_needed;
String Star_data;
String prev_planet;

int findIndex(const String array[], int size, const String &targetValue);

void setup() {
  Zaxis.attach(D3);
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  Wireless.connect();
}

void loop() {
  Planet_needed = firebase.getString("Planet");
  bool planetFound = false;
  for (int i = 0; i < numberOfPlanets; i++) {
    if (Planet_needed.equals(planetsWithMoon[i])) {
      planetFound = true;
      break;
    }
  }

  if (planetFound) {
    HTTPmanager.fetchData("https://api.visibleplanets.dev/v3?latitude=7.4818&longitude=80.3609&showCoords=true&aboveHorizon=false", planetNames, raValues, decValues);
    int index = findIndex(planetNames, MAX_PLANETS, Planet_needed);
    if (index != -1) {
      int degreeIndex = raValues[index].indexOf('h');
      Serial.println(Planet_needed + " : RA: " + raValues[index] + " : DEC:" + decValues[index]);
      Zaxis.write(atoi(raValues[index].substring(0, degreeIndex).c_str()) * 9);
      lcd.setCursor(0, 1);
      lcd.print("              ");
      lcd.setCursor(0, 1);
      lcd.print(Planet_needed + ":");
      lcd.setCursor(0, 2);
      lcd.print("RA: " + String(raValues[index]));
      lcd.setCursor(0, 3);
      lcd.print("DEC: " + String(decValues[index]));
    } else {
      Serial.println("Planet not found!");
    }
  } else {
    if (Planet_needed != prev_planet) {
      Star_data = firebase.getString(Planet_needed);
    }

    Serial.println(Planet_needed + ": " + Star_data);
    lcd.setCursor(0, 1);
    lcd.print("              ");
    lcd.setCursor(0, 1);
    lcd.print(Planet_needed + ":");
    lcd.setCursor(0, 2);
    lcd.print(Star_data.substring(0, 10));
    lcd.setCursor(0, 3);
    lcd.print(Star_data.substring(11, 24));
  }

  prev_planet = Planet_needed;
  Serial.println();
}

int findIndex(const String array[], int size, const String &targetValue) {
  for (int i = 0; i < size; i++) {
    if (array[i] == targetValue) {
      return i;
    }
  }
  return -1;
}
