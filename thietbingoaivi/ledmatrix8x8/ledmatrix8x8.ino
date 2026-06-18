#include "LedControl.h"
//thiết lập các chân led ma trận
#define DIN 13
#define CS 12
#define CLK 11
//tạo đối tượng điều khiển tên matrix
//số 1 có nghĩa là chỉ có 1 module
//không nối tiếp nhiều module
LedControl matrix = LedControl(DIN, CLK, CS, 1);
//tạo các biểu tượng bằng mã HEX
//(Sử dụng các công cụ chuyển đổi Pixel to matrix để tạo mã Hex)
byte ngoi_nha[8]={0x18, 0x24, 0x42, 0xFF, 0x42, 0x5A, 0x5A, 0x7F};
byte mat_cuoi[8]={0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C};
byte hinh_vuong[8]={0xFF, 0x81, 0xBD, 0xA5, 0xA5, 0xBD, 0x81, 0xFF};

void setup() {
  // put your setup code here, to run once:
  matrix.shutdown(0, false); //tắt chế độ ngủ cho module 0 (thứ nhất)
  matrix.setIntensity(0, 5); //chỉnh độ sáng cho module 0 (0 - 15)
  matrix.clearDisplay(0);    //xoá màn hình
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //hiển thị biểu tượng ngôi nhà
  for (int i = 0; i < 8; i++) {
    matrix.setRow(0, i, ngoi_nha[i]);
  }
  delay(2000);

  //hiển thị biểu tượng mặt cười
  for (int i = 0; i < 8; i++) {
    matrix.setRow(0, i, mat_cuoi[i]);
  }
  delay(2000);

  //hiển thị biểu tượng hình vuông
  for (int i = 0; i < 8; i++) {
    matrix.setRow(0, i, hinh_vuong[i]);
  }
  delay(2000);
}