#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
unsigned long startTime = 0;
const int ButtonReset = 13;
const int BuzzerPin = A0;
Servo myservo;
const int potPin = A1;

void sirena();
void urgenta(); 

void setup() {
  lcd.begin(16, 2);
  pinMode(ButtonReset, INPUT_PULLUP);
  myservo.attach(9);
  startTime = millis();
}

void loop() {
  //Reset timer
  if (digitalRead(ButtonReset) == LOW) {
    noTone(BuzzerPin);
    startTime = millis();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reset!");
    lcd.setCursor(0, 1);
    lcd.print("Resetting timer...");
    delay(2000);
    lcd.clear();
  }
  unsigned long elapsedTime = (millis() - startTime) / 1000;
//start ALARM
  if (elapsedTime > 10) {
    sirena();
    urgenta();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("URGENTA!!!");
    delay(1000);
  } else {//Display elapsed time
    lcd.setCursor(0, 0);
    lcd.print("Elapsed Time:   "); 
    lcd.setCursor(0, 1);
    lcd.print(elapsedTime);
    lcd.print(" seconds   ");
  }
 
  delay(200);
}
//Sound siren
void sirena() {
  for (int freq = 500; freq <= 1500; freq += 10) {
    tone(BuzzerPin, freq);
    delay(5);
  }
  for (int freq = 1500; freq >= 500; freq -= 10) {
    tone(BuzzerPin, freq);
    delay(5);
  }
}
//Move servo to indicate urgency
void urgenta(){
  for (int unghi = 0; unghi <= 180; unghi++) {
    myservo.write(unghi);
    delay(15);
  }
  for (int unghi = 180; unghi >= 0; unghi--) {
    myservo.write(unghi);
    delay(15);
  }
}