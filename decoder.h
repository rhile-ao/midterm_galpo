// SEVEN-SEGMENT GPIO PINS
const uint8_t SEG1[] = {32, 33, 25, 26, 27, 14, 12};
const uint8_t SEG2[] = {19, 18, 5, 17, 16, 4, 0};

const uint8_t NUM_SEG = 7;

// DIGIT PATTERNS: A, B, C, D, E, F, G
// COMMON-CATHODE: 1 = ON, 0 = OFF

const uint8_t DIGITS[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

// INITIALIZE SEVEN-SEGMENT PINS
void decoderSetup() {

  for (int i = 0; i < NUM_SEG; i++) {
    pinMode(SEG1[i], OUTPUT);
    pinMode(SEG2[i], OUTPUT);
  }
}

// DISPLAY A SINGLE DIGIT
void displayDigit(const uint8_t SEG[], int number) {

  for (int i = 0; i < NUM_SEG; i++) {
    digitalWrite(SEG[i], DIGITS[number][i]);
  }
}

// DISPLAY COUNTER ON BOTH DISPLAYS
void decoder(int counter) {

  int tens = counter / 10;
  int ones = counter % 10;

  // FIRST DISPLAY SHOWS TENS
  displayDigit(SEG1, tens);

  // SECOND DISPLAY SHOWS ONES
  displayDigit(SEG2, ones);
}
