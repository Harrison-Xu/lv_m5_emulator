#include <Arduino.h>
#include <LittleFS.h>
#include <esp_heap_caps.h>
#include "lvgl_port_m5stack.hpp"
#include "lvgl.h"
// #include "demos/lv_demos.h"
// #include "examples/lv_examples.h"

extern void lottie_1_data(void);
extern void lottie_2_json(void);

void user_app(void) {
    // You can test the lvgl default demo
    /*
    if (lvgl_port_lock()) {
#if LVGL_USE_V8 == 1
        lv_demo_widgets();
#elif LVGL_USE_V9 == 1
        // lv_demo_widgets not work proerly with v9 for now :(
#if defined(ARDUINO) && defined(ESP_PLATFORM)
        lv_demo_benchmark();
#else
        // lv_demo_stress not work properly with actual devices for now :(
        lv_demo_stress();
#endif
#endif
        lvgl_port_unlock();
    }
    */

    // Or you can create your own lvgl app here
    // /*

    if (!LittleFS.begin()) {
        LV_LOG_USER("LittleFS mount failed\n");
    } else {
        LV_LOG_USER("LittleFS mount OK\n");
        File f = LittleFS.open("/RotatingCat.json", "r");
        if (!f) {
            LV_LOG_USER("file open failed\n");
        } else {
            LV_LOG_USER("file size: %d\n", f.size());
            char buf[257] = {0};
            f.readBytes(buf, 256);
            LV_LOG_USER("%s\n", buf);
            f.close();
        }
    }

    if (psramInit()) {
        LV_LOG_USER("PSRAM activate succeed\n");
    } else {
        LV_LOG_USER("PSRAM activate failed\n");
    }
    LV_LOG_USER("Free internal heap: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    LV_LOG_USER("Free PSRAM: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));

    if (lvgl_port_lock()) {
        // static lv_obj_t* btn1 = lv_btn_create(lv_scr_act());
        // lv_obj_align(btn1, LV_ALIGN_CENTER, 0, 0);
        // static lv_obj_t* label = lv_label_create(btn1);
        // lv_label_set_text(label, "Button");
        // lv_obj_center(label);

        lottie_2_json();
        LV_LOG_USER("Lottie example 2 executed\n");

        lvgl_port_unlock();
    }
    // */
}
