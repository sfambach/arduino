// Usb Mouse and Display test
// www.fambach.net
// GPLv2
/***************************************************************************/

#include "hidboot.h"
#include "usbhub.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include "spi4teensy3.h"
#endif
#include <SPI.h>


/***************************************************************************/
#include "U8glib.h"
#include "shape.h"
#include "triangle.h"
#include "rect.h"
#include "circle.h"
#include "cursor.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI

uint8_t width = 20;
uint8_t dist = (128 / 4);
Circle   circ(dist, 64 / 2, width);
Triangle tri(dist * 2, 64 / 2, width);
Rect    rect(dist * 3, 64 / 2, width);
Cursor curs(0, 32, 4);

Shape* shapes[] = {&circ, &tri, &rect, &curs};

uint8_t draw_state = 0;


void draw(void) {
  u8g.setDefaultForegroundColor();
  uint8_t height = 20;
  bool invertCursor = false;
  for (int i = 0; i < 4; i++) {

    boolean b = shapes[i]->intersects(curs.getX(),curs.getY());
    invertCursor = (invertCursor || b);
    shapes[i]->setSelected(b);
    shapes[i]->draw(u8g);
  }
  curs.setSelected(invertCursor);
  curs.draw(u8g);

}
/***************************************************************************/

class MouseRptParser : public MouseReportParser
{

  private:
    int _xmin = 0;
    int _xmax = 128;
    int _ymin = 0;
    int _ymax = 64;
    float _xcur = 64;
    float _ycur = 128;
    float _factor = 0.2f;

  protected:
    void OnMouseMove  (MOUSEINFO *mi);
    void OnLeftButtonUp (MOUSEINFO *mi);
    void OnLeftButtonDown (MOUSEINFO *mi);
    void OnRightButtonUp  (MOUSEINFO *mi);
    void OnRightButtonDown  (MOUSEINFO *mi);
    void OnMiddleButtonUp (MOUSEINFO *mi);
    void OnMiddleButtonDown (MOUSEINFO *mi);
};
void MouseRptParser::OnMouseMove(MOUSEINFO *mi)
{

  _xcur += mi->dX * _factor;

  if(_xcur > _xmax){
    _xcur = _xmax;
  }

  if(_xcur < _xmin){
    _xcur = _xmin;
  }
  
  _ycur += mi->dY * _factor;

   if(_ycur > _ymax){
    _ycur = _ymax;
  }

  if(_ycur < _ymin){
    _ycur = _ymin;
  }

  Serial.print("dx=");
  Serial.print(mi->dX, DEC);
  Serial.print(" dy=");
  Serial.print(mi->dY, DEC);

  Serial.print(" xCur=");
  Serial.print(_xcur, DEC);

  Serial.print(" yCur=");
  Serial.println(_ycur, DEC);

  curs.setLocation(_xcur, _ycur);
  draw();
  
  
};
void MouseRptParser::OnLeftButtonUp (MOUSEINFO *mi)
{
  Serial.println("L Butt Up");
};
void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi)
{
  Serial.println("L Butt Dn");
};
void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi)
{
  Serial.println("R Butt Up");
};
void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi)
{
  Serial.println("R Butt Dn");
};
void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi)
{
  Serial.println("M Butt Up");
};
void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi)
{
  Serial.println("M Butt Dn");
};

USB     Usb;
USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE>    HidMouse(&Usb);

MouseRptParser                               Prs;

void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  HidMouse.SetReportParser(0, &Prs);

  #if defined(ARDUINO)
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
#endif

}

void loop()
{
  Usb.Task();
   // picture loop
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
}

