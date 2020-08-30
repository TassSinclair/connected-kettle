#ifndef connected_kettle_networking_h
#define connected_kettle_networking_h

#include "WiFi.h"

class Networking
{
public:
   Networking(
      const char *wifi_ssid,
      const char *wifi_password,
      const char *host_name
   );

   void connect();
   void loop();
   WiFiClient& getClient();

private:
   WiFiClient _client;
   const char *_wifi_ssid;
   const char *_wifi_password;
   const char *_host_name;
};

#endif
