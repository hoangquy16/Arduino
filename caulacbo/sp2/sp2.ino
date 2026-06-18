#include <DHT.h>
const int DHTPIN = 4;
const int DHTTYPE = DHT11;
const int MOTOR = 5;
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(MOTOR, OUTPUT);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Nhiet do: ");
  Serial.println(t);
  Serial.print("Do am:");
  Serial.println(h);

  Serial.println();

  if (t > 32) {
    digitalWrite(MOTOR, HIGH);
  } else {
    digitalWrite(MOTOR, LOW);
  }
   delay(1200);
}
