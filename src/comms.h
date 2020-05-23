#ifndef smart_kettle_comms_h
#define smart_kettle_comms_h

#include <PubSubClient.h>

class Comms
{
public:
   Comms(PubSubClient pubSubClient,
         const char *mqtt_server
   );

   void begin();
   void loop();
   void publishLoad(float load);
private:
   PubSubClient _pubSubClient;
   const char *_mqtt_server;
   void publish_load(float load);
   const unsigned long _min_delay = 10000;
   const float _min_load_delta = 0.05f;
   float _last_load_value;
   unsigned long _last_load_publish;
   const char *_mqtt_client = "smart-kettle";
   const char *_temperature_topic = "smart-kettle/temperature";
   const char *_load_topic = "smart-kettle/load";
};

#endif
