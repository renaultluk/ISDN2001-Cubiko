#include "cubiko.h"

void setTime() {

}

void goOff() {
    bool stopped;
    while (!stopped) {
        vibrate(500);
        vibrate(500, false);
//        if (digitalRead(STOP_PIN) == HIGH) {
//            stopped = true;
//        }
    }
}

mainState hourglassFunc() {
  // do nothing here
}
