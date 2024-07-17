#include <Arduino.h>
#include "WiFiManager.h"
#include "FirebaseManager.h"
#include "HTTPManager.h"
#include "ServoManager.h"
#include "LCDManager.h"

ServoManager zAxisServo;
LiquidCrystal_I2C lcd(0x27, 20, 4);

const char* ssid = "Yasiru's Galaxy Tab";
const char* password = "unlimited";
const char* referenceUrl = "earendeldata-default-rtdb.asia-southeast1.firebasedatabase.app";
const char* httpUrl = "https://api.visibleplanets.dev/v3?latitude=7.4818&longitude=80.3609&showCoords=true&aboveHorizon=false";
const char* FirebaseUrl = "https://earendeldata-default-rtdb.asia-southeast1.firebasedatabase.app/";

#define az "Z"
#define alt "Y"

#define STEP_PIN_1 D7
#define DIR_PIN_1 D6

#define STEP_PIN_2 D9
#define DIR_PIN_2 D8

FirebaseManager firebase(referenceUrl);
WiFiManager wifiManager(ssid, password, lcd);
HTTPManager httpManager;
FirebaseManagerNew httpManager;

const int MAX_PLANETS = 10;
const int numberOfPlanets = 10;

float az_current_angle = 0;
float alt_current_angle = 0;
float az_to_turn = 0;
float alt_to_turn = 0;

String planetNames[MAX_PLANETS];
String raValues[MAX_PLANETS];
String decValues[MAX_PLANETS];

const String planetsWithMoon[numberOfPlanets] = {
  "Sun", "Moon", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"
};

String planetNeeded;
String starData;
String prevPlanet;

int now_time;

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
  now_time = -30;

  // Set STEP and DIR pins as OUTPUT for both steppers
  pinMode(STEP_PIN_1, OUTPUT);
  pinMode(DIR_PIN_1, OUTPUT);

  pinMode(STEP_PIN_2, OUTPUT);
  pinMode(DIR_PIN_2, OUTPUT);

  // Set initial direction for both steppers (1 for clockwise, 0 for counterclockwise)
  digitalWrite(DIR_PIN_1, HIGH);
  digitalWrite(DIR_PIN_2, HIGH);
}

void loop() {
  if (millis()/1000 - now_time >= 10){
    planetNeeded = firebase.getString("Planet");
    
    bool planetFound = findIndex(planetsWithMoon, numberOfPlanets, planetNeeded) != -1;
    
    if (planetFound) {
      handlePlanetData();
    } else {
      handleStarData();
    }

    prevPlanet = planetNeeded;
    Serial.println();
    now_time = millis()/1000;
  }

    if(int(az_to_turn) != int(az_current_angle)){
      if (az_to_turn > az_current_angle){
      Step(az, 1, true);
      az_current_angle += 1.8;
      // delay(50);
      }else if (az_to_turn < az_current_angle){
      Step(az, 1, false);
      az_current_angle -= 1.8;
      // delay(50);
      }
    }

    if(int(alt_to_turn) != int(alt_current_angle)){
      if (alt_to_turn > alt_current_angle){
      Step(alt, 1, true);
      alt_current_angle += 1.8;
      // delay(50);
      }else if (alt_to_turn < alt_current_angle){
      Step(alt, 1, false);
      alt_current_angle -= 1.8;
      // delay(50);
      }
    }

    // zAxisServo.write(az_current_angle);
    Serial.print(alt_to_turn);
    Serial.print(" : ");
    Serial.print(alt_current_angle);
    Serial.print(" : ");
    Serial.print(az_to_turn);
    Serial.print(" : ");
    Serial.println(az_current_angle);
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
    int altdegreeIndex = decValues[index].indexOf("°");
    Serial.print(decValues[index]);
    Serial.println(planetNeeded + " : RA: " + raValues[index] + " : DEC:" + decValues[index]);

    az_to_turn = int(atoi(raValues[index].substring(0, degreeIndex).c_str())/1.8) * 7 * 1.8 * 2;

    alt_to_turn = -abs(int(atoi(decValues[index].substring(0, altdegreeIndex).c_str())/1.8))  * 1.8;

    if(az_to_turn >= 360){az_to_turn -= 360;}

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

  az_to_turn = int(atoi(starData.substring(3, 10).c_str())/1.8) * 7 * 1.8 * 2;

  alt_to_turn = -abs(int(atoi(starData.substring(15, 24).c_str())/1.8))  * 1.8;

  if(az_to_turn >= 360){az_to_turn -= 360;}


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

void Step(String Axis, int count, bool direction){

  if (Axis == "Z"){
    digitalWrite(DIR_PIN_1, direction);
    for (int x = 0; x < count; x++) {
      digitalWrite(STEP_PIN_1, HIGH);
      delayMicroseconds(500);
      delay(30);
      digitalWrite(STEP_PIN_1, LOW);
      delayMicroseconds(500);
      delay(30);
    }
  }else {
    digitalWrite(DIR_PIN_2, direction);
    for (int x = 0; x < count; x++) {
      digitalWrite(STEP_PIN_2, HIGH);
      delayMicroseconds(500);
      delay(30);
      digitalWrite(STEP_PIN_2, LOW);
      delayMicroseconds(500);
      delay(30);
    }
  }
}
