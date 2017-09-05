 #include <SoftwareSerial.h>
int i=0;
    SoftwareSerial zigbeee(10,11);
 void setup() {
      
      Serial.begin(115200);
      zigbeee.begin(9600);
      
 }

 void loop() {
   while(zigbeee.available() > 0){
  i=zigbeee.read();
  Serial.print(i, HEX);
   Serial.print(" ");
   delay(10);
   }
 }

