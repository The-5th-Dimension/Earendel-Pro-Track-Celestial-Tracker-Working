#include <Arduino.h>
#include "WiFiManager.h"
#include "FirebaseManager.h"
#include "HTTPManager.h"
#include "LCDManager.h"
#include <time.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define _SSID "Dialog 4G 752"         // Your WiFi SSID
#define _PASSWORD "b10F79cD"     // Your WiFi Password
// #define _SSID "Yasiru's Galaxy Tab"          // Your WiFi SSID
// #define _PASSWORD "unlimited"      // Your WiFi PasswordString serverPath = serverName;
const char* referenceUrl = "earendeldata-default-rtdb.asia-southeast1.firebasedatabase.app";
const char* httpUrl = "https://api.visibleplanets.dev/v3?latitude=7.4818&longitude=80.3609&showCoords=true&aboveHorizon=false";
const char* FirebaseUrl = "https://earendeldata-default-rtdb.asia-southeast1.firebasedatabase.app/";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0; // Timezone offset in seconds (e.g. 0 for GMT)
const int   daylightOffset_sec = 3600; // Daylight offset in seconds (e.g. 3600 for DST)

#define az "Z"
#define alt "Y"

FirebaseManager firebase(referenceUrl);
WiFiManager wifiManager(_SSID, _PASSWORD, lcd);
HTTPManager httpManager;
// FirebaseManagerNew httpManager;

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
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  // pinMode(LED_BUILTIN, OUTPUT);
  // digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  // digitalWrite(LED_BUILTIN, HIGH);

//================================================================//
//================================================================//


  Serial.println();
  Serial.println();
  Serial.println();
  // initialize();
  now_time = -30;

  // Initialize and synchronize the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Wait for time to be set
  while (!time(nullptr)) {
    delay(1000);
    Serial.println("Waiting for time to sync...");
  }

}

void loop() {

  // Get current time
  time_t now;
  struct tm timeinfo;
  char strftime_buf[64];

  time(&now);
  localtime_r(&now, &timeinfo);
  
  // Format time into a string
  strftime(strftime_buf, sizeof(strftime_buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
  
  // Print time to serial
  Serial.print("Current time: ");
  Serial.println(strftime_buf);

  if (millis()/1000 - now_time >= 10){
    planetNeeded = firebase.getString("Planet");
    // planetNeeded = "Sun";

    Serial.println(planetNeeded);
    
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
    // Serial.print(alt_to_turn);
    // Serial.print(" : ");
    // Serial.print(alt_current_angle);
    // Serial.print(" : ");
    // Serial.print(az_to_turn);
    // Serial.print(" : ");
    // Serial.println(az_current_angle);
}

// Function definitions
void initialize() {
  wifiManager.connect();
}

void handlePlanetData() {
  Serial.print("Finding Planet Data");
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

  // if (Axis == "Z"){
  //   digitalWrite(DIR_PIN_1, direction);
  //   for (int x = 0; x < count; x++) {
  //     digitalWrite(STEP_PIN_1, HIGH);
  //     delayMicroseconds(500);
  //     delay(30);
  //     digitalWrite(STEP_PIN_1, LOW);
  //     delayMicroseconds(500);
  //     delay(30);
  //   }
  // }else {
  //   digitalWrite(DIR_PIN_2, direction);
  //   for (int x = 0; x < count; x++) {
  //     digitalWrite(STEP_PIN_2, HIGH);
  //     delayMicroseconds(500);
  //     delay(30);
  //     digitalWrite(STEP_PIN_2, LOW);
  //     delayMicroseconds(500);
  //     delay(30);
  //   }
  // }
}
