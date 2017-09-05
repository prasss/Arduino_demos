#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);
XBee xbee = XBee();
uint8_t payload[] = {0,0,0,0};
uint32_t time1;
int p=0;
 XBeeAddress64 add = XBeeAddress64(0x0013a200, 0x415656fd);
 ZBTxRequest zbTx = ZBTxRequest(add, payload,sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();
int s=0;
int i=0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  xbee.setSerial(mySerial);
  pinMode(7, INPUT);
  pinMode(12,OUTPUT);
  //pinMode(13,OUTPUT);
  
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  s=1;p=0; 
}

void loop() {
 
  time1 = millis();
  
  //Serial.println(time1);
  /*
  payload[1]=time1;
  Serial.println(payload[1]);
  delay(2000);
*/

  p=digitalRead(7);
  /*
  Serial.write("p val is"); Serial.println(p);
  if(p)
  {
    Serial.println(s);
    if(s)
    {
    Serial.write("one");
    digitalWrite(12,HIGH);
    payload[0]= p & 0x01;
    payload[1]=time1;
    //temptime=time1;
    zbTx.setFrameId(2);
    xbee.send(zbTx);
    s=0;
    delay(500);
    digitalWrite(12,LOW);
    }
    else{ Serial.write("meh"); delay(500);}
    }
   /* if(state==0)
    { Serial.print("2");
      p=digitalRead(7);
      if(!p)
      {
        state=1;
      
if(!p)
{
  Serial.write("zero");
  s=1;
  delay(500);
}
    }*/
     payload[0]= p & 0x01;
     //i believe millis part is better at the receiver rather then transmitter, 
     //coz here we only transfer one byte of time, so better to have millis running
     //at the receiver 
    // uint8_t seconds=int(time1/1000); // restrict secs to 60? 
     payload[1]= int((time1/1000)%60); 
     /*if(seconds>60)
     { 
      payload[1]= i++;
      if(i>60){i=0;};
     }*/
     payload[2]=int(time1/60000);
     payload[3]=int(time1/3600000);
     
    if(p && s)
    {
      Serial.print("one ");
      digitalWrite(12,HIGH);
     
      Serial.print(payload[0]);
      Serial.print("  ");
      Serial.print(payload[1]);
      Serial.print(" secs  ");
      Serial.print(payload[2]);
      Serial.println(" mins  ");
      zbTx.setFrameId(6);
      xbee.send(zbTx);  //send all payloads
      delay(500);  
      digitalWrite(12,LOW);
      s=0;
    }
    if(!p && !s) 
    {
      Serial.print("zero ");
      Serial.print(payload[0]);
      Serial.print("  ");
      Serial.println(payload[1]);
      
      delay(200);
      s=1;
    }
}
 
  
