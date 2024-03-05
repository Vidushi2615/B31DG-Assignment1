void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  digitalWrite(4, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(4, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
  digitalWrite(5, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(5, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}