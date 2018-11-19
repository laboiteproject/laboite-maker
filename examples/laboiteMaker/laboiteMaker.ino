/*
  laboîte ESP32 v0.1

  laboite "maker edition" is a connected clock that
  displays a lot of information from the Internetz!
  Please have a look at the user guide here:
  https://github.com/laboiteproject/lenuage/wiki/

  created 28 Oct 2018
  modified 11 Nov 2018
  by Baptiste Gaultier

  released under GPLv3
*/

#include <WiFi.h>
#include <WiFiMulti.h>
#include <LaBoite.h>

WiFiMulti wifiMulti;

Boite boite;

// wifi network params
char ssid[] = "";
char pass[] = "";

// lenuage params
char hostName[] = "lenuage.io";
char apikey[]   = "";

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 10000;

void setup() {
  Serial.begin(115200);
  Serial.print(F("laboîte ESP32 v0.1 booting"));

  boite.begin(hostName, apikey);

  wifiMulti.addAP(ssid, pass);

  boite.getTiles();
  boite.updateTiles();
}

void loop() {
  // here is where you'd put code that needs to be running all the time.
  boite.drawTiles();

  // check to see if it's time to connect again to lenuage server
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you were connected
    previousMillis = currentMillis;
    if (wifiMulti.run() == WL_CONNECTED) {
      boite.getTiles();
      boite.updateTiles();
    }
  }
}
