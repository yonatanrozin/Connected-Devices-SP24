/*
 * Arduino MQTT "Will" message example
 * 
 * Enables a setting that automatically sends an MQTT message 
 * with a pre-defined topic and payload when the device
 * disconnects "ungracefully": loses power or internet access
 * 
 * To try it out - add WiFi + MQTT credentials, upload,
 * disconnect device from power and wait a few minutes!
 */

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char ssid[] = "";    // your network SSID (name)
const char pass[] = "";    // your network password (use for WPA, or use as key for WEP)

const char mqtt_user[] = "";
const char mqtt_pass[] = "";

const char broker[]    = "";
const int  port        = 1883;

//define the topic a message will be automatically sent to
//when this device accidentally disconnects
const char willTopic[] = "device_1/status";
const String willPayload = "offline";

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial);
  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
   mqttClient.setId("My device");

  // You can provide a username and password for authentication
   mqttClient.setUsernamePassword(mqtt_user, mqtt_pass);

  // set a will message, used by the broker when the connection dies unexpectedly
  // you must know the size of the message beforehand, and it must be set before connecting
  bool willRetain = true;
  int willQos = 1;

  mqttClient.beginWill(willTopic, willPayload.length(), willRetain, willQos);
  mqttClient.print(willPayload);
  mqttClient.endWill();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  mqttClient.poll();
}
