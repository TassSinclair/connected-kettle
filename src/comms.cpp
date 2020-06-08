#include "comms.h"

const char *Comms::ACTIVATE_TOPIC = "smart-kettle/activate";
const char *Comms::_AVAILABLE = "available";
const char *Comms::_UNAVAILABLE = "unavailable";
const char *Comms::_MQTT_CLIENT = "smart-kettle";
const char *Comms::_TEMPERATURE_VALUE_TOPIC = "smart-kettle/temperature-value";
const char *Comms::_LOAD_VALUE_TOPIC = "smart-kettle/load-value";
const char *Comms::_STATUS_TOPIC = "smart-kettle/status";

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
      _STATUS_TOPIC,
      1,
      true,
      _UNAVAILABLE))
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
  _pubSubClient.subscribe(ACTIVATE_TOPIC);
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
      _STATUS_TOPIC,
      available ? _AVAILABLE : _UNAVAILABLE,
      true
    );
    _last_availability = available;
  }
}

void Comms::publishLoad(float load)
{
  if (_last_load_publish + _min_delay < millis() &&
      (load > _last_load_value + _min_load_delta ||
       load < _last_load_value - _min_load_delta))
  {
    _last_load_publish = millis();
    _last_load_value = load;
    _pubSubClient.publish(
      _LOAD_VALUE_TOPIC,
      String(load, 2).c_str(),
      true);
  }
}

void Comms::publishTemperature(float temperature)
{
  if (_last_temperature_publish + _min_delay < millis() &&
      (temperature > _last_temperature_value + _min_temperature_delta ||
       temperature < _last_temperature_value - _min_temperature_delta))
  {
    _last_temperature_publish = millis();
    _last_temperature_value = temperature;
    _pubSubClient.publish(
      _TEMPERATURE_VALUE_TOPIC,
      String(temperature, 2).c_str(),
      true);
  }
}

void Comms::setCallback(MQTT_CALLBACK_SIGNATURE)
{
  _pubSubClient.setCallback(callback);
}
