#include <Arduino.h>
#include <U8g2lib.h>
#define VER "V-005"

void u8g2_print(U8G2 u8g2, int x, int y, const char *str, const uint8_t *font, const int clear_buffer);

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
void u8g2_print_ver(const char *msg);

/* ---------- OLED ------------ */

/* ---------- GPIO ------------ */
#define USER_BUTTON 0
#define LED_WHITE 35
#define RELAY_1 46
/* ---------- GPIO ------------ */

// put function declarations here:
int myFunction(int, int);

void setup()
{
  Serial.begin(115200);

  u8g2.begin();
  pinMode(USER_BUTTON, INPUT_PULLDOWN);
  pinMode(RELAY_1, OUTPUT);

  for (int i = 0; i < 3; i++)
  {
    u8g2_print_ver("EIN");
    digitalWrite(RELAY_1, HIGH);
    delay(1000);
    u8g2_print_ver("AUS");
    digitalWrite(RELAY_1, LOW);
    delay(1000);
  }
}

void u8g2_print_ver(const char *msg)
{
  u8g2_print(u8g2, 10, 45, msg, FONT_28, true);
  u8g2_print(u8g2, 10, 64, VER, FONT_11, false);
}

int current_button_state = HIGH;
void loop()
{
  int is_button = digitalRead(USER_BUTTON);
  if (is_button == LOW)
  {
    if (current_button_state == HIGH)
    {
      current_button_state = LOW;
      u8g2_print_ver("EIN");
      digitalWrite(RELAY_1, HIGH);
    }
  }
  else
  {
    if (current_button_state == LOW)
    {
      current_button_state = HIGH;
      u8g2_print_ver("AUS");
      digitalWrite(RELAY_1, LOW);
    }
  }
  // put your main code here, to run repeatedly:
}

void u8g2_print(U8G2 u8g2, int x, int y, const char *str, const uint8_t *font, const int clear_buffer)
{
  if (clear_buffer)
    u8g2.clearBuffer();
  u8g2.setFont(font);
  u8g2.drawStr(x, y, str);
  u8g2.sendBuffer();
}
