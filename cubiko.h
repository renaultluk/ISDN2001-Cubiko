#ifndef MAIN_H
#define MAIN_H

// ******* Constants ******** //

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

// ******* Finite State Machine ******** //

typedef enum {
    CASE_INIT,
    CASE_SHAKING,
    CASE_HOURGLASS,
    CASE_MINIGAME,
    CASE_IDLE,
} mainState;

mainState pageStack[10];
int pageStackSize = 0;

// ******* Utils ******* //

void vibrate(int ms, bool vib = true);

void navigateTo(mainState state);

mainState pageBack();

// ******* Gyro ******* //

bool shaking();

// ******* Buttons ******* //

// ******* Hourglass ******* //

mainState hourglassFunc();

// ******* Minigame ******* //

mainState minigameFunc();

#endif