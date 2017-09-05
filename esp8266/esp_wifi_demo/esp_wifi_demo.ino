#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Wafer_2.4G";
const char* password =  "wafer2014";
//const char* mqttServer = "m11.cloudmqtt.com";
//const int mqttPort = 12948;
//const char* mqttUser = "YourMqttUser";
//const char* mqttPassword = "YourMqttUserPassword";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop() {
  client.loop();
}
