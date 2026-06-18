#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(200);
  dht.begin();
  Serial.println("\n=== DHT11 DEBUG START ===");
  Serial.print("Pin: "); Serial.println(DHTPIN);
  Serial.print("Using library: Adafruit DHT\n");
}

void loop() {
  for (int i = 0; i < 3; i++) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    Serial.print("Attempt "); Serial.print(i+1); Serial.print("  -> ");
    if (isnan(t)) Serial.print("T: NaN");
    else Serial.print(String("T: ") + String(t,2) + " C");

    Serial.print("   ");

    if (isnan(h)) Serial.print("H: NaN");
    else Serial.print(String("H: ") + String(h,2) + " %");

    Serial.println();

    delay(800); // nhỏ giữa lần đọc
  }
  Serial.println("--------------------------");
  delay(2000);
}
