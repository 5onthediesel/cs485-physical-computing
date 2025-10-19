//array of arduino pins for each led
const int leds[] = {2, 3, 4, 5};

void setup() {
  //set all pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  //individually write each led high then low (on then off)

  digitalWrite(leds[0], HIGH);
  //2 seconds
  delay(2000);
  digitalWrite(leds[0], LOW);

  digitalWrite(leds[1], HIGH);
  //1 second
  delay(1000);
  digitalWrite(leds[1], LOW);

  digitalWrite(leds[2], HIGH);
  //0.5 seconds
  delay(500);
  digitalWrite(leds[2], LOW);

  digitalWrite(leds[3], HIGH);
  //0.25 seconds
  delay(250);
  digitalWrite(leds[3], LOW);
  delay(500);

  //blink all 4
  for (int i = 0; i < 3; i++) {
    //blink 3 times, i = 0,1,2
    //set all to on
    for (int j = 0; j < 4; j++) {
      digitalWrite(leds[j], HIGH);
    }
    //wait while on
    delay(200);
    //set all off
    for (int j = 0; j < 4; j++) {
      digitalWrite(leds[j], LOW);
    }
    //wait while off
    delay(200);
    //repeat 3 times for i
  }

  //half second before starting sequence over
  delay(500);
}