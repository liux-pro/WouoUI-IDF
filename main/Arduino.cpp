#include "Arduino.h"
#include "u8g2_port.h"

#define PIN_SDA GPIO_NUM_3
#define PIN_SCL GPIO_NUM_2
#define PIN_RST GPIO_NUM_10

extern "C" {
#include "u8g2_esp32_hal.h"
};



void setup() {

    u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
    u8g2_esp32_hal.bus.i2c.sda = PIN_SDA;
    u8g2_esp32_hal.bus.i2c.scl = PIN_SCL;
    u8g2_esp32_hal.reset = PIN_RST;
    u8g2_esp32_hal_init(u8g2_esp32_hal);


    U8G2_SSD1306_128X64_ESP_I2C u8g2;
    u8g2.begin();
    u8g2.setI2CAddress(0x78);
    u8g2.setFont(u8g2_font_wqy12_t_chinese1);
    u8g2.setFontPosBaseline();
    u8g2.clearBuffer();

    u8g2.setDrawColor(1);
//    u8g2.drawStr(10, 10, "abcdef");
    u8g2.setCursor(20,20);
    u8g2.print("111111111");
    u8g2.sendBuffer();

}

void loop() {

}
