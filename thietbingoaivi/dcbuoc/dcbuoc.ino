#include <Stepper.h>
int mot_vong = 2048;
Stepper dc_buoc(mot_vong, 4, 6, 5 , 7); //Chân Stepper dc_buoc(2048, IN1, IN3, IN2, IN4);
void setup() {
  Serial.begin(9600);
  dc_buoc.setSpeed(10); //Tốc độ bước
}
void loop() {
  Serial.println("Quay thuận");
  dc_buoc.step(mot_vong);
  delay(500);

  Serial.println("Quay ngược");
  dc_buoc.step(-mot_vong);
  delay(500);
}
