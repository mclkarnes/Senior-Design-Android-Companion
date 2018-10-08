#include <SimbleeBLE.h>

int i = 5;

void setup()
{
  Serial.begin(9600);
  Serial.println("Waiting for connection...");
  
  SimbleeBLE.deviceName = "Simblee";
  SimbleeBLE.advertisementData = "data";
  SimbleeBLE.advertisementInterval = MILLISECONDS(300);
  SimbleeBLE.txPowerLevel = -20;  // (-20dbM to +4 dBm)

  // start the BLE stack
  SimbleeBLE.begin();
}

void loop()
{
  // print the string when a newline arrives:
  SimbleeBLE.sendInt(i);
  i++;s
  delay(2000);
}


void SimbleeBLE_onConnect()
{
  Serial.println("Connected");
}

void SimbleeBLE_onDisconnect()
{
  Serial.println("Disconnected");
}
