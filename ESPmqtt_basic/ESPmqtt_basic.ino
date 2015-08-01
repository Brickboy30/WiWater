/*
 Basic MQTT example 
 
  - connects to an MQTT server
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "WifiCreds.h"

String(Test2) = "";
// Update these with values suitable for your network.
IPAddress server(192, 168, 1, 118);

void callback(const MQTT::Publish& pub) {
  // handle message arrived
}

WiFiClient wclient;
PubSubClient client(wclient, server);

void setup() {
  // Setup console
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();

  client.set_callback(callback);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");
    WiFi.begin(ssid, pass);

    if (WiFi.status() != WL_CONNECTED)
      return;
    Serial.println("WiFi connected");
  
    if (client.connect("arduinoClient")) {
	    client.publish("Test1",ssid);
	    Test2 = client.subscribe("Test2");
       Serial.println(Test2);
      }
    

    if (client.connected())
      client.loop();
  }
}

