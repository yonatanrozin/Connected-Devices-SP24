/*
  LED Control

  This example scans for Bluetooth® Low Energy peripherals until one with the advertised service
  "19b10000-e8f2-537e-4f6c-d104768a1214" UUID is found. Once discovered and connected,
  it will remotely control the Bluetooth® Low Energy peripheral's LED, when the button is pressed or released.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
  - Button with pull-up resistor connected to pin 2.

  You can use it with another board that is compatible with this library and the
  Peripherals -> LED example.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>

void setup() {
  Serial.begin(9600);
//  while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // initialize the Bluetooth® Low Energy hardware
  BLE.begin();

  Serial.println("BLE central initialized.");
}

void loop() {
  Serial.println("scanning for peripheral");
  
  // start scanning for peripheral devices using a service UUID
  BLE.scanForUuid("");

  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();

    //optional: confirm the device's local name here
//    if (peripheral.localName() != "LED") {
//      return;
//    }

    // stop scanning for devices
    BLE.stopScan();

    //connect to peripheral device
    if (!peripheral.connect()) {
      Serial.println("Can't connect to peripheral");
    } else {
      Serial.println("connected to peripheral!");
    }

    //get characteristics from peripheral
    peripheral.discoverAttributes();

    //get characteristic using characteristic UUID
    BLECharacteristic characteristic1 = 
      peripheral.characteristic("");

    if (characteristic1.canSubscribe()) {
      Serial.println("subscribed to characteristic");
      characteristic1.subscribe();
    }

    if (!characteristic1) {
      Serial.println("characteristic not found.");
      while (1);
   

    while (peripheral.connected()) {
      digitalWrite(LED_BUILTIN, HIGH);
      if (!characteristic1.valueUpdated()) continue;

      //to read from a BLEIntCharacteristic
//      byte valueIn;
//      characteristic1.readValue(valueIn);

      //to read from a BLEFloatCharacteristic:
//      float valueIn;
//      characteristic1.readValue(&valueIn, 4);

      //to read from a BLEStringCharacteristic
//      const int bufSize = 16; //replace with # used in characteristic constructor
//      char valueIn[bufSize];
//      characteristic1.readValue(&valueIn, bufSize);

      //DO STUFF WITH valueIn HERE!!!
      Serial.println(valueIn);
    }

  }

  else {
    Serial.println("no peripheral found.");
    delay(1000);
  }
  
  peripheral.disconnect();
  digitalWrite(LED_BUILTIN, LOW);
}
