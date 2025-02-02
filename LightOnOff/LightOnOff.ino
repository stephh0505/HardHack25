

//variables to ports
const int button1 = A0;
const int button2 = A1;
const int button3 = A2;

const int led1 = 10;
const int led2 = 11;
const int led3 = 12;

const int buzz = A6; 

// Set target times in seconds 
long timeA = At
long timeB = Bt
long timeC = Ct


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

//set output and input stuff
void setup() {

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(buzz, OUTPUT);

 startTime = millis();
}


void loop() {
  


  // Check if Button 1 is pressed (it will turn off LED 1)
  if (digitalRead(button1) == LOW) {
    led1State = false; // Turn off LED 1
  }

  // Check if Button 2 is pressed (it will turn off LED 2)
  if (digitalRead(button2) == LOW) {
    led2State = false; // Turn off LED 2
  }

// Check if Button 3 is pressed (it will turn off LED 2)
  if (digitalRead(button3) == LOW) {
    led3State = false; // Turn off LED 3
  }


  // Turn on LED 1 if it's time (6 hours) and Button 1 is not pressed
  if (elapsedTimeInSeconds >= timeA && elapsedTimeSecs < timeA + 60 && !led1State) {
    led1State = true; // Turn on LED 1
  }

  // Turn on LED 2 if it's time (8 hours) and Button 2 is not pressed
  if (elapsedTimeInSeconds >= timeB && elapsedTimeSecs < timeB + 60 && !led2State) {
    led2State = true; // Turn on LED 2
  }

  // Turn on LED 3 if it's time (10 hours)
  if (elapsedTimeInSeconds >= timeC && elapsedTimeSecs < timeC + 60 && !led3State) {
    led3State = true; // Turn on LED 3
  }


   // Update the LEDs based on their states
  digitalWrite(led1, led1State ? HIGH : LOW); // If led1State is true, turn on LED 1
  digitalWrite(led2, led2State ? HIGH : LOW); // If led2State is true, turn on LED 2
  digitalWrite(led3, led3State ? HIGH : LOW); // If led3State is true, turn on LED 3
  digitalWrite(buzz, led4State ? HIGH : LOW); 
 

  // Wait for a little bit before checking again
  delay(1000); // Delay for 1 second
}







