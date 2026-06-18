#include <TM1637Display.h>

#define RED D1
#define GREEN D2
#define YELLOW D3   // dùng cho màu vàng (pha màu)

#define CLK D5
#define DIO D6

TM1637Display display(CLK, DIO);

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  display.setBrightness(7); // sáng nhất
}

// hàm đếm ngược
void countdown(int time) {
  for(int i = time; i >= 0; i--) {
    display.showNumberDecEx(i, 0, true); // hiển thị 2 số (05,04...)
    delay(1000);
  }
}

void loop() {

  // 🔴 ĐỎ (5s)
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  countdown(5);

  // 🟢 XANH (5s)
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, LOW);
  countdown(5);

  // 🟡 VÀNG (2s)
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);
  countdown(2);
}