#include "cubiko.h"

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ SCREEN_WIDTH * 10 ];
TFT_eSPI tft = TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT); /* TFT instance */

void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
//void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
//{
//    uint16_t touchX, touchY;
//    
//    bool touched = tft.getTouch( &touchX, &touchY, 600 );
//
//    if( !touched )
//    {
//        data->state = LV_INDEV_STATE_REL;
//        
//    }
//    else
//    {
//        data->state = LV_INDEV_STATE_PR;
//
//        /*Set the coordinates*/
//        data->point.x = touchX;
//        data->point.y = touchY;
//    }
//}

void displayInit(){
    lv_init();

    tft.begin();          
    tft.setRotation( 2 );

    uint16_t calData[5] = { 437, 3509, 269, 3588, 0 };
//    tft.setTouch(calData);

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, SCREEN_WIDTH * 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
//    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );

//    lv_port_disp_init();
//    lv_port_indev_init();
//    lv_port_fs_init();
}
