/*
 * ML-303 Button Matrix Test Firmware
 * 
 * Tests all 36 buttons in the ML-303 matrix configuration:
 * - Function Matrix: 4×2 (8 buttons)
 * - Step Matrix: 8×2 (16 buttons)
 * - Note Matrix: 6×2 (12 buttons)
 * 
 * Compatible with ATmega328/Arduino Uno
 * 
 * Author: ML-303 Assembly Assistant
 * Date: December 2024
 */

// Pin definitions based on ML-303 specifications
// Function Matrix
#define FUNC_ROW1    A0  // PA0 - Pin 28
#define FUNC_ROW2    A1  // PA1 - Pin 27
#define FUNC_COL1    A2  // PA2 - Pin 26
#define FUNC_COL2    A3  // PA3 - Pin 25
#define FUNC_COL3    A4  // PA4 - Pin 24
#define FUNC_COL4    A5  // PA5 - Pin 23

// Step Matrix
#define STEP_ROW1    8   // PB0 - Pin 1
#define STEP_ROW2    9   // PB1 - Pin 2
#define STEP_COL1    10  // PB2 - Pin 3
#define STEP_COL2    11  // PB3 - Pin 4
#define STEP_COL3    12  // PB4 - Pin 5
#define STEP_COL4    13  // PB5 - Pin 6
#define STEP_COL5    A0  // PC0 - Pin 7 (shared with analog)
#define STEP_COL6    A1  // PC1 - Pin 8
#define STEP_COL7    2   // PD2 - Pin 9
#define STEP_COL8    3   // PD3 - Pin 10

// Note Matrix
#define NOTE_ROW1    A2  // PC2 - Pin 11
#define NOTE_ROW2    A3  // PC3 - Pin 12
#define NOTE_COL1    A4  // PC4 - Pin 13
#define NOTE_COL2    A5  // PC5 - Pin 14
#define NOTE_COL3    4   // PD4 - Pin 15
#define NOTE_COL4    5   // PD5 - Pin 16
#define NOTE_COL5    6   // PD6 - Pin 17
#define NOTE_COL6    7   // PD7 - Pin 18

// LED indicators
#define LED_PASS     A6  // Pass indicator
#define LED_FAIL     A7  // Fail indicator

// Button state tracking
bool functionButtons[4][2];
bool stepButtons[8][2];
bool noteButtons[6][2];

// Button names for display
const char* functionNames[4][2] = {
  {"WRITE", "RUN"},
  {"PITCH", "TAP"},
  {"CLEAR", "FUNC"},
  {"TIME", "BACK"}
};

const char* noteNames[6][2] = {
  {"C", "C#"},
  {"D", "D#"},
  {"E", "F"},
  {"F#", "G"},
  {"G#", "A"},
  {"A#", "B"}
};

// Test results
int totalButtons = 36;
int passedButtons = 0;
int failedButtons = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("================================="));
  Serial.println(F("ML-303 Button Matrix Test v1.0"));
  Serial.println(F("================================="));
  Serial.println();
  
  // Initialize pins
  initializePins();
  
  // Run initial test
  Serial.println(F("Starting button matrix test..."));
  Serial.println(F("Press each button when prompted"));
  Serial.println();
  
  delay(1000);
}

void loop() {
  // Main test menu
  Serial.println(F("\n--- TEST MENU ---"));
  Serial.println(F("1. Test All Buttons"));
  Serial.println(F("2. Test Function Matrix"));
  Serial.println(F("3. Test Step Matrix"));
  Serial.println(F("4. Test Note Matrix"));
  Serial.println(F("5. Continuous Scan Mode"));
  Serial.println(F("6. Adapter Test Mode"));
  Serial.println(F("7. Show Wiring Diagram"));
  Serial.println(F("Enter choice: "));
  
  while (!Serial.available()) {
    // Wait for input
  }
  
  char choice = Serial.read();
  Serial.println(choice);
  Serial.println();
  
  switch (choice) {
    case '1':
      testAllButtons();
      break;
    case '2':
      testFunctionMatrix();
      break;
    case '3':
      testStepMatrix();
      break;
    case '4':
      testNoteMatrix();
      break;
    case '5':
      continuousScan();
      break;
    case '6':
      adapterTest();
      break;
    case '7':
      showWiringDiagram();
      break;
    default:
      Serial.println(F("Invalid choice"));
  }
}

void initializePins() {
  // Function Matrix
  pinMode(FUNC_ROW1, INPUT_PULLUP);
  pinMode(FUNC_ROW2, INPUT_PULLUP);
  pinMode(FUNC_COL1, OUTPUT);
  pinMode(FUNC_COL2, OUTPUT);
  pinMode(FUNC_COL3, OUTPUT);
  pinMode(FUNC_COL4, OUTPUT);
  digitalWrite(FUNC_COL1, HIGH);
  digitalWrite(FUNC_COL2, HIGH);
  digitalWrite(FUNC_COL3, HIGH);
  digitalWrite(FUNC_COL4, HIGH);
  
  // Step Matrix
  pinMode(STEP_ROW1, INPUT_PULLUP);
  pinMode(STEP_ROW2, INPUT_PULLUP);
  pinMode(STEP_COL1, OUTPUT);
  pinMode(STEP_COL2, OUTPUT);
  pinMode(STEP_COL3, OUTPUT);
  pinMode(STEP_COL4, OUTPUT);
  pinMode(STEP_COL5, OUTPUT);
  pinMode(STEP_COL6, OUTPUT);
  pinMode(STEP_COL7, OUTPUT);
  pinMode(STEP_COL8, OUTPUT);
  for (int i = 0; i < 8; i++) {
    digitalWrite(STEP_COL1 + i, HIGH);
  }
  
  // Note Matrix
  pinMode(NOTE_ROW1, INPUT_PULLUP);
  pinMode(NOTE_ROW2, INPUT_PULLUP);
  pinMode(NOTE_COL1, OUTPUT);
  pinMode(NOTE_COL2, OUTPUT);
  pinMode(NOTE_COL3, OUTPUT);
  pinMode(NOTE_COL4, OUTPUT);
  pinMode(NOTE_COL5, OUTPUT);
  pinMode(NOTE_COL6, OUTPUT);
  for (int i = 0; i < 6; i++) {
    digitalWrite(NOTE_COL1 + i, HIGH);
  }
  
  // LEDs
  pinMode(LED_PASS, OUTPUT);
  pinMode(LED_FAIL, OUTPUT);
  digitalWrite(LED_PASS, LOW);
  digitalWrite(LED_FAIL, LOW);
}

void scanFunctionMatrix() {
  int cols[] = {FUNC_COL1, FUNC_COL2, FUNC_COL3, FUNC_COL4};
  int rows[] = {FUNC_ROW1, FUNC_ROW2};
  
  for (int col = 0; col < 4; col++) {
    // Set column low
    digitalWrite(cols[col], LOW);
    delayMicroseconds(10);
    
    // Read rows
    for (int row = 0; row < 2; row++) {
      functionButtons[col][row] = !digitalRead(rows[row]);
    }
    
    // Set column high again
    digitalWrite(cols[col], HIGH);
  }
}

void scanStepMatrix() {
  int cols[] = {STEP_COL1, STEP_COL2, STEP_COL3, STEP_COL4, 
                STEP_COL5, STEP_COL6, STEP_COL7, STEP_COL8};
  int rows[] = {STEP_ROW1, STEP_ROW2};
  
  for (int col = 0; col < 8; col++) {
    digitalWrite(cols[col], LOW);
    delayMicroseconds(10);
    
    for (int row = 0; row < 2; row++) {
      stepButtons[col][row] = !digitalRead(rows[row]);
    }
    
    digitalWrite(cols[col], HIGH);
  }
}

void scanNoteMatrix() {
  int cols[] = {NOTE_COL1, NOTE_COL2, NOTE_COL3, NOTE_COL4, NOTE_COL5, NOTE_COL6};
  int rows[] = {NOTE_ROW1, NOTE_ROW2};
  
  for (int col = 0; col < 6; col++) {
    digitalWrite(cols[col], LOW);
    delayMicroseconds(10);
    
    for (int row = 0; row < 2; row++) {
      noteButtons[col][row] = !digitalRead(rows[row]);
    }
    
    digitalWrite(cols[col], HIGH);
  }
}

void testAllButtons() {
  Serial.println(F("=== TESTING ALL BUTTONS ==="));
  Serial.println(F("Follow the prompts to test each button"));
  Serial.println();
  
  passedButtons = 0;
  failedButtons = 0;
  
  // Test function buttons
  testFunctionMatrix();
  
  // Test step buttons
  testStepMatrix();
  
  // Test note buttons
  testNoteMatrix();
  
  // Show results
  Serial.println(F("\n=== TEST COMPLETE ==="));
  Serial.print(F("Total buttons: "));
  Serial.println(totalButtons);
  Serial.print(F("Passed: "));
  Serial.println(passedButtons);
  Serial.print(F("Failed: "));
  Serial.println(failedButtons);
  
  if (failedButtons == 0) {
    Serial.println(F("\n*** ALL TESTS PASSED! ***"));
    digitalWrite(LED_PASS, HIGH);
    digitalWrite(LED_FAIL, LOW);
  } else {
    Serial.println(F("\n*** SOME TESTS FAILED ***"));
    digitalWrite(LED_PASS, LOW);
    digitalWrite(LED_FAIL, HIGH);
  }
}

void testFunctionMatrix() {
  Serial.println(F("\n--- Testing Function Matrix ---"));
  
  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 2; row++) {
      Serial.print(F("Press "));
      Serial.print(functionNames[col][row]);
      Serial.print(F(" button... "));
      
      if (waitForButton(0, col, row, 5000)) {
        Serial.println(F("PASS"));
        passedButtons++;
      } else {
        Serial.println(F("FAIL"));
        failedButtons++;
      }
    }
  }
}

void testStepMatrix() {
  Serial.println(F("\n--- Testing Step Matrix ---"));
  
  for (int i = 0; i < 16; i++) {
    int col = i % 8;
    int row = i / 8;
    
    Serial.print(F("Press Step "));
    Serial.print(i + 1);
    Serial.print(F(" button... "));
    
    if (waitForButton(1, col, row, 5000)) {
      Serial.println(F("PASS"));
      passedButtons++;
    } else {
      Serial.println(F("FAIL"));
      failedButtons++;
    }
  }
}

void testNoteMatrix() {
  Serial.println(F("\n--- Testing Note Matrix ---"));
  
  for (int col = 0; col < 6; col++) {
    for (int row = 0; row < 2; row++) {
      Serial.print(F("Press "));
      Serial.print(noteNames[col][row]);
      Serial.print(F(" button... "));
      
      if (waitForButton(2, col, row, 5000)) {
        Serial.println(F("PASS"));
        passedButtons++;
      } else {
        Serial.println(F("FAIL"));
        failedButtons++;
      }
    }
  }
}

bool waitForButton(int matrix, int col, int row, unsigned long timeout) {
  unsigned long startTime = millis();
  
  while (millis() - startTime < timeout) {
    // Scan appropriate matrix
    switch (matrix) {
      case 0:
        scanFunctionMatrix();
        if (functionButtons[col][row]) {
          // Wait for release
          while (functionButtons[col][row]) {
            scanFunctionMatrix();
            delay(10);
          }
          return true;
        }
        break;
      case 1:
        scanStepMatrix();
        if (stepButtons[col][row]) {
          while (stepButtons[col][row]) {
            scanStepMatrix();
            delay(10);
          }
          return true;
        }
        break;
      case 2:
        scanNoteMatrix();
        if (noteButtons[col][row]) {
          while (noteButtons[col][row]) {
            scanNoteMatrix();
            delay(10);
          }
          return true;
        }
        break;
    }
    delay(10);
  }
  
  return false;
}

void continuousScan() {
  Serial.println(F("=== CONTINUOUS SCAN MODE ==="));
  Serial.println(F("Press any button to see its state"));
  Serial.println(F("Send any character to exit"));
  Serial.println();
  
  while (!Serial.available()) {
    scanFunctionMatrix();
    scanStepMatrix();
    scanNoteMatrix();
    
    // Check function buttons
    for (int col = 0; col < 4; col++) {
      for (int row = 0; row < 2; row++) {
        if (functionButtons[col][row]) {
          Serial.print(F("PRESSED: "));
          Serial.println(functionNames[col][row]);
        }
      }
    }
    
    // Check step buttons
    for (int col = 0; col < 8; col++) {
      for (int row = 0; row < 2; row++) {
        if (stepButtons[col][row]) {
          Serial.print(F("PRESSED: Step "));
          Serial.println(row * 8 + col + 1);
        }
      }
    }
    
    // Check note buttons
    for (int col = 0; col < 6; col++) {
      for (int row = 0; row < 2; row++) {
        if (noteButtons[col][row]) {
          Serial.print(F("PRESSED: "));
          Serial.println(noteNames[col][row]);
        }
      }
    }
    
    delay(50);
  }
  
  // Clear serial buffer
  while (Serial.available()) {
    Serial.read();
  }
}

void adapterTest() {
  Serial.println(F("=== ADAPTER TEST MODE ==="));
  Serial.println(F("Tests individual adapter connections"));
  Serial.println(F("Connect adapter between 4-pin switch and ML-303"));
  Serial.println();
  
  Serial.println(F("Testing sequence:"));
  Serial.println(F("1. Common continuity (Pin 1 -> A)"));
  Serial.println(F("2. Row continuity (Pin 2 -> B)"));
  Serial.println(F("3. Column continuity (Pin 3 -> C)"));
  Serial.println(F("4. Isolation test (Pin 4 -> NC)"));
  Serial.println();
  
  // This would require additional test points in real hardware
  Serial.println(F("Please use multimeter to verify:"));
  Serial.println(F("- Pin 1 to Pin A: <1 ohm"));
  Serial.println(F("- Pin 2 to Pin B: <1 ohm"));
  Serial.println(F("- Pin 3 to Pin C: <1 ohm"));
  Serial.println(F("- Pin 4 to all: >1M ohm"));
}

void showWiringDiagram() {
  Serial.println(F("\n=== WIRING DIAGRAM ==="));
  Serial.println(F(""));
  Serial.println(F("Function Matrix (4x2):"));
  Serial.println(F("  Rows: PA0(28), PA1(27)"));
  Serial.println(F("  Cols: PA2(26), PA3(25), PA4(24), PA5(23)"));
  Serial.println(F(""));
  Serial.println(F("Step Matrix (8x2):"));
  Serial.println(F("  Rows: PB0(1), PB1(2)"));
  Serial.println(F("  Cols: PB2(3) through PC1(8)"));
  Serial.println(F(""));
  Serial.println(F("Note Matrix (6x2):"));
  Serial.println(F("  Rows: PC2(11), PC3(12)"));
  Serial.println(F("  Cols: PC4(13) through PD1(18)"));
  Serial.println(F(""));
  Serial.println(F("All rows need 10k pull-up resistors to VCC"));
  Serial.println(F(""));
  Serial.println(F("Adapter connections:"));
  Serial.println(F("  4-pin switch -> 3-pin ML-303"));
  Serial.println(F("  Pin 1 -> A (Common)"));
  Serial.println(F("  Pin 2 -> B (Row)"));
  Serial.println(F("  Pin 3 -> C (Column)"));
  Serial.println(F("  Pin 4 -> Not Connected"));
}

// Utility functions for production testing
void factoryTest() {
  // Quick test all buttons without prompts
  int errors = 0;
  
  // Set all columns high
  initializePins();
  
  // Test each matrix for shorts
  // This would be expanded in production firmware
  
  if (errors == 0) {
    // Flash pass LED 3 times
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_PASS, HIGH);
      delay(200);
      digitalWrite(LED_PASS, LOW);
      delay(200);
    }
  } else {
    // Flash fail LED continuously
    while (1) {
      digitalWrite(LED_FAIL, HIGH);
      delay(500);
      digitalWrite(LED_FAIL, LOW);
      delay(500);
    }
  }
}