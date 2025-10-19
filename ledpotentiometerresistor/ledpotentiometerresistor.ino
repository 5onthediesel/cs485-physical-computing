//array of arduino pins for each led
const int leds[] = {2, 3, 4, 5};
const int potentiometer = A4;

void setup() {
  //set led pins as output
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  //read pot
  int pot = analogRead(potentiometer);

  //map for continuous values of delayy
  //set min and max of map to min/max delay between leds
  int pottime = map(pot, 0, 1023, 800, 100);

  //run through leds continuously, checking each iteration for change in
  //pot changes
  for (int i = 0; i < 4; i++) {
    //led on delay pot time, then off
    digitalWrite(leds[i], HIGH);
    //depending on state of A4 pot
    delay(pottime);
    digitalWrite(leds[i], LOW);
  }
}