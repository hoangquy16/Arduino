#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "Adafruit_SSD1306.h"

#define SS_PIN 10 //Chân Slave Select của module RFID là chân 10
#define RST_PIN 9 //Chân reset của module RFID là chân 9

MFRC522 the_tu(SS_PIN, RST_PIN); //Tạo đối tượng MFRC522 với tên là the_tu
//Tạo mảng để lưu trữ mã thẻ của thẻ RFID
byte ma_the[] = {0, 0, 0, 0}; //Mỗi thẻ RFID có mã là 4 byte
//Tạo mã thẻ đúng để so sánh với mã thẻ đọc được
byte ma_the_dung[4] = {0x93, 0x0F, 0xAF, 0x05}; //Thay đổi mã thẻ đúng theo mã thẻ của bạn

#define SCREEN_WIDTH 128 // OLED màn hình rộng 128 pixel
#define SCREEN_HEIGHT 64 // OLED màn hình cao 64 pixel
#define OLED_RESET -1 // Chân reset của OLED 
#define OLED_ADDRESS 0x3C // Địa chỉ I2C của OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Tạo đối tượng Adafruit_SSD1306 

String code = ""; //Biến để lưu trữ mã thẻ đọc được
void setup() {
  Serial.begin(9600); //Khởi động giao tiếp Serial với tốc độ 9600 baud
  SPI.begin(); //Khởi động giao tiếp SPI
  the_tu.PCD_Init(); //Khởi động module RFID
  Serial.println("RC522 Đã sẵn sàng"); //In ra thông báo đã khởi động module RFID
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS); //Khởi động OLED
  display.clearDisplay(); //Xóa màn hình OLED
  display.setTextSize(1,2); //Đặt kích thước chữ là 2
  display.setTextColor(WHITE); //Đặt màu chữ là trắng
  display.setCursor(0, 0); //Đặt con trỏ về góc trên bên trái
  display.println("Quet the"); //In ra dòng chữ "Ready to scan" trên OLED
  display.display(); //Cập nhật màn hình OLED
}
//Tạo hàm so sánh mã thẻ đọc được với mã thẻ đúng
bool so_sanh(byte ma_the[], byte ma_the_dung[]) {
  for (int i = 0; i < 4; i++) {
    if (ma_the[i] != ma_the_dung[i]) {
      return false; //Nếu có byte nào khác nhau thì trả về false
    }
  }
  return true; //Nếu tất cả byte đều giống nhau thì trả về true
}
void loop() {
  if (!the_tu.PICC_IsNewCardPresent() || !the_tu.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }
  //In ra mã thẻ đọc được trên Serial Monitor
  Serial.print("Ma the: ");
  for(int i = 0; i < the_tu.uid.size; i++) {
    ma_the[i] = the_tu.uid.uidByte[i]; //Lưu mã thẻ vào mảng ma_the
    if (ma_the[i] < 0x10) {
      code += "0"; //Thêm số 0 vào trước nếu byte có giá trị nhỏ hơn 16 để đảm bảo mã thẻ luôn có 8 ký tự
    }
    //Tạo biến để lưu chữ số của byte hiện tại và thêm vào biến code
    String Hexcode = String(ma_the[i], HEX); //Chuyển byte thành chuỗi hex
    code += Hexcode; //Thêm chuỗi hex vào biến code
    //Thêm khoảng trống sau mỗi số để dễ đọc
    code += " ";
  }
    //Chuyển đổi thành kí tự viết hoa 
    code.toUpperCase();
    Serial.println(code); //In ra mã thẻ trên Serial Monitor

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Ma the:");
    display.setCursor(0, 20);
    display.print(code);
    display.display();
    delay(2000); //Đợi 2 giây để hiển thị mã thẻ trên OLED
    code = ""; //Xóa biến code để chuẩn bị cho lần đọc tiếp theo

    //Chạy hàm so sánh mã thẻ đọc được với mã thẻ đúng
    bool ket_qua = so_sanh(ma_the, ma_the_dung);
    Serial.println(ket_qua); //In ra kết quả so sánh trên Serial Monitor

    if (ket_qua == true) {
      display.clearDisplay();
      display.setCursor(10, 20);
      display.print("DUNG THE!");
      display.display();
    } else {
      display.clearDisplay();
      display.setCursor(10, 20);
      display.print("SAI THE!");
      display.display();
    }
    //Hiển thị quét thẻ oled để đọc mã mới
    delay(2000); //Đợi 2 giây để hiển thị kết quả trên OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Quet the");
    display.display();

}