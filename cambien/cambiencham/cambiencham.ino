#include <Arduino.h> // Khai báo thư viện Arduino
#include <Servo.h>   // Khai báo thư viện để điều khiển động cơ Servo
Servo servo;         // Tạo một đối tượng servo để điều khiển
int cbcham = 7;      // Khai báo chân số 7 kết nối với cảm biến chạm
int so_lan = 0;      // Biến lưu trữ số lần chạm, bắt đầu từ 0

void setup() {
  Serial.begin(9600);      // Bắt đầu giao tiếp Serial với tốc độ 9600 baud
  pinMode(cbcham, INPUT);  // Đặt chân cảm biến chạm (số 7) làm đầu vào (nhận tín hiệu)
  servo.attach(6);         // Gắn động cơ servo vào chân số 6
}

void loop() {
  int giatricb = digitalRead(cbcham); // Đọc trạng thái từ cảm biến chạm (1: chạm, 0: không chạm)
  Serial.print("CB Cham:  ");         // In chữ "CB Cham:  " ra Serial Monitor
  Serial.print(giatricb);             // In giá trị đọc được từ cảm biến
  Serial.println();                   // Xuống dòng
  delay(100);                         // Tạm dừng 100ms để ổn định vòng lặp

  if (giatricb == 1) {       // Nếu phát hiện có người chạm (giá trị bằng 1)
    so_lan = so_lan + 1;     // Cộng thêm 1 vào số lần đếm
    delay(300);              // Tạm dừng 300ms (chống nhiễu tín hiệu) tránh nhận 1 lần thành nhiều lần
  } 
  
  // Dựa vào số lần chạm để điều khiển góc quay của servo
  if (so_lan == 0) {
    servo.write(0);          // Nếu là 0, servo quay về 0 độ
  } else if (so_lan == 1) {
    servo.write(45);         // Nếu chạm 1 lần, servo quay đến góc 45 độ
  } else if (so_lan == 2) {
    servo.write(90);         // Nếu chạm 2 lần, servo quay đến góc 90 độ
  } else if (so_lan == 3) {
    servo.write(135);        // Nếu chạm 3 lần, servo quay đến góc 135 độ
  } else if (so_lan == 4) {
    servo.write(180);        // Nếu chạm 4 lần, servo quay đến góc 180 độ
  } else if (so_lan == 5) {
    so_lan = 0;              // Nếu chạm 5 lần, reset đếm về 0 để khởi động chu kỳ mới
  }
}
