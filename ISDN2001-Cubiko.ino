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
    Serial.begin(115200);
    attachInterrupt(BUTTON_PIN, buttonRoutine, RISING);
    attachInterrupt(SCROLL_CHA, scrollRoutine, RISING);

    displayInit();
}

void loop() {
    mainState state = CASE_MINIGAME;

    while (true) {
        switch (state) {
            case CASE_INIT:
                state = initFunc();
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
