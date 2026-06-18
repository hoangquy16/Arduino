#include <MPU6050_tockn.h>
#include <Wire.h>
//Tạo đối tượng điều khiển tên goc_nghieng
MPU6050 goc_nghieng(Wire);
void setup() {
  Serial.begin(9600);
  //Khởi tạo thư viện hỗ trợ I2C
  Wire.begin();
  //Khởi tạo cảm biến góc nghiêng
  goc_nghieng.begin();
  goc_nghieng.calcGyroOffsets(true);
}

void loop() {
  //Cập nhật giá trị góc nghiêng
  goc_nghieng.update();
  //Lấy giá trị góc nghiêng quanh trục X
  int truc_x = goc_nghieng.getAngleX();
  //Lấy giá trị góc nghiêng quanh trục Y
  int truc_y = goc_nghieng.getAngleY();
  //Lấy giá trị góc nghiêng quanh trục Z
  int truc_z = goc_nghieng.getAngleZ();

  //Hiển thị giá trị lên Serial monitor
  Serial.print("Trục X: ");
  Serial.print(truc_x);
  Serial.print(" Trục Y: ");
  Serial.print(truc_y);
  Serial.print(" Trục Z: ");
  Serial.print(truc_z);
  Serial.println();
}
