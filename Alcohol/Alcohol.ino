/*
   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 4fafc201-1fb5-459e-8fcc-c5c9c331914b
   And has a characteristic of: beb5483e-36e1-4688-b7f5-ea07361b26a8

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   A connect hander associated with the server starts a background task that performs notification
   every couple of seconds.
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <string.h>
#include <NeoPixelBus.h>
#include "DFRobot_Alcohol.h"

// BLE'name of the board
#define ESP32_NAME "ESP32-M2"
// Timer delay [us]
#define TIMER_DELAY 2000000 //2s
// SET/RESET simulation mode
#define SIMULATION 1

// const & variables pour la LED RGB
const uint16_t PixelCount = 1;
const uint8_t PixelPin = 48;
NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(PixelCount, PixelPin);
#define colorSaturation 16
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

float alcoholConcentration=0.0;

// const & variables pour le capteur
#define COLLECT_NUMBER   5
#define ALCOHOL_I2C_ADDRESS ALCOHOL_ADDRESS_3
/**
 * select i2c device address 
 * ALCOHOL_ADDRESS_0               0x72
 * ALCOHOL_ADDRESS_1               0x73
 * ALCOHOL_ADDRESS_2               0x74
 * ALCOHOL_ADDRESS_3               0x75
 */
DFRobot_Alcohol_I2C Alcohol(&Wire ,ALCOHOL_I2C_ADDRESS);

// const & variables pour la communication BLE
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;
volatile bool timerUP = false;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Classe Server callback
class MyServerCallbacks: public BLEServerCallbacks 
{
  void onConnect(BLEServer* pServer) 
  {
    deviceConnected = true;
    BLEDevice::startAdvertising();
  };

  void onDisconnect(BLEServer* pServer) 
  {
    deviceConnected = false;
  }
};

// Fonction de callback pour le timer
hw_timer_t *myTimer = NULL;
void IRAM_ATTR onTimer()
{
  static bool ledState=false;
  if (ledState) strip.SetPixelColor(0, green);
  else strip.SetPixelColor(0, red);
  strip.Show();
  ledState=!ledState;
  timerUP = true;
} 

// Initialisation de la carte
void setup() 
{
  // Init. port série
  Serial.begin(115200);

  // Init capteur
#if SIMULATION == 0
  while(!Alcohol.begin())
  {
    Serial.println("Alcohol sensor not found !");
    delay(1000);
  }
#else
  Serial.println("Start in simualtion mode");
#endif
  
  Serial.println("Device connected successfully !");
  /**
   * set measuer mode
   * MEASURE_MODE_AUTOMATIC         active  mode
   * MEASURE_MODE_PASSIVE           passive mode
   */
  Alcohol.setModes(MEASURE_MODE_AUTOMATIC);

  // Init Timer1
  myTimer = timerBegin(0, 80, true);
  timerAttachInterrupt(myTimer, &onTimer, true);
  timerAlarmWrite(myTimer, TIMER_DELAY, true);
  timerAlarmEnable(myTimer);
          
  // Init de la LED RGB
  strip.Begin();
  strip.Show();

  // Create the BLE Device
  BLEDevice::init(ESP32_NAME);
  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);
  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY //|
//                      BLECharacteristic::PROPERTY_INDICATE
                    );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());
  // Start the service
  pService->start();
  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

void loop() 
{
  static bool notifyValue = false;
  // notify changed value
  if (deviceConnected && notifyValue) 
  {
    std::string data = std::to_string(alcoholConcentration);
    pCharacteristic->setValue(data);
    pCharacteristic->notify();
    delay(10); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
    notifyValue = false;
  }
  // disconnecting
  if (!deviceConnected && oldDeviceConnected) 
  {
    delay(500); // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    Serial.println("start advertising");
    oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected) 
  {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }
  if(timerUP)
  {
    timerUP = false;
    /**
    * Smooth data collection
    * COLLECT_NUMBER                 The collection range is 1-100
    */
#if SIMULATION == 0
    alcoholConcentration = Alcohol.readAlcoholData(COLLECT_NUMBER);
    if(alcoholConcentration == ERROR)
    {
      Serial.println("Please check the connection !");
    }else
    {
      Serial.print("Alcohol concentration is ");
      Serial.print(alcoholConcentration);
      Serial.println(" PPM.");
    }
#else
    alcoholConcentration+=0.1;
    if(alcoholConcentration>10.0) alcoholConcentration=0;
#endif
    value=(uint32_t)(alcoholConcentration*100.0);
    notifyValue = true;
  }
}
