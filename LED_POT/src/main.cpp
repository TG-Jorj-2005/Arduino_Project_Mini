#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const int PIN_POT = A0;
const int ENA = 5;
const int IN1 = 7;
const int IN2 = 8;
const int Button_inainte = 2;
const int Button_inapoi = 3;

int viteza = 0;
int sensCurent = 0;

bool motorPornitInainte = false;
bool motorPornitInapoi = false;

unsigned long ultimaDataInainte = 0;
unsigned long ultimaDataInapoi = 0;
const unsigned long DEBOUNCE_DELAY = 50;

bool ultimaStareInainte = HIGH;
bool ultimaStareInapoi = HIGH;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setDirectie(int directie);
void stopMotor();
void AfisareSens(int sens);

void setup() {
  Serial.begin(9600);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Nu am gasit ecranul!");
    while (true);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.display();

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(Button_inainte, INPUT_PULLUP);
  pinMode(Button_inapoi, INPUT_PULLUP);
  
  stopMotor();
}

void loop() {
  int potValue = analogRead(PIN_POT);
  viteza = map(potValue, 0, 1023, 0, 255);
  
  bool stareInainte = digitalRead(Button_inainte);
  bool stareInapoi = digitalRead(Button_inapoi);
  
  if (stareInainte == LOW && ultimaStareInainte == HIGH) {
    if (millis() - ultimaDataInainte > DEBOUNCE_DELAY) {
      motorPornitInainte = !motorPornitInainte;
      
      if (motorPornitInainte) {
        motorPornitInapoi = false;
      }
      
      ultimaDataInainte = millis();
    }
  }
  ultimaStareInainte = stareInainte;
  
  if (stareInapoi == LOW && ultimaStareInapoi == HIGH) {
    if (millis() - ultimaDataInapoi > DEBOUNCE_DELAY) {
      motorPornitInapoi = !motorPornitInapoi;
      
      if (motorPornitInapoi) {
        motorPornitInainte = false;
      }
      
      ultimaDataInapoi = millis();
    }
  }
  ultimaStareInapoi = stareInapoi;
  
  if (motorPornitInainte) {
    setDirectie(1);
    sensCurent = 1;
  } else if (motorPornitInapoi) {
    setDirectie(-1);
    sensCurent = -1;
  } else {
    stopMotor();
    sensCurent = 0;
  }
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Viteza: ");
  display.println(viteza);
  display.print("Sens: ");
  AfisareSens(sensCurent);
  display.display();
  
  delay(10);
}

void setDirectie(int directie) {
  if (directie == 1) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (directie == -1) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  analogWrite(ENA, viteza);
}

void stopMotor() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void AfisareSens(int sens) {
  if (sens == 1) {
    display.print("Inainte");
  } else if (sens == -1) {
    display.print("Inapoi");
  } else {
    display.print("Oprit");
  }
}