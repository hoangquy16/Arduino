#include <Arduino.h>
int ledRed = 7;
int ledGreen = 6;
char mat_khau[] = "SETA"; //Tạo một mảng char để lưu mật khẩu
char nhap_vao[30]; //Tạo một mảng char mật khẩu nhập vào (tối đa 30 ký tự)
int chi_so = 0; //Tạo một biến để lưu chỉ số của phần tử trong mảng nhap_vao
void setup() {
  Serial.begin(9600);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  Serial.println("Nhap mat khau:"); //In ra
}
void loop() {
//Chờ đến khi nhập xong mật khẩu vào Serial Monitor 
  if (Serial.available() > 0) {
    //Biến bien_ky_tu để lưu ký tự được nhập vào
    //Mặt định đọc tùng ký tự chứ không phải đọc một mảng ký tự
    char bien_ky_tu = Serial.read();
    //Serial.println(ky_tu); //In ra ký tự được nhập vào
    //nếu ký tự được nhập vào là phím Enter thì sẽ kết thúc việc nhập mật khẩu
    if (bien_ky_tu == '\n' || bien_ky_tu == '\r') {
      //Thay thế ký tự kết thúc bằng \0 (ký tự null) để kết thúc chuỗi
      nhap_vao[chi_so] = '\0';
      //Đặt lại chỉ số về 0 để chuẩn bị cho lần nhập tiếp theo
      chi_so = 0;
      //So sánh chuỗi được nhập vào với mật khẩu đã lưu
      //strcmp là hàm so sánh chuỗi, có sẵn trong Arduino ide để dùng
      //Để so sánh 2 chuỗi ký tự
      if (strcmp(nhap_vao, mat_khau) == 0) {
        Serial.println("Mat khau dung!"); //In ra nếu mật khẩu đúng
        digitalWrite(ledGreen, HIGH); //Bật đèn xanh
        digitalWrite(ledRed, LOW); //Tắt đèn đỏ
        delay(5000); //Giữ trạng thái đèn trong 5 giây
        digitalWrite(ledGreen, LOW); //Tắt đèn xanh sau 5 gi
        Serial.println("Nhap mat khau:"); //In ra để nhập mật khẩu tiếp theo
      } else {
        Serial.println("Mat khau sai!"); //In ra nếu mật khẩu sai
        digitalWrite(ledGreen, LOW); //Tắt đèn xanh
        digitalWrite(ledRed, HIGH); //Bật đèn đỏ
        delay(5000); //Giữ trạng thái đèn trong 5 giây
        digitalWrite(ledRed, LOW); //Tắt đèn đỏ sau 5 giây
        Serial.println("Nhap mat khau:"); //In ra để nhập mật khẩu tiếp theo
      }
    } else {
      //Nếu ký tự được nhập vào không phải là phím Enter (chưa kết thúc chuỗi)
      //Lưu ký tự được nhập vào phần tử hiện tại của mảng nhap_vao
      nhap_vao[chi_so] = bien_ky_tu;
      //Tăng chỉ số lên 1 để chuẩn bị cho ký tự tiếp theo
      chi_so++;
    }
}
}
