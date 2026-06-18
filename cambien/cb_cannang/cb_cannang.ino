#include <Arduino.h>
#include <HX711.h>

#define DOT 5
#define SCK 6

//Thiết lập các thông số hiệu chuẩn cho cảm biến lực
long khong_vat = 398000; // Giá trị đọc khi không có vật
long vat_chuan = 344500; // Giá trị đọc khi có vật 
int can_chuan = 50; // Trọng lượng của vật chuẩn (đơn vị: gram)
HX711 loadcell;

void setup() {
  Serial.begin(9600);
  // Thiết lập cảm biến lực
  loadcell.begin(DOT, SCK);
  // Hiệu chuẩn cảm biến lực
  float hieu_chuan = (float)(vat_chuan - khong_vat) / can_chuan;
  loadcell.set_scale(hieu_chuan);
  loadcell.tare(); //Tạo đối tượng tare để thiết lập điểm không
}
void loop() {
  // Đọc giá trị trọng lượng từ cảm biến lực
  float trong_luong = loadcell.get_units(10); // Đọc trung bình của 10 lần đo
  Serial.print("Trọng lượng: ");
  Serial.print(trong_luong);
  Serial.println(" g");
  delay(1000); // Đợi 1 giây trước khi đọc lại
} 
