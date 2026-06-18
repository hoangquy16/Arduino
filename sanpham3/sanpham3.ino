#include <Servo.h>
#define trig 9
#define echo 8

Servo servo;
void setup() {
  servo.attach(6);
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  long duration, distance; 
  0digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration / 2.0) / 29.1;
  
  Serial.println(distance);

  if (distance < 10) {
    servo.write(180);
  }else {
    servo.write(0);
  }
  delay(200);
}
