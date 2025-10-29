#include <Servo.h>

Servo myServo;

void setup() {
  // servo pin 3
  myServo.attach(3);
}

void loop() {
  // read potentiometer 0-1023
  int potent = analogRead(A0);

  // map angle to possible 0-180 for all values of potentiometer
  // linear
  int angle = map(potent, 0, 1023, 0, 180);

  // turn servo to angle
  myServo.write(angle);
  // small delay
  delay(15);
}