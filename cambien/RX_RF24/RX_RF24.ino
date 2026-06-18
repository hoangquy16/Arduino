#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//Chân CE và CSN của module nRF24L01
RF24 radio(12, 14);  // CE, CSN
//Mảng chứa địa chỉ để nhận dữ liệu
//Địa chỉ gồm 5 số (0 ~ 255)
//TX và RX phải cùng địa chỉ để có thể giao tiếp với nhau
const byte diachi[5] = { 5, 10, 15, 20, 25 };

//Tạo biến lưu giá trị nhận được từ TX
int nhan_duoc = 0;
//Khai báo các chân LED RGB
int den_do = 26;
int den_xanh_la = 25;
int den_xanh_duong = 27;
void setup() {
  //Khởi động giao tiếp Serial
  Serial.begin(115200);
  //Khởi động các chân LED
  pinMode(den_do, OUTPUT);
  pinMode(den_xanh_la, OUTPUT);
  pinMode(den_xanh_duong, OUTPUT);
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

  if (!radio.available()) {
    Serial.println("Chưa kết nối với TX...!!");
    Serial.println("CHỜ KẾT NỐI......");
  }
}

void loop() {
  //Nhận gói dữ liệu và in dữ liệu ra Serial Monitor
  if (radio.available()) {
    radio.read(&nhan_duoc, sizeof(nhan_duoc));
    Serial.println(nhan_duoc);
    //Điều khiển LED RGB dựa trên giá trị nhận được
    if (nhan_duoc == 1) {
      digitalWrite(den_do, HIGH);
      digitalWrite(den_xanh_la, LOW);
      digitalWrite(den_xanh_duong, LOW);
    } else if (nhan_duoc == 2) {
      digitalWrite(den_do, LOW);
      digitalWrite(den_xanh_la, HIGH);
      digitalWrite(den_xanh_duong, LOW);
    } else if (nhan_duoc == 3) {
      digitalWrite(den_do, LOW);
      digitalWrite(den_xanh_la, LOW);
      digitalWrite(den_xanh_duong, HIGH);
    } else {
      // Tắt tất cả LED nếu nhận được giá trị khác
      digitalWrite(den_do, LOW);
      digitalWrite(den_xanh_la, LOW);
      digitalWrite(den_xanh_duong, LOW);
    }
  }
}
