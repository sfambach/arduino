#ifndef shape_h
#define shape_h


class Shape{
  private:
  boolean selected = false;

  protected:
  uint8_t x, y;

  public:
  Shape(){};
  virtual void draw (U8GLIB_SSD1306_128X64 &u8g)=0;
  virtual bool intersects (uint8_t x, uint8_t y)=0;
  void setSelected(boolean b){selected = b;}
  boolean isSelected(){return selected;}

  virtual void setLocation(uint8_t x, uint8_t y){
        this->x = x; this->y = y;
  }
  
  uint8_t getX(){ return x;}
  uint8_t getY(){ return y;}
  
};


#endif // shape_h
