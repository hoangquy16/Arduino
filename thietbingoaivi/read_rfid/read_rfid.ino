#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 the_tu(SS_PIN, RST_PIN); // Instance of the class
byte ma_the[4] = {0, 0, 0, 0};

void setup() { 
  Serial.begin(9600);
  SPI.begin(); 
  the_tu.PCD_Init(); 
  Serial.println(F("This code scan the MIFARE Classsic NUID."));
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
    the_tu.PICC_HaltA();
    the_tu.PCD_StopCrypto1();
}
