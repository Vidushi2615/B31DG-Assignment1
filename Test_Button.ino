// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(6, INPUT_PULLDOWN);
  pinMode(7, INPUT_PULLDOWN);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  bool buttonState1 = digitalRead(6);
  bool buttonState2 = digitalRead(7);

  // print out the state of the button:
  if (buttonState1){
    Serial.println("1");
  }
  if (buttonState2){
    Serial.println("2");
  }
  delay(70);  // delay in between reads for stability
}
