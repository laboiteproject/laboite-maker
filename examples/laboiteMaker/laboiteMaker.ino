/*
  laboîte ESP32 v0.4

  laboite "maker edition" is a connected clock that
  displays a lot of information from the Internetz!
  Please have a look at the user guide here:
  https://github.com/laboiteproject/lenuage/wiki/

  created 28 Oct 2018
  modified 9 Mar 2020
  by Baptiste Gaultier

  released under GPLv3
*/

#include <WiFi.h>
#include <LaBoite.h>

Boite boite;

// lenuage server name
String hostName = "lenuage.io";

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 10000;

void setup() {
  Serial.begin(115200);

  // ssid/pass and apikey should be configured using wifi
  Serial.println(F("laboîte ESP32 v0.4 booting..."));

  // start wifi, webserver, mDNS, screen... 
  boite.begin(hostName);
}

void loop() {
  // here is where you'd put code that needs to be running all the time.
  boite.drawTiles();

  // check to see if it's time to connect again to lenuage server
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you were connected
    previousMillis = currentMillis;
    if (WiFi.status() == WL_CONNECTED) {
      boite.getTiles();
      boite.updateTiles();
    }
    else
      ESP.restart();
  }
}
