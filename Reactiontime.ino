const int ledPins[3] = {8, 9, 10};  // LEDs
const int buzzer = 6;               // Buzzer
const int buttonPin = 7;            // Button

unsigned long ledOnTime;
unsigned long reactionTime;
unsigned long fastestTime = 100000;
int activeLED;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  for(int i = 0; i < 3; i++){
    pinMode(ledPins[i], OUTPUT);
  }

  randomSeed(analogRead(A0));
  Serial.println("Reaction Timer Ready");
}

void loop() {

  // Countdown animation
  for(int i = 0; i < 3; i++){
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }

  int waitTime = random(2000,5000);
  unsigned long startWait = millis();

  // Detect false start
  while(millis() - startWait < waitTime){
    if(digitalRead(buttonPin) == LOW){
      Serial.println("False Start!");
      tone(buzzer, 200, 500);
      delay(2000);
      return;  // restart loop
    }
  }

  // Light a random LED
  activeLED = random(0,3);
  digitalWrite(ledPins[activeLED], HIGH);
  tone(buzzer, 1000, 200);
  ledOnTime = millis();

  // Wait for button press
  while(digitalRead(buttonPin) == HIGH){
  }

  reactionTime = millis() - ledOnTime;

  // Update fastest reaction
  if(reactionTime < fastestTime){
    fastestTime = reactionTime;
  }

  // Print times
  Serial.print("Reaction time: ");
  Serial.print(reactionTime);
  Serial.println(" ms");

  Serial.print("Fastest time: ");
  Serial.print(fastestTime);
  Serial.println(" ms");
  Serial.println();

  // LED-based reaction feedback
  // LED1 = slow (>350ms), LED2 = average (250-350ms), LED3 = fast (<250ms)
  for(int i = 0; i < 3; i++){ digitalWrite(ledPins[i], LOW); } // clear all
  if(reactionTime < 250){
    digitalWrite(ledPins[2], HIGH);  // fast
  } else if(reactionTime < 350){
    digitalWrite(ledPins[1], HIGH);  // average
  } else {
    digitalWrite(ledPins[0], HIGH);  // slow
  }

  delay(1500);  // show LED feedback

  // Turn off all LEDs for next round
  for(int i = 0; i < 3; i++){ digitalWrite(ledPins[i], LOW); }

  delay(1000); // brief pause before next round
}