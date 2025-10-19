//array of arduino pins for each led
const int leds[] = {2, 3, 4, 5};

//right-left and left-right button pins
const int LR = 6;
const int RL = 9;

//direction 1 LR, -1 RL
int direction = 1;
//index leds
int currentLED = 0;
unsigned long time = 0;

void setup() {
  //all led pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }

  //use internal pullup resistors for buttons
  //less wiring
  pinMode(LR, INPUT_PULLUP);
  pinMode(RL, INPUT_PULLUP);
}

void loop() {
  //read LR button
  if (digitalRead(LR) == LOW) {
    //set direction LR
    direction = 1;
  }
  //read RL button
  if (digitalRead(RL) == LOW) {
    //set direction RL
    direction = -1;
  }

  //every 0.2 seconds, update leds and check direction again
  if (millis() - time > 200) {
    time = millis();

    //set all leds off
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], LOW);
    }

    //turn on currentLED index
    digitalWrite(leds[currentLED], HIGH);

    //index next led with direction (1,-1)
    currentLED += direction;

    //wrap continuously in same direction until other button pressed
    if (currentLED >= 4) currentLED = 0;
    if (currentLED < 0) currentLED = 4 - 1;
  }
}