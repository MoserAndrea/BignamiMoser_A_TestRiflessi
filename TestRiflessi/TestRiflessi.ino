
#include <LiquidCrystal.h>
#define BTN1 13
#define BTN2 12
#define BTN3 11
#define BUZZER 6
#define LED 7
#define RED 2
#define GREEN 1
bool firstRun;
bool passed;
const int rs = 10, en = 9, d4 = 8, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

   void setup() {
  // put your setup code here, to run once:
firstRun = true;
passed = true;
randomSeed(analogRead(0));
Serial.begin(9600);

pinMode(BTN1, INPUT_PULLUP);
pinMode(BTN2, INPUT_PULLUP);
pinMode(BTN3, INPUT_PULLUP);
pinMode(LED, LOW);
pinMode(BUZZER, OUTPUT);
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
 
lcd.begin(16, 2);
}


void loop() {
  // put your main code here, to run repeatedly:

if(firstRun){
welcome();
}

testLed();
if (passed){
  testBuzzer();
  }
else {failure();}
if (passed){
  victory();
  }
else {failure();}
}

void intro(){
 firstRun = false;
 lcd.setCursor(0,0);
  lcd.print("Press Button1 to");
 lcd.setCursor(0,1);
  lcd.print("start countdown!");
  while(digitalRead (BTN1) == HIGH);
  lcd.clear();
  for(int i = 5; i>0; i--)
  {
    lcd.setCursor(7,0);
    lcd.print(String(i));
    delay(1000);
  }
  lcd.setCursor(3,1);
  lcd.print("Get ready!");
}

void testLed(){
intro();
delay(random(300,3001));
int i1 = millis();
digitalWrite(LED, HIGH);
while(digitalRead (BTN2) == HIGH);
int i2 = millis();
digitalWrite(LED, LOW);

lcd.clear();
lcd.setCursor(1,0);
lcd.print(String(i2-i1)+" ms passed.");
passed = (i2-i1 < 300);
}

void testBuzzer(){
intro();
delay(random(300,3001));
int i1 = millis();
tone(BUZZER,8000);
int j;
while(digitalRead (BTN3) == HIGH)
{
  if ((j=millis()) >= i1+6000)
  {noTone(BUZZER);}
}
int i2 = millis();
noTone(BUZZER);

lcd.clear();
lcd.setCursor(1,0);
lcd.print(String(i2-i1)+" ms passed.");
passed = (i2-i1 < 300);
}

void victory(){
  analogWrite(GREEN, 255);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("You passed");
  lcd.setCursor(0,1);
  lcd.print("the challenge!");
  delay(1000);
  lcd.clear();
  lcd.print("Press Button 1");
  lcd.setCursor(0,1);
  lcd.print("to retry!");
  while(digitalRead (BTN1) == HIGH);
  while(digitalRead (BTN1) == LOW);
}
void failure(){
  analogWrite(RED, 255);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("You failed");
  lcd.setCursor(0,1);
  lcd.print("the challenge!");
  delay(1000);
  lcd.clear();
  lcd.print("Press Button 1");
  lcd.setCursor(0,1);
  lcd.print("to retry!");
  while(digitalRead (BTN1) == HIGH);
  while(digitalRead (BTN1) == LOW);
}

void welcome(){
  lcd.setCursor(4,0);
  lcd.print("Welcome!");

  lcd.setCursor(-12,1);
  lcd.print("Button 2: Led-test");
  lcd.print("Button 3: Buzzer-test");

  while(digitalRead(BTN1) == HIGH)
  {
    lcd.scrollDisplayRight();
  }
  lcd.clear();
  /*Serial.println("");
  Serial.println("");*/
}
