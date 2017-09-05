#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial zigbee(10,11);
XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
XBeeAddress64 return_add = XBeeAddress64(0,0);
XBeeAddress64 p1 = XBeeAddress64(0x0013a200, 0x4156571a); //player1
XBeeAddress64 p2 = XBeeAddress64(0x0013a200, 0x415656fd);  //player2
// create reusable response objects for responses we expect to handle 
ZBRxResponse rx = ZBRxResponse();
uint8_t *a;
uint8_t x;
int len;
int u1,d1,u2,d2;
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
       // got a zb rx packet
      return_add = rx.getRemoteAddress64();
      a = rx.getData();     //getData() give an address...so put it in a pointer (here--> a <--is a pointer)
      x=a[0];               //get the first byte and put it in a variable
     // if(return_add == p1)
    //  {
     u1=x & 0x01;    //extract data
     d1=(x & 0x02) >> 1;
     u2=(x & 0x04) >> 2;
     d2=(x & 0x08) >> 3;
 
       if(u1){ Serial.println(1);}
      if(d1){ Serial.println(2);}
      if(u2){ Serial.println(3);}
      if(d2){ Serial.println(4);}
      }
      }}

