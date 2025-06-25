# ML-303 Arduino Integration - Simple Wiring Guide

## Arduino Basic Connections

```
Arduino Uno          →    ML-303 / Components
═══════════════════════════════════════════════

POWER:
5V                   →    LCD VCC, DAC VCC
GND                  →    LCD GND, DAC GND, ML-303 Digital GND

LCD DISPLAY (6 pins):
D12                  →    LCD RS
D11                  →    LCD E  
D10                  →    LCD D4
D9                   →    LCD D5
D8                   →    LCD D6
D7                   →    LCD D7

ML-303 MONITORING (4 pins):
A0                   →    Cutoff CV (via 10kΩ)
A1                   →    Resonance CV (via 10kΩ)
A2                   →    Env Mod CV (via 10kΩ)
A3                   →    Decay CV (via 10kΩ)

MIDI INTERFACE (2 pins):
A4                   →    MIDI RX (via buffer)
A5                   →    MIDI TX (via buffer)

SPI/DAC (2 pins):
D13                  →    MCP4921 CS
D11                  →    MCP4921 SCK/SDI
```

## MCP4921 DAC Wiring

```
MCP4921 Pin    Arduino Pin    Function
═══════════════════════════════════════
1 (VCC)        5V             Power
2 (CS)         D13            Chip Select
3 (SCK)        D11            SPI Clock
4 (SDI)        D11            SPI Data
5 (LDAC)       GND            Immediate Update
6 (VREF)       5V             Voltage Reference
7 (VSS)        GND            Ground
8 (VOUT)       ML-303 CV      Control Voltage Output (0-5V)
```

**Arduino Code:**
```cpp
#include <SPI.h>
#define DAC_CS 13

void setup() {
  SPI.begin();
  pinMode(DAC_CS, OUTPUT);
  digitalWrite(DAC_CS, HIGH);
}

void setCV(uint16_t value) {
  value &= 0x0FFF;  // 12-bit limit
  uint16_t command = 0x3000 | value;
  digitalWrite(DAC_CS, LOW);
  SPI.transfer16(command);
  digitalWrite(DAC_CS, HIGH);
}
```

## ML-303 Safe Tap Points

```
ML-303 Board Location     Arduino Pin    Protection
═══════════════════════════════════════════════════

POWER CONNECTIONS:
+5V Digital Rail          5V             Direct
Digital Ground            GND            Direct

CV MONITORING (High Impedance Only):
Cutoff Pot Wiper         A0             10kΩ resistor
Resonance Pot Wiper      A1             10kΩ resistor  
Env Mod Pot Wiper        A2             10kΩ resistor
Decay Pot Wiper          A3             10kΩ resistor

MIDI MONITORING (PIC18LF452):
Pin RB5 (MIDI RX)        A4             Voltage divider: 10kΩ/10kΩ
Pin RB4 (MIDI TX)        A5             1kΩ current limit

DIGITAL SIGNALS:
Run/Stop Switch          D2             10kΩ pullup
Pattern Button           D3             10kΩ pullup
Clock Output             D4             1kΩ series
```

## CD4049 Overdrive Circuit

```
Signal Flow:
Audio In → 0.1µF Cap → CD4049 Gate 1 → 100kΩ Level → Audio Out
                           ↓
                      100MΩ Feedback

Power Options:
Single Supply: VDD = +9V to +18V, VSS = GND
Dual Supply:   VDD = +15V, VSS = -15V (ML-303 compatible)

Component List:
- 1× CD4049UBE CMOS Inverter (DIP-16)
- 1× 0.1µF coupling capacitor
- 1× 100MΩ feedback resistor
- 1× 100kΩ level potentiometer
```

## Stripboard Construction

### Basic Layout Rules:
```
Rows:    A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
         │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
Holes:   1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5...
         ═══════════════════════════════════════════════════
         Copper tracks run horizontally (left to right)
```

### MIDI Buffer Example (7×4 holes):
```
A: ═══════════════════════════════════ (+5V rail)
B: ═══[10kΩ]═══X═══[10kΩ]═══════════ (signal)
C: ═══════════════════════════════════ (signal)  
D: ═══════════════════════════════════ (GND rail)

Legend: X = track cut, [10kΩ] = resistor
```

### Construction Steps:
1. **Plan Layout**: Draw on paper first
2. **Cut Tracks**: Use 3mm drill between IC pins
3. **Insert Components**: Start with resistors
4. **Solder**: Component side only
5. **Test**: Continuity check before power

### Required Tools:
- Soldering iron (25-40W)
- 3mm drill bit
- Digital multimeter
- Wire strippers
- Rosin core solder (0.6-0.8mm)

## Safety Warnings

⚠️ **CRITICAL SAFETY WARNINGS:**

1. **ML-303 has NO reverse polarity protection**
2. **Always verify connections with multimeter before power-up**
3. **Use high-impedance monitoring only (10kΩ+ resistors)**
4. **Never inject signals directly into ML-303 circuits**
5. **Common ground between Arduino and ML-303 required**

## Pin Assignment Summary

| Function | Arduino Pin | ML-303 Connection | Protection |
|----------|-------------|------------------|------------|
| Power | 5V | +5V Digital | Direct |
| Ground | GND | Digital GND | Direct |
| LCD Control | D7-D12 | 16x2 Display | Direct |
| CV Monitor | A0-A3 | Pot Wipers | 10kΩ resistors |
| MIDI Monitor | A4-A5 | PIC RB4/RB5 | Voltage dividers |
| DAC Control | D11,D13 | MCP4921 | Direct |
| User Controls | D2-D6 | Switches/Gates | 10kΩ pullups |

## Troubleshooting

**No Display:**
- Check LCD power connections
- Verify contrast adjustment
- Test with simple "Hello World" code

**No CV Output:**
- Check MCP4921 power and SPI connections
- Verify CS signal toggles
- Test with multimeter on VOUT pin

**MIDI Issues:**
- Check baud rate (31250)
- Verify optocoupler power
- Test with MIDI monitor software

**No ML-303 Response:**
- Verify common ground
- Check protection resistor values
- Ensure high-impedance connections only