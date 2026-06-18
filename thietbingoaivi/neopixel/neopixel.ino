#include <Adafruit_NeoPixel.h>
#define CHAN_LED 6
#define SO_LED 12
Adafruit_NeoPixel vong_led(SO_LED, CHAN_LED, NEO_GRB + NEO_KHZ800);

uint32_t mau_so_1 = vong_led.Color(23,150,0);
uint32_t mau_so_2 = vong_led.Color(255,30,8);
uint32_t mau_so_3 = vong_led.Color(45, 0,90);
uint32_t mau_so_4 = vong_led.Color(0, 150,150);
uint32_t tat_Den = vong_led.Color(0, 0,0);

int x = A0;
int y = A1;
void setup() {
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  Serial.begin(9600);
  vong_led.begin();
  vong_led.setBrightness(50);
  vong_led.show();
}

void loop() {
  int gt_x = analogRead(x);
  int gt_y = analogRead(y);
  Serial.print("Giá trị X: ");
  Serial.print(gt_x);
  Serial.println();
  Serial.print("Giá trị Y: ");
  Serial.print(gt_y);
  Serial.println();
  if (gt_x < 200) {
    for (int i = 0; i < 12; i++) {
      vong_led.setPixelColor(i, mau_so_1);
      vong_led.show();
      delay(100);
    } 
  }
  else if (gt_x > 800) {
    for (int i = 0; i < 12; i++) {
      vong_led.setPixelColor(i, mau_so_2);
      vong_led.show();
      delay(100);
    } }
    else if (gt_y < 200) {
    for (int i = 0; i < 12; i++) {
      vong_led.setPixelColor(i, mau_so_3);
      vong_led.show();
      delay(100);
    }}
    else if (gt_y > 800) {
    for (int i = 0; i < 12; i++) {
      vong_led.setPixelColor(i, mau_so_4);
      vong_led.show();
      delay(100);
    }
   }else {
      for (int i = 0; i < 12; i++) {
      vong_led.setPixelColor(i, tat_Den);
      vong_led.show();
      delay(100);
    }
    delay(10);}
}
