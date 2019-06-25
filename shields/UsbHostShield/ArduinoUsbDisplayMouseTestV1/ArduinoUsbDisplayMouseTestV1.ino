/** mouse test, motion is shrinked 
* in x direction from 0 to 128 and 
* in y direction from 0 to 64 (size of an ssd 1406 display)
* www.fambach.net
* GNUv2
* 
* This example based on the example of the usb lib
* https://github.com/felis/USB_Host_Shield_2.0
 */

#include "hidboot.h"
#include "usbhub.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include "spi4teensy3.h"
#endif
#include <SPI.h>

class MouseRptParser : public MouseReportParser
{

  private:
    int _xmin = 0;
    int _xmax = 128;
    int _ymin = 0;
    int _ymax = 64;
    float _xcur = 63;
    float _ycur = 127;
    float _factor = 0.1f;

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
}

void loop()
{
  Usb.Task();
}

