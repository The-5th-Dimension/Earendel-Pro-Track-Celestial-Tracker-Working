#ifndef HTTP_MANAGER_H
#define HTTP_MANAGER_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class HTTPManager {
public:
  HTTPManager();
  void fetchData(const String& apiUrl, String planetNames[], String raValues[], String decValues[]);
private:
  void processPayload(const String& payload, std::vector<String>& planetNames, std::vector<String>& raValues, std::vector<String>& decValues);
};

#endif
