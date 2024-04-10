#include <OSCMessage.h>
#include <WiFiNINA.h>  
#include "config.h"

#include <Arduino_LSM6DS3.h> //for Nano 33 IoT
//#include <Arduino_LSM6DSOX.h> 

WiFiUDP udp;

//destination IP address and port
const char ip[] = "10.23.11.148";
const unsigned int outPort = 4242;

void setup() {
  Serial.begin(9600);
  if (!Serial) delay(2000);
  Serial.println("Connecting to WiFi.");
  while (!WiFi.begin(WIFI_SSID, WIFI_PASS)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("WiFi connected.\nIP address: ");
  Serial.println(WiFi.localIP());

  udp.begin(5000); 
  IMU.begin();
}

float x, y, z;
void loop(){

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  }

  OSCMessage msg("/device1/gyro"); //enter OSC msg address as msg argument

  //add arguments, as many as needed
  msg.add(x); 
  msg.add(y);
  
  udp.beginPacket(ip, outPort);
  msg.send(udp); // send the bytes to the SLIP stream
  udp.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message

  delay(20);
}
