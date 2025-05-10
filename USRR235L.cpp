#include <USRR235L.h>

USRR235L::USRR235L() {}

void USRR235L::service() {
  String re = radar_read();
  parse(re);
}

void USRR235L::parse(String data) {
  String targetS;
  String distanceS;
  String energyS;

  if (data == "") {
    return;
  }
  if ((data.substring(0, 3) == "1,R") || (data.substring(0, 3) == "2,R")) {
    targetS = data.substring(0, 1);
    target = targetS.toInt();

    distanceS = data.substring(4, data.indexOf("cm"));
    if (distanceS != "") {
      distance = distanceS.toInt();
    }

    energyS = data.substring(data.indexOf("P:") + 2, data.length());
    if (energyS != "") {
      energy = energyS.toInt();
    }
  }
}
bool USRR235L::is_radar_ok() {
  radar_write("AT+TAGOUT=0");
  delay(50);
  // clear
  radar_read();
  radar_write("AT");
  delay(50);
  String re = radar_read();
  if (re == "OK") {
    radar_write("AT+TAGOUT=2");
    return true;
  }
  return false;
}
void USRR235L::radar_write(String str) {
  radarSerial->println(str);
}
String USRR235L::radar_read() {
  String re;
  long startT = millis();
  while (true) {
    char c;
    if (radarSerial->available()) {
      c = radarSerial->read();
      re += c;
      startT = millis();
    }
    if (c == '\n') {
      break;
    }
    if (millis() - startT > readTimeOut) {
      break;
    }
  }
  re.replace("\r", "");
  re.replace("\n", "");
  return re;
}

bool USRR235L::begin(HardwareSerial *_radarSerial) {
  readTimeOut = 1000;
  target = 0;
  distance = 0;
  energy = 0;

  radarSerial = _radarSerial;
  radarSerial->begin(115200);
  // clear
  readTimeOut = 100;
  for (int i = 0; i != 20; i++) {
    radar_read();
  }
  readTimeOut = 1000;
  if (!is_radar_ok()) {
    return false;
  }
  return true;
}
