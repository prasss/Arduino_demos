#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial zigbee(10,11);
XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
ZBRxResponse rx = ZBRxResponse();
uint8_t *a;
//uint8_t x[4];

void setup() {
 Serial.begin(9600);
 zigbee.begin(9600);
xbee.setSerial(zigbee);
}

void loop() {

  xbee.readPacket();
   
   if (xbee.getResponse().isAvailable()) {
     // got something
     
     if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {

     xbee.getResponse().getZBRxResponse(rx);
    a = rx.getData(); 
     uint8_t state=a[0] & 0x01;
     int secs=a[1];
     int mins=a[2];
     Serial.println(state);
     Serial.println(secs);
     Serial.println(mins);
      
     }
   }
}


