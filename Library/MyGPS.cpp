#include "MyGPS.h"

MyGPS::MyGPS(int rxPin, int txPin) : serial(rxPin, txPin) {}

void MyGPS::begin() {
  serial.begin(9600);
}

void MyGPS::update() {
  if (serial.available()) {
    gps.encode(serial.read());
  }
  if (gps.location.isUpdated()) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    link = "www.google.com/maps/place/" + String(latitude, 6) + "," + String(longitude, 6);
  }
}

double MyGPS::getLatitude() {
  return latitude;
}

double MyGPS::getLongitude() {
  return longitude;
}

String MyGPS::getGoogleMapsLink() {
  return link;
}
