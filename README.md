# 🔋 Digital Voltmeter using PIC16F877A

This project is a simple **digital DC voltmeter** using a **PIC16F877A** microcontroller. It measures input voltage (0–30V DC) using a voltage divider and displays the result on a **4-digit 7-segment display** via multiplexing.

---

## 🖼️ Circuit Diagram

![Digital Voltmeter Circuit](images/digital_voltmeter_circuit.png)

---

## 🖼️ Simulation Output

![Proteus Simulation Output](images/digital_voltmeter_simulation.jpeg)

---

## 🧰 Components Used

| Component               | Value/Part No        |
|------------------------|----------------------|
| Microcontroller        | PIC16F877A           |
| 7-Segment Display      | Common cathode x 4   |
| Resistor R1            | 180kΩ (voltage divider)|
| Resistor R2            | 20kΩ (voltage divider)|
| Resistor Network (RN1) | 330Ω     |
| Potentiometer          | RV1 = 1kΩ           |
| Voltage Source         | V1 = 0–30V DC        |
| Capacitor              | 100nF (Decoupling)   |
| Crystal Oscillator     | 20 MHz (optional)    |

---

## 📐 Voltage Divider Calculation

The input voltage is scaled to the ADC range (0–5V) using a voltage divider:

### Voltage Divider Formula:
\[
V_{\text{adc}} = V_{\text{in}} \times \frac{R1}{R1 + R2}
\]

### Given:
- \( R1 = 1k\Omega \)
- \( R2 = 20k\Omega \)

\[
V_{\text{adc}} = V_{\text{in}} \times \frac{1}{1 + 20} = V_{\text{in}} \times \frac{1}{21}
\]

So:
- **Max input voltage** \( V_{\text{in max}} = 30V \)
- **Max ADC voltage** \( V_{\text{adc}} = 30 \times \frac{1}{21} ≈ 1.43V \)

You can scale this in firmware to display full 0–30V on the 7-segment.

---

## 🔢 ADC Conversion Calculation

PIC16F877A has a 10-bit ADC:

\[
\text{ADC Result} = \left( \frac{V_{\text{adc}}}{V_{\text{ref}}} \right) \times 1023
\]

With \( V_{\text{ref}} = 5V \):

To convert ADC back to input voltage:
\[
V_{\text{adc}} = \frac{\text{ADC Result} \times 5}{1023}
\]

Then scale up to input voltage:
\[
V_{\text{in}} = V_{\text{adc}} \times (1 + \frac{R2}{R1}) = V_{\text{adc}} \times 21
\]

---

## 📟 Microcontroller Configuration

- **Controller**: `PIC16F877A`
- **ADC Pin Used**: `RA0 / AN0` (Pin 2)
- **7-Segment Display Control**:
  - **Data Lines**: `PORTD` (RD0–RD7)
  - **Digit Select Lines**: `PORTB` (RB0–RB3)

---

## 🧾 Code Snippet (main.c)

```c
unsigned int adc_value;
float v_adc, v_in;

void main() {
    // ADC init, port init...

    while (1) {
        adc_value = ReadADC(); // 10-bit ADC value
        v_adc = (adc_value * 5.0) / 1023.0;
        v_in = v_adc * 21.0; // Because of voltage divider (1:21)

        // Display voltage on 7-segment
        display_voltage(v_in);
    }
}
