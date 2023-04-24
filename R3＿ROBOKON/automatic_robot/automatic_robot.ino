#include <DueTimer.h>

#define FLCW 29 //front left pin//
#define FLPWM 5
#define FLCCW 27

#define FRCW 28 //front right pin//
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

#define FLEP 35 //front left encoder pin//
#define FREP 46 //front right encoder pin//
#define RLEP 44 //rear left encoder pin//
#define RREP 42 //rear right encoder pin//
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


volatile int FL = 0;
volatile int FR = 0;
volatile int RL = 0;
volatile int RR = 0;
volatile int MH = 0;

volatile double TALL = 0;
volatile double RAD = 0;
volatile double X45 = 0;
volatile double Y45 = 0;
volatile double X135 = 0;
volatile double Y135 = 0;
volatile double POW45 = 0;
volatile double POW135 = 0;

volatile double RESET_RAD = 0;
volatile double TAN = 0;

volatile int FLD = 0;
volatile int FRD = 0;
volatile int RLD = 0;
volatile int RRD = 0;
volatile int MHD = 0;

volatile int FLE = 0;
volatile int FRE = 0;
volatile int RLE = 0;
volatile int RRE = 0;
volatile int XE = 0;
volatile int YE = 0;
volatile int MHE = 0;

volatile int MOVING_NOW = 0;
volatile double ROTATION = 0;
volatile byte inChar = 0;
volatile int STOP_CLICK_COUNTER = 0;

volatile int LIMIT_UP_FLAG = 0;
volatile int LIMIT_DOWN_FLAG = 0;

volatile int BUTTON_UP_FLAG = 0;
volatile int BUTTON_DOWN_FLAG = 0;

volatile int tenms = 0;
volatile int THREESEC = 0;

long sum = 0;
long val1 = 0, val2 = 0, val3 = 0;

void FLEC() {//tire encoder CHANGEing//
  FLE++;
}

void FREC() {
  FRE++;
}

void RLEC() {
  RLE++;
}

void RREC() {
  RRE++;
}

void XEC_A() {//ground encoder CHANGEing//
  XE += digitalRead(XEP_A) == digitalRead(XEP_B) ? -1 : 1;
}

void XEC_B() {//ground encoder CHANGEing//
  XE += digitalRead(XEP_A) == digitalRead(XEP_B) ? 1 : -1;
}

void YEC_A() {
  YE += digitalRead(YEP_A) == digitalRead(YEP_B) ? -1 : 1;
}

void YEC_B() {
  YE += digitalRead(YEP_A) == digitalRead(YEP_B) ? 1 : -1;
}

void  MHEC() {//rack encoder CHANGEing//
  MHE++;
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
  Timer3.stop();
  attachInterrupt(BUTTON_START, CLICK_START, RISING);
  attachInterrupt(BUTTON_STOP, CLICK_STOP, RISING);
  attachInterrupt(BUTTON_RESET, CLICK_RESET, RISING);
  attachInterrupt(BUTTON_SWITCH, CLICK_SWITCH, HIGH);
  attachInterrupt(BUTTON_UP, CLICK_BUTTON_UP, HIGH);
  attachInterrupt(BUTTON_DOWN, CLICK_BUTTON_DOWN, HIGH);
  attachInterrupt(LIMIT_UP, CLICK_LIMIT_UP, RISING);
  attachInterrupt(LIMIT_DOWN, CLICK_LIMIT_DOWN, RISING);
}

void CLICK_START() {//start button rising//
  Serial.print(F("2\n"));
  if (THREESEC == 0) {
    THREESEC = 1;
    noInterrupts();
    Serial.print(F("3\n"));
    interrupts();
    detachInterrupt(BUTTON_UP);
    detachInterrupt(BUTTON_DOWN);
    detachInterrupt(LIMIT_UP);
    detachInterrupt(LIMIT_DOWN);
    detachInterrupt(BUTTON_START);
    detachInterrupt(BUTTON_STOP);
    detachInterrupt(BUTTON_RESET);
    detachInterrupt(BUTTON_SWITCH);
    Timer1.start();
    Timer2.start();
    Timer3.start();
    Timer4.start();
    STOP_CLICK_COUNTER = 0;
  }
}

void CLICK_STOP() {//stop button rising//
  if (THREESEC == 0) {
    THREESEC = 1;
    noInterrupts();
    interrupts();
    detachInterrupt(BUTTON_UP);
    detachInterrupt(BUTTON_DOWN);
    detachInterrupt(LIMIT_UP);
    detachInterrupt(LIMIT_DOWN);
    detachInterrupt(BUTTON_START);
    detachInterrupt(BUTTON_STOP);
    detachInterrupt(BUTTON_RESET);
    detachInterrupt(BUTTON_SWITCH);
    Timer3.start();
    Timer4.start();
    Timer1.stop();
    Timer2.stop();
    digitalWrite(FLCW, LOW);
    digitalWrite(FRCW, LOW);
    digitalWrite(RLCW, LOW);
    digitalWrite(RRCW, LOW);
    digitalWrite(MHCW, LOW);
    digitalWrite(FLCCW, LOW);
    digitalWrite(FRCCW, LOW);
    digitalWrite(RLCCW, LOW);
    digitalWrite(RRCCW, LOW);
    digitalWrite(MHCCW, LOW);
    analogWrite(FLPWM, 0);
    analogWrite(FRPWM, 0);
    analogWrite(RLPWM, 0);
    analogWrite(RRPWM, 0);
    analogWrite(MHPWM, 0);
    FL = 0;
    FR = 0;
    RL = 0;
    RR = 0;
    MOVING_NOW = 0;
    STOP_CLICK_COUNTER ++;
  }
}

void CLICK_RESET() {//start button rising//
  Serial.print(F("1\n"));
  if (THREESEC == 0) {
    THREESEC = 1;
    noInterrupts();
    Serial.print(F("1\n"));
    interrupts();
    detachInterrupt(BUTTON_UP);
    detachInterrupt(BUTTON_DOWN);
    detachInterrupt(LIMIT_UP);
    detachInterrupt(LIMIT_DOWN);
    detachInterrupt(BUTTON_START);
    detachInterrupt(BUTTON_STOP);
    detachInterrupt(BUTTON_RESET);
    detachInterrupt(BUTTON_SWITCH);
    Timer3.start();
    Timer4.start();
    while (XE > 10 || XE < -10 || YE > 10 || YE < -10) {

      RESET_RAD = -1.0 * (atan2(YE, XE) / 3.141592);

      X45 = 0.5 * sin(RESET_RAD) + 0.5 * cos(RESET_RAD);
      Y45 = X45;

      X135 = -0.5 * sin(RESET_RAD) + 0.5 * cos(RESET_RAD);
      Y135 = 0.5 * sin(RESET_RAD) - 0.5 * cos(RESET_RAD);

      POW45 = sqrt(X45 * X45 + Y45 * Y45) * MAX_PWM;
      POW135 = sqrt(X135 * X135 + Y135 * Y135) * MAX_PWM;

      FL = POW45;
      FR = POW135;
      RL = POW135;
      RR = POW45;

    }
    digitalWrite(FLCW, LOW);
    digitalWrite(FRCW, LOW);
    digitalWrite(RLCW, LOW);
    digitalWrite(RRCW, LOW);
    digitalWrite(MHCW, LOW);
    digitalWrite(FLCCW, LOW);
    digitalWrite(FRCCW, LOW);
    digitalWrite(RLCCW, LOW);
    digitalWrite(RRCCW, LOW);
    digitalWrite(MHCCW, LOW);
    analogWrite(FLPWM, 0);
    analogWrite(FRPWM, 0);
    analogWrite(RLPWM, 0);
    analogWrite(RRPWM, 0);
    analogWrite(MHPWM, 0);
    FL = 0;
    FR = 0;
    RL = 0;
    RR = 0;
  }
}

void CLICK_SWITCH() {//switch button high//
  if (MOVING_NOW == 0 && STOP_CLICK_COUNTER % 2 == 1) { //1 or kisuu,migi
    FL = 45;
    FR = 45;
    RL = 45;
    RR = 45;
    digitalWrite(FLCW, HIGH);
    digitalWrite(FLCCW, LOW);
    digitalWrite(FRCCW, HIGH);
    digitalWrite(FRCW, LOW);
    digitalWrite(RLCCW, HIGH);
    digitalWrite(RLCW, LOW);
    digitalWrite(RRCW, HIGH);
    digitalWrite(RRCCW, LOW);
    Serial.print(F("g\n"));
  } else if (MOVING_NOW == 0 && STOP_CLICK_COUNTER % 2 == 0) { //after 2 guusuu,ue
    FL = 45;
    FR = 45;
    RL = 45;
    RR = 45;
    digitalWrite(FLCW, HIGH);
    digitalWrite(FLCCW, LOW);
    digitalWrite(FRCW, HIGH);
    digitalWrite(FRCCW, LOW);
    digitalWrite(RLCW, HIGH);
    digitalWrite(RLCCW, LOW);
    digitalWrite(RRCW, HIGH);
    digitalWrite(RRCCW, LOW);
    Serial.print(F("h\n"));
  }
}

void CLICK_LIMIT_UP() {
  Serial.print(F("1\n"));
  if (THREESEC == 0) {
    THREESEC = 1;
    noInterrupts();
    Serial.print(F("1\n"));
    interrupts();
    detachInterrupt(BUTTON_UP);
    detachInterrupt(BUTTON_DOWN);
    detachInterrupt(LIMIT_UP);
    detachInterrupt(LIMIT_DOWN);
    detachInterrupt(BUTTON_START);
    detachInterrupt(BUTTON_STOP);
    detachInterrupt(BUTTON_RESET);
    detachInterrupt(BUTTON_SWITCH);
    Timer3.start();
    Timer4.start();
    LIMIT_UP_FLAG = 1;
    digitalWrite(MHCW, LOW);
    digitalWrite(MHCCW, LOW);
    analogWrite(MHPWM, 0);
  }
}

void CLICK_LIMIT_DOWN() {
  Serial.print(F("1\n"));
  if (THREESEC == 0) {
    THREESEC = 1;
    noInterrupts();
    Serial.print(F("1\n"));
    interrupts();
    detachInterrupt(BUTTON_UP);
    detachInterrupt(BUTTON_DOWN);
    detachInterrupt(LIMIT_UP);
    detachInterrupt(LIMIT_DOWN);
    detachInterrupt(BUTTON_START);
    detachInterrupt(BUTTON_STOP);
    detachInterrupt(BUTTON_RESET);
    detachInterrupt(BUTTON_SWITCH);
    Timer3.start();
    Timer4.start();
    LIMIT_DOWN_FLAG = 1;
    digitalWrite(MHCW, LOW);
    digitalWrite(MHCCW, LOW);
    analogWrite(MHPWM, 0);
  }
}

void MOTER_SETTINGS() {
  MOVING_NOW = 1;
  while (MOVING_NOW == 1) {
    if (XE > 500 && YE > 500) {//migiue ikisugi
      digitalWrite(FLCW, LOW);
      digitalWrite(FLCCW, HIGH);
      digitalWrite(RRCW, HIGH);
      digitalWrite(RRCCW, LOW);
      digitalWrite(FRCW, LOW);
      digitalWrite(FRCCW, LOW);
      digitalWrite(RLCW, LOW);
      digitalWrite(RLCCW, LOW);
      FL = 80;
      FR = 80;
      RL = 80;
      RR = 80;
    } else if (XE > 500 && YE < -500) {//hidariue ikisugi
      digitalWrite(FLCW, LOW);
      digitalWrite(FLCCW, LOW);
      digitalWrite(RRCW, LOW);
      digitalWrite(RRCCW, LOW);
      digitalWrite(FRCW, LOW);
      digitalWrite(FRCCW, HIGH);
      digitalWrite(RLCW, LOW);
      digitalWrite(RLCCW, HIGH);
      FL = 80;
      FR = 80;
      RL = 80;
      RR = 80;
    } else if (XE < -500 && YE < -500) {//hidarisita ikisugi
      digitalWrite(FLCW, HIGH);
      digitalWrite(FLCCW, LOW);
      digitalWrite(RRCW, HIGH);
      digitalWrite(RRCCW, LOW);
      digitalWrite(FRCW, LOW);
      digitalWrite(FRCCW, LOW);
      digitalWrite(RLCW, LOW);
      digitalWrite(RLCCW, LOW);
      FL = 80;
      FR = 80;
      RL = 80;
      RR = 80;
    } else if (XE > 500 && YE < -500) {//migisita ikisugi
      digitalWrite(FLCW, LOW);
      digitalWrite(FLCCW, LOW);
      digitalWrite(RRCW, LOW);
      digitalWrite(RRCCW, LOW);
      digitalWrite(FRCW, HIGH);
      digitalWrite(FRCCW, LOW);
      digitalWrite(RLCW, HIGH);
      digitalWrite(RLCCW, LOW);
      FL = 80;
      FR = 80;
      RL = 80;
      RR = 80;
    } else if (XE > 500 && YE < 500 && YE > -500) {//ue ikisugi
      digitalWrite(FLCW, LOW);
      digitalWrite(FLCCW, HIGH);
      digitalWrite(RRCW, LOW);
      digitalWrite(RRCCW, HIGH);
      digitalWrite(FRCW, LOW);
      digitalWrite(FRCCW, HIGH);
      digitalWrite(RLCW, LOW);
      digitalWrite(RLCCW, HIGH);
      FL = 80;
      FR = 80;
      RL = 80;
      RR = 80;
    } else if (YE < -500 && XE < 500 && XE > -500) {//hidari ikisugi
      digitalWrite(FLCW, HIGH);
      digitalWrite(FLCCW, LOW);
      digitalWrite(RRCW, HIGH);
      digitalWrite(RRCCW, LOW);
      digitalWrite(FRCW, LOW);
      digitalWrite(FRCCW, HIGH);
      digitalWrite(RLCW, LOW);
      digitalWrite(RLCCW, HIGH);
      FL = 80;
      FR = 80;
      RL = 80;
      RR = 80;
    } else if (XE < -500 && YE < 500 && YE > -500) {//sita ikisugi
      digitalWrite(FLCCW, LOW);
      digitalWrite(FLCW, HIGH);
      digitalWrite(RRCCW, LOW);
      digitalWrite(RRCW, HIGH);
      digitalWrite(FRCCW, LOW);
      digitalWrite(FRCW, HIGH);
      digitalWrite(RLCCW, LOW);
      digitalWrite(RLCW, HIGH);
      FL = 80;
      FR = 80;
      RL = 80;
      RR = 80;
    } else if (YE < -500 && XE < 500 && XE > -500) {//migi ikisugi
      digitalWrite(FLCCW, HIGH);
      digitalWrite(FLCW, LOW);
      digitalWrite(RRCCW, HIGH);
      digitalWrite(RRCW, LOW);
      digitalWrite(FRCCW, LOW);
      digitalWrite(FRCW, HIGH);
      digitalWrite(RLCCW, LOW);
      digitalWrite(RLCW, HIGH);
      FL = 80;
      FR = 80;
      RL = 80;
      RR = 80;
    } else {
      RAD = analogRead(RAND);
      TALL = RAD;
      X45 = 0.5 * sin(RAD) + 0.5 * cos(RAD);
      Y45 = X45;

      X135 = -0.5 * sin(RAD) + 0.5 * cos(RAD);
      Y135 = 0.5 * sin(RAD) - 0.5 * cos(RAD);

      POW45 = sqrt(X45 * X45 + Y45 * Y45) * MAX_PWM;
      POW135 = sqrt(X135 * X135 + Y135 * Y135) * MAX_PWM;
      FL = POW45;
      FR = POW135;
      RL = POW135;
      RR = POW45;
      Serial.println(F(";;"));
      Serial.println(FL);
      Serial.println(FR);
      Serial.println(RL);
      Serial.println(RR);
      if (Y45 > 0) { //+だったら//
        digitalWrite(FLCW, HIGH);
        digitalWrite(FLCCW, LOW);
        digitalWrite(RRCW, HIGH);
        digitalWrite(RRCCW, LOW);
      } else { //-だったら//
        digitalWrite(FLCW, LOW);
        digitalWrite(FLCCW, HIGH);
        digitalWrite(RRCW, LOW);
        digitalWrite(RRCCW, HIGH);
      }

      if (Y135 > 0) { //+だったら//
        digitalWrite(FRCW, HIGH);
        digitalWrite(FRCCW, LOW);
        digitalWrite(RLCW, HIGH);
        digitalWrite(RLCCW, LOW);

      } else { //-だったら//
        digitalWrite(FRCW, LOW);
        digitalWrite(FRCCW, HIGH);
        digitalWrite(RLCW, LOW);
        digitalWrite(RLCCW, HIGH);
      }
    }
    digitalWrite(FLCW, LOW);
    digitalWrite(FLCCW, LOW);
    digitalWrite(FRCW, LOW);
    digitalWrite(FRCCW, LOW);
    digitalWrite(RLCW, LOW);
    digitalWrite(RLCCW, LOW);
    digitalWrite(RRCW, LOW);
    digitalWrite(RRCCW, LOW);
    FL = 0;
    FR = 0;
    RL = 0;
    RR = 0;
  }
}

void DANCING() {
bailout:
  if (Serial1.available() > 0) {
    byte data_size = Serial1.available();    //受信したデータ数を取得（桁数取得のため）
    byte num[data_size];                    //桁数分の配列を設定
    //for文内で1文字ずつのASCIIコードを数値に変換
    for (byte i = 0 ; i < data_size ; i++)
    {
      char val = Serial1.read();             //受信データの読み込み 1byteぶん
      //char文字valが数字の場合はif文内処理、そうでない場合else内処理
      if (isdigit(val)) {
        num[i] = val - '0';                 //ASCII文字を数値に変換
        sum = sum * 10 + num[i];            //桁数を考慮して数値に変換

      } else {
        Serial.println("Please enter a number.");
        Serial.println("");                      //valが数字でない場合bailoutへ抜ける
        goto bailout;
      }

    }
    ROTATION = sum;
    sum = 0;

  }else{
    ROTATION = 0;
  }
  if (ROTATION > 1 && ROTATION <= 180) {
    if (FL < 0) {
      FL = 0;
    }
    if (FL > MAX_PWM) {
      FL = MAX_PWM;
    }
    if (FR < 0) {
      FR = 0;
    }
    if (FR > MAX_PWM) {
      FR = MAX_PWM;
    }
    if (RL < 0) {
      RL = 0;
    }
    if (RL > MAX_PWM) {
      RL = MAX_PWM;
    }
    if (RR < 0) {
      RR = 0;
    }
    if (RR > MAX_PWM) {
      RR = MAX_PWM;
    }
    analogWrite(FLPWM, FL - 5);
    analogWrite(RRPWM, RR + 5);
    analogWrite(FRPWM, FR + 5);
    analogWrite(RLPWM, RL - 5);
  } else if (ROTATION < 359 && ROTATION >= 180) {
    if (FL < 0) {
      FL = 0;
    }
    if (FL > MAX_PWM) {
      FL = MAX_PWM;
    }
    if (FR < 0) {
      FR = 0;
    }
    if (FR > MAX_PWM) {
      FR = MAX_PWM;
    }
    if (RL < 0) {
      RL = 0;
    }
    if (RL > MAX_PWM) {
      RL = MAX_PWM;
    }
    if (RR < 0) {
      RR = 0;
    }
    if (RR > MAX_PWM) {
      RR = MAX_PWM;
    }
    analogWrite(FLPWM, FL + 5);
    analogWrite(RRPWM, RR - 5);
    analogWrite(FRPWM, FR - 5);
    analogWrite(RLPWM, RL + 5);
  } else {
    if (FL < 0) {
      FL = 0;
    }
    if (FL > MAX_PWM) {
      FL = MAX_PWM;
    }
    if (FR < 0) {
      FR = 0;
    }
    if (FR > MAX_PWM) {
      FR = MAX_PWM;
    }
    if (RL < 0) {
      RL = 0;
    }
    if (RL > MAX_PWM) {
      RL = MAX_PWM;
    }
    if (RR < 0) {
      RR = 0;
    }
    if (RR > MAX_PWM) {
      RR = MAX_PWM;
    }
    analogWrite(FLPWM, FL);
    analogWrite(RRPWM, RR);
    analogWrite(FRPWM, FR);
    analogWrite(RLPWM, RL);
  }
}

void CLICK_BUTTON_UP() {
  FL = 0;
  FR = 0;
  RL = 0;
  RR = 0;
  while (digitalRead(BUTTON_DOWN) == HIGH) {
    digitalWrite(MHCCW, HIGH);
    digitalWrite(MHCW, LOW);
    analogWrite(MHPWM, 50);
  }
  digitalWrite(MHCCW, LOW);
  digitalWrite(MHCW, LOW);
  analogWrite(MHPWM, 0);
}

void CLICK_BUTTON_DOWN() {
  FL = 0;
  FR = 0;
  RL = 0;
  RR = 0;
  while (digitalRead(BUTTON_DOWN) == HIGH) {
    digitalWrite(MHCCW, LOW);
    digitalWrite(MHCW, HIGH);
    analogWrite(MHPWM, 50);
  }
  digitalWrite(MHCCW, LOW);
  digitalWrite(MHCW, LOW);
  analogWrite(MHPWM, 0);
}

void THREESECTIMER() {
  Timer4.stop();
  THREESEC = 0;
  Serial.print(F("owa"));
}

void setup() {
  Serial.begin(2400);
  Serial1.begin(115200);

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

  for (int routine = 0; routine < 20; routine++) {

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

  delay(20);

  pinMode(XEP_A, INPUT);
  pinMode(XEP_B, INPUT);
  pinMode(YEP_A, INPUT);
  pinMode(YEP_B, INPUT);
  pinMode(BUTTON_UP, INPUT);
  pinMode(BUTTON_DOWN, INPUT);

  Serial.print(F("\naa"));

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
  attachInterrupt(BUTTON_SWITCH, CLICK_SWITCH, HIGH);
  attachInterrupt(BUTTON_UP, CLICK_BUTTON_UP, HIGH);
  attachInterrupt(BUTTON_DOWN, CLICK_BUTTON_DOWN, HIGH);
  attachInterrupt(LIMIT_UP, CLICK_LIMIT_UP, RISING);
  attachInterrupt(LIMIT_DOWN, CLICK_LIMIT_DOWN, RISING);

  Timer1.attachInterrupt(MOTER_SETTINGS);
  Timer1.start(500000);//500ms//
  Timer1.stop();

  Timer2.attachInterrupt(DANCING);
  Timer2.start(100000);//100ms//
  Timer2.stop();

  Timer3.attachInterrupt(START_WARIKOMI);
  Timer3.start(10000);//10ms//
  Timer3.stop();

  Timer4.attachInterrupt(THREESECTIMER);
  Timer4.start(200000);//200ms//
  Timer4.stop();
  Serial.print(F("\nbb"));
}

void loop() {
  if (MHE > 900 && MHD == 0) {
    MHD = 1;
    MHE = 0;
    digitalWrite(MHCCW, HIGH);
    digitalWrite(MHCW, LOW);
    analogWrite(MHPWM, 204);
  } else if (MHE > 900 && MHD == 1) {
    MHD = 0;
    MHE = 0;
    digitalWrite(MHCCW, LOW);
    digitalWrite(MHCW, HIGH);
    analogWrite(MHPWM, 204);
  }
}
