#include <Servo.h>

Servo myServo;

void setup() {
  // pin 9 for signal
  myServo.attach(9);
}

void loop() {
  // all the way counterclockwise rotation
  myServo.write(0);
  delay(1000);  // wait 1 second

  // all the way clockwise rotation
  myServo.write(180);
  delay(1000);
}