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

void touchPadRoutine() {
    touch_queue[touch_queue_tail] = T4;
    touch_queue_tail = (touch_queue_tail + 1) % TOUCH_QUEUE_LENGTH;
    if (touch_queue_tail == touch_queue_head) {
        touch_queue_head = (touch_queue_head + 1) % TOUCH_QUEUE_LENGTH;
    }
}