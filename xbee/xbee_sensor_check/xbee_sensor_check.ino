/*


 */




#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A0,A1); // RX, TX
XBee xbee = XBee();   // create the XBee object
uint8_t payload[] = { 0 };

XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x4156583e);  // SH + SL Address of receiving XBee
ZBTxRequest zbTx = ZBTxRequest(addr64, payload,sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();



void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  xbee.setSerial(mySerial);
  pinMode(A2,INPUT);

}

void loop() 
{
 

}
