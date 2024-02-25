
// Pin configuration of Switch
#define s1 6 //Switch 1
#define s2 7 //Switch 2

//Pin configuration of LED
#define sigA 4 //Signal A or LED 1
#define sigB 5 //Signal B or LED 2

//Width of Signal B
#define SIG_B_WIDTH 50

//Values corresponding to the first 5 letters in the surname "naduparambil"
#define n 14
#define a 1
#define d 4
#define u 21
#define p 16

//Variables to read switch values and determine the case
int sw1 = 0, sw2 = 0; //Switch 1 and Switch 2
int temp = 0;

void setup() {
  Serial.begin(9600);

  pinMode(s1, INPUT_PULLDOWN); //setting switch 1 pin as INPUT with pull-down resistor configuration
  pinMode(s2, INPUT_PULLDOWN); //setting switch 1 pin as INPUT with pull-down resistor configuration
  pinMode(sigA, OUTPUT);// setting sigA pin(LED 1/signal A) as OUTPUT
  pinMode(sigB, OUTPUT);// setting sigB pin(LED 2/signal B) as OUTPUT

  Serial.println(A,B,C,D,M,R);
}

void loop() {
  //Calculate the Parameters: 5 letters of the surname "Nadup"
  int A = n * 100; // parameter 'a' calculated as n*100
  int B = a * 100; // parameter 'b' calculated as a*100
  int C = d + 4; // parameter 'c' calculated as d+4
  int D = u * 500; // parameter 'd' calculated as u*500
  int M = ( p % 4 ) + 1;// mode is calculated as rem(p/4) + 1 = rem(16/4) + 1 = 1. Hence we use mode 1
  int R = C - 3; // parameter used in mode '1' where we reduce the pulses by 3, r = c-3

  sw1 = digitalRead(s1); // reading from Switch 1 (s1) and storing it in sw1
  sw2 = digitalRead(s2); // reading from Switch 2 (s2) and storing it in sw2
  
  if(sw1 == HIGH)         // using if else to determine the case
  {
    digitalWrite(sigA, LOW);
    digitalWrite(sigB, LOW);
  }

  else{

    digitalWrite(sigB, HIGH);
    delay(SIG_B_WIDTH);
    digitalWrite(sigB, LOW);
    
    if(sw2 == LOW)
    {
      for(int i = 0 ; i < C ; i++ )
      {
        digitalWrite(sigA, HIGH);
        delay(A);
        digitalWrite(sigA, LOW);
        delay(B);
        A = A+50;
      }
    }
    else
    {
      for(int i = 0 ; i < R ; i++ )
      {
        digitalWrite(sigA, HIGH);
        delay(A);
        digitalWrite(sigA, LOW);
        delay(B);
        A = A+50;
      }
    }
    
    delay(D);
  
  }
}
