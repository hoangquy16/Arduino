#include <Stepper.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int mot_vong = 2048;

int button_trai = 8;
int button_phai = 9;

Stepper dc_buoc(mot_vong, 4, 6, 5, 7);

// BIẾN ĐẾM SỐ BƯỚC THỰC TẾ
long so_buoc = 0;

void setup() {
  Serial.begin(9600);

  pinMode(button_trai, INPUT);
  pinMode(button_phai, INPUT);
  
  dc_buoc.setSpeed(10);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1,2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int gt_trai = digitalRead(button_trai);
  int gt_phai = digitalRead(button_phai);

  display.clearDisplay();

  if (gt_trai == 1) {
    dc_buoc.step(mot_vong / 2);
    so_buoc += mot_vong / 2;
    delay(300);
  }

  if (gt_phai == 1) {
    dc_buoc.step(-mot_vong / 2);
    so_buoc -= mot_vong / 2;
    delay(300);
  }

  display.setCursor(0, 0);
  display.print("So buoc: ");
  display.print(so_buoc);

  display.display();
}
