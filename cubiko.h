#ifndef MAIN_H
#define MAIN_H

// ******* Constants ******** //

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#define SCROLL_CHA 32
#define SCROLL_CHB 33

#define BUTTON_PIN 25

#define VIBRATION_PIN 12

// ******* Variables ******** //

bool button_pressed = 0;
bool scrolled = 0;

int scroll_direction = 0;

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

void vibrate(int ms, int strength = 150);

void navigateTo(mainState state);

mainState pageBack();

// ******* Gyro ******* //

bool shaking();

// ******* Interrupts ******* //

void buttonRoutine();
void scrollRoutine();

// ******* Hourglass ******* //

mainState hourglassFunc();

// ******* Minigame ******* //

mainState minigameFunc();

#endif