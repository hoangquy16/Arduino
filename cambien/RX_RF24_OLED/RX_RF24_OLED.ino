//RX
#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <nRF24L01.h>
#include <RF24.h>
//Chân CE và CSN của module nRF24L01
RF24 radio(12, 14); // CE, CSN
//Mảng chứa địa chỉ để nhận dữ liệu
//Địa chỉ gồm 5 số (0 ~ 255)
//TX và RX phải cùng địa chỉ để có thể giao tiếp với nhau
const byte diachi[5] = {5, 10, 15, 20, 25};

//Tạo biến lưu giá trị nhận được từ TX
int nhan_duoc = 0;

#define SCREEN_WIDTH 128 //Khai báo chiều rộng của màn hình
#define SCREEN_HEIGHT 64 //Khai báo chiều cao của màn hình
#define OLED_RESET     -1 //Khai báo chân reset của màn hình
#define SCREEN_ADDRESS 0x3C ///< Địa chỉ I2C của màn hình
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
//Khởi động giao tiếp Serial
Serial.begin(115200);
//Kiểm tra thiết bị  có hoạt động không
if (!radio.begin()) {
  Serial.println("Thiết bị nRF24L01 không hoạt động!");
  while (1) {};
}
//Mở đường truyền dữ liệu với địa chỉ đã định
radio.openReadingPipe(1, diachi);
//Cài đặt bộ khuếch đại tín hiệu
radio.setPALevel(RF24_PA_HIGH);
//Chọn kênh truyền dữ liệu. Có 125 kênh từ 0 ~ 125
radio.setChannel(80);
//Đặt module nhận dữ liệu
radio.startListening();

if (!radio.available())
{
    Serial.println("Chưa kết nối với TX...!!");
    Serial.println("CHỜ KẾT NỐI......");
}
display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
display.setTextColor(WHITE);
display.setTextSize(1,2);
display.setCursor(0, 0);
display.clearDisplay();
}
void loop() {
//Nhận gói dữ liệu và in ra Serial Monitor
if (radio.available()) {
  radio.read(&nhan_duoc, sizeof(nhan_duoc));
  Serial.print("Giá trị nhận được: ");
  Serial.println(nhan_duoc);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Gia tri nhan duoc: ");
  display.setCursor(0, 20);
  display.print(nhan_duoc);
  display.display();
}
}
