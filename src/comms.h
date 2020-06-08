#ifndef smart_kettle_comms_h
#define smart_kettle_comms_h

#include <PubSubClient.h>

class Comms
{
public:
   Comms(PubSubClient pubSubClient,
         const char *mqtt_server
   );

   void connect();
   void loop();
   void publishAvailability(boolean available);
   void publishLoad(float load);
   void publishTemperature(float load);
   void setCallback(MQTT_CALLBACK_SIGNATURE);
   static const char *ACTIVATE_TOPIC;

private:
   PubSubClient _pubSubClient;
   bool _last_availability;
   const char *_mqtt_server;
   const unsigned long _min_delay = 10000;
   const float _min_load_delta = 0.05f;
   float _last_load_value;
   const float _min_temperature_delta = 1.0f;
   float _last_temperature_value;
   unsigned long _last_temperature_publish;
   unsigned long _last_load_publish;
   const char *_available = "available";
   const char *_unavailable = "unavailable";
   const char *_mqtt_client = "smart-kettle";
   const char *_temperature_value_topic = "smart-kettle/temperature-value";
   const char *_load_value_topic = "smart-kettle/load-value";
   const char *_status_topic = "smart-kettle/status";
};

#endif
