// led pins d2-d5
const int led[] = {2, 3, 4, 5};

void setup() {
  // leds output
  for (int i = 0; i < 4; i++) {
    pinMode(led[i], OUTPUT);
  }
}

void loop() {
  // read a0 photocell sensor
  int photocell = analogRead(A0);

  // 150 for full dark, hand on photocell, 600 for bright room
  // map photocell 150-600 to number of leds, scale 0-4
  int lightLevel = map(photocell, 150, 600, 0, 4);
  // make sure in range 0-4, anything darker just do 0, anything 
  // brighter like flashlight, just do all 4
  lightLevel = constrain(lightLevel, 0, 4);

  // up to lightlevel, max4, turn on that number of leds
  for (int i = 0; i < 4; i++) {
    if (i < lightLevel) {
      digitalWrite(led[i], HIGH);
    } else {
      digitalWrite(led[i], LOW);
    }
  }

  delay(100);
}