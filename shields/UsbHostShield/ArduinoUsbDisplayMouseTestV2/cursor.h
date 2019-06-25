#ifndef cursor_h
#define cursor_h

#include "U8glib.h"
#include <math.h>
#include "shape.h"

class Cursor : public Shape {

  private:
    uint8_t radius;

  public:

    Cursor(uint8_t x, uint8_t y, uint8_t width):Shape() {

      this->x = x ;
      this->y = y ;
      this->radius = width / 2;

    }

    void draw (U8GLIB_SSD1306_128X64 &u8g) {
      if (isSelected()) {
         
        u8g.setDefaultBackgroundColor();
        u8g.drawDisc( x , y , radius);
        u8g.setDefaultForegroundColor();
        
      } else {
        u8g.drawCircle( x , y , radius);
      }
    }

   virtual bool intersects (uint8_t x, uint8_t y) {
       return false;
    }

    
};


#endif // cursor_h
