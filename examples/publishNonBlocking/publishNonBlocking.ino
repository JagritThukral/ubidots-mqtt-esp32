/******************************************
 *
 * This example works for both Industrial and STEM users.
 * If you are using the old educational platform,
 * please consider to migrate your account to a STEM plan
 *
 * Developed by Jose Garcia, https://github.com/jotathebest/
 *
 * ****************************************/

/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "...."     // Your Ubidots TOKEN
#define WIFINAME "...."  // Your SSID
#define WIFIPASS "...."  // Your Wifi Pass

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Auxiliar variables
 ****************************************/

bool connected = false;

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.setDebug(true);  // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  connected = client.connected();
  if (!connected) {
    Serial.println("Not connected, attempting to connect ...");
    connected = client.connect();
  }

  // Publish values to 2 different data sources

  if (connected) {
    client.add("stuff", 10.2);  // Insert your variable Labels and the value to be sent
    client.ubidotsPublish("source1");
    client.add("stuff", 10.2);
    client.add("more-stuff", 120.2);
    client.ubidotsPublish("source2");
    client.loop();
  }
  delay(5000);
}
