#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifimulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifimulti;
#define DEVICE "ESP8266"
#endif

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#define WIFI_SSID "HCILAB"
#define WIFI_PASSWORD "dit_hci2022"

#define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "SCSC52JHxy6bwSXGdeKxxWwKJoSiWK7epLWc_dEBnbT43YMuqN0ja18bQ3GORtbywji5MjLkddqY2ElICG06Bg=="
#define INFLUXDB_ORG "d6e7d4ac862afa26"
#define INFLUXDB_BUCKET "Weather"

#define TZ_INFO "UTC2"

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
Point sensor(INFLUXDB_BUCKET);

void wifi_setup()
{
    WiFi.mode(WIFI_STA);
    wifimulti.addAP(WIFI_SSID,WIFI_PASSWORD);
    Serial.print("Connecting to WIFI");
    while(wifimulti.run()!=WL_CONNECTED)
    {
      Serial.print(".");
      delay(100);
    }
    Serial.println();

    // Accurate time for certificate validation
    // The NTP servers are used as provided by: https://www.pool.ntp.org/zone/
    sensor.addTag("device", DEVICE);
    sensor.addTag("SSID", WiFi.SSID());

    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

    // Check server connection
    if(client.validateConnection())
    {
      Serial.print("Connected to InfluxDB:");
      Serial.println(client.getServerUrl());
    }
    else
    {
      Serial.print("InfluxDB connection failed: ");
      Serial.println(client.getLastErrorMessage());
    }

}


void write_to_db(double *temperature,double *humidity)
{
  sensor.clearFields();
  sensor.addField("rssi",WiFi.RSSI());

  Serial.print("Writing: ");
  Serial.println(sensor.toLineProtocol());

  sensor.addField("Temperature",*temperature);
  sensor.addField("Humidity",*humidity);

  if(wifimulti.run()!=WL_CONNECTED)
  {
    Serial.println("Wifi Connection lost");
  }

  if(!client.writePoint(sensor))
  {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  delay(1000);
}

