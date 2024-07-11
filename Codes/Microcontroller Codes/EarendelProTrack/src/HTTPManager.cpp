#include "HTTPManager.h"

HTTPManager::HTTPManager() {}

void HTTPManager::fetchData(const String& apiUrl, String planetNames[], String raValues[], String decValues[]){
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  if (https.begin(*client, apiUrl)) {
    int httpCode = https.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        DynamicJsonDocument doc(32);
        deserializeJson(doc, payload);
        JsonArray data = doc["data"];

        int i = 0;
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

          planetNames[i] = name;
          raValues[i] = String(raNegative ? "-" : "") + String(raHours) + "h " + String(raMinutes) + "m " + String(raSeconds) + "s";
          decValues[i] = String(decNegative ? "-" : "") + String(decDegrees) + "° " + String(decArcMinutes) + "' " + String(decArcSeconds) + "\"";
          i++;
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
