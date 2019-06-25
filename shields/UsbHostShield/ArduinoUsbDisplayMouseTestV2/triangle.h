#ifndef triangle_h
#define triangle_h

#include "U8glib.h"
#include <math.h>
#include "shape.h"

class Triangle : public Shape {

  private:
    uint8_t xa, ya, xb, yb, xc, yc;
    uint8_t width;

  public:

    Triangle(uint8_t x, uint8_t y, uint8_t width):Shape() {
      uint8_t half = width / 2;
      xa = x - half ;
      ya = y - half;
      xb = x + half;
      yb = y - half;
      xc = x;
      yc = y + half;
      this->width = width;

    }

    void draw (U8GLIB_SSD1306_128X64 &u8g) {
      if (isSelected()) {
        u8g.drawTriangle(xa, ya, xb, yb, xc, yc);
      } else {
        //u8g.drawTriangle(xa,ya,xb,yb,xc,yc);
        u8g.drawLine(xa, ya, xb, yb) ;
        u8g.drawLine(xa, ya, xc, yc) ;
        u8g.drawLine(xb, yb, xc, yc) ;
      }
    }

   virtual bool intersects (uint8_t x, uint8_t y) {

      int abc = abs(xa*(yb - yc) + xb*(yc - ya) + xc*(ya - yb));
      int abcp = abs(xa*(yb - y) + xb*(yc - ya) + xc*(y - yb) + x*(ya - yc));
      int abpc = abs(xa*(yb - yc) +xb* (y - ya) + x*(yc - yb) + xc*(ya - y));
      int apbc = abs(xa*(y - yc) + x*(yb - ya) + xb*(yc - y) + xc*(ya - yb));

      return ( max(max(2 * abcp, 2 * abpc), 2 * apbc) <= (2 * abc));

    }


    virtual void setLocation(uint8_t x, uint8_t y) {
      uint8_t half = width / 2;

      xa = x - half ;
      ya = y - half;
      xb = x + half;
      yb = y - half;
      xc = x;
      yc = y + half;
    }


};

#endif // triangle_h
