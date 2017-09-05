#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#define LED_BUILTIN 2
#define door_no 4
void setup() {
  Serial.begin(9600);                                  //Serial connection
  Serial.setDebugOutput(true);
  pinMode(16, OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(16, LOW);
  for(uint8_t t = 4; t > 0; t--) {
    Serial.flush();
    delay(500);
  }
  WiFi.setOutputPower(0);
  WiFi.persistent(false);
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin("MotoG4", "gamesgame");
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(WiFi.status());
  }
  if (WiFi.status() == WL_CONNECTED){
    digitalWrite(LED_BUILTIN, LOW);
  }
}
bool locked = true;
unsigned long timeLocked;
unsigned long timeNow;
void loop() {
  bool data_available = false;
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    Serial.flush();
    String cmdstr;
    char cmd=0;
    HTTPClient http;    //Declare object of class HTTPClient
    delay(50);
    if (Serial.available()){
      ////////////////////Assemble cmdstr//////////////////
      while(cmd != 10){
        cmd=Serial.read();
        if(cmd!=13 && cmd!=10 && cmd!=0){
          cmdstr+=cmd;
        }
        delay(100);
      }
      //////////////////////////////////////////////////////
      data_available = true;
    }
  if (locked && data_available){
    ///////////////////////Assemble JSON//////////////////////////////////
    StaticJsonBuffer<80> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();
    JSONencoder["UID"] = cmdstr;
    JSONencoder["door"] = door_no;
    char JSONmessageBuffer[100];
    JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    //////////////////////////////////////////////////////////////////////
    http.begin("http://192.168.0.8:8080/Access");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
    delay(100);
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();    //Get the response payload
    if (payload.equals("yes\n")){
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(16, HIGH);
      locked = false;
    }
    timeLocked = millis();//Start timer
    http.end();
  }else{
    timeNow = millis();
    if (timeNow - timeLocked > 4000){
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(16, LOW);
      locked = true;
    }
    delay(50);
  }
}else{
  digitalWrite(LED_BUILTIN, HIGH);
}
Serial.flush();
delay(500);  //Send a request every 30 seconds
}
