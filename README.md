# ISDN2001-Cubiko
 
# Pinout:

VCC   3.3v

GND   GND

CS    15

RESET 4

DC    2

MOSI  23

SCK   18 

LED   3.3v

MISO  19

T_CLK 18

T_CS  21

T_DIN 23

T_DO  19

T_IRQ leave it empty

# Library use
 bodmer/TFT_eSPI@^2.3.85
 
 lvgl/lvgl@^8.1.0
 
 arduino-libraries/NTPClient@^3.1.0

/For arduino IDE/

file/preference : include: https://dl.espressif.com/dl/package_esp32_index.json

Download esp32 in board manager

choose ESP32 Dev module

braud rate 115200

# Usage (important!)
For espi library:

 library/TFT_eSPI/User_setup.h
 
 comment line 161 to line 163
 
 uncomment line 196 to line 201 and line 214 (define of pins)

For lvgl library:

 library/lvgl/lv_conf_template.h
 
 move the file to library folder and rename to lv_conf.h (same level with lvgl folder) ie. library/lv_conf.h
 
 change line 15 from #if 0 to #if 1
 
 change line 88 from #define LV_TICK_CUSTOM 0 to #define LV_TICK_CUSTOM 1 (otherwise touch won't work)
