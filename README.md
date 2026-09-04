# LED_LCD — Emergency Timer (LCD + Servo + Buzzer)

A project that measures the time elapsed since the last reset and triggers an alarm (siren sound + servo motor movement) if the elapsed time exceeds a critical threshold. It can be used as a simulation of an emergency/warning system with a time limit.

### Components

* Arduino Uno
* 16x2 LCD (parallel interface, without I2C)
* Servo motor
* Passive buzzer
* Push button (reset)

### Connections

| Component          | Arduino Pin        |
| ------------------ | ------------------ |
| LCD (RS, E, D4-D7) | 12, 11, 5, 4, 3, 2 |
| Reset Button       | D13                |
| Buzzer             | A0                 |
| Servo              | D9                 |

### How It Works

* When the system starts, the timer begins counting the elapsed seconds using `millis()`.
* The LCD displays the elapsed time in real time, in seconds.
* If the elapsed time exceeds **10 seconds** without a reset, the system enters **"EMERGENCY"** mode:

  * The buzzer plays a siren sound with an increasing/decreasing frequency between 500–1500 Hz.
  * The servo motor continuously moves between 0° and 180° as a visual alarm signal.
  * The LCD displays the message **"EMERGENCY!!!"**.
* Pressing the reset button stops the alarm, resets the timer to 0, and displays a confirmation message.

### Required Libraries

* `LiquidCrystal` — included with the Arduino IDE
* `Servo` — included with the Arduino IDE

### Note

The 10-second threshold is intentionally short for quick testing. For real-world use, increase the value in `if (elapsedTime > 10)` to an appropriate time interval for your specific scenario.

---

# DC Motor Control — Speed and Direction (Potentiometer + OLED)

A project that controls a DC motor using an **L293D motor driver**, with adjustable speed controlled by a potentiometer and direction controlled by two push buttons. The current motor status is displayed live on an I2C OLED display.

### Components

* Arduino Uno
* L293D motor driver
* DC motor
* Potentiometer (speed control)
* 2 push buttons (forward / reverse)
* 0.96" SSD1306 OLED display (I2C)

### Connections

| Component      | Arduino Pin |
| -------------- | ----------- |
| Potentiometer  | A0          |
| ENA (driver)   | D5 (PWM)    |
| IN1 (driver)   | D7          |
| IN2 (driver)   | D8          |
| Forward Button | D2          |
| Reverse Button | D3          |
| OLED SDA/SCL   | A4 / A5     |

### How It Works

* The potentiometer controls the motor speed using PWM values from 0–255 through `analogWrite()` on the ENA pin.
* Each button acts as a **toggle**, turning the corresponding direction ON or OFF. The button does not need to be held down.
* Pressing one direction button automatically disables the opposite direction, preventing contradictory motor commands.
* Software debounce with a **50 ms** delay/filter prevents false button readings.
* The OLED display shows the current motor speed and rotation direction in real time:

  * **Forward**
  * **Reverse**
  * **Stopped**

### Required Libraries

* `Adafruit_GFX`
* `Adafruit_SSD1306`

---

# 🌡️ ESP32 Temperature Monitoring System

A simple temperature monitoring system built using an **ESP32**.

## 🚀 Features

* 🌡️ Measures temperature using a **DS18B20** temperature sensor
* 📺 Displays the temperature on an **ST7735 TFT display**
* 🟢 Green LED indicates a normal temperature
* 🔴 Red LED indicates a high temperature
* 🔊 Buzzer alarm activates when the temperature is too high
* 💻 Temperature is also displayed in the Serial Monitor

---

## 🚨 Temperature Status

### 🟢 Normal Mode

When the temperature is **35°C or below**:

* Green LED → **ON**
* Red LED → **OFF**
* Display → `TEMP OK`
* Status → **NORMAL**

### 🔴 Emergency Mode

When the temperature is **above 35°C**:

* Red LED → **ON**
* Green LED → **OFF**
* Display → `EMERGENCY!`
* Buzzer → **Siren Alarm**

---

## 🔧 Components

* ESP32
* DS18B20 Temperature Sensor
* ST7735 TFT Display
* 🔴 Red LED
* 🟢 Green LED
* 🔊 Buzzer

---

## 🔌 Pin Configuration

| Component | GPIO |
| --------- | ---- |
| DS18B20   | 4    |
| Red LED   | 19   |
| Green LED | 26   |
| Buzzer    | 25   |
| TFT CS    | 5    |
| TFT DC    | 2    |
| TFT RST   | 15   |
| TFT SCLK  | 18   |
| TFT MOSI  | 23   |

---

## 📚 Required Libraries

```text
Adafruit GFX
Adafruit ST7735
SPI
OneWire
DallasTemperature
```
