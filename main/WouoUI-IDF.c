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

#define PIN_SDA 3

#define PIN_SCL 2

#define PIN_RST 10

static const char *TAG = "ssd1306";

_Noreturn void task_test_SSD1306i2c(void *ignore) {
    setup();
    while (1){
        loop();
        vTaskDelay(10);
    }
}


void app_main(void) {
    xTaskCreatePinnedToCore(task_test_SSD1306i2c, "task_test_SSD1306i2c", 4 * 1024, NULL, 5, NULL, 1);
}
