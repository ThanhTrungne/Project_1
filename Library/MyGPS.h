#ifndef MYGPS_H
#define MYGPS_H

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

class MyGPS {
public:
  MyGPS(int rxPin, int txPin);
  void begin();
  void update();
  double getLatitude();
  double getLongitude();
  String getGoogleMapsLink();

private:
  TinyGPSPlus gps;
  double latitude;
  double longitude;
  String link;
  SoftwareSerial serial;
};

#endif
