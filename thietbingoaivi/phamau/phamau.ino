//Bộ pha màu với led neopixel bằng keypad
#include <Adafruit_NeoPixel.h>
#define CHAN_LED 10
#define SO_LED 12
Adafruit_NeoPixel vong_led(SO_LED, CHAN_LED, NEO_GRB + NEO_KHZ800);
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

int red = 0;
int green = 0;
int blue = 0;
int do_sang = 50;
void setup() {
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  vong_led.begin();
  vong_led.setBrightness(do_sang);
  vong_led.show();
}
void loop() {
  char key = customKeypad.getKey();
  Serial.print(key);
  if (key) {
    if (key == '1') red = 85;
    if (key == '2') red = 170;
    if (key == '3') red = 255;
    if (key == '4') green = 85;
    if (key == '5') green = 170;
    if (key == '6') green = 255;
    if (key == '7') blue = 85;
    if (key == '8') blue = 170;
    if (key == '9') blue = 255;
    if (key == '0') { red = 0; green = 0; blue = 0;} 
    if (key == 'A') red += 30 ;
    if (key == 'B') blue += 30 ;
    if (key == 'C') green += 30 ;
    if (key == '*') { 
      do_sang += 50;
     if (do_sang > 255 ) do_sang = 255 ;
    vong_led.setBrightness(do_sang);}
    if (key == '#') { 
      do_sang -= 50;
     if (do_sang < 0 ) do_sang = 0 ;
    vong_led.setBrightness(do_sang);}
  }
  uint32_t color = vong_led.Color(red, green, blue);
  for (int i = 0; i < SO_LED; i++) {
    vong_led.setPixelColor(i, color);
    delay(10);
  } vong_led.show();
}
