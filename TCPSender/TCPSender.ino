#include <WiFiNINA.h>

WiFiClient client;

const char server[] = ""; //local IP address of receiver device goes here
const int portNum = 8080; //desired port # goes here. Make sure the receiver is listening on the same port!

const char WIFI_SSID[] = ""; //WiFi network name goes here
const char WIFI_PASS[] = ""; //WiFi password goes here

void setup() {
  Serial.begin(9600);
  //retry connection until WiFi is connected successfully
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    // Attempt connection to WPA/WPA2 network.
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    delay(3000);
  }
  Serial.println("connected!");
}

void loop() {
  //connect to client if disconnected, or send TCP message if conected
  if (!client.connected()) {
    Serial.println("connecting");
    client.connect(server, portNum);
    delay(1000);
    return;
  } else {
    //add something more interesting here
    Serial.print("sending TCP message");
    client.print(millis());
    delay(50);
  }
}
