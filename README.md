# ubidots-mqtt-esp32
Forked  to make it work with both esp32 and esp8266

MQTT library for connecting to Ubidots using MQTT protocol and an ESP32 or ESP8266 chip.

## Setup

### 1. Uninstall "Ubidots MQTT for ESP8266"
   - Go to Tools > manage libraries
   - search for "Ubidots MQTT for ESP8266" 
   - remove the library
   - ![image](https://github.com/user-attachments/assets/08c544f6-3242-43e8-ae36-27490b0847f9)

### 2. (a) installing from library manager
- go to tools > manage libraries
- search "Ubidots MQTT for ESP32 and ESP8266"
- install
- install the PubSubClient library if not installed already by clicking on "install all"
- ![image](https://github.com/user-attachments/assets/c0c01c3c-5e60-448f-87b5-cbb442b19423) ![image](https://github.com/user-attachments/assets/8d5994ce-6ff9-4103-8e48-7930f18e99e6)


### 2. (b) manually (not recommended)
2. Download this library [click to download](https://github.com/JagritThukral/ubidots-mqtt-esp32/archive/refs/heads/master.zip)
3. Now, click on Sketch -> Include Library -> Add .ZIP Library
4. Select the .ZIP file that you have just downloaded and then “Accept” or “Choose”
5. Go to Sketch/Program -> Include Library -> Library Manager and install the PubSubClient library 

# Documentation

## Constructor

### Ubidots

`Ubidots(char* token)`
`Ubidots(char* token, char* clientName)`
Creates an Ubidots instance, you must setup as input your Ubidots TOKEN, the MQTT client name is optional and must be unique so we recommend you to insert random ASCII characters if you decide to use it, if you don't pass the clientName as parameter to the constructor the library will try to get the MAC of the device as default client name.

- @token, [Required]. Your Ubidots unique account [TOKEN](http://help.ubidots.com/user-guides/find-your-token-from-your-ubidots-account).
- @clientName, [Optional] [default] = device unique MAC address. The MQTT unique client id to be identified by the broker.
## Methods

### Ubidots

`add(char* variableLabel, float value, char *context, char *timestamp)`
Add a variable with a value, context and timestamp to be sent to a certain data source, once you use add() you can publish your variable using the ubidotsPublish() method. You can add 5 variables maximum before of publish them. 
**Important:** As this library depends on a Pubsubclient client, the max length of the JSON dictionary to send by default is 128 bytes, if you want to publish more than 3 variables and they have context or long names you should set at PubSubclient.h the MQTT_MAX_PACKET_SIZE to 512, you can see on your serial console the dictionary to POST if you call the ```setDebug(bool debug)``` method and pass a true value to it. For more information, refer to the PubSubclient official library: https://github.com/knolleary/pubsubclient

- @variable_label, [Required]. The label of the variable where the dot will be stored.
- @value, [Required]. The value of the dot.
- @context, [Optional]. The dot's context.
- @timestamp, [Optional]. The dot's timestamp in milliseconds.

`begin(void (*callback)(char*,uint8_t*,unsigned int))`
Sets the callback function for subscribed topics

- @callback [Mandatory] Pointer to the callback function that will process the incoming data

`connected()`
Returns True if the device is connected to the MQTT broker

`loop()`
Infinite loop for MQTT connection, insert it at the end of your routine

`reconnect()`
For trying to make a reconnection every 5 seconds if the connection is lost.

`ubidotsSetBroker(char* broker)`
Sets the broker properly for publish and subscribe to Ubidots accounts. If your account if a business one, set "business.api.ubidots.com" or the endpoint provided by Ubidots as your broker, see examples for more information.
By default, broker will be set to publish and subscribe to free educational version accounts with broker "things.ubidots.com".

- @broker, [Optional] [default] = `industrial.api.ubidots.com`. The server to send data url.

`setDebug(bool debug)`
Make available debug messages through the serial port.

`ubidotsPublish(char *deviceLabel)`
Publishes the variables added to the specified device label.
- @deviceLabel [Mandatory] Device label that stores the the values to be ingested

`ubidotsSubscribe(char* deviceLabel, char* variableLabel)`
Subscribe to the specified device label and variable label of your Ubidots account.

- @deviceLabel [Mandatory] Device label that stores the variable to retrieve values from
- @variableLabel [Mandatory] Variable label to retrieve values from

`bool connect(const char* clientName, const char* username, const char* password)`
Connects to the broker using a custom client name, username and password

- @clientName, [Optional] [default] = device unique MAC address. The MQTT unique client id to be identified by the broker.
- @username, [optional] [default] = Ubidots account token used in the constructor. The username to be identified by the broker
- @password, [optional] [default] = Ubidots account token used in the constructor. The password to be identified by the broker

`void wifiConnection(char* ssid, char* pass)`
Connects to an available WiFi network using WAP2.

- @ssid [Mandatory] SSID of the network to connect to
- @pass [Mandatory] WiFi network password

`void disconnect()`
Disconnects gracefully from the broker, closing the socket


# Examples

Please refer to examples folder.
