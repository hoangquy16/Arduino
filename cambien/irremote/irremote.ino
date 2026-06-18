#include <IRremote.h>
int chan_tin_hieu = 3;
int R = 9;
int G = 10;
int B = 11;
IRrecv remote(chan_tin_hieu);
decode_results ketqua;
void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(9600);
  remote.enableIRIn();
}
void loop() {
  if (remote.decode(&ketqua)) {
    unsigned long ma_code = ketqua.value;
    Serial.println(ma_code);
    if (ma_code == 16753245) {
      digitalWrite(R, HIGH);
    } else if (ma_code == 16736925) {
      digitalWrite(G, HIGH);
    } else if (ma_code == 16769565) {
      digitalWrite(B, HIGH);
    } else if (ma_code == 16720605) {
      digitalWrite(R, LOW);
    } else if (ma_code == 16712445) {
      digitalWrite(G, LOW);
    } else if (ma_code == 16761405) {
      digitalWrite(B, LOW);
    } else if (ma_code == 16769055) {
      digitalWrite(R, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(B, HIGH);
    } else if (ma_code == 16754775) {
      digitalWrite(R, LOW);
      digitalWrite(G, LOW);
      digitalWrite(B, LOW);
    }
    delay(1000);
    remote.resume();
  }
}
