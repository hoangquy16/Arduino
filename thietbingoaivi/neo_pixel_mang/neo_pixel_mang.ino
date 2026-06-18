#include <Adafruit_NeoPixel.h>
#define CHAN_LED 6
#define SO_LED 12
Adafruit_NeoPixel vong_led(SO_LED, CHAN_LED, NEO_GRB + NEO_KHZ800);

uint32_t red = vong_led.Color(200, 0, 0);
uint32_t green = vong_led.Color(0, 200, 0);
uint32_t blue = vong_led.Color(0, 0, 200);
uint32_t purple = vong_led.Color(200, 0, 200);
uint32_t yellow = vong_led.Color(200, 150, 0);
uint32_t aqua = vong_led.Color(0, 150, 150);
uint32_t orange = vong_led.Color(200, 50, 0);
uint32_t white = vong_led.Color(200, 200, 200);
uint32_t jade_green = vong_led.Color(0, 255, 50);
uint32_t pink = vong_led.Color(200, 0, 10);
uint32_t tat = vong_led.Color(0, 0, 0);

// Tạo mảng chứa các màu đã tạo
uint32_t mau_rgb[12] = { red, orange, yellow, green,
                        jade_green, aqua, blue, purple,
                        aqua, orange, pink, white };

void setup() {
  Serial.begin(9600);
    vong_led.begin();
    vong_led.setBrightness(50);
    vong_led.show();
}
void loop() {
  //Hiệu ứng chạy đèn thuận chiều kim đồng hồ
  for (int i = 0; i < 12; i++) {
    vong_led.setPixelColor(i, mau_rgb[i]);
    vong_led.show();
    delay(50);
  }
  //Hiệu ứng chạy đèn ngược chiều kim đồng hồ
  for (int i = 11; i >= 0; i--) {
    vong_led.setPixelColor(i, mau_rgb[i]);
    vong_led.show();
    delay(50);
  }
  delay(1000);
  //Hiệu ứng chớp tắt tất cả các đèn
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 12; i++) {
      vong_led.setPixelColor(i, tat);
    }
    vong_led.show();
    delay(500);
    for (int i = 11; i >= 0; i--) {
      vong_led.setPixelColor(i, mau_rgb[11 - i]);
      vong_led.show();
    }
    delay(500);
  }
}
