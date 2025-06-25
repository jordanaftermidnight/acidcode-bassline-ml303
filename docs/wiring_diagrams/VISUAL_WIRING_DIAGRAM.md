# ML-303 Arduino Integration - Visual Wiring Diagram

## I2C Connection Overview

```
ML-303 Sequencer Board                    Arduino Pro Micro
┌─────────────────────────┐              ┌─────────────────┐
│                         │              │                 │
│  ┌─────────────────┐    │              │  ┌───────────┐  │
│  │   PIC18LF452    │    │              │  │           │  │
│  │   40-Pin DIP    │    │              │  │  ATmega   │  │
│  │                 │    │              │  │  32U4     │  │
│  │ 18○ RC3/SCL ────┼────┼──────────────┼──┼─○ Pin 3   │  │
│  │ 23○ RC4/SDA ────┼────┼──────────────┼──┼─○ Pin 2   │  │
│  │ 11○ VDD/+5V ────┼────┼──────────────┼──┼─○ VCC     │  │
│  │ 12○ VSS/GND ────┼────┼──────────────┼──┼─○ GND     │  │
│  │                 │    │              │  │           │  │
│  └─────────────────┘    │              │  └───────────┘  │
│                         │              │                 │
│  ┌─────┐ ┌─────────┐    │              │  ┌───┐         │
│  │ LCD │ │ Controls│    │              │  │USB│         │
│  └─────┘ └─────────┘    │              │  └───┘         │
└─────────────────────────┘              └─────────────────┘
```

## Wire Color Coding

```
Connection Type    Wire Color    Purpose
═══════════════════════════════════════════════════════════════
Power Supply       RED          +5V from ML-303 to Arduino
Ground             BLACK        Common ground connection  
I2C Data           BLUE         SDA data line (bidirectional)
I2C Clock          GREEN        SCL clock line (from PIC)
```

## Physical Connection Details

```
ML-303 Side (PIC18LF452)          Arduino Pro Micro Side
════════════════════════════       ═══════════════════════

Pin 18 (RC3) ──────[GREEN]────────→ Pin 3 (SCL)
Pin 23 (RC4) ──────[BLUE]─────────→ Pin 2 (SDA)  
Pin 11 (VDD) ──────[RED]──────────→ VCC
Pin 12 (VSS) ──────[BLACK]────────→ GND
```

## Step-by-Step Wiring Instructions

### 1. Preparation
- [ ] Power off ML-303 completely
- [ ] Gather 4 wires: Red, Black, Blue, Green (22-24 AWG)
- [ ] Strip 3mm from each wire end
- [ ] Have multimeter ready for testing

### 2. ML-303 Connections (PIC18LF452)
```
Looking at PIC chip from above:
                    ┌─────┐
               Pin 1│  U  │Pin 40
                    │     │
              Pin 11│ VDD │Pin 30    ← Connect RED wire here
              Pin 12│ VSS │Pin 29    ← Connect BLACK wire here
                    │     │
              Pin 18│ RC3 │Pin 23    ← Connect GREEN wire here (Pin 18)
                    │ RC4 │          ← Connect BLUE wire here (Pin 23)
                    │     │
               Pin 20└─────┘Pin 21
```

### 3. Arduino Pro Micro Connections
```
Arduino Pin Layout (looking at component side):
┌─────────────────┐
│  [USB]          │
│                 │
│ Pin 2 ○ ← BLUE  │ (SDA)
│ Pin 3 ○ ← GREEN │ (SCL)  
│                 │
│   VCC ○ ← RED   │ (+5V)
│   GND ○ ← BLACK │ (Ground)
│                 │
└─────────────────┘
```

### 4. Testing Sequence
```
Test Order:
1. Visual inspection ✓
2. Continuity check ✓  
3. Power off test ✓
4. Power on test ✓
5. Communication test ✓
```

## I2C Configuration Settings

### PIC18LF452 (Master)
```
Configuration:
├── Mode: I2C Master
├── Clock Speed: 100kHz  
├── SSPADD Register: 24 (for 10MHz oscillator)
└── Pull-ups: Internal enabled

Code Example:
SSPCON = 0x28;     // Enable I2C Master mode
SSPADD = 24;       // 100kHz with 10MHz osc
SSPSTAT = 0x80;    // Slew rate control disabled
```

### Arduino Pro Micro (Slave)
```
Configuration:
├── Mode: I2C Slave
├── Address: 0x43 (67 decimal)
├── Clock Speed: 100kHz max
└── Library: Wire.h

Code Example:
#include <Wire.h>
void setup() {
  Wire.begin(0x43);        // Join I2C as slave #67
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}
```

## Physical Mounting Guide

```
Side View of ML-303 Case:
                     
├─────────────────────────────┤ ← Case lid
│                             │
│  ┌─────────────┐            │ ← 15mm clearance
│  │  Arduino    │            │   minimum
│  │  Pro Micro  │            │
│  └─────────────┘            │
│ ○ ○           ○ ○           │ ← M3 standoffs  
├─────────────────────────────┤   (10mm height)
│ ┌─────────────────────────┐ │
│ │    ML-303 Sequencer     │ │ ← Main board
│ │        Board            │ │
│ └─────────────────────────┘ │
├─────────────────────────────┤ ← Case bottom
```

## Troubleshooting Guide

### No Communication
```
Check:                           Expected:
┌─────────────────────────────┐ ┌──────────────────┐
│ 1. Power voltage            │ │ 4.8V - 5.2V     │
│ 2. Ground continuity        │ │ 0Ω resistance    │
│ 3. SDA/SCL connectivity     │ │ <1Ω resistance   │  
│ 4. Arduino programming      │ │ Upload success   │
│ 5. Serial monitor output    │ │ "Waiting for..." │
└─────────────────────────────┘ └──────────────────┘
```

### Connection Verification
```
Multimeter Test Points:
ML-303 Pin 11 to Arduino VCC: Should read ~5V
ML-303 Pin 12 to Arduino GND: Should read 0V  
ML-303 Pin 18 to Arduino Pin 3: Should have <1Ω resistance
ML-303 Pin 23 to Arduino Pin 2: Should have <1Ω resistance
```

## Safety Checklist

```
Before Power-On:                     Status
┌────────────────────────────────┐   ┌──────┐
│ ML-303 powered completely off  │   │ [ ]  │
│ All wire connections secure    │   │ [ ]  │
│ No shorts between power/signal │   │ [ ]  │
│ Arduino programmed via USB     │   │ [ ]  │
│ Multimeter tests passed        │   │ [ ]  │
│ Standoffs properly installed   │   │ [ ]  │
│ Wire strain relief attached    │   │ [ ]  │
└────────────────────────────────┘   └──────┘
```

## Success Indicators

### Phase 1 Complete When:
- [ ] Arduino LED lights up when ML-303 powered on
- [ ] Serial monitor shows "I2C initialized, waiting for commands..."
- [ ] No smoke, burning smell, or excessive heat
- [ ] ML-303 operates normally (display, sounds, controls)
- [ ] I2C communication established (address 0x43 responds)

## Next Phase Preview

```
Phase 2 Additions:
┌─────────────────┐
│ Phase 1: I2C    │ ← Current phase
├─────────────────┤
│ Phase 2: LCD    │ ← LCD display takeover
├─────────────────┤  
│ Phase 3: FX     │ ← Effects processing
├─────────────────┤
│ Phase 4: MIDI   │ ← MIDI expansion
└─────────────────┘
```

---
**⚠️ CRITICAL SAFETY REMINDER:**
- Never connect/disconnect wires while ML-303 is powered on
- Always verify connections with multimeter before applying power
- If anything gets hot or smells unusual, power off immediately
- Use proper ESD precautions when handling both boards