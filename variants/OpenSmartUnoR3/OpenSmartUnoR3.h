#ifndef OpenSmartUnoR3_h
#define OpenSmartUnoR3_h

#define LED1 
#define LED2
#define LED3
#define SW1
#define SW2
#define SW3
#define BUZZER 



class OpenSmartUnoR3 {
  

private:
bool _test = false;
  public:
enum SWITCH{
  SW1,
  SW2,
  SW3
  
};
  static void init(bool test = false){
    _test = test;
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    pinMode(SW1, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);
    pinMode(SW3, INPUT_PULLUP);
    
  }

  static void loop(){
    if(_test){
      // do something hers  
    }
  }

  bool getSwitch(SWITCH sw){
    
    
  }


  
};






#endif // OpenSmartUnoR3_h
