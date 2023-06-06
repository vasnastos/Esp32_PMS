#include <DHT.h>
#include <TimeLib.h>
#include <LiquidCrystal_I2C.h>
#define DHTPIN 4
#define DHTTYPE DHT11
#define SDA 8
#define SCL 9

DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

void print_time()
{
  now();
  Serial.print("*******");
  Serial.print(day());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(year());
  Serial.print(" ");
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.println("*******");
}

double read_temperature()
{
  float temperature = dht.readTemperature();
  print_time();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  return temperature;
}

double read_humidity()
{
  float humidity = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("*************************************************\n\n\n");
  return humidity;
}

// LCD Display functions
void setup_lcd()
{
  Wire.begin(SDA,SCL);
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void display_to_lcd(double *temperature,double *humidity)
{
  lcd.setCursor(2,0);
  lcd.print("Temperature:");
  lcd.print(*temperature);
  lcd.setCursor(2,1);
  lcd.print("Humidity:");
  lcd.print(*humidity);
}
