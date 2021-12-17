#include "cubiko.h"


mainState initFunc() {
    if (shaking()) {
        return CASE_SHAKING;
    }
}

mainState shakingFunc() {

}

mainState idleFunc() {

}

void setup() {
    attachInterrupt(BUTTON_PIN, buttonRoutine, RISING);
    attachInterrupt(SCROLL_CHA, scrollRoutine, RISING);

    touchAttachInterrupt(T4, T4touchPadRoutine, TOUCH_THRESHOLD);
    touchAttachInterrupt(T5, T5touchPadRoutine, TOUCH_THRESHOLD);
    touchAttachInterrupt(T6, T6touchPadRoutine, TOUCH_THRESHOLD);
}

void loop() {
    mainState state = CASE_INIT;

    while (true) {
        switch (state) {
            case CASE_INIT:
                state = initFunc();
                break;
            case CASE_FACE:
                state = faceFunc();
                break;
            case CASE_SHAKING:
                state = shakingFunc();
                break;
            case CASE_HOURGLASS:
                navigateTo(state);
                state = hourglassFunc();
                break;
            case CASE_MINIGAME:
                navigateTo(state);
                state = minigameFunc();
                break;
            case CASE_IDLE:
                state = idleFunc();
                break;
        }
    }
}