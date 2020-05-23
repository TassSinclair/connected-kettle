#include "HX711.h"
#include <WiFi.h>
#include <Wire.h>

#include <display.h>
#include <comms.h>
#include <Arduino.h>
#include "secrets.h"
#include <PubSubClient.h>

const int CONTRAST_PIN = 27;
const int BACKLIGHT_PIN = 13;

const int DOUT_PIN = 22;
const int SCK_PIN = 23;

const int RS = 26;
const int EN = 25;

const int D4 = 5;
const int D5 = 18;
const int D6 = 19;
const int D7 = 21;

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

const long LOADCELL_DIVIDER = -1100000;
const long LOADCELL_OFFSET = 38821;

HX711 loadcell;

void start_wifi()
{
  // WiFi.forceSleepWake();
  // delay(1);
  // WiFi.persistent(false);
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

void setup()
{
  Serial.begin(460800);
  display.begin();
  display.print("Setting up wifi", mqtt_server);
  start_wifi();
  display.print("Setting up comms", mqtt_server);
  comms.begin();
  display.print("Setting up scale", "");
  loadcell.begin(DOUT_PIN, SCK_PIN);
  loadcell.set_scale(LOADCELL_DIVIDER); //Adjust to this calibration factor
  loadcell.set_offset(LOADCELL_OFFSET);
  loadcell.tare();
}

inline float max(float a, float b) { return a > b ? a : b; }

void loop()
{
  comms.loop();
  loadcell.set_scale(LOADCELL_DIVIDER); //Adjust to this calibration factor
  Serial.print("Reading: ");
  float load = max(loadcell.get_units(10), 0);
  Serial.print(load, 4);
  Serial.print(" kg");
  Serial.println();
  display.printLoad(load);
  comms.publishLoad(load);
  
}