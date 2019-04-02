#define BTN1 13
#define BTN2 12
#define BTN3 11
#define BUZZER 6
#define LED 7

bool firstRun;
bool passed;
bool turn;   
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




}





void loop() {
  // put your main code here, to run repeatedly:

if(firstRun){
Serial.println("Welcome");
}

testLed();
if (passed){
  testBuzzer();
  }
/*  else {failure();}
  if (passed){
    victory();
    }
    else {failure();}
*/

}

void intro(){
 firstRun = false;
  Serial.println("Press Button 1 to start the countdown");
  while(digitalRead (BTN1) == HIGH);
  for( int i = 5; i>0; i--)
  {
  Serial.println(String(i));
  delay(1000);
  
  }
  Serial.println("Get ready!");
}

void testLed(){
intro();
delay(random(300,3001));
int i1 = millis();
digitalWrite(LED, HIGH);
while(digitalRead (BTN2) == HIGH);
int i2 = millis();
digitalWrite(LED, LOW);
Serial.println(String(i2-i1)+" ms Passed.");
passed = (i2-i1 < 600);
}

void testBuzzer(){
intro();
delay(random(300,3001));
int i1 = millis();
tone(BUZZER,1000);
int j;
while(digitalRead (BTN3) == HIGH)
{
  if ((j=millis()) >= i1+2000)
  {noTone(BUZZER);}
}
int i2 = millis();
noTone(BUZZER);
Serial.println(String(i2-i1)+" ms Passed.");
passed = (i2-i1 < 600);
}
  
