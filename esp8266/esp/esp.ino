#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
char cmd=0;

char data[]="UID=";
void setup() {
 
  Serial.begin(9600);                                  //Serial connection
  WiFi.begin("daph", "wafer1234");   //WiFi connection
  Serial.flush();
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    //Serial.println("Waiting for connection");
 
  }
 
}
 
void loop() {
  
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    String cmdstr;
    char cmd=0;
    Serial.flush();
    delay(500);
   
    for(int k=0;k<4;k++)
    cmdstr+=data[k];
  while(cmd!=13)
  {
  if (Serial.available())
      {
      cmd=Serial.read();
      if(cmd!=13 && cmd!=10)
        {
        cmdstr+=cmd;
        
        }
      }
  }
      
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://192.168.43.217:8080/test");      //Specify request destination
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
 
   int httpCode = http.POST(cmdstr);   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   //Serial.println(httpCode);   //Print HTTP return code
   //Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(2000);  //Send a request every 30 seconds
 
}
