# Candy Dispenser/Machine STM32

## Requirement
- Use C programming
- Use Embedded Studio or Vs Code
- Use Microcontroller

---

## Components and tools
The following hardware and software components are mainly used in the lab.
- **Boards:**
   - [development boards](https://www.conrad.de/de/p/stmicroelectronics-nucleo-f446re-entwicklungsboard-nucleo-f446re-stm32-f4-series-1416934.html) NUCLEO-F446RE STM32 F4 Series: [Manuel](https://www.st.com/resource/en/data_brief/nucleo-c031c6.pdf), [schematic](https://www.snapeda.com/parts/NUCLEO-F446RE/STMicroelectronics/view-part/?ref=mouser)
- **Servo**
  - [Servo motor](https://www.amazon.com/DIYables-Degree-Arduino-ESP8266-Raspberry/dp/B0BPFXTZ73/ref=asc_df_B0BPFXTZ73?tag=bingshoppinga-20&linkCode=df0&hvadid=80333258194147&hvnetw=o&hvqmt=e&hvbmt=be&hvdev=c&hvlocint=&hvlocphy=91544&hvtargid=pla-4583932723000478&msclkid=87ca843323571fb316afed887e990500&th=1) Servo Motor SG90 180 Degree for Arduino, ESP32, ESP8266, Raspberry Pi, [Makerguides](https://www.makerguides.com/de/servo-arduino-tutorial-de/)
- **Level sensor** [sensor](https://www.ifm.com/us/en)

---

## Installation(s)
- Embedded Studio Development environment of the company Segger including simulator [download](https://www.segger.com/products/development-tools/embedded-studio/)

  > ⚠️ **WARNING:**  
  > When installing, make sure that the J-Link device drivers or USB drivers are also installed.

- If you have not done this, the program download to the Nucleo board will not work.  
  In that case, you must install the drivers manually:

  - Download the necessary drivers: [download](https://www.segger.com/downloads/jlink)  
  - Install the package  
  - Start `SEGGERJlink_USBDriverInstDrivers.exe`

- Configuration Embedded Studio
  - Check project settings
  - Target Connection: JLINK
  - Target Device: STM32F446RET
  <img width="947" height="910" alt="image" src="https://github.com/user-attachments/assets/9638f5ee-67fc-48a7-89eb-d42a8aa4f0fc" />


---

## Hardware Components

| Component           | Connection / Function                                  |
|--------------------|--------------------------------------------------------|
| Servo              | Timer 3, Channel 0 – moves the slider                |
| RGB LED            | Timer 3, Channels 1–3 – indicates operation and stock |
| Button             | GPIO Port C12, active-low – triggers candy release   |
| Stock Sensor       | ADC Channel 1 – light-dependent resistor             |

---

## Servo Control

- The servo moves within a limited range (min/max pulse width as constants).
- Movement to the release position and back occurs **gradually**, not abruptly, to protect the mechanics.
- At least 100 steps with short delays in between.

---

## Stock Level Detection

- Sensor connected to ADC via voltage divider.
- High ADC value → candy present  
- Low ADC value → stock low/empty
- Threshold depends on ambient light.
- Limited number of releases when “low stock” until full again.

---

## Process Flow

1. Servo in resting position
2. Button pressed → servo moves forward → candy released → servo returns
3. RGB LED shows status in parallel:
   - **Green:** stock OK  
   - **Red:** stock low  
   - **Blue:** servo moving

---

## RGB LED Indication

| Status                  | Color |
|-------------------------|-------|
| Stock sufficient        | Green |
| Stock low               | Red   |
| Servo in motion         | Blue  |
---

## Function of the Dispenser
The storage container contains chewy candies. After inserting a coin, it falls into a slider that is moved forward by a servo motor. A chewy candy is dispensed in the process, and the coin is directed into a collection container. If there is no coin in the slider, no dispensing occurs.

A light-sensitive resistor in the storage area allows the detection of the fill level. If the fill level decreases, this can be detected by evaluating the ADC value.

<img width="413" height="571" alt="image" src="https://github.com/user-attachments/assets/5574733c-d429-4b32-a605-e4e75f07433d" />

