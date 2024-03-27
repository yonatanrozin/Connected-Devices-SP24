#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
/////// WiFi Settings ///////
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

char serverAddress[] = "68.183.134.255";  // server IP address
int port = 1880; //HTTP default is 80, or use a different port

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid); // print the network name;

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    delay(1000);
  }

  // print the SSID of the network you're attached to:
  Serial.print("WiFi connected.");

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  Serial.println("making GET request");

  char endpoint[] = "/messages"; //put your endpoint here
  client.get(endpoint);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  //to parse response into a number (if needed):
//  float responseFloat = response.toFloat(); 
//  int responseInt = response.toInt();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}
