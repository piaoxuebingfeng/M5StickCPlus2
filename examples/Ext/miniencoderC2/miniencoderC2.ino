/**
 * @file miniencoderC2.ino
 * @author piaoxuebingfeng
 * @brief M5StickCPlus2 with M5Unit-MiniEncoderC test
 * @version 0.1
 * @date 2024-06-24
 *
 *
 * @Hardwares: M5StickCPlus2
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5StickCPlus2: https://github.com/m5stack/M5StickCPlus2
 * M5Unit-MiniEncoderC: https://github.com/m5stack/M5Unit-MiniEncoderC.git
 */

#include "M5StickCPlus2.h"
#include "Unit_MiniEncoderC.h"


UNIT_MINIENCODERC sensor;

uint16_t delay_time = 0;
int32_t last_value  = 0;
uint8_t i2c_address = 0;


void page_get_encoder(void) {
    int32_t encoder_value = sensor.getEncoderValue();
    bool btn_status       = sensor.getButtonStatus();
    Serial.println(encoder_value);
    if (last_value != encoder_value) {
        if (last_value > encoder_value) {
            sensor.setLEDColor(1, 0x000011);
        } else {
            sensor.setLEDColor(2, 0x110000);
        }
        last_value = encoder_value;
    } else {
        // sensor.setLEDColor(0, 0x001100);
    }
    if (!btn_status) {
        sensor.setLEDColor(0, 0x001100);
    }
    // StickCP2.Display.clear();
    StickCP2.Display.fillRect(0, 0, 135, 80, BLACK);
    StickCP2.Display.setTextColor(StickCP2.Display.color565(255, 255, 255));
    StickCP2.Display.drawString("BTN:" + String(btn_status), 10, 10);
    StickCP2.Display.drawString("ENCODER:", 10, 40);
    StickCP2.Display.setCursor(10, 65);
    StickCP2.Display.setTextColor(GREEN);
    StickCP2.Display.printf("%d", encoder_value);
    StickCP2.Display.setTextColor(WHITE);
    StickCP2.Display.drawString("btnA:", 10, 120);
    StickCP2.Display.setTextColor(ORANGE);
    StickCP2.Display.drawString("get inc", 10, 150);
    StickCP2.Display.setTextColor(WHITE);
    StickCP2.Display.drawString("btnB:", 10, 180);
    StickCP2.Display.setTextColor(ORANGE);
    StickCP2.Display.drawString("reset", 10, 210);

}

void get_inc_value(void) {
    int32_t inc_value = sensor.getIncrementValue();
    Serial.printf("Inc:%d", inc_value);
}


void setup() {
    auto cfg = M5.config();
    StickCP2.begin(cfg);
    sensor.begin(&Wire, MINIENCODERC_ADDR, 0, 26, 100000UL);
    
    delay_time  = 20;
    i2c_address = sensor.getI2CAddress();

    StickCP2.Display.setRotation(0);

    StickCP2.Display.setTextSize(2);
    // StickCP2.Display.setTextColor(StickCP2.Display.color565(255, 0, 0));
    // StickCP2.Display.setCursor(6, 10);
    // StickCP2.Display.printf("HelloWorld");
    StickCP2.Display.fillRect(0, 0, 135, 90, StickCP2.Display.color565(0, 0, 0));
}

void loop() {
    StickCP2.update();
    if (StickCP2.BtnA.wasPressed()) {
      get_inc_value();
    } else if (M5.BtnB.wasPressed()) {
        sensor.resetCounter();
    }
    page_get_encoder();
}
