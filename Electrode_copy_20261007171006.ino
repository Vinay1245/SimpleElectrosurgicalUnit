const int buttonPin1 = 4;
const int buttonPin2 = 3;
const int buttonPin3 = 2;
const int ledGreen = 5;
const int buzzer = 6;

int sevenSegmentA = 12;
int sevenSegmentB = 13;
int sevenSegmentC = 11;
int sevenSegmentD = 10;
int sevenSegmentE = 9;
int sevenSegmentF = 8;
int sevenSegmentG = 7;

int lastButtonState1 = HIGH;
int lastButtonState2 = HIGH;
int lastButtonState3 = HIGH;

int buttonState1;
int buttonState2;
int buttonState3;


enum Mode{
  STANDBY,
  CUT,
  FULGURATION,
  BLEND
};


Mode current_mode = STANDBY;

void setup(){
  pinMode(sevenSegmentA, OUTPUT);
  pinMode(sevenSegmentB, OUTPUT);
  pinMode(sevenSegmentC, OUTPUT);
  pinMode(sevenSegmentD, OUTPUT);
  pinMode(sevenSegmentE, OUTPUT);
  pinMode(sevenSegmentF, OUTPUT);
  pinMode(sevenSegmentG, OUTPUT);

  pinMode(ledGreen, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);

  Serial.begin(9600);

  displayMode();
}


void loop(){
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);


  //Button 1 standby and treat
  if (buttonState1 == LOW && lastButtonState1 == HIGH){
    if (current_mode == STANDBY){
      current_mode = CUT;
    }
    else{
      current_mode = STANDBY;

      noTone(buzzer);
    }
    displayMode();
    delay(50);
  }

  //button 2 cycle
  if (buttonState2 == LOW && lastButtonState2 == HIGH){
    if (current_mode != STANDBY){
      if (current_mode == CUT){
        current_mode = FULGURATION;
      }
      else if (current_mode == FULGURATION){
        current_mode = BLEND;
      }
      else if (current_mode == BLEND){
        current_mode = CUT;
      }
      else{
        current_mode = STANDBY;
      }

      displayMode();
    }
    delay(50);
  }

  //button 3 buzzer!
  if (buttonState3 == LOW){
    if (current_mode == CUT){
      tone(buzzer, 523);
    }
    else if (current_mode == FULGURATION){
      tone(buzzer, 587);
    }
    else if (current_mode == BLEND){
      tone(buzzer, 659);
    }
    else if (current_mode == STANDBY){
      noTone(buzzer);
      digitalWrite(ledGreen, LOW);
    }
    else{
      noTone(buzzer);
    }
  }

  else{
    noTone(buzzer);
  }

  //shine led on use
  if (current_mode == STANDBY){
    digitalWrite(ledGreen, LOW);
  }
  else{
    digitalWrite(ledGreen, HIGH);
  }

  //button state thingy
  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;
  lastButtonState3 = buttonState3;
}

void displayMode(){
  //s
  if (current_mode == STANDBY){
    sevenSegment(1, 0, 1, 1, 0, 1, 1);
    digitalWrite(ledGreen, LOW);
  }
  //c
  else if (current_mode == CUT){
    sevenSegment(1, 0, 0, 1, 1, 1, 0);
    digitalWrite(ledGreen, HIGH);
  }
  //f
  else if (current_mode == FULGURATION){
    sevenSegment(1, 0, 0, 0, 1, 1, 1);
    digitalWrite(ledGreen, HIGH);
  }
  // b
  else if (current_mode == BLEND){
    sevenSegment(0, 0, 1, 1, 1, 1, 1);
    digitalWrite(ledGreen, HIGH);
  }
  // error
  else{
    sevenSegment(1, 0, 0, 1, 1, 1, 1);
    digitalWrite(ledGreen, LOW);
    noTone(buzzer);
  }
}


void sevenSegment(bool Astate, bool Bstate, bool Cstate, bool Dstate, bool Estate, bool Fstate, bool Gstate){
  digitalWrite(sevenSegmentA, Astate);
  digitalWrite(sevenSegmentB, Bstate);
  digitalWrite(sevenSegmentC, Cstate);
  digitalWrite(sevenSegmentD, Dstate);
  digitalWrite(sevenSegmentE, Estate);
  digitalWrite(sevenSegmentF, Fstate);
  digitalWrite(sevenSegmentG, Gstate);
}
