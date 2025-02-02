#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

unsigned long lastCheck = 0;
char key;
char timeStr[17];
String inputBuffer = "";

// Time variables
unsigned long year = 2025;
unsigned int month = 2;
unsigned int day = 1;
unsigned int hours;
unsigned int minutes;
unsigned long timeInMinutes = 0;

// time ints
unsigned long At = 0;
unsigned long Bt = 0; 
unsigned long Ct = 0;
unsigned int tempHours = 0;
unsigned int tempMinutes= 0;


//variables to ports
const int button1 = A2;
const int button2 = A1;
const int button3 = A0;
const int buzz = A3; 

//notes for buzz song 
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880

int melody[] = {
  NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_G4, 
  NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_G4, 
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_G4
};

int noteDurations[] = {
  150, 150, 150, 150, 150, 150, 150, 150, 100,
  150, 150, 150, 150, 150, 150, 150, 150, 100,
  100, 100, 100, 150, 150, 150, 150, 150, 100,
  100, 100, 150, 150, 150, 150, 150, 100
};


const int led1 = 10;
const int led2 = 11;
const int led3 = 12;

//time variables
unsigned long startTime;
unsigned long elapsedTime;

//set states
bool led1State = false;
bool led2State = false;
bool led3State = false;

bool lastButton1State = LOW;
bool lastButton2State = LOW;
bool lastButton3State = LOW;

bool button1Pressed = false;
bool button2Pressed = false;
bool button3Pressed = false;

bool buzzerState = false;

bool inSetup = true;
int intArray[2];

void setup() {
  lcd.init();
  lcd.backlight();
  displayWaitingScreen();
  Serial.begin(9600);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(buzz, OUTPUT);
  handleTimeSetup();
  inSetup = false;
}

void loop() {
  key = customKeypad.getKey();

  if (key) {
    handleKeyPress(key);
  }

  unsigned long currentMillis = millis();

  if (currentMillis - lastCheck >= 1000) { //60000) {
    lastCheck = currentMillis;
    updateTime();
    updateDisplay();
    checkButtonState();
    updateAlarms();
  }
}

void handleKeyPress(char key) {
  if (key == 'D') {
    changeTime("Current time?");
    hours = intArray[0];
    minutes = intArray[1];
  } else if (key == 'A') {
    changeTime("Time for Pill A?");
    At = (intArray[0] * 60) + intArray[1];
  } else if (key == 'B') {
    changeTime("Time for Pill B?");
    Bt = (intArray[0] * 60) + intArray[1];
  } else if (key == 'C') {
    changeTime("Time for Pill C?");
    Ct = (intArray[0] * 60) + intArray[1];
  }
}

void handleTimeSetup() {
  while (true) {
    key = customKeypad.getKey();
    if (key == 'D') {
      changeTime("Current time?");
      hours = intArray[0];
      minutes = intArray[1];
      changeTime("Time for Pill A?");
      At = (intArray[0] * 60) + intArray[1];
      changeTime("Time for Pill B?");
      Bt = (intArray[0] * 60) + intArray[1];
      changeTime("Time for Pill C?");
      Ct = (intArray[0] * 60) + intArray[1];
      break;
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Invalid!");
      delay(1000);
      displayWaitingScreen();
    }
  }
}

void changeTime(char* str) {
  inputBuffer = "";
  setSetupMessage(str);

  while (true) {
    key = customKeypad.getKey();
    if (key) {
      if (key == '#') {
        if (inputBuffer.length() > 1) {  // Check if removal possible
          lcd.setCursor(5 + inputBuffer.length() - 1, 1);
          lcd.print(' ');
          inputBuffer.remove(inputBuffer.length() - 1, 1);
        }
      } else if (key == '*') {
        if (inSetup) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Finish setup!");
          delay(1000);
          setSetupMessage(str);
          lcd.print(inputBuffer);
        } else {
          break;
        }
      } else if (isDigit(key)) {
        inputBuffer += key;
        lcd.setCursor(5 + inputBuffer.length() - 1, 1);
        lcd.print(key);
        if (inputBuffer.length() == 4) {
          // Process current time input
          tempHours = (inputBuffer.substring(0, 2)).toInt();
          tempMinutes = (inputBuffer.substring(2, 4)).toInt();
          // Validate time
          if (tempHours < 24 && tempMinutes < 60) {  // Fixed variable names
            delay(1000);
            intArray[0] = tempHours;
            intArray[1] = tempMinutes;
          } else {
            invalidTimeDisplay();
          }
        }
      }
    }
  }
}

void invalidTimeDisplay() {
  inputBuffer = "";
  lcd.setCursor(0, 1);
  lcd.print("Invalid!");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("HHMM:            ");
}

void setSetupMessage(char *message) {
  lcd.clear();
  lcd.print(message);
  lcd.setCursor(0, 1);
  lcd.print("HHMM:");
}

void resetButton() {
  // Check if Button 1 is pressed (it will turn off LED 1)
  if (digitalRead(button1) == LOW) {
    led1State = false; // Turn off LED 1
    buzzerState = false;
  }

  // Check if Button 2 is pressed (it will turn off LED 2)
  if (digitalRead(button2) == LOW) {
    led2State = false; // Turn off LED 2
    buzzerState = false;
  }

  // Check if Button 3 is pressed (it will turn off LED 2)
  if (digitalRead(button3) == LOW) {
    led3State = false; // Turn off LED 3
    buzzerState = false;
  }
}

void checkButtonState() {
  timeInMinutes = (hours * 60) + minutes;
  
    // Turn on LED 1 if it's time (6 hours) and Button 1 is not pressed
  if (timeInMinutes == At) {
    Serial.println("Entered LED 1");
    led1State = true; // Turn on LED 1
    buzzerState = true;
  }

  // Turn on LED 2 if it's time (8 hours) and Button 2 is not pressed
  if (timeInMinutes == Bt) {
    Serial.println("Entered LED 2");
    led2State = true; // Turn on LED 2
    buzzerState = true;
  }

  // Turn on LED 3 if it's time (10 hours)
  if (timeInMinutes == Ct) {
    Serial.println("Entered LED 3");
    led3State = true; // Turn on LED 3
    buzzerState = true;
  }

  if (buzzerState) {
    for (int i = 0; i < sizeof(melody) / sizeof(int); i++) {
      updateAlarms();
      int duration = noteDurations[i];  
      tone(buzz, melody[i], duration);
      delay(duration * 1.1);
      resetButton();
    }
  }
}

void displayWaitingScreen() {
  lcd.clear();
  lcd.print("Press D to start");
  lcd.setCursor(0, 1);
  lcd.print("time setup");
}

void updateAlarms() {
  digitalWrite(led1, led1State ? HIGH : LOW); // If led1State is true, turn on LED 1
  digitalWrite(led2, led2State ? HIGH : LOW); // If led2State is true, turn on LED 2
  digitalWrite(led3, led3State ? HIGH : LOW); // If led3State is true, turn on LED 3
  digitalWrite(buzz, buzzerState ? HIGH : LOW);
}

void updateTime() {
  minutes++;
  if (minutes == 60) {
    minutes = 0;
    hours++;
  }
  if (hours == 24) {
    hours = 0;
    day++;
  }

  if (month == 2) {
    if (day == 28 && year % 4 == 0) {
    
    }
  }

  if (month == 12) {
    month = 1;
    year++;
  }
}

void updateDisplay() {
  lcd.clear();
  snprintf(timeStr, sizeof(timeStr), "%02u/%02u/%04lu %02u:%02u", month, day, year, hours, minutes);
  lcd.setCursor(0, 0);
  lcd.print(timeStr);
}
