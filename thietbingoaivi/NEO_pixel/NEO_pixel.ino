#include <Adafruit_NeoPixel.h>
#define CHAN_LED 6
#define SO_LED 12
Adafruit_NeoPixel vong_led(SO_LED, CHAN_LED, NEO_GRB + NEO_KHZ800);

uint32_t mau_so_1 = vong_led.Color(23,150,0);
uint32_t mau_so_2 = vong_led.Color(255,30,8);
uint32_t mau_so_3 = vong_led.Color(45, 0,90);
void setup() {
  Serial.begin(9600);
  vong_led.begin();
  vong_led.setBrightness(50);
  vong_led.show();
}

void loop() {
  for (int i = 0; i < 12; i++) {
    vong_led.setPixelColor(i, mau_so_1);
    vong_led.show();
    delay(100);
  } 
  for (int i = 0; i < 12; i++) {
    vong_led.setPixelColor(i, mau_so_2);
    vong_led.show();
    delay(100);
  }
  for (int i = 0; i < 12; i++) {
    vong_led.setPixelColor(i, mau_so_3);
    vong_led.show();
    delay(100);
  }
}
