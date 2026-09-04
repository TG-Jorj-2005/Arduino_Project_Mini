## LED_LCD — Cronometru de Urgență (LCD + Servo + Buzzer)

Proiect care numără timpul scurs de la ultimul reset și declanșează o alarmă 
(sunet de sirenă + mișcare de servomotor) dacă timpul depășește un prag critic — 
util ca simulare pentru un sistem de avertizare/urgență cu timp limită.

### Componente
- Arduino Uno
- LCD 16x2 (mod paralel, fără I2C)
- Servomotor
- Buzzer pasiv
- Buton (reset)

### Conexiuni

| Componentă        | Pin Arduino |
|--------------------|-------------|
| LCD (RS, E, D4-D7) | 12, 11, 5, 4, 3, 2 |
| Buton Reset        | D13         |
| Buzzer             | A0          |
| Servo              | D9          |

### Funcționare
- La pornire, cronometrul începe să numere secundele scurse (`millis()`).
- Ecranul LCD afișează timpul scurs în timp real, în secunde.
- Dacă timpul depășește **10 secunde** fără reset, se declanșează starea de "URGENȚĂ":
  - Buzzer-ul redă o sirenă (frecvență crescătoare/descrescătoare între 500-1500 Hz).
  - Servomotorul se mișcă continuu între 0° și 180°, ca semnal vizual de alarmă.
  - LCD-ul afișează mesajul "URGENTA!!!".
- Apăsarea butonului de reset oprește alarma, resetează cronometrul la 0 și afișează un mesaj de confirmare.

### Biblioteci necesare
- `LiquidCrystal` (inclusă în Arduino IDE)
- `Servo` (inclusă în Arduino IDE)

### Notă
Pragul de 10 secunde e setat scurt pentru testare rapidă — pentru o utilizare reală, 
mărește valoarea din `if (elapsedTime > 10)` la un interval potrivit scenariului tău.







## Control Motor DC — Viteză și Direcție (Potențiometru + OLED)

Proiect care controlează un motor DC folosind un driver de motor L293D, 
cu viteză reglabilă din potențiometru și direcție comandată din două butoane, 
iar starea curentă e afișată live pe un ecran OLED I2C.

### Componente
- Arduino Uno
- Driver de motor L293D
- Motor DC
- Potențiometru (control viteză)
- 2 butoane (înainte / înapoi)
- OLED 0.96" SSD1306 (I2C)

### Conexiuni

| Componentă      | Pin Arduino |
|------------------|-------------|
| Potențiometru    | A0          |
| ENA (driver)     | D5 (PWM)    |
| IN1 (driver)     | D7          |
| IN2 (driver)     | D8          |
| Buton înainte    | D2          |
| Buton înapoi     | D3          |
| OLED SDA/SCL     | A4 / A5     |

### Funcționare
- Potențiometrul controlează viteza motorului (PWM 0-255) prin `analogWrite` pe pinul ENA.
- Fiecare buton **comută** (toggle) pornit/oprit pentru sensul respectiv — nu trebuie ținut apăsat.
- Apăsarea unui buton dezactivează automat sensul opus, ca motorul să nu primească comenzi contradictorii.
- Debounce software (50ms) evită citiri false la apăsarea butoanelor.
- Ecranul OLED afișează în timp real viteza curentă și sensul de rotație (Înainte / Înapoi / Oprit).

### Biblioteci necesare
- `Adafruit_GFX`
- `Adafruit_SSD1306`


# 🌡️ ESP32 Temperature Monitoring System

A simple temperature monitoring system built with an **ESP32**.

## 🚀 Features

- 🌡️ Reads temperature using a **DS18B20**
- 📺 Displays the temperature on an **ST7735 TFT display**
- 🟢 Green LED indicates normal temperature
- 🔴 Red LED indicates high temperature
- 🔊 Buzzer alarm activates when the temperature is too high
- 💻 Temperature is also displayed in the Serial Monitor

---

## 🚨 Temperature Status

### 🟢 Normal Mode

When the temperature is **35°C or below**:

- Green LED → **ON**
- Red LED → **OFF**
- Display → `TEMP OK`
- Status → `NORMAL`

### 🔴 Emergency Mode

When the temperature is **above 35°C**:

- Red LED → **ON**
- Green LED → **OFF**
- Display → `URGENTA!`
- Buzzer → **Siren alarm**

---

## 🔧 Components

- ESP32
- DS18B20 Temperature Sensor
- ST7735 TFT Display
- 🔴 Red LED
- 🟢 Green LED
- 🔊 Buzzer

---

## 🔌 Pin Configuration

| Component | GPIO |
|-----------|------|
| DS18B20 | 4 |
| Red LED | 19 |
| Green LED | 26 |
| Buzzer | 25 |
| TFT CS | 5 |
| TFT DC | 2 |
| TFT RST | 15 |
| TFT SCLK | 18 |
| TFT MOSI | 23 |

---

## 📚 Libraries

```text
Adafruit GFX
Adafruit ST7735
SPI
OneWire
DallasTemperature
