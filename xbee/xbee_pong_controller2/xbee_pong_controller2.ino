#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A0,A1); // RX, TX
XBee xbee = XBee();   // create the XBee object
uint8_t payload[] = { 0 };

XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41035ebd);  // SH + SL Address of receiving XBee
ZBTxRequest zbTx = ZBTxRequest(addr64, payload,sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int u=0,d=0;


void setup() {
 //mySerial.begin(9600);
  Serial.begin(9600);
  mySerial.begin(9600);
  xbee.setSerial(mySerial);
  
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop()
{
u = digitalRead(7);
d = digitalRead(6);
u=!u;
d=!d;

if(u){
digitalWrite(13,u);
payload[0]= ( (u << 3) | (d<<2)) & 0x0F;
  zbTx.setFrameId(5);
  xbee.send(zbTx);
delay(5);
digitalWrite(13,!u);
}

if(d){
digitalWrite(13,d);
payload[0]= ( (u << 3) | (d<<2)) & 0x0F;
  zbTx.setFrameId(5);
  xbee.send(zbTx);
delay(5);
digitalWrite(13,!d);
}
delay(20);
}

