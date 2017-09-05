
#include <XBee.h>
/*
This example is for Series 2 XBee
Receives a ZB RX packet and sets a PWM value based on packet data.
Error led is flashed if an unexpected packet is received
*/
XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
ZBRxResponse rx = ZBRxResponse();   ///rx is a instance of ZBRxResponse()

int dataLed = 13;

void setup() {
  //pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(dataLed,  OUTPUT);
  Serial.begin(9600);
  xbee.begin(Serial); 
  }

void loop() {       // continuously reads packets, looking for ZB Receive
    xbee.readPacket();
    if (xbee.getResponse().isAvailable()) {  // got something
      
        if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {   // got a zb rx packet
         // now fill our zb rx class
            xbee.getResponse().getZBRxResponse(rx);
            // set dataLed PWM to value of the first byte in the data
        analogWrite(dataLed, rx.getData(0));
          } } }
