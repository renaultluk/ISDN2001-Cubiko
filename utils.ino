#include "cubiko.h"

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

void buttonRoutine() {
    button_pressed = 1;
}

void scrollRoutine() {
    scrolled = 1;
    if (digitalRead(SCROLL_CHB) == LOW) {
        scroll_direction = 1;
    } else {
        scroll_direction = -1;
    }
}