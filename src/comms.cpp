#include <PubSubClient.h>
#include "comms.h"

Comms::Comms(
   PubSubClient pubSubClient,
   const char* mqtt_server
   ): _pubSubClient(pubSubClient)
{
   _mqtt_server = mqtt_server;
   _last_load_value = -1;
   _last_load_publish = 0;
}


void Comms::begin()
{
  _pubSubClient.setServer(_mqtt_server, 1883);
  while (!_pubSubClient.connected())
  {
    Serial.print("MQTT connecting: ");
    Serial.println(_mqtt_server);
    if (_pubSubClient.connect(_mqtt_client))
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
}

void Comms::loop()
{
  _pubSubClient.loop();
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
      _load_topic,
      String(load, 2).c_str(),
      true);
  }
}
