#include <WiFiNINA.h>
#include "config.h"

WiFiUDP udpClient;

//configure your WiFi information inside config.h file

const char server[] = "192.168.0.238"; //local IP address of receiver device goes here
const int port = 4242; //desired port # goes here. Make sure the receiver is listening on the same port!

//the port OTHER devices should use when sending to this one
const int localPort = 5000;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  //retry connection until WiFi is connected successfully
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect to SSID: ");
    // Attempt connection to WPA/WPA2 network.
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    delay(500);
  }
  Serial.println("connected!");

  udpClient.begin(localPort);
}

char messageBuffer[256];

void loop() {
  if (millis()%100 < 10) {    
    //add something more interesting here
    udpClient.beginPacket(server, port);
    udpClient.print(millis());
    udpClient.endPacket();
    delay(10);
  }

  //check for incoming packets
  if (udpClient.parsePacket()) {
    udpClient.read(messageBuffer, 255);
    Serial.print("UDP received: ");
    Serial.println(atoi(messageBuffer));
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  
}
