#include "Arduino.h"
#include "u8g2_port.h"

U8G2_SSD1306_128X64_ESP_I2C u8g2;

void setup() {
    u8g2.begin();
    u8g2.setFont(u8g2_font_wqy12_t_chinese1);
    u8g2.setFontPosBaseline();
    u8g2.clearBuffer();

    u8g2.setDrawColor(1);
    u8g2.setCursor(20,20);
    u8g2.print("111111111");
    u8g2.sendBuffer();

}

void loop() {

}
