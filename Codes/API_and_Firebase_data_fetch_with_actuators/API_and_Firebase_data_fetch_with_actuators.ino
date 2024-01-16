#include <Arduino.h>
#include "WiFiManager.h"
#include "FirebaseManager.h"
#include "HTTPManager.h"
#include "ServoManager.h"
#include "LCDManager.h"

ServoManager zAxisServo;
LiquidCrystal_I2C lcd(0x27, 20, 4);

const char* ssid = "UNITY";
const char* password = "basnayake";
const char* referenceUrl = "earendeldata-default-rtdb.asia-southeast1.firebasedatabase.app";
const char* httpUrl = "https://api.visibleplanets.dev/v3?latitude=7.4818&longitude=80.3609&showCoords=true&aboveHorizon=false";

FirebaseManager firebase(referenceUrl);
WiFiManager wifiManager(ssid, password, lcd);
HTTPManager httpManager;

const int MAX_PLANETS = 10;
const int numberOfPlanets = 10;

String planetNames[MAX_PLANETS];
String raValues[MAX_PLANETS];
String decValues[MAX_PLANETS];

const String planetsWithMoon[numberOfPlanets] = {
  "Sun", "Moon", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"
};

String planetNeeded;
String starData;
String prevPlanet;

// Function declarations
int findIndex(const String array[], int size, const String &targetValue);
void initialize();
void handlePlanetData();
void handleStarData();

void setup() {
  zAxisServo.attach(D3);
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  initialize();
}

void loop() {
  planetNeeded = firebase.getString("Planet");
  
  bool planetFound = findIndex(planetsWithMoon, numberOfPlanets, planetNeeded) != -1;
  
  if (planetFound) {
    handlePlanetData();
  } else {
    handleStarData();
  }

  prevPlanet = planetNeeded;
  Serial.println();
}

// Function definitions
void initialize() {
  wifiManager.connect();
}

void handlePlanetData() {
  httpManager.fetchData(httpUrl, planetNames, raValues, decValues);

  int index = findIndex(planetNames, MAX_PLANETS, planetNeeded);

  if (index != -1) {
    int degreeIndex = raValues[index].indexOf('h');
    Serial.println(planetNeeded + " : RA: " + raValues[index] + " : DEC:" + decValues[index]);
    zAxisServo.write(atoi(raValues[index].substring(0, degreeIndex).c_str()) * 9);

    lcd.setCursor(0, 1);
    lcd.print("              ");
    lcd.setCursor(0, 1);
    lcd.print(planetNeeded + ":");
    lcd.setCursor(0, 2);
    lcd.print("RA: " + String(raValues[index]));
    lcd.setCursor(0, 3);
    lcd.print("DEC: " + String(decValues[index]));
  } else {
    Serial.println("Planet not found!");
  }
}

void handleStarData() {
  if (planetNeeded != prevPlanet) {
    starData = firebase.getString(planetNeeded);
  }

  Serial.println(planetNeeded + ": " + starData);
  lcd.setCursor(0, 1);
  lcd.print("              ");
  lcd.setCursor(0, 1);
  lcd.print(planetNeeded + ":");
  lcd.setCursor(0, 2);
  lcd.print(starData.substring(0, 10));
  lcd.setCursor(0, 3);
  lcd.print(starData.substring(11, 24));
}

int findIndex(const String array[], int size, const String &targetValue) {
  for (int i = 0; i < size; i++) {
    if (array[i] == targetValue) {
      return i;
    }
  }
  return -1;
}
