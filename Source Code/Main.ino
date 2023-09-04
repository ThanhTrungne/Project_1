#include <SoftwareSerial.h>
#include "MyGPS.h"

#define rx 10
#define tx 11
SoftwareSerial SIM800L(rx, tx);

MyGPS gps(rx, tx);

//---------------------------------------
#define SW420 4
#define buzzer 5
#define led 6
#define button 7
//---------------------------------------
int state = 0;
int state1 = 0;
String link;
const String AT = "AT+C";
//---------------------------------------
const String PHONE = "+84857819828";
//---------------------------------------

void setup() {
  //_________________________________
  pinMode(SW420, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  //_________________________________
  Serial.begin(9600);
  SIM800L.begin(9600);
  delay(5000);
  //_________________________________
  SIM800L.println(AT + "MGF=1");
  delay(1000);
  SIM800L.println(AT + "NMI=1,2,0,0,0");
  delay(1000);
  SIM800L.println("ATE0");
  delay(1000);
  Serial.println("Setup Complete! SIM800L is Ready!");
  //_________________________________
  gps.begin();
}

void loop() {
  gps.update();
  CheckSMS();
  state1 = digitalRead(led);
  if (state1 == 1) {
    state = digitalRead(SW420);
    Serial.println(state);
    delay(1000);
  } else {
    state = 0;
  }
  if (state == 1) {
    digitalWrite(buzzer, HIGH);
    delay(500);
    SIM800L.println("ATD" + PHONE + ";");
    digitalWrite(buzzer, LOW);
  }
}

void CheckSMS() {
  //------------------------------------------
  while (SIM800L.available()) {
    String buff = SIM800L.readString();
    if (buff.indexOf(PHONE) > -1) {
      //_____________________________________
      if (buff.indexOf("ON") > -1) {
        buff = "";
        digitalWrite(led, HIGH);
        Reply("Device ON");
      }
      //_____________________________________
      else if (buff.indexOf("OFF") > -1) {
        buff = "";
        digitalWrite(led, LOW);
        Reply("Device OFF");
      }
      //_____________________________________
      else if (buff.indexOf("Location") > -1) {
        buff = "";
        SIM800L.println(AT + "MGF=1");
        delay(1000);
        SIM800L.println(AT + "MGS=\"" + PHONE + "\"");
        delay(1000);
        SIM800L.print(gps.getGoogleMapsLink());
        delay(100);
        SIM800L.write(0x1A); //ascii code for ctrl-26
        delay(1000);
      }
      //_____________________________________
    }
  }
  //---------------------------------------------
}

void Reply(String text) {
  SIM800L.println(AT + "MGF=1");
  delay(1000);
  SIM800L.println(AT + "MGS=\"" + PHONE + "\"");
  delay(1000);
  SIM800L.print(text);
  delay(100);
  SIM800L.write(0x1A); //ascii code for ctrl-26
  delay(1000);
}
