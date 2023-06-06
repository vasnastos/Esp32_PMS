#include "influxdb_setup.h"
#include "handler.h"

double humidity_reader;
double temperature_reader;

void setup() {
  Serial.begin(115200);
  wifi_setup();
  setup_lcd();
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  temperature_reader=read_temperature();
  humidity_reader=read_humidity();
  write_to_db(&temperature_reader,&humidity_reader);
  display_to_lcd(&temperature_reader,&humidity_reader);
  delay(5000);
}
