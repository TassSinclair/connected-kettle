#include "Servo.h"

#include "display.h"
#include "comms.h"
#include "scale.h"
#include "networking.h"
#include "thermistor.h"
#include "secrets.h"

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

Networking networking(wifi_ssid, wifi_password, "connected-kettle");

Comms comms(
  networking.getClient(),
  mqtt_server
  );

const int DOUT_PIN = 22;
const int SCK_PIN = 23;
Scale scale(DOUT_PIN, SCK_PIN);

void callback(const char *topic, byte *payload, unsigned int length)
{
  if (scale.read() > 0.2)
  {
    display.set_backlight(false);
    servo.attach(SERVO_PIN);
    servo.write(25);
    delay(200);
    servo.write(75);
    delay(200);
    servo.detach();
    display.set_backlight(true);
    comms.publishBoiling(true);
  } else {
    comms.publishBoiling(false);
  }
}

void setup()
{
  Serial.begin(460800);
  display.connect();
  display.print("Setting up wifi", mqtt_server);
  networking.connect();
  display.print("Setting up comms", mqtt_server);
  comms.connect();
  comms.setCallback(callback);
  display.print("Setting up scale", "");
  scale.connect();
  display.clear();
}

void loop()
{
  networking.loop();
  comms.loop();

  float load = scale.read();
  Serial.print("Load: ");
  Serial.println(load, 2);

  float temperature = thermistor.read();
  Serial.print("Temperature: ");
  Serial.println(temperature, 2);

  display.clear();

  if (temperature > 0) {
    comms.publishAvailability(true);
    display.set_backlight(true);
    display.print_load(load);
    display.print_temperature(temperature);

    comms.publishLoad(load);
    comms.publishTemperature(temperature);
  } else {
    comms.publishAvailability(false);
    display.set_backlight(false);
  }
}