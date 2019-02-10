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
#include <Preferences.h>
#include "LaBoite.h"

#define PUSHBUTTON_PIN  12 // Attach pushbutton to pin 12 from GND
#define LED_PIN         26 // Attach LED to pin 26 and GND
#define MATRIX_CS_PIN   4  // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI)
#define MATRIX_COLUMNS  4
#define MATRIX_ROWS     2
#define BITMAP          0
#define TEXT            1

Preferences preferences;
Max72xxPanel matrix = Max72xxPanel(MATRIX_CS_PIN, MATRIX_COLUMNS, MATRIX_ROWS);

const byte splashScreenBitmap[] = {
  0x03, 0xc0, 0x0f, 0xf0, 0x1f, 0xf8, 0x38, 0x1c, 0x70, 0x0e, 0xe1, 0x87, 0x47, 0xe2,
  0x0f, 0xf0, 0x1c, 0x38, 0x08, 0x10, 0x01, 0x80, 0x03, 0xc0, 0x03, 0xc0, 0x01, 0x80
};

boolean buttonPressed;

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

  // rotate the matrix
  for(int i=0; i< MATRIX_COLUMNS*MATRIX_ROWS; i++)
    matrix.setRotation(i, 1);

  matrix.setFont(&XWindowSystemFont5x7);

  for(int i=0; i<87; i++)
    _updateSplashScreen();

  pinMode(LED_PIN, OUTPUT);
  pinMode(PUSHBUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PUSHBUTTON_PIN), interruptServiceRoutine, FALLING);
}

void Boite::_updateSplashScreen() {
  if(_intensityIncreases) {
    matrix.drawBitmap(8, 1, splashScreenBitmap, 16, 14, HIGH);
    matrix.write();
    matrix.setIntensity(_currentIntensity);
    delay(50);
    _currentIntensity++;
    if(_currentIntensity == 16) {
      _intensityIncreases = false;
      _currentIntensity--;
    }

  }
  else {
    matrix.drawBitmap(8, 1, splashScreenBitmap, 16, 14, HIGH);
    matrix.write();
    matrix.setIntensity(_currentIntensity);
    delay(50);
    _currentIntensity--;
    if(_currentIntensity == -1){
      _intensityIncreases = true;
      _currentIntensity++;
      Serial.print('.');
    }
  }
}

boolean Boite::getTiles()
{
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

boolean Boite::updateTiles()
{
  for(int i=0;i<TILES_ARRAY_SIZE; i++) {
    if(_tiles[i].getId()) {
      updateTile(i);
#ifdef DEBUG
      Serial.println(_tiles[i].asString());
#endif
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
  getApiKeyFromSerial();
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

void Boite::_fade(int id)
{
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

void Boite::getConfig() {
  preferences.begin("laboite", false);

  _ssid = preferences.getString("ssid");
  _pass = preferences.getString("pass");

  _apikey = preferences.getString("apikey");

  Serial.println(F("Here is your current laboite configuration:"));
  Serial.println("- ssid:" + _ssid);
  Serial.println("- pass:****************");
  Serial.println("- apikey:" + _apikey);
  Serial.println(F("Please send \"ssid/pass\" or \"apikey\" to change your configuration"));

  while(_ssid == "" || _pass == "" || _apikey == "") {
    String incomingSerialData = "";
    char incomingChar;
    while(Serial.available()) {
      incomingChar = Serial.read();
      incomingSerialData += incomingChar;
    }
    if(incomingSerialData != "") {
      int indexOfSlash = incomingSerialData.indexOf('/');
      if(indexOfSlash > -1) {
        _ssid = incomingSerialData.substring(0, indexOfSlash);
        Serial.println("ssid:" + _ssid + " (updated)");
        _pass = incomingSerialData.substring(indexOfSlash+1);
        Serial.println("pass:" + _pass + " (updated)");
        preferences.putString("ssid", _ssid);
        preferences.putString("pass", _pass);
      }
      else {
        Serial.println("apikey:" + incomingSerialData + " (updated)");
        _apikey = incomingSerialData;
        preferences.putString("apikey", _apikey);
      }
    }
  }
  preferences.end();
}


void Boite::getApiKeyFromSerial() {
  preferences.begin("laboite", false);
  String incomingSerialData = "";
  char incomingChar;
  while(Serial.available()) {
    incomingChar = Serial.read();
    incomingSerialData += incomingChar;
  }
  if(incomingSerialData != "") {
    Serial.println("apikey:" + incomingSerialData + " (updated)");
    _apikey = incomingSerialData;
    preferences.putString("apikey", _apikey);
    preferences.end();
    Serial.println(F("laboite restarting..."));
    ESP.restart();
  }
}
