#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

#define Led_Rosu 19
#define Led_Verde 26
#define Buzz_pin 25

#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  15
#define TFT_SCLK 18
#define TFT_MOSI 23

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void sirena();

void setup() {
  Serial.begin(115200);

  sensors.begin();

  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

  pinMode(Buzz_pin, OUTPUT);
  pinMode(Led_Rosu, OUTPUT);
  pinMode(Led_Verde, OUTPUT);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(0);
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
}

void loop() {

  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);

  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  // CURATAM DISPLAY-UL INAINTE DE AFISARE
  tft.fillScreen(ST77XX_BLACK);

  if (temperatura > 35) {

    digitalWrite(Led_Rosu, HIGH);
    digitalWrite(Led_Verde, LOW);

    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(2);

    tft.setCursor(5, 10);
    tft.println("URGENTA!");

    tft.setTextColor(ST77XX_WHITE);

    tft.setCursor(5, 40);
    tft.println("Temp:");

    tft.setCursor(5, 65);
    tft.print(temperatura, 1);
    tft.println(" C");

    tft.setCursor(5, 100);
    tft.println("PREA MARE!");

    sirena();

  } else {

    digitalWrite(Led_Rosu, LOW);
    digitalWrite(Led_Verde, HIGH);

    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(2);

    tft.setCursor(5, 15);
    tft.println("TEMP OK");

    tft.setTextColor(ST77XX_WHITE);

    tft.setCursor(5, 50);
    tft.println("Temp:");

    tft.setCursor(5, 75);
    tft.print(temperatura, 1);
    tft.println(" C");

    tft.setCursor(5, 110);
    tft.println("NORMAL");

    delay(1000);
  }
}


// SIRENA
void sirena() {

  // urcare
  for (int frecventa = 700; frecventa <= 2200; frecventa += 25) {
    tone(Buzz_pin, frecventa);
    delay(8);
  }

  // coborare
  for (int frecventa = 2200; frecventa >= 700; frecventa -= 25) {
    tone(Buzz_pin, frecventa);
    delay(8);
  }

  // a doua sirena
  for (int frecventa = 700; frecventa <= 2200; frecventa += 25) {
    tone(Buzz_pin, frecventa);
    delay(8);
  }

  // coborare
  for (int frecventa = 2200; frecventa >= 700; frecventa -= 25) {
    tone(Buzz_pin, frecventa);
    delay(8);
  }

  noTone(Buzz_pin);
}