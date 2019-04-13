
#include <LiquidCrystal.h>
#include <LiquidCrystal.h>
#define BTN1 7 //avvio
#define BTN2 5 //led
#define BTN3 3 //buzzer
#define BUZZER 4
#define LED 6
#define RED 1
#define GREEN 2
bool firstRun;
bool passed;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  // put your setup code here, to run once:
  firstRun = true;
  passed = true;
  randomSeed(analogRead(0));
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  lcd.begin(16, 2);
}


void loop() {
  // put your main code here, to run repeatedly:
  while ( digitalRead(BTN1) == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("Welcome!");
    lcd.setCursor(0,1);
    lcd.print("Press BtnRED");  
  }
  welcome();
  testLed();
  testBuzzer();
  
  if (passed) {
    victory();
  }
  else {
    failure();
  }
  
}

void intro() {
  firstRun = false;
  lcd.clear();
  while (digitalRead (BTN1) == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("Press BtnRED to");
    lcd.setCursor(0, 1);
    lcd.print("start countdown!");
  }
  lcd.clear();
  
  for (int i = 5; i > 0; i--)
  {
    lcd.setCursor(7, 0);
    lcd.print(String(i));
    delay(1000);
  }
  lcd.setCursor(3, 1);
  lcd.print("Get ready!");
}

void testLed() {
  intro();
  delay(random(300, 3001));
  int i1 = millis();
  digitalWrite(LED, HIGH);
  while (digitalRead (BTN2) == LOW){
    
  }
  int i2 = millis();
  digitalWrite(LED, LOW);

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(String(i2 - i1) + " ms passed.");
  passed = (i2 - i1 < 300);
  delay(2000);
}

void testBuzzer() {
  intro();
  delay(random(300, 3001));
  int i1 = millis();
  tone(BUZZER,1000);
  while (digitalRead (BTN2) == LOW){
    
  }
  int i2 = millis();
  noTone(BUZZER);

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(String(i2 - i1) + " ms passed.");
  passed = (i2 - i1 < 300);
  delay(2000);
}

void victory() {
  analogWrite(GREEN, 255);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You passed");
  lcd.setCursor(0, 1);
  lcd.print("the challenge!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press Btn_RED");
  lcd.setCursor(0, 1);
  lcd.print("to retry!");
  while (digitalRead (BTN1) == LOW);
  {
    
  }
  analogWrite(GREEN,0);
}
void failure() {
  analogWrite(RED, 255);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You failed");
  lcd.setCursor(0, 1);
  lcd.print("the challenge!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press Button 1");
  lcd.setCursor(0, 1);
  lcd.print("to retry!");
  while (digitalRead (BTN1) == LOW);
  {
    
  }
  analogWrite(RED,0);
}

void welcome() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Button Blue: Led-test");
  lcd.setCursor(0, 1);
  lcd.print("Button Blue: Buzzer-test");

  for (int posizione = 0; posizione <= 20; posizione++) {
    delay(300);
    lcd.scrollDisplayLeft();
  }
}
