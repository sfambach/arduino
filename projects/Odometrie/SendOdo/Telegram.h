#pragma once

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print (x)
#define DEBUG_PRINTLN(x) Serial.println (x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

class Telegram {


  private:
    


  public:


    const char* POS_TELEGRAM_TEMPLATE = "%d;%d;%d;";
    String sendPosTelegram(int8_t left, int8_t right) {

      String s;
      s += micros();
      s += ";";
      s += left;
      s += ";";
      s += right;
      s += ";";
      return s;
    }



};


static Telegram Tele;
