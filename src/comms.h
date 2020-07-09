#ifndef connected_kettle_comms_h
#define connected_kettle_comms_h

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
   static const char *POST_BOILING_TOPIC;

private:
   PubSubClient _pubSubClient;
   bool _last_availability;
   const char *_mqtt_server;
   static const unsigned long _MIN_DELAY = 10000;
   static const float _MIN_LOAD_DELTA;
   static const float _MIN_TEMPERATURE_DELTA;
   float _last_load_value;
   float _last_temperature_value;
   unsigned long _last_temperature_publish;
   unsigned long _last_load_publish;
   static const char *_STATUS_AVAILABLE;
   static const char *_STATUS_UNAVAILABLE;
   static const char *_MQTT_CLIENT;
   static const char *_GET_TEMPERATURE_TOPIC;
   static const char *_GET_LOAD_TOPIC;
   static const char *_GET_STATUS_TOPIC;
};

#endif
