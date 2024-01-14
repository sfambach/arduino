
#include "FS.h"
#include "SD_MMC.h"

#ifndef FAILED(s1, s2)
#define FAILED(s1, s2) Serial.print("ERROR: ");Serial.print(s1);Serial.print(" ");Serial.println(s2);
#endif

#define TTGO_T18_V1_4

#if defined TTGO_T18_V1_4

#define CLK 14
#define CMD 15
#define D0 2
#define D1 4
#define D2 12
#define D3 13

#else

#define CLK 14
#define CMD 15
#define D0 2
#define D1 4
#define D2 12
#define D3 13

#endif



// commands
#define COMMAND_CREATE_DIR  "mkdir"
#define COMMAND_DELETE_DIR  "rmdir"
#define COMMAND_LIST_DIR    "ls"

#define COMMAND_CREATE_FILE "touch"
#define COMMAND_DELETE      "rm"
#define COMMAND_CAT_FILE    "cat"

// const int chipSelect = 8;


/** the card type and working status

*/
void checkSDCard() {

  // fix for E (89153) sdmmc_sd: sdmmc_init_sd_scr: send_scr (1) returned 0x109
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
 

  SD_MMC.setPins(CLK, CMD, D0); //, D1, D2, D3);

  if (!SD_MMC.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD_MMC.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD_MMC card attached");
    return;
  }

  Serial.print("SD_MMC Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
  Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);
  //SD_MMC.end();
}
/** show the content of all directories

*/
void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {

  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    root.close();
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    root.close();
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      file.rewindDirectory();
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
      file.close();
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
      file.close();

    }
   
    file = root.openNextFile();
  }
  root.close();

}

void ls() {
//  if (!SD_MMC.begin()) {
//      Serial.println("Card Mount Failed");
//      return;
//  }
  listDir(SD_MMC, "/", 5);
//
//  SD_MMC.end();
}


/** create a directory
    full path is needed
*/
void mkdir(String name) {
  Serial.printf("Creating Dir: %s\n", name);
  if (SD_MMC.mkdir(name)) {
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}


/** delete a directory
    full path is needed
*/
void rmdir(String name) {
  Serial.print(F("Delete dir: "));
  Serial.print(name);

  if (SD_MMC.rmdir(name)) {
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

void touch(String name) {
  if (name.length() < 2) {
    FAILED(F("File name to short: "), name);
    return;
  }

  File myFile = SD_MMC.open(name, FILE_WRITE);
  if (!myFile) {
    FAILED(F("Can't open file: "), name);
    return;
  }

  myFile.close();

}
void rm(String name) {

  if (name.length() < 2) {
    FAILED(F("File name to short: "), name);
    return;
  }

  if (!SD_MMC.exists(name)) {
    FAILED(F("File not found: "), name);
    return;
  }

  File myFile = SD_MMC.open(name);
  if (!myFile) {
    FAILED(F("Can't open file: "), name);
    return;
  }

  if (myFile.isDirectory()) {
    FAILED(F("File is a directory, please use rmdir "), name);
    return;
  }
  SD_MMC.remove(name);
}

void cat(String name) {
  // re-open the file for reading:
  File myFile = SD_MMC.open(name);
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
