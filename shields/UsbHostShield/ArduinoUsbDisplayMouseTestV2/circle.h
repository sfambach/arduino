#ifndef circle_h
#define circle_h

#include "U8glib.h"
#include <math.h>
#include "shape.h"

class Circle : public Shape {

  private:
    uint8_t radius;

  public:

    Circle(uint8_t x, uint8_t y, uint8_t width):Shape() {

      this->x = x ;
      this->y = y ;
      this->radius = width / 2;

    }

    void draw (U8GLIB_SSD1306_128X64 &u8g) {
      if (isSelected()) {
        u8g.drawDisc( x , y , radius);
      } else {
        u8g.drawCircle( x , y , radius);
      }
    }

   virtual bool intersects (uint8_t x, uint8_t y) {
       uint8_t res = sqrt(pow(x - this->x,2) + pow(y - this->y,2));
       return res <= radius;  
    }

    
};


#endif // circle_h
