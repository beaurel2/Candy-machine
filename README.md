# Candy Dispenser/Machine STM32

## Requirement
- Use C programming
- Use Embedded Studio or Vs Code
- Use Microcontroller

---

A small candy dispenser controlled by an STM32 microcontroller (Nucleo-Board F446RE).  
The dispenser releases candies when a coin is inserted or the button is pressed and shows the stock level with an RGB LED.

---

## Components and tools
The following hardware and software components are mainly used in the lab.
- **Boards:**
   - [development boards](https://www.conrad.de/de/p/stmicroelectronics-nucleo-f446re-entwicklungsboard-nucleo-f446re-stm32-f4-series-1416934.html) NUCLEO-F446RE STM32 F4 Series: [Manuel](https://www.st.com/resource/en/data_brief/nucleo-c031c6.pdf), [schematic](https://www.snapeda.com/parts/NUCLEO-F446RE/STMicroelectronics/view-part/?ref=mouser)

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

## Function of the Dispenser

- The storage container holds chewing candies.
- After inserting a coin, it falls into a slider.
- A servo moves the slider forward, releasing a candy.
- The coin is directed to the collection tray.
- If no coin is in the slider, no candy is released.

- A light-dependent resistor (LDR) in the storage area detects the stock level.  
  If the stock is low, it can be detected by reading the ADC value.

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
