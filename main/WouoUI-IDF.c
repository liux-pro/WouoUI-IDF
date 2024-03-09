#include <sys/cdefs.h>
#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>
#include <u8g2.h>
#include "Arduino.h"

#include "sdkconfig.h"
#include "u8g2_esp32_hal.h"



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
        vTaskDelay(10);
    }
}


void app_main(void) {
    xTaskCreatePinnedToCore(task_test_SSD1306i2c, "task_test_SSD1306i2c", 4 * 1024, NULL, 5, NULL, 1);
}
