//TX
//Khai báo thư viện SPI để giao tiếp với module RF24
#include <SPI.h>
//Khai báo thư viện RF24 để điều khiển module RF24
#include <RF24.h>
//Khai báo chân CE và CSN của module RF24
RF24 radio(8, 7);
//Mảng chứa địa chỉ để gửi dữ liệu
//Địa chỉ của module RF24 (5 byte)
const byte diachi[5] = { 5, 10, 15, 20, 25 };

//Tạo các gói dữ liệu để gửi và nhận
int tat_den = 0;
int den_do = 1;
int den_xanh_la = 2;
int den_xanh_duong = 3;

void setup() {
  //Khởi động giao tiếp Serial để hiển thị dữ liệu
  Serial.begin(9600);
  //Kiểm tra thiết bị có hoat động không
  if (!radio.begin()) {
    Serial.println("Khong tim thay module RF24");
    while (1) {}  // Dừng chương trình nếu không tìm thấy module
  }
  //Tạo đường truyền dữ liệu theo địa chỉ đã khai báo
  radio.openWritingPipe(diachi);
  //Cài đặt bộ khuếch đại công suất để tăng khoảng cách truyền
  radio.setPALevel(RF24_PA_HIGH);
  //Chọn kênh truyền dữ liệu. Có 125 kênh (0-125) để tránh nhiễu sóng
  radio.setChannel(80);
  //Đặt module ở chế độ phát sóng
  radio.stopListening();

  if (!radio.available()) {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI......!!");
  }
}

void loop() {
  //Gửi lần lượt từng gói dữ liệu để điều khiển các đèn
  radio.write(&tat_den, sizeof(tat_den));
  Serial.println("TẮT ĐÈN");
  delay(2000);  //Đợi 2 giây trước khi gửi lệnh tiếp theo

  radio.write(&den_do, sizeof(den_do));
  Serial.println("BẬT ĐÈN ĐỎ");
  delay(2000);

  radio.write(&den_xanh_la, sizeof(den_xanh_la));
  Serial.println("BẬT ĐÈN XANH LÁ");
  delay(2000);

  radio.write(&den_xanh_duong, sizeof(den_xanh_duong));
  Serial.println("BẬT ĐÈN XANH DƯƠNG");
  delay(000);
}
