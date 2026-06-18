// Mạng + Led
int led[5] = {7, 6, 5, 4, 3};
//Phần tử [0] = 7 phần tử [1] = 6 
void setup() {
  //Vòng lặp for cấu hình OUTPUT cho mảng
  for (int i = 0; i < 5 ; i++) {
    pinMode(led[i], OUTPUT);
  } 
}
void loop() {
  //Sáng từ led tăng dần theo chỉ số
  //Sáng từ [0] đến [4]
  for (int i = 0; i < 5; i++) {
    digitalWrite(led[i], HIGH);
    delay(1000);
  } 
  delay(1000);
  //Tắt từng led tăng dần theo chỉ số
  //Tắt từ [0] đến [4]
  for(int i = 4 ; i >= 0 ; i--) {
    digitalWrite(led[i], LOW);
    delay(1000);
  }
}
