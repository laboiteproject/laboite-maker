/*
  LaBoite.h - Library for laboite maker edition.
  Created by Baptiste Gaultier, November 2, 2018.
  Released under GPLv3
*/

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <Fonts/XWindowSystemFont5x7.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <Preferences.h>
#include "LaBoite.h"

#define PUSHBUTTON_PIN  12 // Attach pushbutton to pin 12 from GND
#define LED_PIN         26 // Attach LED to pin 26 and GND
#define MATRIX_CS_PIN   4  // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI)
#define MATRIX_COLUMNS  4
#define MATRIX_ROWS     2
#define BITMAP          0
#define TEXT            1

DNSServer dnsServer;
WebServer webServer(80);
Preferences preferences;
Max72xxPanel matrix = Max72xxPanel(MATRIX_CS_PIN, MATRIX_COLUMNS, MATRIX_ROWS);

const byte wifiBitmap[] = {
  0x38, 0x44, 0x92, 0x28, 0x00, 0x10
};

const IPAddress apIP(192, 168, 4, 1);

boolean buttonPressed;
boolean confMode = true;
String ssidList;

Tile::Tile()
{
  _id = NULL;
  _last_activity = NULL;
  _duration = NULL;
  _brightness = NULL;
  _transition = NULL;
}


Tile::Tile(unsigned int id, unsigned long last_activity, unsigned int duration, byte brightness, byte transition)
{
  _id = id;
  _last_activity = last_activity;
  _duration = duration;
  _brightness = brightness;
  _transition = transition;
}

String Tile::asString()
{
  String tileString = "";
  tileString += String("id: ") + _id + String("| last_activity: ") + _last_activity;
  if(_duration)
    tileString += String("| duration: ") + _duration + String("| brightness: ") + _brightness + String("| transition: ") + _transition;

  return tileString;
}

Item::Item()
{
  _type = NULL;
  _x = NULL;
  _y = NULL;
  _content = "";
}


Item::Item(byte type, int x, int y, String content)
{
  _type = type;
  _x = x;
  _y = y;
  _content = content;
}

void Item::setType(const char * type)
{
  // if the first char is 'b', it means that it is bitmap
  if(type[0] == 'b')
    _type = 0;
  // else it has to be a text
  else
    _type = 1;
}

String Item::asString()
{
  String itemString = "";
  itemString += String("type: ") + _type + String("| width: ") + _width + String("| height: ") + _height + String("| x: ") + _x + String("| y: ") + _y + String("| content: ") + _content;

  return itemString;
}

Boite::Boite()
{
  buttonPressed = false;
  _intensityIncreases = true;
  _currentIntensity = 0;
}

void interruptServiceRoutine() {
  buttonPressed = true;
}

void Boite::begin(String server)
{
  _server =server;

  // starting mDNS reponder on http://laboite.local
  if (!MDNS.begin("laboite")) {
    Serial.println(F("Error setting up MDNS responder!"));
    while(1) delay(1000);
  }
#ifdef DEBUG
  Serial.println(F("mDNS responder started"));
#endif

  preferences.begin("laboite", false);

  _ssid = preferences.getString("ssid");
  _pass = preferences.getString("pass");

  _apikey = preferences.getString("apikey");

  Serial.println(F("Hello, here is your current laboite configuration:"));
  Serial.println("- ssid:" + _ssid);
  Serial.print(F("- pass:"));
  for (int i = 0; i < _pass.length(); i++)
    Serial.print('*');
  Serial.println();
  Serial.println("- apikey:" + _apikey);

  // rotate the matrix
  for(int i=0; i< MATRIX_COLUMNS*MATRIX_ROWS; i++)
    matrix.setRotation(i, 1);

  matrix.setFont(&XWindowSystemFont5x7);

  matrix.fillScreen(LOW);
  matrix.drawBitmap(0, 0, wifiBitmap, 8, 6, HIGH);
  String message = "start";
  for (int c = 0; c < message.length(); c++ )
    matrix.drawChar(8+c*5, 6, message.charAt(c), HIGH, LOW, 1);
  matrix.write();

  if(_ssid.length() && _pass.length() && _apikey.length()) {
#ifdef DEBUG
    Serial.print("Trying to connect to the saved ssid ");
    Serial.print(_ssid);
#endif

    WiFi.begin(_ssid.c_str(), _pass.c_str());
    for (int i = 0; i < 30; i++) {
      if (WiFi.status() == WL_CONNECTED) {
#ifdef DEBUG
        Serial.println();
        Serial.println("Connected!");
        matrix.fillScreen(LOW);
        matrix.drawBitmap(0, 0, wifiBitmap, 8, 6, HIGH);
        message = "OK!";
        for (int c = 0; c < message.length(); c++ )
          matrix.drawChar(8+c*5, 6, message.charAt(c), HIGH, LOW, 1);
        matrix.write();
#endif
        confMode = false;
        _startWebServer();
        return;
      }
      delay(500);
#ifdef DEBUG
      Serial.print(F("."));
#endif
    }
#ifdef DEBUG
    Serial.println(F("Wifi timed out."));
#endif
    confMode = true;
    // Reset wifi config
    preferences.remove("ssid");
    preferences.remove("pass");
    preferences.remove("apikey");
    preferences.end();
#ifdef DEBUG
    Serial.println("Configuration erased!");
#endif
  }
  if(confMode) {
#ifdef DEBUG
    Serial.println(F("Configuration mode activated!"));
#endif
    matrix.fillScreen(LOW);
    matrix.drawBitmap(0, 0, wifiBitmap, 8, 6, HIGH);
    message = "conf.";
    for (int c = 0; c < message.length(); c++ )
      matrix.drawChar(8+c*5, 6, message.charAt(c), HIGH, LOW, 1);
    matrix.write();
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect();
    delay(100);
    int n = WiFi.scanNetworks();
    delay(100);
    for (int i = 0; i < n; ++i) {
      ssidList += "<option value=\"";
      ssidList += WiFi.SSID(i);
      ssidList += "\">";
      ssidList += WiFi.SSID(i);
      ssidList += "</option>";
    }
    delay(100);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("laboite");

    // if DNSServer is started with "*" for domain name, it will reply with
    // provided IP to all DNS request
    dnsServer.start(53, "*", apIP);

    _startWebServer();

    Serial.println(F("Starting Access Point with ssid: \"laboite\""));
  }

  pinMode(LED_PIN, OUTPUT);
  pinMode(PUSHBUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PUSHBUTTON_PIN), interruptServiceRoutine, FALLING);
  Serial.println(F("laboite v0.4 is now starting..."));
}

boolean Boite::getTiles()
{
  if(!confMode) {
    // set all tiles back to default
    for(int i=0;i<TILES_ARRAY_SIZE; i++)
      _tiles[i].setId(0);

    HTTPClient http;
#ifdef DEBUG
    Serial.print(F("Get tiles, HTTP request: "));
    Serial.print(F("http://"));
    Serial.print(_server);
    Serial.print(F("/boites/"));
    Serial.print(_apikey);
    Serial.println(F("/"));
#endif

    http.begin(_server, 80, "/boites/" + _apikey + "/");

    // start connection and send HTTP header
    if(http.GET() == HTTP_CODE_OK) {
      // Please adjust the size of the buffer below if you have a lot of tiles here
      StaticJsonBuffer<1024> jsonBuffer;

      // Parse JSON object
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      if (!root.success()) {
#ifdef DEBUG
        Serial.println(F("JSON parsing failed!"));
#endif
        return false;
      }

      // Extract values
      JsonArray& tilesFromJson = root["tiles"];

      int i = 0;
      for (auto tileFromJson : tilesFromJson) {
        Tile tile;
        tile.setId(tileFromJson["id"].as<unsigned int>());
        tile.setLastActivity(tileFromJson["last_activity"].as<unsigned long>());
        _tiles[i] = tile;
        i++;
      }
    }
    else {
#ifdef DEBUG
      Serial.println("HTTP request failed, disconnecting!");
#endif
      return false;
    }

    http.end();
    return true;
  }
}

boolean Boite::updateTiles()
{
  Serial.println("updateTiles");
  if(!confMode) {
    for(int i=0;i<TILES_ARRAY_SIZE; i++) {
      if(_tiles[i].getId()) {
        updateTile(i);
#ifdef DEBUG
        Serial.println(_tiles[i].asString());
#endif
      }
    }
  }
}

boolean Boite::updateTile(unsigned int id)
{
  HTTPClient http;

#ifdef DEBUG
  Serial.print(F("Tile updating, HTTP request: "));
  Serial.print(F("http://"));
  Serial.print(_server);
  Serial.print(F("/boites/"));
  Serial.print(_apikey);
  Serial.print(F("/tiles/"));
  Serial.print(_tiles[id].getId());
  Serial.println(F("/"));
#endif

  http.begin(_server, 80, "/boites/" + _apikey + "/tiles/" + _tiles[id].getId() + "/");

  // start connection and send HTTP header
  if(http.GET() == HTTP_CODE_OK) {
    // Please adjust the size of the buffer below if you have a lot of tiles here
    StaticJsonBuffer<1280> jsonBuffer;

    // Parse JSON object
    JsonObject& root = jsonBuffer.parseObject(http.getString());
    if (!root.success()) {
#ifdef DEBUG
      Serial.println(F("JSON parsing failed!"));
#endif
      _tiles[id].setId(0);
      return false;
    }

    // Extract values
    _tiles[id].setDuration(root["duration"].as<unsigned int>());
    _tiles[id].setBrightness(root["brightness"].as<byte>());
    _tiles[id].setTransition(root["transition"].as<byte>());

    JsonArray& itemsFromJson = root["items"];

    int i = 0;
    for (auto itemFromJson : itemsFromJson) {
      Item item;
      item.setType(itemFromJson["type"].as<char*>());
      item.setWidth(itemFromJson["width"].as<byte>());
      item.setHeight(itemFromJson["height"].as<byte>());
      item.setX(itemFromJson["x"].as<byte>());
      item.setY(itemFromJson["y"].as<byte>());
      item.setContent(itemFromJson["content"].as<char*>());
      _tiles[id].items[i] = item;
      i++;
    }
  }
  else {
#ifdef DEBUG
    Serial.println("HTTP request failed, disconnecting!");
#endif
    return false;
  }
  http.end();
  return true;
}

boolean Boite::sendPushButtonRequest()
{
  // set buttonPressed back to default value:
  buttonPressed =false;

  HTTPClient http;

#ifdef DEBUG
  Serial.print(F("Push button triggered, HTTP request: "));
  Serial.print(F("http://"));
  Serial.print(_server);
  Serial.print(F("/boites/"));
  Serial.print(_apikey);
  Serial.println(F("/pushbutton/"));
#endif

  http.begin(_server, 80, "/boites/" + _apikey + "/pushbutton/");

  // start connection and send HTTP request
  if(http.GET() == HTTP_CODE_OK) {
    for (size_t i = 0; i < 3; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
      delay(500);
    }
  }
  else {
#ifdef DEBUG
    Serial.println("HTTP request failed, disconnecting!");
#endif
    return false;
  }
  http.end();
  return true;
}

void Boite::drawTiles()
{
  if(confMode)
    dnsServer.processNextRequest();
  webServer.handleClient();

  for(int i=0;i<TILES_ARRAY_SIZE; i++) {
    if(_tiles[i].getId()) {
      matrix.fillScreen(LOW);
      _currentIntensity = _tiles[i].getBrightness();
      matrix.setIntensity(_currentIntensity);
      drawTile(i);
      _drawTileTransition(i);
    }
  }
}

void Boite::drawTile(int id)
{
  if(buttonPressed)
    sendPushButtonRequest();
  if(confMode)
    dnsServer.processNextRequest();
  webServer.handleClient();

  boolean isScrolling = false;
  for(int i=0; i<ITEMS_ARRAY_SIZE; i++) {
    Item item = _tiles[id].items[i];
    if(item.getContent() != "") {
      if(item.getType() == TEXT) {
        // item is a text
        if(item.getContent().length() < 6) {
          for (int c = 0; c < item.getContent().length(); c++ )
            matrix.drawChar(item.getX()+c*5, item.getY()+6, item.getContent().charAt(c), HIGH, LOW, 1);
        }
        else {
          // text will be scrolling
          isScrolling = true;
          for(int i=MATRIX_COLUMNS*8; i > int(item.getContent().length())*-5; i--) {
            matrix.fillRect(0, item.getY(), 32, 7, LOW);
            for (int c = 0; c < item.getContent().length(); c++ )
              matrix.drawChar(i+c*5, item.getY()+6, item.getContent().charAt(c), HIGH, LOW, 1);
            matrix.write();
            delay(int(_tiles[id].getDuration()/(32+int(item.getContent().length())*5)));
          }
        }
      }
      else {
        // item is a bitmap
        byte bitmap[64];
        for (int i=0, c = 2; c < item.getContent().length(); i++, c+=2) {
          // TODO
          //Serial.print(item.getContent().charAt(c));
          //Serial.println(item.getContent().charAt(c+1));
          String bitmapByte = item.getContent().substring(c, c+2);
          bitmap[i] = strtol(bitmapByte.c_str(), NULL, 16);
        }
        matrix.drawBitmap(item.getX(), item.getY(), bitmap, item.getWidth (), item.getHeight(), HIGH);
      }
#ifdef DEBUG
      Serial.println(item.asString());
#endif
    }
  }
  matrix.write();
  if(!isScrolling)
    delay(_tiles[id].getDuration());
}

void Boite::drawTile(int id, int x, int y)
{
  for(int i=0; i<ITEMS_ARRAY_SIZE; i++) {
    Item item = _tiles[id].items[i];
    if(item.getContent() != "") {
      if(item.getType() == TEXT) {
        // item is a text
        if(item.getContent().length() < 6) {
          for (int c = 0; c < item.getContent().length(); c++ )
            matrix.drawChar(item.getX()+c*5+x, item.getY()+6+y, item.getContent().charAt(c), HIGH, LOW, 1);
        }
      }
      else {
        // item is a bitmap
        byte bitmap[64];
        for (int i=0, c = 2; c < item.getContent().length(); i++, c+=2) {
          String bitmapByte = item.getContent().substring(c, c+2);
          bitmap[i] = strtol(bitmapByte.c_str(), NULL, 16);
        }
        matrix.drawBitmap(item.getX()+x, item.getY()+y, bitmap, item.getWidth(), item.getHeight(), HIGH);
      }
#ifdef DEBUG
      Serial.println(item.asString());
#endif
    }
  }
  matrix.write();
}

void Boite::_drawTileTransition(int id)
{
  switch(_tiles[id].getTransition()) {
    case 1:
      // fadeout
      for(int i=_currentIntensity; i>=0; i--) {
        matrix.setIntensity(i);
        delay(50);
      }
      // fadein next tile (if there is one)
      if(_tiles[id+1].getId()) {
        matrix.fillScreen(LOW);
        drawTile(id+1, 0, 0);
        for(byte i=0; i<=_tiles[id+1].getBrightness(); i++) {
          matrix.setIntensity(i);
          delay(50);
        }
      }
      break;
    case 2:
      for(int x=MATRIX_COLUMNS*8; x>0; x--) {
        matrix.fillScreen(LOW);
        drawTile(id, x-MATRIX_COLUMNS*8, 0);
        if(_tiles[id+1].getId()) {
          drawTile(id+1, x, 0);
          _fade(id+1);
        }
        else {
          drawTile(0, x-1, 0);
          _fade(0);
        }
        matrix.write();
      }
      break;
    case 3:
      for(int x=0; x<MATRIX_COLUMNS*8; x++) {
        matrix.fillScreen(LOW);
        drawTile(id, x, 0);
        if(_tiles[id+1].getId()) {
          drawTile(id+1, x-MATRIX_COLUMNS*8, 0);
          _fade(id+1);
        }
        else {
          drawTile(0, x-MATRIX_COLUMNS*8-1, 0);
          _fade(0);
        }
        matrix.write();
      }
      break;
    case 4:
        for(int y=MATRIX_ROWS*8; y>0; y--) {
          matrix.fillScreen(LOW);
          drawTile(id, 0, y-MATRIX_ROWS*8);
          if(_tiles[id+1].getId()) {
            drawTile(id+1, 0, y);
            _fade(id+1);
          }
          else {
            drawTile(0, 0, y);
            _fade(0);
          }
          matrix.write();
        }
        break;
    case 5:
      for(int y=0; y<=MATRIX_ROWS*8; y++) {
        matrix.fillScreen(LOW);
        drawTile(id, 0, y);
        if(_tiles[id+1].getId()) {
          drawTile(id+1, 0, y-MATRIX_ROWS*8);
          _fade(id+1);
        }
        else {
          drawTile(0, 0, y-MATRIX_ROWS*8);
          _fade(0);
        }
        matrix.write();
      }
      break;
    }
}

void Boite::_fade(int id) {
  if(_currentIntensity == _tiles[id].getBrightness()) return;
  if(_currentIntensity < _tiles[id].getBrightness()) {
    _currentIntensity++;
    matrix.setIntensity(_currentIntensity);
  }
  else {
    _currentIntensity--;
    matrix.setIntensity(_currentIntensity);
  }
}

String Boite::_makePage(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  s += "<title>";
  s += title;
  s += "</title></head><body style=\"font-family: monospace;\">";
  s += contents;
  s += "</body></html>";
  return s;
}

String Boite::_urlDecode(String input) {
  String s = input;
  s.replace("%20", " ");
  s.replace("+", " ");
  s.replace("%21", "!");
  s.replace("%22", "\"");
  s.replace("%23", "#");
  s.replace("%24", "$");
  s.replace("%25", "%");
  s.replace("%26", "&");
  s.replace("%27", "\'");
  s.replace("%28", "(");
  s.replace("%29", ")");
  s.replace("%30", "*");
  s.replace("%31", "+");
  s.replace("%2C", ",");
  s.replace("%2E", ".");
  s.replace("%2F", "/");
  s.replace("%2C", ",");
  s.replace("%3A", ":");
  s.replace("%3A", ";");
  s.replace("%3C", "<");
  s.replace("%3D", "=");
  s.replace("%3E", ">");
  s.replace("%3F", "?");
  s.replace("%40", "@");
  s.replace("%5B", "[");
  s.replace("%5C", "\\");
  s.replace("%5D", "]");
  s.replace("%5E", "^");
  s.replace("%5F", "-");
  s.replace("%60", "`");
  return s;
}

void Boite::_startWebServer() {
  if (confMode) {
    Serial.print(F("Starting Web Server at "));
    Serial.println(WiFi.softAPIP());
    webServer.on("/settings", [&]() {
      String s = "<h1>Wi-Fi Settings</h2><p>Please select your SSID,  enter your password and API key.</p>";
      s += "<form method=\"get\" action=\"setap\"><label>SSID: </label><select name=\"ssid\">";
      s += ssidList;
      s += "</select><br>Password: <input name=\"pass\" length=64 type=\"password\">";
      s += "<br>API key: <input name=\"apikey\" length=64><input type=\"submit\"></form>";
      webServer.send(200, "text/html", _makePage("Wi-Fi Settings", s));
    });
    webServer.on("/setap", [&]() {
      String _ssid = _urlDecode(webServer.arg("ssid"));
      Serial.print("SSID: ");
      Serial.println(_ssid);
      String _pass = _urlDecode(webServer.arg("pass"));
      Serial.print("Password: ");
      Serial.println(_pass);
      String _apikey = _urlDecode(webServer.arg("apikey"));
      Serial.print("API key: ");
      Serial.println(_apikey);
      Serial.println("Writing laboite configuration to Non-volatile storage...");

      // Store wifi config
      preferences.putString("ssid", _ssid);
      preferences.putString("pass", _pass);
      preferences.putString("apikey", _apikey);
      preferences.end();
      Serial.println("Configuration saved!");

      String s = "<h1>Setup complete.</h1><p>device will be connected to \"";
      s += _ssid;
      s += "\" after the restart.";
      webServer.send(200, "text/html", _makePage("Wi-Fi Settings", s));
      delay(3000);
      ESP.restart();
    });
    webServer.onNotFound([&]() {
      String s = "<h1>AP mode</h1><p><a href=\"/settings\">Wi-Fi Settings</a></p>";
      webServer.send(200, "text/html", _makePage("AP mode", s));
    });
  }
  else {
    Serial.print("Starting Web Server at ");
    Serial.println(WiFi.localIP());
    webServer.on("/", [&]() {
      String s = "<h1>STA mode</h1><p><a href=\"/reset\">Reset Wi-Fi Settings</a></p>";
      webServer.send(200, "text/html", _makePage("STA mode", s));
    });
    webServer.on("/reset", [&]() {
      // reset the wifi config
      preferences.remove("ssid");
      preferences.remove("pass");
      preferences.remove("apikey");
      String s = "<h1>Wi-Fi settings was reset.</h1><p>Resetting device in 3s.</p>";
      webServer.send(200, "text/html", _makePage("Reset Wi-Fi Settings", s));
      delay(3000);
      ESP.restart();
    });
  }
  webServer.begin();
}
