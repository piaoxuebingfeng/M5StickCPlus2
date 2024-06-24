/**
 * @file lcdshow.ino
 * @author piaoxuebingfeng
 * @brief M5StickCPlus2 Display Test
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
 */

#include "M5StickCPlus2.h"



void setup() {
    auto cfg = M5.config();
    StickCP2.begin(cfg);
    StickCP2.Display.setRotation(3);

    StickCP2.Display.setTextSize(2);
    StickCP2.Display.setTextColor(StickCP2.Display.color565(255, 0, 0));
    StickCP2.Display.setCursor(6, 10);
    StickCP2.Display.printf("HelloWorld");
}

void loop() {
    delay(1000);
}
