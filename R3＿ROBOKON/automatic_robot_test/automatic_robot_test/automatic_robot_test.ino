#include <DueTimer.h>

#define FLCW 29 //front left pin//
#define FLPWM 5
#define FLCCW 27

#define FRCW 28 //fhront right pin//
#define FRPWM 6
#define FRCCW 26

#define RLCW 25 //rear left pin//
#define RLPWM 4
#define RLCCW 23

#define RRCW 22 //rear right pin//
#define RRPWM 3
#define RRCCW 24

#define MHCW 33 //high rope pin//
#define MHPWM 7
#define MHCCW 31

//#define FLEP 35 //front left encoder pin//
//#define FREP 46 //front right encoder pin//
//#define RLEP 44 //rear left encoder pin//
//#define RREP 42 //rear right encoder pin//
#define MHEP 38 //high moter encoder pin//

#define XEP_A 36 //X ground encoder Apin//
#define XEP_B 34 //X ground encoder Bpin//
#define YEP_A 40 //Y ground encoder Apin//
#define YEP_B 32 //Y ground encoder Bpin//

#define BUTTON_START 51 //start button pin//
#define BUTTON_STOP 47 //stop button pin//
#define BUTTON_RESET 43 //reset button pin//
#define BUTTON_UP 37
#define BUTTON_DOWN 49
#define BUTTON_SWITCH 45

#define LIMIT_UP 41 //limit switch up//
#define LIMIT_DOWN 39 //limit switch down//

#define EMER_IN 40 //emer switch pin//

#define RAND 10

#define MAX_PWM 180 //maximum pwm value//
#define MAX_PWM_MH 70

volatile int FL;
volatile int FR;
volatile int RL;
volatile int RR;
volatile int MH;
volatile int FLB;
volatile int FRB;
volatile int RLB;
volatile int RRB;
volatile int MHB;

volatile int TALL;
volatile int RAD;
volatile int X45;
volatile int Y45;
volatile int X135;
volatile int Y135;
volatile int POW45;
volatile int POW135;

volatile int FLD = 0;
volatile int FRD = 0;
volatile int RLD = 0;
volatile int RRD = 0;
volatile int MHD = 0;

volatile int FLE = 0;
volatile int FRE = 0;
volatile int RLE = 0;
volatile int RRE = 0;
volatile int XE_A = 0;
volatile int XE_B = 0;
volatile int YE_A = 0;
volatile int YE_B = 0;
volatile int MHE = 0;

volatile int FLEB = 0;
volatile int FREB = 0;
volatile int RLEB = 0;
volatile int RREB = 0;
volatile int MHEB = 0;

volatile int FRF = 0;
volatile int RLF = 0;
volatile int RRF = 0;

volatile int MOVIMNG_NOW = 0;
volatile int ROTATION = 0;
volatile byte inChar = 0;
volatile int STOP_CLICK_COUNTER = 0;

volatile int COUNTER = 0;
volatile int FLAG = 0;
volatile int tenms = 0;

void FLEC() {//tire encoder CHANGEing//
  FLE++;
  //  Serial.print(F("FLE:"));
  //  Serial.print(FLE);
}
void FREC() {
  FRE++;
  //  Serial.print(F("FRE:"));
  //  Serial.print(FRE);
}
void RLEC() {
  RLE++;
  //  Serial.print(F("RLE:"));
  //  Serial.print(RLE);
}
void RREC() {
  RRE++;
  //  Serial.print(F("RRE:"));
  //  Serial.print(RRE);
}
void XEC_A() {//ground encoder CHANGEing//
  //  Serial.print(F("XE_A:"));
  //  Serial.print(XE_A);
  XE_A++;
}
void XEC_B() {//ground encoder CHANGEing//
  //  Serial.print(F("XE_B:"));
  //  Serial.print(XE_B);
  XE_B++;
}
void YEC_A() {
  //  Serial.print(F("YE_A:"));
  //  Serial.print(YE_A);
  YE_A++;
}
void YEC_B() {
  //  Serial.print(F("YE_B:"));
  //  Serial.print(YE_B);
  YE_B++;
}
void  MHEC() {//rack encoder CHANGEing//
  MHE++;
  //    Serial.print(F("MHE:"));
  //    Serial.print(MHE);
}

void STOP_WARIKOMI();
void CLICK_START();
void CLICK_STOP();
void CLICK_RESET();
void CLICK_SWITCH();
void CLICK_BUTTON_UP();
void CLICK_BUTTON_DOWN();
void CLICK_LIMIT_UP();
void CLICK_LIMIT_DOWN();

void START_WARIKOMI() {
  Timer2.stop();
  attachInterrupt(BUTTON_UP, CLICK_BUTTON_UP, RISING);
  attachInterrupt(BUTTON_DOWN, CLICK_BUTTON_DOWN, RISING);
  attachInterrupt(LIMIT_UP, CLICK_LIMIT_UP, RISING);
  attachInterrupt(LIMIT_DOWN, CLICK_LIMIT_DOWN, RISING);
  attachInterrupt(BUTTON_START, CLICK_START, RISING);
  attachInterrupt(BUTTON_STOP, CLICK_STOP, RISING);
  attachInterrupt(BUTTON_RESET, CLICK_RESET, RISING);
  attachInterrupt(BUTTON_SWITCH, CLICK_SWITCH, RISING);
  Serial.print(F("\nato\n"));
}

void CLICK_START() {//start button rising//

  detachInterrupt(BUTTON_UP);
  detachInterrupt(BUTTON_DOWN);
  detachInterrupt(LIMIT_UP);
  detachInterrupt(LIMIT_DOWN);
  detachInterrupt(BUTTON_START);
  detachInterrupt(BUTTON_STOP);
  detachInterrupt(BUTTON_RESET);
  detachInterrupt(BUTTON_SWITCH);
  Serial.print(F("1\n"));
  Timer2.start();
}
void CLICK_STOP() {//stop button rising//

  detachInterrupt(BUTTON_UP);
  detachInterrupt(BUTTON_DOWN);
  detachInterrupt(LIMIT_UP);
  detachInterrupt(LIMIT_DOWN);
  detachInterrupt(BUTTON_START);
  detachInterrupt(BUTTON_STOP);
  detachInterrupt(BUTTON_RESET);
  detachInterrupt(BUTTON_SWITCH);
  Serial.print(F("2\n"));
  Timer2.start();
}
void CLICK_RESET() {//reset button rising//

  detachInterrupt(BUTTON_UP);
  detachInterrupt(BUTTON_DOWN);
  detachInterrupt(LIMIT_UP);
  detachInterrupt(LIMIT_DOWN);
  detachInterrupt(BUTTON_START);
  detachInterrupt(BUTTON_STOP);
  detachInterrupt(BUTTON_RESET);
  detachInterrupt(BUTTON_SWITCH);
  Serial.print(F("3\n"));
  Timer2.start();
}
void CLICK_SWITCH() {// button rising//

  detachInterrupt(BUTTON_UP);
  detachInterrupt(BUTTON_DOWN);
  detachInterrupt(LIMIT_UP);
  detachInterrupt(LIMIT_DOWN);
  detachInterrupt(BUTTON_START);
  detachInterrupt(BUTTON_STOP);
  detachInterrupt(BUTTON_RESET);
  detachInterrupt(BUTTON_SWITCH);
  Serial.print(F("4\n"));
  Timer2.start();
}
void CLICK_BUTTON_UP() {// button rising//
  detachInterrupt(BUTTON_UP);
  detachInterrupt(BUTTON_DOWN);
  detachInterrupt(LIMIT_UP);
  detachInterrupt(LIMIT_DOWN);
  detachInterrupt(BUTTON_START);
  detachInterrupt(BUTTON_STOP);
  detachInterrupt(BUTTON_RESET);
  detachInterrupt(BUTTON_SWITCH);
  Serial.print(F("5\n"));
  Timer2.start();
}
void CLICK_BUTTON_DOWN() {// button rising//
  detachInterrupt(BUTTON_UP);
  detachInterrupt(BUTTON_DOWN);
  detachInterrupt(LIMIT_UP);
  detachInterrupt(LIMIT_DOWN);
  detachInterrupt(BUTTON_START);
  detachInterrupt(BUTTON_STOP);
  detachInterrupt(BUTTON_RESET);
  detachInterrupt(BUTTON_SWITCH);
  Serial.print(F("6\n"));
  Timer2.start();
}
void CLICK_LIMIT_UP() { //limit switch up clicked//

  detachInterrupt(BUTTON_UP);
  detachInterrupt(BUTTON_DOWN);
  detachInterrupt(LIMIT_UP);
  detachInterrupt(LIMIT_DOWN);
  detachInterrupt(BUTTON_START);
  detachInterrupt(BUTTON_STOP);
  detachInterrupt(BUTTON_RESET);
  detachInterrupt(BUTTON_SWITCH);
  Serial.print(F("7\n"));
  Timer2.start();
}
void CLICK_LIMIT_DOWN() { //limit switch down clicked//

  detachInterrupt(BUTTON_UP);
  detachInterrupt(BUTTON_DOWN);
  detachInterrupt(LIMIT_UP);
  detachInterrupt(LIMIT_DOWN);
  detachInterrupt(BUTTON_START);
  detachInterrupt(BUTTON_STOP);
  detachInterrupt(BUTTON_RESET);
  detachInterrupt(BUTTON_SWITCH);
  Serial.print(F("8\n"));
  Timer2.start();
}

void SERIAL_PRINT() { //タイマ割り込みで実行される関数、2秒ごと//
  Serial.print(F("FLE:"));//各エンコーダの値を出力//
  Serial.print(FLE);
  Serial.print(F("\nFRE:"));
  Serial.print(FRE);
  Serial.print(F("\nRLE:"));
  Serial.print(RLE);
  Serial.print(F("\nRRE:"));
  Serial.print(RRE);
  Serial.print(F("\nXE_A:"));
  Serial.print(XE_A);
  Serial.print(F("\nXE_B:"));
  Serial.print(XE_B);
  Serial.print(F("\nYE_A:"));
  Serial.print(YE_A);
  Serial.print(F("\nYE_B:"));
  Serial.print(YE_B);
  Serial.print(F("\nMHE:"));
  Serial.print(MHE);
  Serial.print(F("\n\n"));
  COUNTER ++;
}

void setup() {
  Serial.begin(2400);
  Serial3.begin(1200);

  pinMode(FLCW, OUTPUT);
  pinMode(FLCCW, OUTPUT);
  pinMode(FRCW, OUTPUT);
  pinMode(FRCCW, OUTPUT);
  pinMode(RLCW, OUTPUT);
  pinMode(RLCCW, OUTPUT);
  pinMode(RRCW, OUTPUT);
  pinMode(RRCCW, OUTPUT);
  pinMode(MHCW, OUTPUT);
  pinMode(MHCCW, OUTPUT);
  pinMode(RAND, INPUT);

  for (int routine = 0; routine < 20; routine++) {//ここから開幕ルーチン//

    digitalWrite(FLCCW, LOW);
    digitalWrite(FRCCW, LOW);
    digitalWrite(RLCCW, LOW);
    digitalWrite(RRCCW, LOW);
    digitalWrite(FLCW, HIGH);
    digitalWrite(FRCW, HIGH);
    digitalWrite(RLCW, HIGH);
    digitalWrite(RRCW, HIGH);
    digitalWrite(MHCW, HIGH);
    digitalWrite(MHCCW, LOW);
    delay(20);

    digitalWrite(FLCW, LOW);
    digitalWrite(FRCW, LOW);
    digitalWrite(RLCW, LOW);
    digitalWrite(RRCW, LOW);
    digitalWrite(MHCW, LOW);
    analogWrite(FLPWM, MAX_PWM);
    analogWrite(FRPWM, MAX_PWM);
    analogWrite(RLPWM, MAX_PWM);
    analogWrite(RRPWM, MAX_PWM);
    analogWrite(MHPWM, 255);
    delay(20);

    analogWrite(FLPWM, 0);
    analogWrite(FRPWM, 0);
    analogWrite(RLPWM, 0);
    analogWrite(RRPWM, 0);
    analogWrite(MHPWM, 0);
    digitalWrite(FLCCW, HIGH);
    digitalWrite(FRCCW, HIGH);
    digitalWrite(RLCCW, HIGH);
    digitalWrite(RRCCW, HIGH);
    digitalWrite(MHCCW, HIGH);
    delay(20);
  }

  digitalWrite(MHCCW, LOW);
  digitalWrite(RLCCW, LOW);
  digitalWrite(RRCCW, LOW);
  digitalWrite(FLCCW, LOW);
  digitalWrite(FRCCW, LOW);

  delay(20);//ここまで開幕ルーチン//

  digitalWrite(MHCW, HIGH); //最初に上昇機構を少し上昇//
  analogWrite(MHPWM, 150);
  delay(700);
  digitalWrite(MHCW, LOW);
  analogWrite(MHPWM, 0);

  //  pinMode(FLEP,INPUT_PULLUP);
  //  pinMode(FREP,INPUT_PULLUP);
  //  pinMode(RLEP,INPUT_PULLUP);
  //  pinMode(RREP,INPUT_PULLUP);

  //  attachInterrupt(FLEP, FLEC, CHANGE);
  //  attachInterrupt(FREP, FREC, CHANGE);
  //  attachInterrupt(RLEP, RLEC, CHANGE);
  //  attachInterrupt(RREP, RREC, CHANGE);
  attachInterrupt(XEP_A, XEC_A, CHANGE);
  attachInterrupt(XEP_B, XEC_B, CHANGE);
  attachInterrupt(YEP_A, YEC_A, CHANGE);
  attachInterrupt(YEP_B, YEC_B, CHANGE);
  attachInterrupt(MHEP, MHEC, CHANGE);
  attachInterrupt(BUTTON_START, CLICK_START, RISING);
  attachInterrupt(BUTTON_STOP, CLICK_STOP, RISING);
  attachInterrupt(BUTTON_RESET, CLICK_RESET, RISING);
  attachInterrupt(BUTTON_SWITCH, CLICK_SWITCH, RISING);
  attachInterrupt(BUTTON_UP, CLICK_BUTTON_UP, RISING);
  attachInterrupt(BUTTON_DOWN, CLICK_BUTTON_DOWN, RISING);
  attachInterrupt(LIMIT_UP, CLICK_LIMIT_UP, RISING);
  attachInterrupt(LIMIT_DOWN, CLICK_LIMIT_DOWN, RISING);


  //  Timer1.attachInterrupt(SERIAL_PRINT);
  //  Timer1.start(1000000);//1s//
  //  Timer1.start();

  Timer2.attachInterrupt(START_WARIKOMI);
  Timer2.start(1000000);//1000ms//
  Timer2.stop();
}

void loop() {
  if (COUNTER == 4 && FLAG == 0) { //2秒ごとに全てのモータを反転//
    digitalWrite(FLCW, HIGH);
    digitalWrite(FLCCW, LOW);
    analogWrite(FLPWM, 204);
    digitalWrite(FRCW, HIGH);
    digitalWrite(FRCCW, LOW);
    analogWrite(FRPWM, 204);
    digitalWrite(RLCW, HIGH);
    digitalWrite(RLCCW, LOW);
    analogWrite(RLPWM, 204);
    digitalWrite(RRCW, HIGH);
    digitalWrite(RRCCW, LOW);
    analogWrite(RRPWM, 204);
    digitalWrite(MHCW, HIGH);
    digitalWrite(MHCCW, LOW);
    analogWrite(MHPWM, 50);
    COUNTER = 0;
    FLAG = 1;
  } else if (COUNTER == 4 && FLAG == 1) {
    digitalWrite(FLCW, LOW);
    digitalWrite(FLCCW, HIGH);
    analogWrite(FLPWM, 100);
    digitalWrite(FRCW, LOW);
    digitalWrite(FRCCW, HIGH);
    analogWrite(FRPWM, 100);
    digitalWrite(RLCW, LOW);
    digitalWrite(RLCCW, HIGH);
    analogWrite(RLPWM, 100);
    digitalWrite(RRCW, LOW);
    digitalWrite(RRCCW, HIGH);
    analogWrite(RRPWM, 100);
    digitalWrite(MHCW, LOW);
    digitalWrite(MHCCW, HIGH);
    analogWrite(MHPWM, 50);
    COUNTER = 0;
    FLAG = 0;
  }
}
