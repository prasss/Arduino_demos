#include <XBee.h>
#include <SoftwareSerial.h>
/*
This example is for Series 2 XBee
 Sends a ZB TX request with the value of analogRead(pin5) and checks the status response for success
*/
SoftwareSerial mySerial(A0,A1); // RX, TX
XBee xbee = XBee();   // create the XBee object
uint8_t payload[] = { 0 };

XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x4156583e);  // SH + SL Address of receiving XBee
ZBTxRequest zbTx = ZBTxRequest(addr64, payload,sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int m=0,l=0,r=0;


void setup() {
 //mySerial.begin(9600);
  Serial.begin(9600);
  mySerial.begin(9600);
  xbee.setSerial(mySerial);
  
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop()
{
r = digitalRead(7);
m = digitalRead(6);
l = digitalRead(5);
r=!r;
m=!m;
l=!l;

if(r){
digitalWrite(13,r);
//Serial.print(r);
payload[0]= ((l << 2) | (m << 1) | r) & 0x0F;
  zbTx.setFrameId(5);
  xbee.send(zbTx);
delay(5);
digitalWrite(13,!r);
}

if(m){
digitalWrite(4,m);
//Serial.print(m);
payload[0]= ((l << 2) | (m << 1) | r) & 0x0F;
  zbTx.setFrameId(5);
  xbee.send(zbTx);
delay(5);
digitalWrite(4,!m);
}

if(l){
digitalWrite(3,l);
//Serial.print(l);
payload[0]= ((l << 2) | (m << 1) | r) & 0x0F;
  zbTx.setFrameId(5);
  xbee.send(zbTx);
delay(5);
digitalWrite(3,!l);
  
}
delay(100);
}

