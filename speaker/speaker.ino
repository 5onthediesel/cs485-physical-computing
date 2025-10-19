//speaker arduino pin
const int speaker = 8;

void setup() {
  //set speaker as output
  pinMode(speaker, OUTPUT);
}

void loop() {
  //play notes for 0.4s each, half second delay between tones
  //A3 note, 220hz
  tone(speaker, 220, 400);
  delay(500);
   // G4 note, 392hz
  tone(speaker, 392, 400);
  delay(500);
   // A4 note, 440hz
  tone(speaker, 440, 400);
  delay(500);
  //delay 1s
  delay(1000);
}