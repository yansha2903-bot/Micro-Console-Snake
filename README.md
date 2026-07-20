# SnakeOnXIAO 🐍

A pocket-sized, custom-built retro gaming console made from scratch just to play the legendary Snake game!

This repository contains the full hardware design (KiCad schematic and PCB layout) and the custom C++ game engine running on a **Seeed Studio XIAO RP2040** microcontroller.

---

## 🛠️ Project Structure

* **`PCB/`** — KiCad project files:
* `*.kicad_pro` — KiCad project management file.
* `*.kicad_sch` — Clean electrical schematic with custom net labels.
* `*.kicad_pcb` — Custom PCB routing, component layout, and geometric board shape.
* **`Firmware/`** — Game source code:
* `*codeSnake.ino` — Arduino IDE C++ sketch running the custom Snake game loop.
* * **`Images`** — images of my project.

---

## 🚀 Hardware & Architecture

* **Microcontroller:** Seeed Studio XIAO RP2040 (chosen for its tiny form factor and huge performance).
* **Display:** 0.96" I2C OLED display ($128 \times 64$ pixels) powered by the SSD1306 driver.
* **Controls:** 4x 6x6mm tactile buttons arranged as a classic D-Pad layout for fluid movement.
* **Pinout Configuration:**
* **Buttons (D-Pad):** Connected directly to digital pins `D0` (Up), `D1` (Down), `D2` (Left), and `D3` (Right) using internal `INPUT_PULLUP` resistors.
* **OLED Screen (I2C):** Connected to hardware I2C pins `D4` (SDA) and `D5` (SCL). Powered by the `3V3` and `GND` lines.

---

## 💻 Game Engine Features

The game code is written in C++ using Arduino IDE and utilizes `Adafruit_GFX` and `Adafruit_SSD1306` libraries.

* **Dynamic Game Loop:** Runs at a stable frame rate, processing inputs, updating game logic, and rendering graphics in real-time.
* **Smart Collision Detection:** Full grid tracking to handle when the snake eats food (and grows!), hits the custom map borders, or runs into its own tail.
* **Grid-Aligned Spawning:** Random food spawning that perfectly matches the coordinate system of the snake segments.
* **Zero External Components:** Uses the RP2040's internal pull-up resistors to keep the PCB layout extremely clean and beginner-friendly.

---

## 👾 How to Open and Explore

### 1. Hardware & PCB Layout (KiCad)
1. Download or clone this repository.
2. Open **KiCad 10** (or newer).
3. Load the project from the `PCB/` directory.
4. Open the Schematic Editor to view connections, or jump into the PCB Editor and hit `Alt + 3` to see the full 3D model of the console!

### 2. Flashing the Firmware (Arduino)
1. Open the `.ino` file in the **Arduino IDE**.
2. Go to *Tools -> Manage Libraries* and install **Adafruit GFX** and **Adafruit SSD1306**.
3. Select **Seeed XIAO RP2040** in your Boards Manager.
4. Connect your console via USB-C, choose the correct port, and hit **Upload**!
