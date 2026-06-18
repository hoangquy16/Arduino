#include <Servo.h>
Servo servo;

#include <Keypad.h>
const byte ROWS = 4; 
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8, 9}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String mk_dung = "2025";
String mk_nhap = "";

int R = 11;
int G = 12;
int B = 13;
void setup() {
  servo.attach(10);
  servo.write(0);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;);
  }

  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(15, 3);
  display.print("HAY NHAP MK: ");
  display.display();     // FIX 1: thiếu display.display()
}

void loop() {
  display.setTextSize(1);
  char ky_tu = customKeypad.getKey();

  if (ky_tu) {
    if (ky_tu == '#') {
      kiem_tra_mk();
    }
    else if (ky_tu == '*') {
      mk_nhap = "";
      display.clearDisplay();
      display.setCursor(15, 3);
      digitalWrite(B ,HIGH);
      digitalWrite(G ,LOW); 
      digitalWrite(R, LOW);
      display.print("HAY NHAP MK: ");
      display.display();   // FIX 2: thiếu display.display()
    }
    else {
      mk_nhap += ky_tu;
      display.setCursor(10 + (mk_nhap.length() - 1) * 6, 20); // FIX 3: tọa độ sai
      display.print('*');
      display.display();   // FIX 4: thiếu display.display()
    }
  }
}

void kiem_tra_mk() {
  display.clearDisplay();

  if (mk_nhap == mk_dung) {
    display.setTextSize(1);
    display.setCursor(15, 10);
    display.print("MK DUNG ROI");

    display.setCursor(30, 30);   // FIX 5: không trùng dòng
    display.print("MO CUA");

    display.display();
    digitalWrite(G ,HIGH);
    digitalWrite(B ,LOW); 
    digitalWrite(R, LOW);
    servo.write(90);
    delay(7000);

    display.clearDisplay();
    display.setCursor(30, 20);
    display.print("DONG CUA");
    display.display();

    servo.write(0);
    delay(2000);
  } 
  else {
    display.setCursor(15, 20);
    display.print("MK SAI");
    display.display();      
    digitalWrite(R ,HIGH);  
    digitalWrite(B ,LOW); 
    digitalWrite(G, LOW);
    delay(2000);

    display.clearDisplay();
    display.setCursor(15, 20);
    display.print("NHAP LAI!");
    display.display();          // FIX 7
    delay(2000);
  }

  mk_nhap = "";
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(15, 3);
  digitalWrite(B ,HIGH);
  digitalWrite(G ,LOW); 
  digitalWrite(R, LOW);
  display.print("HAY NHAP MK: ");
  display.display();            // FIX 8
}
