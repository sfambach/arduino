/**
 * Display a bar chart on an lcd displa 2 Lines 16 Cols
 * 
 * GPLv3
 * Visit https://fambach.net if you want
 */


/******************************************************************/
// global data
const uint8_t BAR_COUNT = 16;
int values[BAR_COUNT];
uint8_t rows = 2;
uint8_t columns = 16;


// value settings
int UPPER = 1000;
int LOWER = 100;


/******************************************************************/
// LCD init
#include <LiquidCrystal.h>
#include "CustomChars.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void initDisplay(){
   lcd.begin(columns, rows);       // start the library
   lcd.setCursor(0,0);
   lcd.print("Bar Chart"); // print a simple message
   initCustomChars(lcd);
   digitalWrite(6,LOW); // only for my board to switch the buzzer off
   delay(2000);
}

void displayBars(){
    lcd.clear();


    if( columns >= BAR_COUNT){

      // 1 bar = 1 colum, go over all columns
      for(int col = 0; col < BAR_COUNT ; col ++){
        
        uint8_t value = map(values[col], LOWER,UPPER,0,16);

        if(value > 8 ){ // upper and lower field needed
          lcd.setCursor(col,0);
          lcd.write((byte) value-8); 
          
          lcd.setCursor(col,1);
          lcd.write((byte) 8); 
          
        } else if(value > 0) {
        
            lcd.setCursor(col,1);
            lcd.write((byte)value); 
        }
      }

      
    }else {
      // not defined now
    }
    digitalWrite(6,LOW); // only for my board to switch the buzzer off
  
}


/******************************************************************/



void initArray(boolean randValues){
  for(int i =0; i < BAR_COUNT; i++){
     if(randValues){
      values[i] = random(LOWER, UPPER);      
    }else {
      values[i] = LOWER;      
    }
  }
}

void shiftArrayToTheRight(){
  for(int i = BAR_COUNT-1 ; i > 0 ; i--){
    values[i] = values[i-1];
  }

  values[0]=0;
}


/******************************************************************/


 void setup(){

    initArray(false);
    initDisplay();
  
 }



void loop(){

  //initArray(true);
  // shift array to the right
  shiftArrayToTheRight();
  // add new value at left
  values[0] = random(LOWER, UPPER); 

  
  displayBars();
  delay(4000);
  
}
