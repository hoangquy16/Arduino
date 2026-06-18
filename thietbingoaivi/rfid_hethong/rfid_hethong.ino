#include <Servo.h>
Servo servo;
int R = 5;
int G = 4;
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 the_tu(SS_PIN, RST_PIN); 
byte ma_the[4] = {0, 0, 0, 0};
byte ma_dung[4] = {0x21, 0x46, 0x34, 0x98};
byte ma_den[4] = {0x93, 0x0F, 0xAF, 0x05};
void setup() { 
  servo.write(0);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  servo.attach(6);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.setTextColor(WHITE);
  Serial.begin(9600);
  SPI.begin(); 
  the_tu.PCD_Init(); 
  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(15,20);
      display.print("QUET THE");
      display.display();
}
 bool so_sanh(byte the_doc[4], byte the_so_sanh[4]) {
    for (int i = 0; i < 4; i++) {
      if (the_doc[i] != the_so_sanh[i]) {
        return false;
    }
  }
    return true; 
    }
    
void loop() {
  if ( ! the_tu.PICC_IsNewCardPresent())
    return;
  if ( ! the_tu.PICC_ReadCardSerial())
    return;

  Serial.print(F("Card UID: "));
  for (byte i = 0; i < the_tu.uid.size; i++) {
    ma_the[i] = the_tu.uid.uidByte[i];
    Serial.print(ma_the[i] < 0x10 ? "0" : "");
    Serial.print(ma_the[i], HEX);
  }
    Serial.println();
    bool ket_qua = so_sanh(ma_the, ma_dung);
    bool ket_qua_den = so_sanh(ma_the, ma_den);
    delay(100);

    if (ket_qua == true) {
      servo.write(90);
      display.clearDisplay();
      digitalWrite(R, HIGH);
      display.setTextSize(1);
      display.setCursor(0, 16);
      display.print("Your name: QUY");
      display.setCursor(0, 31);
      display.print("Age : 13");
      display.setCursor(0, 46);
      display.print("Class: 8");
      display.display();
      delay(5000);
      servo.write(0);
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(15, 20);
      display.print("QUET THE");
      display.display();
      digitalWrite(G, LOW);
    } else if (ket_qua_den == true) {
      digitalWrite(G, HIGH);
      digitalWrite(R, LOW);
      servo.write(0);
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(15, 20);
      display.print("BAT DEN");
      display.display();
    } 
    the_tu.PICC_HaltA();
    the_tu.PCD_StopCrypto1();
    delay(500);
}
