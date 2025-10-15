// (200-400), lower = harder, higher = easier
// int speed = 200;
int speed = 300;
// int speed = 400;

//start program with lowest difficulty
int difficulty = 1;
int maxdifficulty = 5;

#include <avr/io.h>
#include <Arduino.h>

//copied straight from myself lol
#define c1 5
#define c2 2
#define c3 0
#define c4 3
#define c5 1
#define c6 4
#define c7 6
#define c8 7
#define r1 8
#define r2 10
#define r4 9
#define r5 13
#define r7 A0
#define r8 A1
#define r6 A3
#define r3 A4

int column[] = {c1, c2, c3, c4, c5, c6, c7, c8};
int row[] = {r1, r2, r3, r4, r5, r6, r7, r8};

//10 numbers in countdown, 0-9
int countdown = 9;
//countdown and spinner timers
unsigned long lastCountdown = 0;
unsigned long lastSpin = 0;

//need to check for debounce
unsigned long debounce = 0;

//gap variable, altered by difficulty
int diffGap = 0;

//start spinner at border index 0, top left
int spinner = 0;

//whether it should be spinning or not;
//after button press, want to stop, but start with it spinning
bool spinning = true;
//also want one for countdown
bool countdowning = true;

//win and lose condition booleans
bool winCondition = false;
bool loseCondition = false;

//for border
struct Point {int r; int c;};

//border LEDout pin locs from top left going clockwise
Point border[28] = {
  {0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},
  {0,7},{1,7},{2,7},{3,7},{4,7},{5,7},{6,7},
  {7,7},{7,6},{7,5},{7,4},{7,3},{7,2},{7,1},
  {7,0},{6,0},{5,0},{4,0},{3,0},{2,0},{1,0}
};

//number draw arrays 0–9
byte numbers[10][8][8] = {
  // 0
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // 1
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // 2
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // 3
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // 4
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // 5
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // 6
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // 7
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // 8
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // 9
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  }
};
//====================================================================
//lose condition image
byte lose[8][8] = {
  {1,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,1,0},
  {0,0,1,0,0,1,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,1,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1}
};
//win condition image
byte win[8][53] = {
  //Y O U   W I N
  //goddam this is taking forever
  { 1,1,0,0,1,1, 0, 0,1,1,1,1,0, 0, 1,1,0,0,1,1, 0,0,0,0,0,0, 1,1,0,0,0,1,1, 0, 1,1, 0, 1,0,0,0,1,1, 0,1,1,0,0,0,0,0,0,0},
  { 1,1,0,0,1,1, 0, 1,1,1,1,1,1, 0, 1,1,0,0,1,1, 0,0,0,0,0,0, 1,1,0,0,0,1,1, 0, 1,1, 0, 1,1,0,0,1,1, 0,1,1,0,0,0,0,0,0,0},
  { 1,1,0,0,1,1, 0, 1,1,0,0,1,1, 0, 1,1,0,0,1,1, 0,0,0,0,0,0, 1,1,0,0,0,1,1, 0, 1,1, 0, 1,1,1,0,1,1, 0,1,1,0,0,0,0,0,0,0},
  { 0,1,1,1,1,0, 0, 1,1,0,0,1,1, 0, 1,1,0,0,1,1, 0,0,0,0,0,0, 1,1,0,1,0,1,1, 0, 1,1, 0, 1,1,1,0,1,1, 0,1,1,0,0,0,0,0,0,0},
  { 0,1,1,1,1,0, 0, 1,1,0,0,1,1, 0, 1,1,0,0,1,1, 0,0,0,0,0,0, 1,1,0,1,0,1,1, 0, 1,1, 0, 1,1,1,1,1,1, 0,1,1,0,0,0,0,0,0,0},
  { 0,0,1,1,0,0, 0, 1,1,0,0,1,1, 0, 1,1,0,0,1,1, 0,0,0,0,0,0, 1,1,0,1,0,1,1, 0, 1,1, 0, 1,1,0,1,1,1, 0,0,0,0,0,0,0,0,0,0},
  { 0,0,1,1,0,0, 0, 1,1,1,1,1,1, 0, 1,1,1,1,1,1, 0,0,0,0,0,0, 1,1,1,1,1,1,1, 0, 1,1, 0, 1,1,0,0,1,1, 0,1,1,0,0,0,0,0,0,0},
  { 0,0,1,1,0,0, 0, 0,1,1,1,1,0, 0, 1,1,1,1,1,1, 0,0,0,0,0,0, 1,1,1,1,1,1,1, 0, 1,1, 0, 1,1,0,0,0,1, 0,1,1,0,0,0,0,0,0,0}
};
//==============================SETUP=================================
//==============================SETUP==============================
void setup() {
  //set all rows output
  for (int r = 0; r < 8; r++) {
    pinMode(row[r], OUTPUT);
  }
  //set portD output
  DDRD = B11111111;
  //set the button as a pullup input pin
  pinMode(11, INPUT_PULLUP);
  countdown = 9;
  //if i want to restart spinner in top left, index 0
  //spinner = 0;
  spinning = true;
  countdowning = true;
  winCondition = false;
  loseCondition = false;
  //logic for changing winning gap with difficulty
  //either 4, 3, 2, or 1 LED gap, scaled with 2s
  if(difficulty < 3) {
    diffGap = 3;
  } else {
    if(difficulty < 4) {
      diffGap = 2;
    } else {
      if(difficulty < 5) {
        diffGap = 1;
      } else {
        diffGap = 0;
      }
    }
  }
}
//====================================================================
void render() {
  //start every row off
  for (int r = 0; r < 8; r++) {
    digitalWrite(row[r], HIGH);
  }
  //start portD all off
  PORTD = B00000000;

  //index through rows outer
  for (int r = 0; r < 8; r++) {
    //temp byte dPort to edit and pass to PORTD later
    uint8_t dPort = 0;

    //draw countdown number
    //index through columns
    for (int c = 0; c < 8; c++) {
      //pick 2d array within 3d array for correct countdown num
      if (numbers[countdown][r][c]) {
        //set that column high in temp dPort
        dPort |= (1 << column[c]);
      }
    }

    // draw border loop
    for (int i = 0; i < 28; i++) {
      //if in row 7, and column 3 or 4, exit loop and iterate
      if (border[i].r == 7 && border[i].c >= 2 && border[i].c <= 2+diffGap) {
        if(i == spinner) {
          if (border[i].r == r) {
          dPort |= (1 << column[border[i].c]);
          }
        }
        continue;
      }
      // if border pixel index = spinner index, exit loop and iterate
      if (i == spinner) continue;
      //otherwise, write border pixel column on in temp dPort
      if (border[i].r == r) {
        dPort |= (1 << column[border[i].c]);
      }
    }

    //output temp byte to port D
    PORTD = dPort;
    //set row on
    digitalWrite(row[r], LOW);
    //delay
    delayMicroseconds(1000);
    //set row off, after 1ms delay
    digitalWrite(row[r], HIGH);
  }
}
//==============================ANIMATIONS=============================
//win animation
void drawWin() {
  //i literally copied this from myself, from ok scroll
  //changed variable names, and matrix bounds to 43 instead of 17
  //but it's mine lol so i can copy paste myself right?
    static int winOffset = 0;

  //basically refresh rate, loops through this many times, decreasing refresh
  //increases scroll speed
  for (int refresh = 0; refresh < 10; refresh++) {
    //iterate through rows
    for (int r = 0; r < 8; r++) {
      //turn every row off first
      for (int i = 0; i < 8; i++) {
        digitalWrite(row[i], HIGH);
      }
      //temp variable to edit then pass to PORTD
      uint8_t winPort = 0;
      //loop through columns
      for (int c = 0; c < 8; c++) {
        //shifts pattern by add scroll offset, then wrap so it's continuous
        //select which colum of ok[][] to read
        int colSelect = (c + winOffset) % 53;
        //if bit is 1, write a 1 to temp column bit
        if (win[r][colSelect]) winPort |= (1 << column[c]);
      }
      //pass whole byte to PORTD
      PORTD = winPort;
      //turn on row at r
      digitalWrite(row[r], LOW);
      //1ms delay
      delayMicroseconds(1000);
      //turn row r off
      digitalWrite(row[r], HIGH);
    }
  }
  //shifts window, add 1 to col add
  winOffset++;
  //resets scroll offset back to 0 at array ending to restart scroll
  if (winOffset >= 53) {
    winOffset = 0;
  }
  //check for button press
  if (digitalRead(11) == LOW) {
      delay(50);
      //wait for release, when player is ready to play again
      while(digitalRead(11) == LOW);
      difficulty = 1;
      spinner = 0;
      setup();  // restart the game
      return;   // exit the winDraw function
    }
}

//lose animation, draw an X, same logic as before
void drawLose() {
  for (int r = 0; r < 8; r++) {
    uint8_t losePort = 0;
    for (int c = 0; c < 8; c++) {
      if (lose[r][c]) {
        losePort |= (1 << column[c]);
      }
    }
    PORTD = losePort;
    digitalWrite(row[r], LOW);
    delayMicroseconds(1000);
    digitalWrite(row[r], HIGH);
  }
}
//====================================================================
//reset all variables, only upping difficulty

//can't get this pos to work so forget about it
// void resetGameHarder() {
//   countdown = 9;
//   spinner = 0;
//   spinning = true;
//   lastCountdown = millis();
//   lastSpin = millis();
//   difficulty += 2;
// }
// void resetGame() {
//   countdown = 9;
//   spinner = 0;
//   spinning = true;
//   lastCountdown = millis();
//   lastSpin = millis();
// }
//====================================================================
void loop() {
  //keep track of current time
  unsigned long now = millis();

  //check for win conditions upon calling loop():
  if(winCondition) {
    drawWin();
    return;
  }
  //check for lose conditions upon calling loop():
  if(loseCondition || countdown == 0) {
    while(millis() - now < 3000) {
      drawLose();
    }
    difficulty = 1;
    spinner = 0;
    setup();
    return;
  }
//====================================================================
  //check if still counting down and 1s has passed, update countdown number
  if (countdowning && now - lastCountdown >= 1000) {
    //if so, subtract one from countdown until 0
    if (countdown > 0) {
      countdown--;
    }
    //reset countdown timer reference to current time
    lastCountdown = now;
  }
//====================================================================
  // check for button press, and debounce (ENDGAME)
  if (digitalRead(11) == LOW && millis() - debounce > 200) {
    //stop spinning if so
    spinning = false;
    //and stop counting down
    countdowning = false;
    //update button press time
    debounce = millis();
    if (border[spinner].r == 7 && border[spinner].c >= 2 && border[spinner].c <= 2+diffGap) {
      if(difficulty < maxdifficulty) {
        difficulty++;
        setup();
        return;
      } else {
        winCondition = true;
      }
    } else {
      loseCondition = true;
    }
  }
//====================================================================
  //-------else:
  //check if 50ms has passed while countdown is active and 
  //spinner not stopped
  if (countdown > 0 && spinning && countdowning && now - lastSpin >= speed / (difficulty*2)) {
    //if all true, increase spinner position
    spinner++;
    //loop spinner back to index 0 once it reaches top left again, 
    //border index 28
    if (spinner >= 28) {
      spinner = 0;
    }
    //reset spinner timer reference to current time
    lastSpin = now;
  }

  //recall method to produce whole display, with updated countdown,
  //updated spinner number, and if button was pressed
  render();
}
