const int input[] = { 3, 2 };
const int output[] = { 4, 5 };
int input1State = 0 ;
int input2State = 0 ;
byte R2_run = 0 ;
byte isControlRelay = 0 ;
int relay1State ;
int relay2State ;
int RedLED = 15 ;
int BlueLED = 13 ;
int GreenLED = 12 ;
//byte isControlRelay = 0 ;
elapsedMillis REL2_timeElapsed; //declare global if you don't want it reset every time loop runs
unsigned int REL2_interval = 5 ;


void Relay1(int state) {
  if (state == 1) {
    digitalWrite(output[0], LOW);
    relay1State = 1 ;
    digitalWrite(RedLED, HIGH);
  }
  if (state == 0) {
    digitalWrite(output[0], HIGH);
    relay1State = 0 ;
    digitalWrite(RedLED, LOW);
  }
}

void Relay2(int state, int seconds ) {
  int R2_push_interval = seconds ;
  if (relay2State != 1 and R2_run == 1) {
    REL2_timeElapsed = 0 ;
    //isControlRelay = 0 ;
    R2_run = 0 ;
  }
  
  if (state == 1 ) {
    if ( REL2_timeElapsed >= R2_push_interval*1000 ) {
      relay2State = 0 ;
      digitalWrite(output[1], HIGH);
      digitalWrite(BlueLED, LOW);
    } else {
      relay2State = 1 ;
      digitalWrite(output[1], LOW);
      digitalWrite(BlueLED, HIGH);
    }
  } else if (state == 0 ) {
    relay2State = 0 ;
    digitalWrite(output[1], HIGH);
    digitalWrite(BlueLED, LOW);
  }
}

void Relay2on() {
  //REL2_timeElapsed = 0 ;
  R2_run = 1 ;
  Relay2(1,REL2_interval);
}
void Relay2off() {
  Relay2(0,0);
}

void setup_IO() {
  for (int OutputPin = 0; OutputPin < 2; OutputPin++) {
    pinMode(output[OutputPin], OUTPUT);
  }
  for (int InputPin = 0; InputPin < 2; InputPin++) {
    pinMode(input[InputPin], INPUT_PULLUP);
  }
  pinMode(RedLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  Relay1(0);
  Relay2(0,0);
}

void read_IOs() {
  input1State = digitalRead(input[0]);
  input2State = digitalRead(input[1]);
  
  if (input2State == LOW ) {
    Relay2(1,REL2_interval);
  }

  if ( relay1State == 0 and relay2State == 0 ) {
    digitalWrite(GreenLED, HIGH);
  } else {
    digitalWrite(GreenLED, LOW);
  }
}
