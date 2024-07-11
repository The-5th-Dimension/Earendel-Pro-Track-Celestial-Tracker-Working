#include "WiFiManager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password, LiquidCrystal_I2C& lcd)
  : ssid(ssid), password(password), lcd(lcd) {}

void WiFiManager::connect() {
  // WiFi.mode(WIFI_STA);
  // WiFi.disconnect();
  // delay(1000);

  // // Connect to WiFi
  // Serial.println();
  // Serial.println();
  // Serial.print("Connecting to: ");
  // Serial.println(_SSID);
  // WiFi.begin(_SSID, _PASSWORD);

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print("-");
  // }

  // Serial.println("");
  // Serial.println("WiFi Connected");

  // // Print the IP address
  // Serial.print("IP Address: ");
  // Serial.print("http://");
  // Serial.print(WiFi.localIP());
  // Serial.println("/");
  // // digitalWrite(LED_BUILTIN, HIGH);
}
