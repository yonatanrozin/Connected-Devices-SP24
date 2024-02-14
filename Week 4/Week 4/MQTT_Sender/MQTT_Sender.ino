#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

WiFiClient wifi;
MqttClient mqtt(wifi);

//WiFi network info: ssid and password
const char wifi_ssid[] = "";
const char wifi_pass[] = "";

//MQTT broker info: url and port (1883 default for MQTT)
const char broker[] = "";
const int  port = 1883;

//if needed: broker authentication credentials
const char mqtt_user[] = "";
const char mqtt_pass[] = "";

//the topic this device will publish messages to
const char pubTopic[] = "device_1";

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    WiFi.begin(wifi_ssid, wifi_pass);
    delay(1000);
  }
  Serial.println("\nWiFi connected!");

  //give your device any name, to use for identification
  mqtt.setId("My Arduino");

  //set mqtt credentials, if needed
  mqtt.setUsernamePassword(mqtt_user, mqtt_pass);

  if (!mqtt.connect(broker, port)) {
    //error codes
    //  -1: credentials rejected
    //  -2: can't connect to broker
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqtt.connectError());
    while (true) {}; //do nothing forever
  } else Serial.println("MQTT connected.");
}

const int sendInterval = 1000;
void loop() {

  if (millis() % sendInterval < 10) {
    mqtt.beginMessage(pubTopic);
    mqtt.print(millis());
    mqtt.endMessage();
    delay(10);
  }
  
}
