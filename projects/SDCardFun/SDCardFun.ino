/*
  Based on Arduino SD card test only for AVR controller

  CS Pin is 10

  Inspired by the CardInfo Example
  created  28 Mar 2011 by Limor Fried
  modified 24 July 2020 by Tom Igoe
  modified 08 March 2020 by Stefan Fambach
*/
// include the SD library:

#include <SPI.h>
#include <SD.h>


#if defined (__AVR__)
  #include"AvrFunctions.h"
#elif defined(ESP32) || defined(ESP8266)
  #include"EspFunctions.h"
#else 
  #error "only for avr and esp controllers"
#endif


#define FAILED(s1, s2) Serial.print("ERROR: ");Serial.print(s1);Serial.print(" ");Serial.println(s2);

// commands
#define COMMAND_CREATE_DIR  "mkdir"
#define COMMAND_DELETE_DIR  "rmdir"
#define COMMAND_LIST_DIR    "ls"

#define COMMAND_CREATE_FILE "touch"
#define COMMAND_DELETE      "rm"
#define COMMAND_CAT_FILE    "cat"



// const int chipSelect = 8;
const int chipSelect = 10; // logger shield, Neo-6M GPS shield
// const int chipSelect = 9; // mp3 shield


/** parse user input and call the correct function

*/
void parseInput(String input, String &command, String &content) {
  int16_t indexOfSpace = input.indexOf(' ');
  Serial.print(F("Index of space: "));
  Serial.println(indexOfSpace);
  boolean hasContent = false;
  if (indexOfSpace < 2) {
    command = input;
  } else {
    command = input.substring(0, indexOfSpace);
    content = input.substring(indexOfSpace + 1, input.length());
    content.trim();
    hasContent = true;
  }
  command.trim();

  Serial.print(F("User input [Command|Content] : "));
  Serial.print(command);
  Serial.print("|");
  Serial.println(content);

  if (content.indexOf("/") != 0) {
    content = "/" + content;
  }

  if (command.equalsIgnoreCase(COMMAND_CREATE_DIR)) {
    mkdir(content);
  } else if (command.equalsIgnoreCase(COMMAND_DELETE_DIR)) {
    rmdir(content);
  } else if (command.equalsIgnoreCase(COMMAND_LIST_DIR)) {
    ls();
  } else if (command.equalsIgnoreCase(COMMAND_CREATE_FILE)) {
    touch(content);
  } else if (command.equalsIgnoreCase(COMMAND_DELETE)) {
    rm(content);
  } else if (command.equalsIgnoreCase(COMMAND_CAT_FILE)) {
    cat(content);
  }
}

/** setup sketch

*/
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  checkSDCard();
  ls();
}

void loop(void) {
  if (Serial.available()) {
    String input = Serial.readString();
    input.trim();
    Serial.println(input);
    String command;
    String content;
    parseInput(input, command, content);
  }
}
