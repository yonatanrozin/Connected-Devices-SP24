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
const char subTopic[] = "userInput";

//the maximum size of incoming message 
//ensure messages won't be longer than this!
const int bufferLength = 32;

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
  mqtt.setId("Yony's Arduino"); 

  //set mqtt credentials, if needed
  mqtt.setUsernamePassword(mqtt_user, mqtt_pass);

  if (!mqtt.connect(broker, port)) {
    //error codes
    //  -1: credentials rejected
    //  -2: can't connect to broker
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqtt.connectError());
    while (true) {}; //do nothing forever
  } 
  
  Serial.println("MQTT connected.");
  mqtt.subscribe(subTopic);
}

void loop() {

  //run this function regularly to prevent 
  //your mqtt connection from timing out!
  mqtt.poll();

  if (mqtt.available()) {
    Serial.print("Message received on topic: ");
    Serial.println(mqtt.messageTopic());

    //the raw message text (not parsed into a number)
    char messageBuffer[bufferLength];
    mqtt.readBytes(messageBuffer, bufferLength);

    //the message parsed into a usable float:
    float messageFloat = atof(messageBuffer);

    //do something with message values here:
    //if (messageFloat > 500) {} //etc...

    Serial.println(messageBuffer);
    Serial.println(atof(messageBuffer));
 
    Serial.println();
  }
  
}
