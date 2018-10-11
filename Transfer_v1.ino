#include <SimbleeBLE.h>
#include <QueueArray.h>

char muxID;
int dataout;
bool devicestatus = false;
const int datapin = 7; // whatever our data pin ends up being, make it this number

QueueArray <int> data;

void setup()
{
  for (int i=2; i<6; i++)
  {
    //set all pins (currently 2 through 5) to digital output pins to use 
    pinMode(i, OUTPUT);
  }
  
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
  // for each MUX input i
  for (int i=0; i<9; i++) 
  {
    // store i as a byte for each input (currently 8 inputs)
    muxID = (char)i;
    
    // cycle through the bits of i, setting digital output to LSB 1/0 and then shifting the byte for next LSB
    for (int j=2; j<6; j++)
    {
      // write 0/1 to each pin bit until j is complete
      digitalWrite(j, muxID%2); 
      //cycle to the next significant bit in byte muxID
      muxID/=2;
    }
    // read from the data pin with binary ID muxID
    dataout = analogRead(datapin);
    // put analog data read from pin into bottom of queue as int
    data.push(dataout);

    // if the queue for data gets larger than 20 items and device is connected
    if (data.count() > 20 && devicestatus)
    {
      // while there is more than 1 item in data and device is connected
      while (data.count() > 1 && devicestatus)
      {
          // send elements in data to connected device
          SimbleeBLE.sendByte(data.pop());
      }
    }
  }
}


// These functions simply print "Connected" and "Disconnected" when the android device connects to the BLE  stream
// Additionally, these functions now set a "turn on" boolean variable to true and false based on connected status, so that device does not transmit when not connected.
void SimbleeBLE_onConnect()
{
  Serial.println("Connected");
  devicestatus = true;
}

void SimbleeBLE_onDisconnect()
{
  Serial.println("Disconnected");
  devicestatus = false;
}
