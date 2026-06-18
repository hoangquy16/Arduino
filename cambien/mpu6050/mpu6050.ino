#include <MPU6050_tockn.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
//Tạo đối tượng điều khiển tên goc_nghieng
MPU6050 goc_nghieng(Wire);

#define CHAN_LED 5
#define SO_LED 12
Adafruit_NeoPixel vong_led(SO_LED, CHAN_LED, NEO_GRB + NEO_KHZ800);
uint32_t mau_so_1 = vong_led.Color(0, 255, 0);
uint32_t mau_so_2 = vong_led.Color(255, 0, 0);
uint32_t mau_so_3 = vong_led.Color(45, 0, 90);
void setup() {
  digitalww
  vong_led.begin();
  vong_led.setBrightness(50);
  vong_led.show();
  Serial.begin(9600);
  //Khởi tạo thư viện hỗ trợ I2C
  Wire.begin();
  //Khởi tạo cảm biến góc nghiêng
  goc_nghieng.begin();
  goc_nghieng.calcGyroOffsets(true);
}
void loop() {
  goc_nghieng.update();
  int truc_x = goc_nghieng.getAngleX();
  int truc_y = goc_nghieng.getAngleY();
  //Hiển thị giá trị lên Serial monitor
  Serial.print(" Trục Y: ");
  Serial.print(truc_y);
  Serial.println();

  if (truc_y < -20) {
    for (int i = 0; i < 12; i++) {
      vong_led.setPixelColor(i, mau_so_2);
      vong_led.show();
      delay(10);
    }
  } else if (truc_y > 20) {
    for (int i = 0; i < 12; i++) {
      vong_led.setPixelColor(i, mau_so_2);
      vong_led.show();
      delay(10);
    }
  } else {
    for (int i = 0; i < 12; i++) {
      vong_led.setPixelColor(i, mau_so_1);
      vong_led.show();
      delay(10);
    }
  }
}
