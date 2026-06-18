//Thiết bị đo khoảng cách và hiển thị lên Neopixel
#include <Adafruit_NeoPixel.h>
#define CHAN_LED 6
#define SO_LED 12
int coi = 7 ;
int trig = 8;
int echo = 9;
Adafruit_NeoPixel vong_led(SO_LED, CHAN_LED, NEO_GRB + NEO_KHZ800);

uint32_t mau_so_1 = vong_led.Color(23,150,0);
uint32_t mau_so_2 = vong_led.Color(255,30,8);
uint32_t mau_so_3 = vong_led.Color(45, 0,90);
void setup() {
  pinMode(coi, OUTPUT);
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  vong_led.begin();
  vong_led.setBrightness(50);
  vong_led.show();
  randomSeed(analogRead(A0));
}

void loop() {
  long duration, distance;  
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration / 2.0) / 29.1;
  Serial.println(distance);
  
  uint32_t mau_random = vong_led.Color( random(256), random(256), random(256));
  int soLedSang = map(distance, 5, 50, 1, SO_LED); 
  if (distance < 10) {
    digitalWrite(coi, HIGH);
  } else {
    digitalWrite(coi, LOW);
  }
  vong_led.clear();
  for (int i = 0; i < soLedSang; i++) {
    vong_led.setPixelColor(i, mau_random);
    delay(10);
  } vong_led.show();
    
}
