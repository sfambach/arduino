#ifndef rect_h
#define rect_h

#include "U8glib.h"
#include <math.h>
#include "shape.h"

class Rect : public Shape {

  private:
    uint8_t width;

  public:

    Rect(uint8_t x, uint8_t y, uint8_t width):Shape() {
      uint8_t halfw = width / 2;

      this->x = x - halfw;
      this->y = y - halfw;
      this->width = width;

    }

    void draw (U8GLIB_SSD1306_128X64 &u8g) {
      if (isSelected()) {
        u8g.drawBox( x , y , width, width);
      } else {
        u8g.drawFrame( x , y , width, width);
      }
    }

    virtual bool intersects (uint8_t x, uint8_t y) {

      if (x > this->x + width) {
        return false;
      } else if ( x < this->x) {
        return false;
      } else if (y > this->y + width) {
        return false;
      } else if (y < this->y) {
        return false;
      }
      return true;
    }

    virtual void setLocation(uint8_t x, uint8_t y) {
      uint8_t halfw = width / 2;

      this->x = x - halfw;
      this->y = y - halfw;
    }
};


#endif // rect_h
