// Pin configuration of Switch
#define s1 6 //Switch 1
#define s2 7 //Switch 2

//Pin configuration of LED
#define sigA 4 //Signal A or LED 1
#define sigB 5 //Signal B or LED 2

//Width of Signal B
#define SIG_B_WIDTH 50

//Values corresponding to the first 5 letters in the surname "naduparambil"
#define n 13
#define a 1
#define d 4
#define u 6
#define p 11

//Variables to read switch values and store it in temporary variables
int sw1 = 0, sw2 = 0; //Switch 1 and Switch 2
int ts1 = 0, ts2 = 0;

void switch1(){
  sw1 = digitalRead(s1); // reading from Switch 1 (s1) and storing it in sw1
}

void switch2(){
  sw2 = digitalRead(s2); // reading from Switch 2 (s2) and storing it in sw2
}

void setup() {
  Serial.begin(9600);

  pinMode(s1, INPUT_PULLDOWN); //setting switch 1 pin as INPUT with pull-down resistor configuration
  pinMode(s2, INPUT_PULLDOWN); //setting switch 1 pin as INPUT with pull-down resistor configuration
  pinMode(sigA, OUTPUT);// setting sigA pin(LED 1/signal A) as OUTPUT
  pinMode(sigB, OUTPUT);// setting sigB pin(LED 2/signal B) as OUTPUT
  attachInterrupt(s1, switch1, HIGH);
  attachInterrupt(s2, switch2, HIGH);
}

void loop() {
  //Calculate the Parameters: 5 letters of the surname "Nadup"
  int A = n * 100; // parameter 'a' calculated as n*100
  int B = a * 100; // parameter 'b' calculated as a*100
  int C = d + 4; // parameter 'c' calculated as d+4
  int D = u * 500; // parameter 'd' calculated as u*500
  int M = ( p % 4 ) + 1;// mode is calculated as rem(p/4) + 1 = rem(11/4) + 1 = 4. Hence we use mode 4

  //Start with no output at both the signals
  digitalWrite(sigA, LOW);
  digitalWrite(sigB, LOW);

  //Start signal B
  digitalWrite(sigB, HIGH);
  delay(SIG_B_WIDTH); // Keep the pulse high for 50 microsec
  digitalWrite(sigB, LOW);

  if(ts2 == LOW)
  {
    for(int i = 0 ; i < C ; i++ )
    {
      if ( ts1 == LOW )
      {
        digitalWrite(sigA, HIGH);
      }
      delay(A);
      digitalWrite(sigA, LOW);
      delay(B);
      A = A + 50;
    }   
    delay(D);
  }
  else
  {
    for(int i = 0 ; i < C ; i++ )
    {
      if ( ts1 == LOW )
      {
        digitalWrite(sigA, HIGH);
      }
      delay(A);
      digitalWrite(sigA, LOW);
      delay(B/2);
      A = A + 50;
    }
    delay(D/2);
  }

  ts1 = sw1 ;  
  ts2 = sw2 ;

  sw1 = 0;
  sw2 = 0;
}
