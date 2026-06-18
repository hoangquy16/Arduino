#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int number_1 = 0;
int number_2 = 0;

void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
    }
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Nhap 2 so:");
  display.display();
}
void loop() {
  //Chờ đến khi có dữ liệu từ Serial
  if (Serial.available() > 0) {
    //Gán giá trị từ Serial vào biến number_1 và number_2
    number_1 = Serial.parseInt();
    number_2 = Serial.parseInt();
    //Xoá các dữ liệu thừa trong bộ nhớ đệm
    while (Serial.available() > 0) {
      Serial.read();
    }
  //Hiển thị số vừa nhập lên Serial Monitor
  Serial.print("Số thứ nhất: ");
  Serial.println(number_1);
  Serial.print("Số thứ hai: ");
  Serial.println(number_2);
  
  //Bất đầu tính toán
  int tong = number_1 + number_2;
  int hieu = number_1 - number_2;

  //Hiển thị kết quả tính tổng lên OLED
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(number_1);
  display.print(" + ");
  display.print(number_2);
  display.setCursor(0,20);
  display.print(" = ");
  display.print(tong);
  display.display();
  delay(4000);

  //Hiển thị kết quả tính hiệu 
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(number_1);
  display.print(" - ");
  display.print(number_2);
  display.setCursor(0,20);
  display.print(" = ");
  display.print(hieu);
  display.display();
  delay(4000);

  //Hiển thị nhập số trên oled
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Nhap 2 so:");
  display.display();
}
}