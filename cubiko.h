#ifndef MAIN_H
#define MAIN_H

// ******* Includes ******** //

#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>

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

// ******* Display ******* //

void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );

void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );

void displayInit();

#endif