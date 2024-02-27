#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#include <ESP32Firebase.h>

class FirebaseManager {
public:
  FirebaseManager(const char* referenceUrl);
  String getString(const String& path);
private:
  Firebase firebase;
};

#endif
