#include <SimbleeBLE.h>

int i = 1;

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
  SimbleeBLE.sendInt(i); //sends i every 2 seconds, increasing i by 1 each time around the loop
  //this actually sends a single byte, so once you get past single digits the phone starts recognizing it as punctuation, and then letters, ASCII style
  i++;
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
