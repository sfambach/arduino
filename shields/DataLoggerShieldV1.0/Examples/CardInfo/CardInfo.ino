/*
  Based on Arduino SD card test

  CS Pin is 10 

  Inspired by the CardInfo Example
  created  28 Mar 2011 by Limor Fried
  modified 24 July 2020 by Tom Igoe
  modified 08 March 2020 by Stefan Fambach
*/
// include the SD library:
#include <SPI.h>
#include <SD.h>

#define FAILED(s1, s2) Serial.print("ERROR: ");Serial.print(s1);Serial.print(" ");Serial.println(s2);

// commands
#define COMMAND_CHANGE_DIR  "cd"
#define COMMAND_CREATE_DIR  "mkdir"
#define COMMAND_LIST_DIR    "ls"

#define COMMAND_CREATE_FILE "touch"
#define COMMAND_DELETE      "rm"

#define BACK ".."

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

String curDir = "/";

// change this to match your SD shield or module;
// Default SPI on Uno and Nano: pin 10
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// MKR Zero SD: SDCARD_SS_PIN


//const int chipSelect = 8;
const int chipSelect = 10; // logger shield, Neo-6M GPS shield
//const int chipSelect = 9; // mp3 shield

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
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }

  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
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


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  checkSDCard();
  ls();

}
void ls() {

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
   return;
  }
  Serial.println(F("\nFiles found on the card (name, date and size in bytes): "));
  File file = SD.open(curDir);

  if(!file){
      FAILED(F("Path not found"),curDir);
  }
  
  if(!file.isDirectory()){
      FAILED(F("Is a file not a directory "),curDir);
  }

  File subfile;
  while( (subfile = file.openNextFile())){
    
    Serial.print(subfile.isDirectory()?"D: ":"F: ");    
    Serial.print(subfile.name());    
    Serial.print('\t');    
    Serial.print(subfile.size());    
    Serial.println(" Bytes");
    
  }

  // list all files in the card with date and size
  //root.ls(LS_R | LS_DATE | LS_SIZE);
  //root.close();

  SD.end();
}

void cd(String name) {

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
   return;
  }
  
  // if name equal ...
  if(name.equals(BACK)){
    String newDir = curDir.substring(0,curDir.lastIndexOf("/"));
    Serial.print("Change dir to: ");
    Serial.print(newDir);
    if(newDir.length() <= 0){
      FAILED(F("Change to directory not possible: "),name);
      SD.end();
      return;
    }
    curDir = newDir;
  }

  // dir exists?
  if(!SD.exists(curDir+"/"+name)){
    FAILED(F("Directory does not exist: "),curDir+"/"+name);
    SD.end();
  }
  String newDir = curDir+"/"+name;
  Serial.print("Change dir to: ");
   Serial.print(newDir);
  File newRoot = SD.open(newDir);

  if(!newRoot.isDirectory()){
    FAILED(F("File is not a directory: "),newDir);
    SD.end();
    return;
  }

  // save new dir
  curDir = newDir;
  SD.end();
  

}

void mkdir(String name) {
  Serial.print(F("Create dir: "));
  Serial.print(name);


  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
   return;
  }

   File dir = SD.open("/",FILE_WRITE); //root.openRoot(volume);
  // dir.rewindDirectory();
  if(SD.exists(name)){
    Serial.println(F("... Dir already exists"));
    return;
  }

  if(SD.mkdir( name)){
    Serial.println(F("... Created "));
  } else {
    Serial.println(F("... NOT Created ERROR"));
  }

   SD.end();
}

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

  Serial.print("Command / Content : ");
  Serial.print(command);
  Serial.print(" / ");
  Serial.println(content);

  if (command.equalsIgnoreCase(COMMAND_CHANGE_DIR)){
    Serial.println(F("Change dir"));
  } if (command.equalsIgnoreCase(COMMAND_CREATE_DIR)) {
    mkdir(content);
  } if (command.equalsIgnoreCase(COMMAND_LIST_DIR)) {
    Serial.println(F("list dir"));
    ls();
  } if (command.equalsIgnoreCase(COMMAND_CREATE_FILE)) {
    Serial.println(F("Create file"));

  } if (command.equalsIgnoreCase(COMMAND_DELETE)) {
    Serial.println(F("Delete"));
  }
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
