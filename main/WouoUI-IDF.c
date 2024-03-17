#include <sys/cdefs.h>
#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>
#include <u8g2.h>
#include <unity.h>
#include "Arduino.h"

#include "sdkconfig.h"
#include "u8g2_esp32_hal.h"
#include "iot_button.h"
#include "iot_knob.h"


static const char *TAG = "ssd1306";

_Noreturn void task_test_SSD1306i2c(void *ignore) {

#define PIN_CLK GPIO_NUM_5

// MOSI - GPIO 13
#define PIN_MOSI GPIO_NUM_2

// RESET - GPIO 26
#define PIN_RESET GPIO_NUM_7

// DC - GPIO 27
#define PIN_DC GPIO_NUM_1

// CS - GPIO 15
#define PIN_CS GPIO_NUM_0
    u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
    u8g2_esp32_hal.bus.spi.clk = PIN_CLK;
    u8g2_esp32_hal.bus.spi.mosi = PIN_MOSI;
    u8g2_esp32_hal.bus.spi.cs = PIN_CS;
    u8g2_esp32_hal.dc = PIN_DC;
    u8g2_esp32_hal.reset = PIN_RESET;
    u8g2_esp32_hal_init(u8g2_esp32_hal);
    setup();
    while (1) {
        loop();
        vTaskDelay(pdMS_TO_TICKS(3));
    }
}

void virtualShortPress();

void virtualLongPress();

void virtualCCW();

void virtualCW();

static void button_long_press_cb(void *arg, void *data) {
    virtualLongPress();
    ESP_LOGI(TAG, "button_long_press_cb");
}

static void button_short_press_cb(void *arg, void *data) {
    virtualShortPress();
    ESP_LOGI(TAG, "button_short_press_cb");
}

static void knob_left_cb(void *arg, void *data) {
    virtualCCW();
    ESP_LOGI(TAG, "KONB: KONB_LEFT");
}

static void knob_right_cb(void *arg, void *data) {
    virtualCW();
    ESP_LOGI(TAG, "KONB: KONB_right");
}

knob_handle_t s_knob;
knob_config_t cfg;

void app_main(void) {
// create knob

    cfg.default_direction = 0,
    cfg.gpio_encoder_a = 10,
    cfg.gpio_encoder_b = 6,

    s_knob = iot_knob_create(&cfg);
    if (NULL == s_knob) {
        ESP_LOGE(TAG, "knob create failed");
    }

    iot_knob_register_cb(s_knob, KNOB_LEFT, knob_left_cb, NULL);
    iot_knob_register_cb(s_knob, KNOB_RIGHT, knob_right_cb, NULL);


    xTaskCreatePinnedToCore(task_test_SSD1306i2c, "task_test_SSD1306i2c", 4 * 1024, NULL, 5, NULL, 0);
}
