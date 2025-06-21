
# 🔋 Digital Voltmeter using PIC16F877A

This project is a simple **digital DC voltmeter** built using a **PIC16F877A** microcontroller.  
It measures input voltage (0–30V DC) using a voltage divider and displays the result on a **4-digit 7-segment display** using **multiplexing**.

---

## 🖼️ Circuit Diagram

![Digital Voltmeter Circuit](images/digital_voltmeter_circuit.png)

---

## 🖼️ Simulation Output

![Proteus Simulation Output](images/digital_voltmeter_simulation.jpeg)

---

## 🧰 Components Used

| Component               | Value/Part No           |
|------------------------|-------------------------|
| Microcontroller        | PIC16F877A              |
| 7-Segment Display      | 4-digit, Common Cathode |
| Resistor R1            | 180kΩ (Voltage Divider) |
| Resistor R2            | 20kΩ (Voltage Divider)  |
| Resistor Network       | 330Ω (for segments)     |
| Capacitor              | 100nF (Decoupling)      |
| Potentiometer          | 1kΩ (for voltage input) |
| DC Voltage Source      | 0–30V DC                |
| Crystal Oscillator     | 20 MHz (Optional)       |
| PIC Programmer         | Pickit 2/3 or compatible|

---

## 📐 Voltage Divider Calculation

To measure up to 30V with a 5V ADC, a voltage divider scales down the input:

**Voltage Divider Formula**:
```
Vadc = Vin × (R2 / (R1 + R2))
```

**Values**:
- R1 = 180kΩ  
- R2 = 20kΩ

**Calculation**:
```
Vadc = Vin × (20 / (180 + 20)) = Vin × (20 / 200) = Vin × 0.1
```

So for Vin = 30V:
```
Vadc = 30 × 0.1 = 3.0V
```

This is within the safe 0–5V ADC range.

---

## 🔢 ADC to Voltage Conversion

**PIC16F877A** has a 10-bit ADC (0–1023) with reference voltage = 5V.

**ADC output:**
```
ADC = (Vadc / 5V) × 1023
```

To convert ADC back to input voltage:
```
Vadc = (ADC × 5) / 1023
Vin = Vadc × (R1 + R2) / R2 = Vadc × 10
Vin = (ADC × 5 × 10) / 1023
Vin ≈ ADC × 0.0488
```

---

## 📟 Microcontroller & Pin Mapping

| Function            | Port        | Pin Numbers           |
|---------------------|-------------|------------------------|
| ADC Input           | RA0/AN0     | Pin 2                  |
| Segment Data Lines  | PORTD (RD0–RD7) | Pins 19–22, 27–30   |
| Digit Control Lines | PORTB (RB0–RB3) | Pins 33–36         |

---

## 🧾 Code Logic Overview (main.c)

```c
unsigned int adc_value;
float v_adc, v_in;

void main() {
    // Initialize ADC and I/O Ports

    while (1) {
        adc_value = Analog_read(0);                 // Read ADC value (0–1023)
        v_adc = (adc_value * 5.0) / 1023.0;         // Convert to actual voltage
        v_in = v_adc * 10.0;                        // Scale up using divider factor

        display_voltage(v_in);                      // Show on 7-segment display
    }
}
```

---

## 📂 Folder Structure

```
Digital_Voltmeter_Project/
├── code/
│   └── main.c
├── images/
│   ├── digital_voltmeter_circuit.png
│   └── digital_voltmeter_simulation.jpeg
├── proteus/
│   └── DigitalVoltmeter.pdsprj
├── README.md
```

---

## 🧪 Proteus Simulation Setup

**Steps:**
1. Place **PIC16F877A** MCU.
2. Add **4-digit 7-segment common cathode display**.
3. Connect segment lines to **PORTD**.
4. Connect digit select lines to **PORTB (RB0–RB3)**.
5. Connect **R1 = 180kΩ** and **R2 = 20kΩ** in series from Vin to GND.
6. Connect the middle of divider to **RA0/AN0**.
7. Add **crystal (20MHz)** and decoupling capacitors.
8. Power the MCU with 5V.

---

## 🛠 Tools Used

- **MPLAB X IDE** + XC8 Compiler
- **Proteus 8** (Simulation)
- **VS Code** (Editing)
- **Git & GitHub** (Version Control)

---

## 🔁 Timesheet Remarks (Week Summary)

| Day       | Activity Summary |
|-----------|------------------|
| Monday    | Explored MPLAB software features and environment setup. |
| Tuesday   | Studied PIC16F877A architecture and wrote ADC display code. |
| Wednesday | Designed voltage divider & ADC circuit in Proteus. |
| Thursday  | Simulated digital voltmeter using Proteus with display output. |
| Friday    | Optimized flickering issue in 7-segment multiplexing code. |

---

## 📌 Author

**Sathish S**  
Final Year ECE Student  
Sri Ramakrishna Engineering College, Coimbatore  
2025

---

## 📎 GitHub Repository

[👉 View Project on GitHub](https://github.com/Sathish0298/Digital_Voltmeter_Project)

---

## ✅ Final Notes

- Display shows **actual voltage** (e.g., 24.5V input → 24.5 on display).
- Code uses ADC channel 0 (RA0) and 10-bit resolution.
- Ensure all resistors and connections match exactly for accurate reading.
