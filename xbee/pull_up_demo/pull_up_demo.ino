void setup() {
  // put your setup code here, to run once:
pinMode(12, INPUT_PULLUP);
pinMode(11, INPUT_PULLUP);
pinMode(10, INPUT_PULLUP);
pinMode(13, OUTPUT);
pinMode(7, OUTPUT);
pinMode(6, OUTPUT);
Serial.begin(9600);
}

void loop() {
  loop:
  // put your main code here, to run repeatedly:
bool r = digitalRead(12);
bool m = digitalRead(11);
bool l = digitalRead(10);
r=!r;
m=!m;
l=!l;
if(r){
digitalWrite(13,r);
Serial.print(r);
delay(5);
digitalWrite(13,!r);
goto loop;
}
if(m){
digitalWrite(7,m);
Serial.print(m);
delay(5);
digitalWrite(7,!m);
goto loop;
}
if(l){
digitalWrite(6,l);
Serial.print(l);
delay(5);
digitalWrite(6,!l);
goto loop;
}

delay(100);
}
