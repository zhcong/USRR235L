#include <Arduino.h>
#include <HardwareSerial.h>

class USRR235L {
public:
  USRR235L();
  int target;
  int distance;
  int energy;

  bool begin(HardwareSerial *_radarSerial);
  void service();
  void cfar(int value);
private:
  int readTimeOut;
  HardwareSerial *radarSerial;

  void parse(String data);
  bool is_radar_ok();
  void radar_write(String str);
  String radar_read();
  void pause();
  void catch_read();
};