/**
   Display a bar chart on an lcd displa 2 Lines 16 Cols

   GPLv3
   Visit https://fambach.net if you want
*/


/******************************************************************/
// global data
#define BAR_COUNT 16 // how many bars should we display
int values[BAR_COUNT];

#define ROWS 2        // rows of display
#define COLS 16       // columns of display
#define UPPER 1000    // upper value of measurement eg 1065 hpa 
#define LOWER 100     // lower value of measurement eg 650 hpa
#define CHAR_LINES 8  // lines in a character

/******************************************************************/
// LCD init
#include <LiquidCrystal.h>
#include "CustomChars.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void initDisplay() {
  lcd.begin(COLS, ROWS);    // start the library
  lcd.setCursor(0, 0);      // set the cursor to the upper left corner
  lcd.print("Bar Chart");   // print a simple message
  initCustomChars(lcd);     // add the own chracters 
  digitalWrite(6, LOW);     // only for my board to switch the buzzer off
  delay(2000);              // wait some seconds to show the text
}

void displayBars() {
  lcd.clear();
  // determine which is smaller the screen or the array, take the smaller one
  int end =  min(COLS ,  BAR_COUNT);

  // loop over the array with values 
  for (int col = 0; col < end ; col ++) { 

    // map the measurement values to pixel lines
    uint8_t value = map(values[col], LOWER, UPPER, 0, 16);

    // loop over the rows of the display and set the right character
    for (int row = ROWS - 1; row >= 0 ; row--) {
      lcd.setCursor(col, row);

      if (value == 0) {
        break;
      }

      if ( (value - CHAR_LINES) > 0 ) {
        lcd.write((byte) CHAR_LINES);
      } else {
        lcd.write((byte)value);
        break;
      }
      value -= CHAR_LINES;
    }

  }
  digitalWrite(6, LOW); // only for my board to switch the buzzer off

}

/******************************************************************/
// array functions
void initArray(boolean randValues) {
  for (int i = 0; i < BAR_COUNT; i++) {
    if (randValues) {
      values[i] = random(LOWER, UPPER);
    } else {
      values[i] = LOWER;
    }
  }
}

void shiftArrayToTheRight() {
  for (int i = BAR_COUNT - 1 ; i > 0 ; i--) {
    values[i] = values[i - 1];
  }
  values[0] = 0;
}

/******************************************************************/
void setup() {
  initArray(false);
  initDisplay();
}

void loop() {

  // shift array to the right
  shiftArrayToTheRight();
  // add new value at left
  values[0] = random(LOWER, UPPER);


  displayBars();
  delay(4000);

}
