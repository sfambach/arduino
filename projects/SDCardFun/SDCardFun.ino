/*
  Based on Arduino SD card test only for AVR controller

  CS Pin is 10

  Inspired by the CardInfo Example
  created  28 Mar 2011 by Limor Fried
  modified 24 July 2020 by Tom Igoe
  modified 08 March 2020 by Stefan Fambach
*/
// include the SD library:

#if defined (__AVR__)
  // everythins is ok 
#elif defined(ESP32) || defined(ESP8266)
  #error this sketch is only for arduino not for esp
#else 
  #error only for avr controllers
#endif

#include <SPI.h>
#include <SD.h>

#define FAILED(s1, s2) Serial.print("ERROR: ");Serial.print(s1);Serial.print(" ");Serial.println(s2);

// commands
#define COMMAND_CREATE_DIR  "mkdir"
#define COMMAND_DELETE_DIR  "rmdir"
#define COMMAND_LIST_DIR    "ls"

#define COMMAND_CREATE_FILE "touch"
#define COMMAND_DELETE      "rm"
#define COMMAND_CAT_FILE    "cat"


// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
File myFile;

// const int chipSelect = 8;
const int chipSelect = 10; // logger shield, Neo-6M GPS shield
// const int chipSelect = 9; // mp3 shield

/** the card type and working status

*/
void checkSDCard() {

  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    Serial.println(chipSelect);
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println(F("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card"));
    while (1);
  }

  Serial.print(F("Clusters:          "));
  Serial.println(volume.clusterCount());
  Serial.print(F("Blocks x Cluster:  "));
  Serial.println(volume.blocksPerCluster());

  Serial.print(F("Total Blocks:      "));
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print(F("Volume type is:    FAT"));
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1 KB)
  Serial.print(F("Volume size (KB):  "));
  Serial.println(volumesize);
  Serial.print(F("Volume size (MB):  "));
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print(F("Volume size (GB):  "));
  Serial.println((float)volumesize / 1024.0);

}

/** show the content of all directories

*/
void ls() {

  if (!root.openRoot(volume)) {
    FAILED(F("Cannot open volumen"), "");
    return;
  }

  root.ls(LS_R | LS_DATE | LS_SIZE);

  root.close();
}


/** create a directory
    full path is needed
*/
void mkdir(String name) {
  Serial.print(F("Create dir: "));
  Serial.print(name);

  File dir = SD.open("/", FILE_WRITE); //root.openRoot(volume);
  // dir.rewindDirectory();
  if (SD.exists(name)) {
    Serial.println(F("... Dir already exists"));
    return;
  }

  if (SD.mkdir( name)) {
    Serial.println(F("... Created "));
  } else {
    Serial.println(F("... NOT Created ERROR"));
  }
}


/** delete a directory
    full path is needed
*/
void rmdir(String name) {
  Serial.print(F("Delete dir: "));
  Serial.print(name);

  File dir = SD.open("/", FILE_WRITE); //root.openRoot(volume);
  // dir.rewindDirectory();
  if (SD.exists(name)) {

    if (SD.rmdir( name)) {
      Serial.println(F("... Deleted "));
    } else {
      Serial.println(F("... NOT Deleted ERROR"));
    }
  } else {
    FAILED(F("... dir not found: "), name);
    return;
  }
}

void touch(String name) {
  if (name.length() < 2) {
    FAILED(F("File name to short: "), name);
    return;
  }

  myFile = SD.open(name, FILE_WRITE);
  if(!myFile){
    FAILED(F("Can't open file: "),name);
    return;
  }
    
  myFile.close();

}
void rm(String name) {

  if (name.length() < 2) {
    FAILED(F("File name to short: "), name);
    return;
  }
  
  if (!SD.exists(name)) {
    FAILED(F("File not found: "), name);
    return;
  }

  myFile = SD.open(name);
  if(!myFile){
    FAILED(F("Can't open file: "),name);
    return;
  }
  
  if(myFile.isDirectory()){
    FAILED(F("File is a directory, please use rmdir "),name);
    return;
  }
  SD.remove(name);
}

void cat(String name) {
  // re-open the file for reading:
  myFile = SD.open(name);
  if (myFile) {
    Serial.print(name);
    Serial.println(" :");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    FAILED(F("Can not open File :"), name);
  }
}

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
  while (!SD.begin(chipSelect)) {
    Serial.println(F("initialization failed!"));
    delay(2000) ;
  }
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
