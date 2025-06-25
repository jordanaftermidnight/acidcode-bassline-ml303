# ML-303 Arduino Integration - Unicode Line Art

## Physical Connection Diagram

```
                    ML-303 ARDUINO INTEGRATION
                         I2C Communication
    
    ╔══════════════════════════════════════════════════════════════════╗
    ║                        ML-303 Sequencer Board                   ║
    ╠══════════════════════════════════════════════════════════════════╣
    ║                                                                  ║
    ║    ┌─────────────────────────────────────────────┐               ║
    ║    │             PIC18LF452-I/P                  │               ║
    ║    │              40-Pin DIP                     │               ║
    ║    │                                             │               ║
    ║    │  ●18 RC3/SCL ──────────────────────────────┼──────┐        ║
    ║    │  ●23 RC4/SDA ──────────────────────────────┼─────┐│        ║
    ║    │  ●11 VDD/+5V ──────────────────────────────┼────┐││        ║
    ║    │  ●12 VSS/GND ──────────────────────────────┼───┐│││        ║
    ║    │                                             │   ││││        ║
    ║    └─────────────────────────────────────────────┘   ││││        ║
    ║                                                      ││││        ║
    ║    ┌─────────┐ ┌───────────┐ ┌──────────┐           ││││        ║
    ║    │   LCD   │ │  Knobs &  │ │  MIDI    │           ││││        ║
    ║    │ Display │ │ Switches  │ │Interface │           ││││        ║
    ║    └─────────┘ └───────────┘ └──────────┘           ││││        ║
    ╚══════════════════════════════════════════════════════┼┼┼┼════════╝
                                                           ││││
                     ┌─ GREEN Wire (I2C SCL) ──────────────┘│││
                     ├─ BLUE Wire (I2C SDA) ────────────────┘││ 
                     ├─ RED Wire (+5V Power) ────────────────┘│
                     └─ BLACK Wire (Ground) ──────────────────┘
                                                           ││││
    ╔══════════════════════════════════════════════════════┼┼┼┼════════╗
    ║                     Arduino Pro Micro                ││││        ║
    ╠══════════════════════════════════════════════════════┼┼┼┼════════╣
    ║                                                      ││││        ║
    ║    ┌─ USB Connector (Programming)                    ││││        ║
    ║    │                                                 ││││        ║
    ║  ┌───┐  ┌─────────────────────────────────────────┐  ││││        ║
    ║  │USB│  │           ATmega32U4                    │  ││││        ║
    ║  │   │  │         Microcontroller                 │  ││││        ║
    ║  └───┘  │                                         │  ││││        ║
    ║         │  Pin 3 (SCL) ●──────────────────────────┼──┘│││        ║
    ║         │  Pin 2 (SDA) ●──────────────────────────┼───┘││        ║
    ║         │         VCC  ●──────────────────────────┼────┘│        ║
    ║         │         GND  ●──────────────────────────┼─────┘        ║
    ║         └─────────────────────────────────────────┘              ║
    ║                                                                  ║
    ╚══════════════════════════════════════════════════════════════════╝
```

## Wire Color Reference

```
    ╔═══════════════════╦═══════════════╦══════════════════════════╗
    ║   Wire Color      ║   Function    ║        Connection        ║
    ╠═══════════════════╬═══════════════╬══════════════════════════╣
    ║  🔴 RED           ║ +5V Power     ║ PIC Pin 11 → Arduino VCC ║
    ║  ⚫ BLACK         ║ Ground        ║ PIC Pin 12 → Arduino GND ║
    ║  🔵 BLUE          ║ I2C SDA Data  ║ PIC Pin 23 → Arduino P2  ║
    ║  🟢 GREEN         ║ I2C SCL Clock ║ PIC Pin 18 → Arduino P3  ║
    ╚═══════════════════╩═══════════════╩══════════════════════════╝
```

## Mounting Configuration

```
                            SIDE VIEW
    
    Case Lid  ╔══════════════════════════════════════════════════╗
              ║                                                  ║
              ║  ← 15mm minimum clearance for case closure      ║
              ║                                                  ║
              ║    ┌─────────────────┐                          ║
              ║    │   Arduino Pro   │ ← USB facing outward     ║
              ║    │     Micro       │   for programming        ║
              ║    └─────────────────┘                          ║
              ║     ○               ○  ← M3×10mm standoffs      ║
              ╠══════════════════════════════════════════════════╣
              ║                                                  ║
              ║  ┌─────────────────────────────────────────────┐ ║
              ║  │          ML-303 Sequencer Board            │ ║
              ║  │                                             │ ║
              ║  │  [PIC] [LCD] [Controls] [Audio] [Power]    │ ║
              ║  └─────────────────────────────────────────────┘ ║
              ║                                                  ║
    Case Base ╚══════════════════════════════════════════════════╝
```

## Step-by-Step Connection Guide

```
    STEP 1: PREPARATION
    ┌─────────────────────────────────────────────────────────────┐
    │  □ Power off ML-303 completely                              │
    │  □ Gather wires: 22-24 AWG, Red/Black/Blue/Green           │
    │  □ Strip 3mm from each wire end                             │
    │  □ Have multimeter ready for testing                       │
    └─────────────────────────────────────────────────────────────┘
    
    STEP 2: ML-303 CONNECTIONS
    ┌─────────────────────────────────────────────────────────────┐
    │    PIC18LF452 (Looking at chip from above)                 │
    │                                                             │
    │           ┌───────────────────────┐                        │
    │      Pin 1│                       │Pin 40                  │
    │           │                       │                        │
    │    Pin 11 ●─ RED wire (+5V)       │                        │
    │    Pin 12 ●─ BLACK wire (GND)     │                        │
    │           │                       │                        │
    │    Pin 18 ●─ GREEN wire (SCL)     │Pin 23 ●─ BLUE (SDA)   │
    │           │                       │                        │
    │           └───────────────────────┘                        │
    └─────────────────────────────────────────────────────────────┘
    
    STEP 3: ARDUINO CONNECTIONS
    ┌─────────────────────────────────────────────────────────────┐
    │    Arduino Pro Micro (Component side view)                 │
    │                                                             │
    │    ┌─────────────────┐                                     │
    │    │      [USB]      │ ← Face outward                      │
    │    │                 │                                     │
    │    │ Pin 2 ●────── BLUE wire (SDA)                        │
    │    │ Pin 3 ●────── GREEN wire (SCL)                       │
    │    │                 │                                     │
    │    │   VCC ●────── RED wire (+5V)                         │
    │    │   GND ●────── BLACK wire (Ground)                    │
    │    │                 │                                     │
    │    └─────────────────┘                                     │
    └─────────────────────────────────────────────────────────────┘
```

## Testing Checklist

```
    PRE-CONNECTION TESTING
    ┌─────────────────────────────────────────────────────────────┐
    │  ✓ Visual inspection of all connections                     │
    │  ✓ Continuity test: Each wire end-to-end                   │
    │  ✓ No shorts between power and signal wires                │
    │  ✓ Arduino programmable via USB                            │
    └─────────────────────────────────────────────────────────────┘
    
    POST-CONNECTION TESTING  
    ┌─────────────────────────────────────────────────────────────┐
    │  ✓ Power on ML-303: Arduino LED should light up            │
    │  ✓ Serial monitor: "I2C initialized, waiting..."           │
    │  ✓ ML-303 functions normally (display, sounds, controls)   │
    │  ✓ I2C communication test: Address 0x43 responds           │
    └─────────────────────────────────────────────────────────────┘
```

## Success Indicators

```
    🎉 PHASE 1 COMPLETE WHEN:
    
    ┌─ Power ─────────────────────────────────────────────────────┐
    │  ● Arduino LED lights up when ML-303 powered on             │
    │  ● Voltage reads 4.8V - 5.2V on VCC pin                    │
    └─────────────────────────────────────────────────────────────┘
    
    ┌─ Communication ─────────────────────────────────────────────┐
    │  ● Serial monitor shows initialization messages             │
    │  ● I2C scanner detects device at address 0x43              │
    │  ● No communication timeouts or errors                     │
    └─────────────────────────────────────────────────────────────┘
    
    ┌─ Safety ───────────────────────────────────────────────────┐
    │  ● No smoke, burning smell, or excessive heat              │
    │  ● ML-303 operates exactly as before modification          │
    │  ● All original functions work (LCD, knobs, MIDI)          │
    └─────────────────────────────────────────────────────────────┘
```