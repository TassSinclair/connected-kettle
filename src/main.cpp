#include <Servo.h>
#include <WiFi.h>
#include <Wire.h>

#include <display.h>
#include <comms.h>
#include <scale.h>
#include <thermistor.h>
#include <Arduino.h>
#include "secrets.h"
#include <PubSubClient.h>

const int SERVO_PIN = 32;
Servo servo;

const int THERMISTOR_PIN = A0;
Thermistor thermistor(THERMISTOR_PIN);

const int RS = 26;
const int EN = 25;
const int D4 = 5;
const int D5 = 18;
const int D6 = 19;
const int D7 = 21;
const int BACKLIGHT_PIN = 13;
const int CONTRAST_PIN = 27;
const int CONTRAST = 110;
Display display(
  LiquidCrystal(RS, EN, D4, D5, D6, D7, BACKLIGHT_PIN, POSITIVE),
  CONTRAST_PIN,
  CONTRAST
);

WiFiClient espClient;

Comms comms(
  PubSubClient(espClient),
  mqtt_server
  );

const int DOUT_PIN = 22;
const int SCK_PIN = 23;
Scale scale(DOUT_PIN, SCK_PIN);

void start_wifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);
  Serial.print("WiFi connecting: ");
  Serial.println(wifi_ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(const char *topic, byte *payload, unsigned int length)
{
  if (strcmp(topic, "smart-kettle/activate") == 0)
  {
      servo.write(30);
      delay(200);
      servo.write(70);
  }
}

void setup()
{
  Serial.begin(460800);
  display.begin();
  display.print("Setting up wifi", mqtt_server);
  start_wifi();
  display.print("Setting up comms", mqtt_server);
  comms.begin();
  comms.setCallback(callback);
  display.print("Setting up scale", "");
  scale.begin();

  servo.attach(
        SERVO_PIN,
        2
    );
  display.clear();
}

void loop()
{
  comms.loop();

  float load = scale.read();
  Serial.print("Load: ");
  Serial.println(load, 2);

  float temperature = thermistor.read();
  Serial.print("Temperature: ");
  Serial.println(temperature, 2);

  display.clear();
  display.printLoad(load);
  display.printTemperature(temperature);
  comms.publishLoad(load);
  comms.publishTemperature(temperature);
}