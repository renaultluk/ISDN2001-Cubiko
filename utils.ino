#include "cubiko.h"

void vibrate(int ms, int strength) {
    analogWrite(VIBRATION_PIN, strength);
    delay(ms);
    analogWrite(VIBRATION_PIN, 0);
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