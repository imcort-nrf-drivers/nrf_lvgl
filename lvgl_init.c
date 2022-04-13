#include "lvgl_init.h"

#include "st7735.h"

void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one
     *`put_px` is just an example, it needs to implemented by you.*/
    
//    int32_t x, y;
//    for(y = area->y1; y <= area->y2; y++) {
//        for(x = area->x1; x <= area->x2; x++) {
//            ST7735_DrawPixel(x, y, *(uint16_t*)color_p);
//            color_p++;
//        }
//    }
    
    ST7735_DrawImage(area->x1, area->y1, area->x2, area->y2, (uint16_t*)color_p);
    
    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

void lv_begin(void)
{

    lv_init();
    ST7735_Init();
    ST7735_FillScreen(ST7735_BLACK);
    /*A static or global variable to store the buffers*/
    static lv_disp_draw_buf_t disp_buf;

    /*Static or global buffer(s). The second buffer is optional*/
    static lv_color_t buf_1[MY_DISP_HOR_RES * 10];

    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, MY_DISP_HOR_RES * 10);
    
    static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
    disp_drv.flush_cb = my_flush_cb;        /*Set a flush callback to draw to the display*/
    disp_drv.hor_res = MY_DISP_HOR_RES;                 /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = MY_DISP_VER_RES;                 /*Set the vertical resolution in pixels*/

    lv_disp_t * disp;
    disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

}
