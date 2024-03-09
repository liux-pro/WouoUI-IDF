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


static const char *TAG = "ssd1306";

_Noreturn void task_test_SSD1306i2c(void *ignore) {
#define PIN_SDA GPIO_NUM_3
#define PIN_SCL GPIO_NUM_2
#define PIN_RST GPIO_NUM_10
    u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
    u8g2_esp32_hal.bus.i2c.sda = PIN_SDA;
    u8g2_esp32_hal.bus.i2c.scl = PIN_SCL;
    u8g2_esp32_hal.reset = PIN_RST;
    u8g2_esp32_hal_init(u8g2_esp32_hal);
    setup();
    while (1) {
        loop();
//        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
void virtualShortPress();
void virtualLongPress();
static void button_long_press_cb(void *arg, void *data)
{
    virtualLongPress();
    ESP_LOGI(TAG, "button_long_press_cb");
}
static void button_short_press_cb(void *arg, void *data)
{
    virtualShortPress();
    ESP_LOGI(TAG, "button_short_press_cb");
}
static void button_left_cb(void *arg, void *data)
{

    ESP_LOGI(TAG, "button_left_cb");
}
static void button_right_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "button_right_cb");
}


static button_handle_t g_btns[4] = {0};

void app_main(void) {
    button_config_t cfg = {
            .type = BUTTON_TYPE_MATRIX,
            .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS,
            .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS,
            .matrix_button_config = {
                    .row_gpio_num = 0,
                    .col_gpio_num = 0,
            }
    };

    cfg.matrix_button_config.row_gpio_num = 5;
    cfg.matrix_button_config.col_gpio_num = 8;
    g_btns[0] = iot_button_create(&cfg);
    TEST_ASSERT_NOT_NULL(g_btns[0]);
    iot_button_register_cb(g_btns[0], BUTTON_PRESS_DOWN, button_long_press_cb, NULL);

    cfg.matrix_button_config.row_gpio_num = 5;
    cfg.matrix_button_config.col_gpio_num = 9;
    g_btns[1] = iot_button_create(&cfg);
    TEST_ASSERT_NOT_NULL(g_btns[1]);
    iot_button_register_cb(g_btns[1], BUTTON_PRESS_DOWN, button_short_press_cb, NULL);

    cfg.matrix_button_config.row_gpio_num = 4;
    cfg.matrix_button_config.col_gpio_num = 8;
    g_btns[2] = iot_button_create(&cfg);
    TEST_ASSERT_NOT_NULL(g_btns[2]);
    iot_button_register_cb(g_btns[2], BUTTON_PRESS_DOWN, button_left_cb, NULL);


    cfg.matrix_button_config.row_gpio_num = 4;
    cfg.matrix_button_config.col_gpio_num = 9;
    g_btns[3] = iot_button_create(&cfg);
    TEST_ASSERT_NOT_NULL(g_btns[3]);
    iot_button_register_cb(g_btns[3], BUTTON_PRESS_DOWN, button_right_cb, NULL);


    xTaskCreatePinnedToCore(task_test_SSD1306i2c, "task_test_SSD1306i2c", 4 * 1024, NULL, 5, NULL, 0);
}
