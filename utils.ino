#include "cubiko.h"

#define VIBRATION_PIN 2

void vibrate(int ms, bool vib) {
    digitalWrite(VIBRATION_PIN, vib);
    delay(ms);
    digitalWrite(VIBRATION_PIN, LOW);
}

void navigateTo(mainState currentState) {
    pageStack[pageStackSize] = currentState;
    pageStackSize++;
}

mainState pageBack() {
    pageStackSize--;
    vibrate(50, true);
    return pageStack[pageStackSize - 1];
}