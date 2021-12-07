#ifndef MAIN_H
#define MAIN_H

// ******* Constants ******** //

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#define SCROLL_CHA 5
#define SCROLL_CHB 8

#define BUTTON_PIN 10

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

void vibrate(int ms, bool vib = true);

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