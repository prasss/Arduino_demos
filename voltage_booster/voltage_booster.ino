const int pwm = 1;
const int potinput = A1;
const int feedbackinput = A3;
int potinputval;
int feedbackinputval;
int pwmval;


void setup()
{
  pinMode(pwm, OUTPUT);
  pinMode(potinput, INPUT);
  pinMode(feedbackinput, INPUT);
  digitalWrite(pwm, LOW);
  pwmval = 0;
}

void loop() {
  potinputval = analogRead(potinput);
  potinputval = map(potinputval, 1023, 0, 255, 0);
  feedbackinputval = analogRead(feedbackinput);
  feedbackinputval = map(feedbackinputval, 1023, 0, 255, 0);

  //do we need feedback? 
  //i feel no because we are supplying this voltage to the driver, which 
  //takes in a minimal current, but then if a different driver takes in a different 
  //current value? better safe then sorry :P
  
   while (potinputval > feedbackinputval) {  //condition1
    if (pwmval == 230) {
      potinputval = analogRead(potinput);
      potinputval = map(potinputval, 1023, 0, 255, 0);
      feedbackinputval = analogRead(feedbackinput);
      feedbackinputval = map(feedbackinputval, 1023, 0, 255, 0);
    }
    else {
      pwmval = pwmval + 1;
      analogWrite(pwm, pwmval);
      potinputval = analogRead(potinput);
      potinputval = map(potinputval, 1023, 0, 255, 0);
      feedbackinputval = analogRead(feedbackinput);
      feedbackinputval = map(feedbackinputval, 1023, 0, 255, 0);
    }
  }

  
  while (potinputval < feedbackinputval) {    //condition2
    if (pwmval == 0) {
      potinputval = analogRead(potinput);
      potinputval = map(potinputval, 1023, 0, 255, 0);
      feedbackinputval = analogRead(feedbackinput);
      feedbackinputval = map(feedbackinputval, 1023, 0, 255, 0);
    }
    else {
      pwmval = pwmval - 1;
      analogWrite(pwm, pwmval);
      potinputval = analogRead(potinput);
      potinputval = map(potinputval, 1023, 0, 255, 0);
      feedbackinputval = analogRead(feedbackinput);
      feedbackinputval = map(feedbackinputval, 1023, 0, 255, 0);
    }
  }
}
