
// Pin configuration of Switch
#define s1 = 6; //Switch 1
#define s2 = 7; //Switch 2

//Pin configuration of LED
#define sigA = 4; //Signal A or LED 1
#define sigB = 5; //Signal B or LED 2

//Calculate the Parameters: 5 letters of surname "Nadup"
#define a = 1400;// parameter 'a' calculated as n*100 = 14*100 = 1400
#define b = 100;// parameter 'b' calculated as a*100 = 1*100 = 100
#define c = 8; // parameter 'c' calculated as d+4 = 4+4=8
#define d = 10500;// parameter 'd' calculated as u*500 = 21*500 = 10500
// mode is calculated as rem(p/4) + 1 = rem(16/4) + 1 = 1. Hence we use mode 1
#define r = 5;// parameter used in mode '1' where we reduce the pulses by 3, r = c-3 = 8-3 = 5

//Variables to read switch values and determine the case
int sw1 = 0, sw2 = 0; //Switch 1 and Switch 2
int case = 0;

void setup() {
  pinMode(s1, INPUT_PULLDOWN); //setting switch 1 pin as INPUT with pull down resistor configuration
  pinMode(s2, INPUT_PULLDOWN); //setting switch 1 pin as INPUT with pull down resistor configuration
  pinMode(sigA, OUTPUT);// setting sigA pin(LED 1/signal A) as OUTPUT
  pinMode(sigB, OUTPUT);// setting sigB pin(LED 2/signal B) as OUTPUT
}

void loop() {
  sw1 = digitalRead(s1); // reading from Switch 1 (s1) and storing it in sw1
  sw2 = digitalRead(s2); // reading from Switch 2 (s2) and storing it in sw2
  
  if(sw1 == HIGH)         // using if else to determine the case
  {
    case = 1;
  }

  else{
    if(sw2 == LOW)
    {
      case = 2;
    }
    else
    {
      case = 3;
    }
  }

  switch (case) 
  {
    case 1:
      digitalWrite(sigA, LOW);
      digitalWrite(sigB, LOW);

    case 2:
      digitalWrite(sigB, HIGH);
      delay(50);
      digitalWrite(sigB, LOW);

      for(int i = 0 ; i < c ; i++ )
      {
        digitalWrite(sigA, HIGH);
        delay(a);
        digitalWrite(sigA, LOW);
        delay(b);
        a = a+50;
      }
      delay(d);

    case 3: 
      digitalWrite(sigB, HIGH);
      delay(50);
      digitalWrite(sigB, LOW);

      for(int i = 0 ; i < r ; i++ )
      {
        digitalWrite(sigA, HIGH);
        delay(a);
        digitalWrite(sigA, LOW);
        delay(b);
        a = a+50;
      }
      delay(d);
  }
}
