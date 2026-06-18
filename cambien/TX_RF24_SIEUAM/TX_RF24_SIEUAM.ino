//TX
#include <Arduino.h>
//Khai báo thư viện SPI để giao tiếp với module RF24
#include <SPI.h>
//Khai báo thư viện RF24 để điều khiển module RF24
#include <RF24.h>
//Khai báo chân CE và CSN của module RF24
RF24 radio(8, 7);
//Mảng chứa địa chỉ để gửi dữ liệu
//Địa chỉ của module RF24 (5 byte)
const byte diachi[5] = {5, 10, 15, 20, 25};

//Tạo các gói dữ liệu để gửi và nhận
int trig = 2;
int echo = 3;


void setup() {
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
//Khởi động giao tiếp Serial để hiển thị dữ liệu
  Serial.begin(9600);
//Kiểm tra thiết bị có hoat động không
    if (!radio.begin()) {
        Serial.println("Khong tim thay module RF24");
        while (1) {} // Dừng chương trình nếu không tìm thấy module
    }
//Tạo đường truyền dữ liệu theo địa chỉ đã khai báo
    radio.openWritingPipe(diachi);
//Cài đặt bộ khuếch đại công suất để tăng khoảng cách truyền
    radio.setPALevel(RF24_PA_HIGH);
//Chọn kênh truyền dữ liệu. Có 125 kênh (0-125) để tránh nhiễu sóng
    radio.setChannel(80);
//Đặt module ở chế độ phát sóng
    radio.stopListening();

    if (!radio.available())
    {
        Serial.println("Chưa kết nối được với RX...!!");
        Serial.println("CHỜ KẾT NỐI......!!");
    }    
}

void loop() {
unsigned long duration, distance;
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
duration = pulseIn(echo, HIGH);
distance = (duration / 2) / 29.1; // Tính khoảng cách dựa trên thời gian và tốc độ âm thanh
Serial.print("Khoang cach: ");
Serial.print(distance);
Serial.println(" cm");
//Gửi dữ liệu khoảng cách qua module RF24
radio.write(&distance, sizeof(distance));
delay(200); // Đợi 0,5 giây trước khi gửi dữ liệu tiếp theo
}
