#ifndef irisi_h
#define iris_h
class iris {

  protected:
    uint16_t _irisMin = 120;
    uint16_t _irisMax = 720;
    int8_t _lightPin = -1;
    uint16_t _iScale = 512     // Iris scale (0-1023) passed in
                       Behaviour _behaviour = NONE;

  public:
    enum Behaviour {NONE, SMOOTH};
    Iris(int8_t lightPin)_lightPin(lightPin) {


    }

    void calculateSize() {

      // check the light pin
      if (_lightPin > -1) {

        int16_t currentBrightness = analogRead(_lightPin);

        // no sensor so setup light min and max to
        // And scale to iris range (IRIS_MAX is size at LIGHT_MIN)
        v = map(v, 0, (_lightMax - _lightMin), _irisMax, _irisMin);

        if (_behaviour == Behaviour.SMOOTH) {
          static int16_t irisValue = (IRIS_MIN + IRIS_MAX) / 2;
          irisValue = ((irisValue * 15) + v) / 16;
          frame(irisValue);
        } else {
          frame(v);
        }

      } else {

      }
    }

  



  private:




};

#endif // iris_h
