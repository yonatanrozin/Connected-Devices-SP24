#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
/////// WiFi Settings ///////
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

char serverAddress[] = "68.183.134.255";  //server IP address
int port = 1880; //use HTTP default port 80, or use 1880 for node-red

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);                   

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }

  Serial.println("WiFi connected.");

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  Serial.println("making POST request");

  //if sending raw text:
//  String contentType = "text/plain";
//  String postData = "hello from Arduino"; //to send a string, or
//  String postData = String(123.456); //to send a number

  //if sending a formatted JSON object (useful for updating multiple values)
  String contentType = "application/json"; //if sending a formatted JSON object
  String postData = "{\"deviceID\": 1, \"value\": VALUE}"; //use single-quotes inside a JSON object literal
  postData.replace("VALUE", String(millis())); //replace millis() with your own sensor data
  
  char endpoint[] = "/messages";
  client.post(endpoint, contentType, postData); //use client.put() to make a put request

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}
