#include <LittleFS.h>
#include "lvgl.h"
#if LV_USE_LOTTIE

/**
 * Load an lottie animation from file
 */
void lottie_2_json(void) {
    lv_obj_t* lottie = lv_lottie_create(lv_scr_act());

    File f = LittleFS.open("/test-500.json", "r");
    if (!f) {
        LV_LOG_USER("file open failed\n");
        return;
    }
    size_t file_size  = f.size();
    uint8_t* file_buf = (uint8_t*)heap_caps_malloc(file_size, MALLOC_CAP_SPIRAM);
    if (!file_buf) {
        LV_LOG_USER("file_buf PSRAM alloc failed\n");
        f.close();
        return;
    }
    size_t readBytes = f.read(file_buf, file_size);
    f.close();
    if (readBytes != file_size) {
        LV_LOG_USER("file read failed: size mismatch\n");
        free(file_buf);
        return;
    }
    lv_lottie_set_src_data(lottie, file_buf, file_size);
    LV_LOG_USER("lottie set from data, size=%d\n", file_size);

    // lv_lottie_set_src_file(lottie, "/approve.json");
    // lv_obj_invalidate(lottie);
    // LV_LOG_USER("lv_lottie_set_src_file executed\n");

#if LV_DRAW_BUF_ALIGN == 4 && LV_DRAW_BUF_STRIDE_ALIGN == 1
    /*If there are no special requirements, just declare a buffer
      x4 because the Lottie is rendered in ARGB8888_PREMULTIPLIED format*/
    uint8_t* lottie_buf = (uint8_t*)heap_caps_malloc(240 * 240 * 4, MALLOC_CAP_SPIRAM);
    if (!lottie_buf) {
        LV_LOG_USER("PSRAM alloc failed, try allocating in DRAM...\n");
        lottie_buf = (uint8_t*)malloc(240 * 240 * 4);  // fallback
        if (!lottie_buf) {
            LV_LOG_USER("Out of memory!\n");
            return;
        }
    }
    lv_lottie_set_buffer(lottie, 240, 240, lottie_buf);
#else
    /*For GPUs and special alignment/strid setting use a draw_buf instead*/
    LV_DRAW_BUF_DEFINE(draw_buf, 64, 64, LV_COLOR_FORMAT_ARGB8888_PREMULTIPLIED);
    lv_lottie_set_draw_buf(lottie, &draw_buf);
#endif
    lv_obj_set_size(lottie, 240, 240);
    lv_obj_center(lottie);
}

#else

void lv_example_lottie_2(void) {
    /*fallback for online examples*/

    lv_obj_t* label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Lottie cannot be previewed online");
    lv_obj_center(label);
}

#endif /*LV_USE_LOTTIE*/
