#include "cubiko.h"

pt ptFaceMain;
pt ptFacePet;
pt ptFaceShake;

void checkPet() {
    int pet_index = 0;
    int i = touch_queue_head;
    while (i != touch_queue_tail) {
        if (touch_queue[i] = TOUCH_PADS[pet_index]) {
            pet_index++;
        }
        if (pet_index == 3) {
            // TODO: prompt petted animation
            break;
        }
        i = (i + 1) % TOUCH_QUEUE_LENGTH;
    }
}

int FaceMainThread(struct pt *pt) {
    PT_BEGIN(pt);
    while (true) {
        checkPet();
        PT_YIELD(pt);
    }
    PT_END(pt);
}

int FacePetThread(struct pt *pt) {
    PT_BEGIN(pt);
    while (true) {
        int maxStrength = 0;
        for (int i = 0; i < 3; i++) {
            int strength = touchRead(TOUCH_PADS[i]);
            if (strength < TOUCH_THRESHOLD) {
                if (strength < maxStrength) {
                    maxStrength = strength;
                }
            }
        }
        maxStrength = TOUCH_THRESHOLD - maxStrength - TOUCH_MIN;
        maxStrength = map(maxStrength, 0, TOUCH_THRESHOLD - TOUCH_MIN, 0, 255);
        vibrate(1000, maxStrength);
        PT_YIELD(pt);
    }
    PT_END(pt);
}

int FaceShakeThread(struct pt *pt) {
    PT_BEGIN(pt);
    while (true) {
        if (shaking()) {

        }
    }
    PT_END(pt);
}

mainState faceFunc() {
    PT_SCHEDULE(FaceMainThread(&ptFaceMain));
    PT_SCHEDULE(FacePetThread(&ptFacePet));
    PT_SCHEDULE(FaceShakeThread(&ptFaceShake));
}