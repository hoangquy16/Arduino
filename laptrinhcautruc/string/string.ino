//Serial + String + led
#include <Arduino.h>
int led = 9;
String nhap_vao = ""; //Biến lưu lệnh nhập vào từ Serial Monitor
void setup() {  
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  // In ra Serial Monitor hướng dẫn người dùng nhập lệnh
  Serial.println("Nhap lenh on hoac off de bat tat den LED");
} 
void loop() {
  if (Serial.available() > 0) {
    // Đọc lệnh từ Serial Monitor
    // \n là phím enter (phím xuong dòng) để kết thúc lệnh
    nhap_vao = Serial.readStringUntil('\n');
    nhap_vao.trim(); // Loại bỏ khoảng trắng thừa
    // Kiểm tra lệnh và điều khiển LED
    if (nhap_vao == "on") {
      digitalWrite(led, HIGH); // Bật LED
      Serial.println("BAT DEN");
    } else if (nhap_vao == "off") {
      digitalWrite(led, LOW); // Tắt LED
      Serial.println("TAT DEN");
    } else
    {
      Serial.println("Chi nhap on hoac off.");
    }
  }
}