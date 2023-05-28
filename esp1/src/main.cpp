#include <Arduino.h>
#include <U8g2lib.h>

void u8g2_print(int x, int y, const char* str, const uint8_t* font, const int clear_buffer);

/* ---------- OLED ------------ */
#define OLED_RESET 21
#define OLED_DATA 17
#define OLED_CLOCK 18

#define FONT_14 u8g2_font_profont22_tf
#define FONT_11 u8g2_font_t0_17_tf
#define FONT_21 u8g2_font_logisoso22_tf
#define FONT_28 u8g2_font_logisoso28_tf
#define FONT_38 u8g2_font_logisoso38_tf
#define FONT_50 u8g2_font_logisoso50_tf

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_RESET, OLED_CLOCK, OLED_DATA);
/* ---------- OLED ------------ */

/* ---------- BUTTON ------------ */
#define USER_BUTTON 0
/* ---------- BUTTON ------------ */

int count = 0;
char buf[100]; 

void setup() {
  pinMode(USER_BUTTON, INPUT_PULLDOWN);
  u8g2.begin();
  sprintf(buf, "%04d", count++);
  u8g2_print(2, 37, buf, FONT_21, true);
}

void loop() {
  int btn_state = digitalRead(USER_BUTTON);
  if (!btn_state) sprintf(buf, "%04d", count++);
  u8g2_print(2, 37, buf, FONT_21, true);
  delay(50);
}

void u8g2_print(int x, int y, const char* str, const uint8_t* font, const int clear_buffer) {
  if (clear_buffer) u8g2.clearBuffer();
  u8g2.setFont(font);
  u8g2.drawStr(x, y, str);
  u8g2.sendBuffer();
}
