#include "cubiko.h"

int field_arr[3] = {0, 0, 0};   // second, minute, hour
int field_num = 0;

int countdown_seconds = 0;
bool countdown_active = false;

// ******* temp ******* //
bool scrollup = true;
bool scrolldown = true;
bool switchtimebuttonclicked = true;

void showTimer() {

}

int toSeconds(int hours, int minutes, int seconds) {
    return (hours * 3600) + (minutes * 60) + seconds;
}

void setTime() {
    float last_x = 0;
    float last_y = 0;
    float last_z = 0;
    while (!flipped(last_x, last_y, last_z)) {
        if (switchtimebuttonclicked) {
            field_num = (field_num + 1) % 3;
        }
        if (scrollup) {
            if ((field_arr[field_num] + 1 > 59) && (field_num != 2)) {
                field_arr[field_num+1] += 1;
            }
            field_arr[field_num] = (field_arr[field_num] + 1) % 60;
        } 
        if (scrolldown) {
            field_arr[field_num] = (field_arr[field_num] - 1 < 0)? 0 : field_arr[field_num] - 1;
        }
    }
    countdown_seconds = toSeconds(field_arr[2], field_arr[1], field_arr[0]);
    showTimer();
    countdown_active = true;
}

void countdown() {
    while (countdown_seconds > 0) {
        if (switchtimebuttonclicked) {
            countdown_active = !countdown_active;
        }
        if (countdown_active) {
            delay(1000);
            countdown_seconds--;
        }
    }
}

void goOff() {
    bool stopped;
    while (!stopped) {
        vibrate(500);
        vibrate(500, false);
        if (switchtimebuttonclicked) {
            stopped = true;
        }
    }
}

mainState hourglassFunc() {
    setTime();
    countdown();
    goOff();
}
