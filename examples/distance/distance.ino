#include <USRR235L.h>

USRR235L* radar = new USRR235L();

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("hello");

  // esp32 c3 uart0 pin: rx->20, tx->21
  radar->begin(&Serial0);
}

void loop() {
  radar->service();
  Serial.print("target:");
  Serial.print(radar->target);
  Serial.print(", distance:");
  Serial.print(radar->distance);
  Serial.print(", energy:");
  Serial.println(radar->energy);
}
