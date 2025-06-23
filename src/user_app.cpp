#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <esp_heap_caps.h>
#include "lvgl_port_m5stack.hpp"
#include "lvgl.h"

extern "C" {
    #include "ebike/lv_demo_ebike.h"
    #include "lv_demos.h"
}

#define SD_SPI_SCK_PIN  36
#define SD_SPI_MISO_PIN 35
#define SD_SPI_MOSI_PIN 37
#define SD_SPI_CS_PIN   4

extern "C" void lv_fs_arduino_sd_init(void);
// extern void lottie_1_data(void);
// extern void lottie_2_json(void);
extern void lv_demo_ebike();

String file_name = "/Test500.json";

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

    if (psramInit()) {
        LV_LOG_USER("PSRAM activate OK\n");
    } else {
        LV_LOG_USER("PSRAM activate failed\n");
    }
    LV_LOG_USER(" DRAM largest free block: %d bytes\n", heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));
    LV_LOG_USER(" DRAM free size         : %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    LV_LOG_USER("PSRAM largest free block: %d bytes\n", heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM));
    LV_LOG_USER("PSRAM free size         : %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    LV_LOG_USER("Stack left: %d\n", uxTaskGetStackHighWaterMark(NULL));

    void* lv_ptr = lv_malloc(32);
    LV_LOG_USER("lv_ptr = %p\n", lv_ptr);
    void* psram_ptr = heap_caps_malloc(32, MALLOC_CAP_SPIRAM);
    LV_LOG_USER("psram_ptr = %p\n", psram_ptr);
    /*
        SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
        for (int retry = 0; retry < 5; retry++) {
            if (SD.begin(SD_SPI_CS_PIN, SPI, 25000000)) {
                LV_LOG_USER("SD card mount OK\n");
                lv_fs_arduino_sd_init();
                LV_LOG_USER("LVGL file system (Arduino SD) init OK\n");
                break;
            } else {
                LV_LOG_USER("SD card mount failed, retrying... (%d)", retry + 1);
            }
            delay(200);
        }
        File root = SD.open("/");
        while (true) {
            File entry = root.openNextFile();
            if (!entry) break;
            entry.close();
        }
        root.close();

        File f = SD.open(file_name);
        if (!f) {
            LV_LOG_USER("%s file open failed\n", file_name);
            return;
        } else {
            LV_LOG_USER("%s file size: %d\n", file_name, f.size());
            char test_buf[33] = {0};
            f.readBytes(test_buf, 32);
            LV_LOG_USER("%s\n", test_buf);
            f.close();
        }
    */
    if (lvgl_port_lock()) {
        // lv_obj_t* bg = lv_obj_create(lv_scr_act());
        // lv_obj_set_size(bg, 320, 240);
        // lv_obj_center(bg);
        // lv_obj_set_style_bg_color(bg, lv_color_black(), 0);
        // lv_obj_set_style_border_width(bg, 0, 0);
        /*
                lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), 0);

                lv_obj_t* lottie = lv_lottie_create(lv_scr_act());
                if (!lottie) {
                    LV_LOG_USER("Lottie create failed");
                    return;
                }

                // lv_lottie_set_src_file(lottie, "S:/approve.json");
                // LV_LOG_USER("Lottie set from file\n");

                File f            = SD.open(file_name);
                size_t file_size  = f.size();
                uint8_t* file_buf = (uint8_t*)heap_caps_malloc(file_size + 1, MALLOC_CAP_SPIRAM);
                if (file_buf && f) {
                    size_t read_len     = f.read(file_buf, file_size);
                    file_buf[file_size] = 0;
                    lv_lottie_set_src_data(lottie, file_buf, file_size);
                    lv_refr_now(NULL);
                    LV_LOG_USER("Lottie set from data, size = %d\n", file_size);
                }
                f.close();

        #if LV_DRAW_BUF_ALIGN == 4 && LV_DRAW_BUF_STRIDE_ALIGN == 1
                // If there are no special requirements, just declare a buffer
                // x4 because the Lottie is rendered in ARGB8888_PREMULTIPLIED format
                uint8_t* lottie_buf = (uint8_t*)heap_caps_malloc(240 * 240 * 4, MALLOC_CAP_SPIRAM);
                if (!lottie_buf) {
                    LV_LOG_USER("lottie_buf PSRAM alloc failed, try allocating in DRAM...\n");
                    lottie_buf = (uint8_t*)malloc(240 * 240 * 4);  // fallback
                    if (!lottie_buf) {
                        LV_LOG_USER("Out of memory!\n");
                        return;
                    }
                }
                lv_lottie_set_buffer(lottie, 240, 240, lottie_buf);
        #endif
                lv_obj_set_size(lottie, 240, 240);
                lv_obj_center(lottie);
                LV_LOG_USER("Lottie program finished\n");
        */
        lv_demo_ebike();

        LV_LOG_USER(" DRAM largest free block: %d bytes\n", heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));
        LV_LOG_USER(" DRAM free size         : %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
        LV_LOG_USER("PSRAM largest free block: %d bytes\n", heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM));
        LV_LOG_USER("PSRAM free size         : %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
        LV_LOG_USER("Stack left: %d\n", uxTaskGetStackHighWaterMark(NULL));

        lvgl_port_unlock();
    }
    // */
}
