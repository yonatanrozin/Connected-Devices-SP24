#include <ArduinoBLE.h>

/*  BLE peripheral starter code
 *  By Yonatan Rozin
 *  
 *  Advertises a BLE service with a single characteristic
 *  Turns on the built-in LED when a central device connects
 */

//a UUID v4 ID which other devices will use to connect to this one
//generate a new one here: https://www.uuidgenerator.net/version4
char serviceUUID[] = "";
//create a BLE service using the service UUID
BLEService testService(serviceUUID);

//create a UUID for each characteristic to be advertised on your service
//pick a digit in your service UUID, increase it by 1 and use as the characteristic UUID
//repeat for each characteristic, if using more than one
char characteristicUUID[] = "";

//create BLE characteristics using the corresponding UUID.
//BLE characteristics can have different types, depending on the data being used
//characteristics also have various permissions, such as read, write and notify
//  BLERead: allows devices to read the value of the characteristic
//  BLEWrite: allows devices to modify the value of the characteristic
//  BLENotify: allows devices to "subscribe" to changes in the characteristic value

//uncomment a line below to create a characteristic, depending on your desired data type
//and specify permissions as needed, separated by | (ie: BLERead | BLEWrite | BLENofity)

//BLEBoolCharacteristic testCharacteristic(characteristicUUID, BLERead | BLENotify); //booleans (true/false)
//BLEIntCharacteristic testCharacteristic(characteristicUUID, BLERead | BLEWrite| BLENotify); //integers between -255 and 255
//BLEFloatCharacteristic testCharacteristic(characteristicUUID, BLERead | BLENotify); //integers > 255 and floating-point numbers (use for numbers >255)
//BLEDoubleCharacteristic testCharacteristic(characteristicUUID, BLERead | BLENotify); //HUGE numbers/floating-point numbers
BLEStringCharacteristic testCharacteristic(characteristicUUID, BLERead | BLEWrite|  BLENotify, 16); //strings of max length (change number to increase/decrease)
//BLEByteCharacteristic testCharacteristic(characteristicUUID, BLERead | BLEWrite|  BLENotify); 

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  if (!BLE.begin()) {
    Serial.println("BLE initialization failed.");
    while (1); //do nothing forever
  }

  BLE.setLocalName("Device name");
  BLE.setAdvertisedService(testService);
  testService.addCharacteristic(testCharacteristic);
  BLE.addService(testService);
  BLE.advertise();

  Serial.println("BLE peripheral initialized.");
  
}

void loop() {

  // put your main code here, to run repeatedly:
  BLEDevice central = BLE.central();
  if (central && central.connected()) {
    digitalWrite(LED_BUILTIN, HIGH);

    //write some stuff to your characteristics here
    //make sure to use the correct data type!
//    testCharacteristic.writeValue("hello");
//    testCharacteristic.writeValue(millis());
//    testCharacteristic.writeValue(true);
//    testCharacteristic.writeValue(String(555));
    

    //if characteristic has BLEWrite access:
//    if (testCharacteristic.written()) {
        //get the value here - make sure to use the correct data type!
//      String dataIn = testCharacteristic.value();
//      Serial.println(dataIn);
//    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  

  
  
  
}
