#include "comms.h"

const char *Comms::POST_BOILING_TOPIC = "connected-kettle/post/boiling";
const char *Comms::_STATUS_AVAILABLE = "available";
const char *Comms::_STATUS_UNAVAILABLE = "unavailable";
const char *Comms::_MQTT_CLIENT = "connected-kettle";
const char *Comms::_GET_TEMPERATURE_TOPIC = "connected-kettle/get/temperature";
const char *Comms::_GET_LOAD_TOPIC = "connected-kettle/get/load";
const char *Comms::_GET_STATUS_TOPIC = "connected-kettle/get/status";
const float Comms::_MIN_LOAD_DELTA = 0.05f;
const float Comms::_MIN_TEMPERATURE_DELTA = 1.0f;

Comms::Comms(
   PubSubClient pubSubClient,
   const char* mqtt_server
   ): _pubSubClient(pubSubClient), _mqtt_server(mqtt_server)
{
   _last_load_value = -1;
   _last_load_publish = 0;
}


void Comms::connect()
{
  while (!_pubSubClient.connected())
  {
    _pubSubClient.setServer(_mqtt_server, 1883);
    Serial.print("MQTT connecting: ");
    Serial.println(_mqtt_server);
    if (_pubSubClient.connect(
      _MQTT_CLIENT,
      _GET_STATUS_TOPIC,
      1,
      true,
      _STATUS_UNAVAILABLE))
    {
      Serial.println("MQTT connected");
    }
    else
    {
      Serial.print("MQTT failed, reason: ");
      Serial.println(_pubSubClient.state());
      Serial.println("MQTT retrying in 5 seconds");
      delay(5000);
    }
  }
  _pubSubClient.subscribe(POST_BOILING_TOPIC);
  _last_availability = false;
  publishAvailability(true);
}

void Comms::loop()
{
  if (!_pubSubClient.connected())
  {
    connect();
  }
  _pubSubClient.loop();
}

void Comms::publishAvailability(boolean available)
{
  if (available != _last_availability)
  {
    _pubSubClient.publish(
      _GET_STATUS_TOPIC,
      available ? _STATUS_AVAILABLE : _STATUS_UNAVAILABLE,
      true
    );
    _last_availability = available;
  }
}

void Comms::publishLoad(float load)
{
  if (_last_load_publish + _MIN_DELAY < millis() &&
      (load > _last_load_value + _MIN_LOAD_DELTA ||
       load < _last_load_value - _MIN_LOAD_DELTA))
  {
    _last_load_publish = millis();
    _last_load_value = load;
    _pubSubClient.publish(
      _GET_LOAD_TOPIC,
      String(load, 2).c_str());
  }
}

void Comms::publishTemperature(float temperature)
{
  if (_last_temperature_publish + _MIN_DELAY < millis() &&
      (temperature > _last_temperature_value + _MIN_TEMPERATURE_DELTA ||
       temperature < _last_temperature_value - _MIN_TEMPERATURE_DELTA))
  {
    _last_temperature_publish = millis();
    _last_temperature_value = temperature;
    _pubSubClient.publish(
      _GET_TEMPERATURE_TOPIC,
      String(temperature, 2).c_str());
  }
}

void Comms::setCallback(MQTT_CALLBACK_SIGNATURE)
{
  _pubSubClient.setCallback(callback);
}
