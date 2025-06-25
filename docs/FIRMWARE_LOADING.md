# ML-303 Firmware Loading & Programming Guide

## 🎯 Overview

This guide covers loading firmware into both the ML-303's PIC microcontroller and the optional Arduino enhancement system. Both are required for full functionality.

## 📁 Firmware Files Overview

### PIC Firmware (Required - Core ML-303)
```
firmware/
├── Transistor/           # Primary firmware developer
│   ├── 6.1/             # Latest stable (recommended)
│   ├── ml303v55final.syx # V5.5 Final (proven stable)
│   ├── ml303v61.syx     # V6.1 (latest features)
│   └── ml303v7beta.syx  # V7 Beta (experimental)
└── Matze/               # Alternative firmware builds
    ├── fw501alpha/      # V5.01 Alpha source
    └── mlv4/           # ML V4 source
```

### Arduino Firmware (Optional - Enhancements)
- `ml303-arduino-code-FIXED.txt` - **Use this one!** (pin conflicts resolved)
- `ml303-arduino-code.txt` - **Do NOT use** (has pin conflicts)
- `ml303-test-sketch.txt` - Hardware testing code

## 🔧 Part 1: PIC Firmware Loading

### Required Hardware
- **PIC Programmer**: PICkit 3/4, ICD 3, or compatible
- **Programming Software**: MPLAB X IDE + IPE (free from Microchip)
- **Target**: PIC18LF452-I/P (in ML-303)

### Recommended Firmware Version
**Start with V5.5 Final** (`ml303v55final.syx`) - most stable
**Upgrade to V6.1** later if desired (`ml303v61.syx`) - latest features

### Programming Procedure

#### Step 1: Hardware Setup
```
CRITICAL: Remove PIC from ML-303 before programming!
Never attempt in-circuit programming - can damage ML-303!
```

1. **Remove PIC18LF452-I/P from ML-303 socket**
2. **Insert into programmer or breadboard with programming headers**
3. **Connect PICkit programmer**:
   ```
   PICkit  →  PIC18LF452-I/P
   ──────────────────────────
   VCC     →  Pin 11 (+5V)
   GND     →  Pin 12 (GND)
   PGC     →  Pin 28 (RB6/PGC)
   PGD     →  Pin 27 (RB7/PGD)
   MCLR    →  Pin 1 (MCLR/VPP)
   ```

#### Step 2: Software Setup
1. **Download MPLAB X IDE** (free): https://www.microchip.com/mplab/mplab-x-ide
2. **Install IPE** (MPLAB X Integrated Programming Environment)
3. **Connect PICkit** and verify detection in IPE

#### Step 3: Firmware Programming

**Method A: Using .hex file (if available)**
```bash
# In MPLAB IPE:
1. Select Device: PIC18LF452
2. Select Tool: PICkit 3/4
3. Load Hex File: [firmware].hex
4. Program Device
5. Verify Programming
```

**Method B: Using .syx file (SysEx MIDI)**
```bash
# Convert .syx to .hex first:
1. Use hex2bin or similar tool
2. Or load .syx into ML-303 via MIDI (requires working ML-303)
```

#### Step 4: Verification
1. **Read device** to verify programming successful
2. **Check configuration bits**:
   - Oscillator: HS (High Speed Crystal)
   - Watchdog: OFF (for development)
   - Code Protection: OFF
   - Boot Block: OFF

### Common Programming Issues

#### "Device not found"
- Check all connections (especially power and ground)
- Verify PICkit is working (test with known good PIC)
- Ensure PIC18LF452-I/P (not regular PIC18F452)

#### "Programming failed"  
- Clean PIC pins with isopropyl alcohol
- Check for bent pins or socket issues
- Try slower programming speed
- Verify power supply voltage (5V±0.25V)

#### "Verification failed"
- PIC may be damaged - try new PIC
- Check for proper .hex file format
- Verify configuration bits are correct

## 🎮 Part 2: Arduino Firmware Loading

### Required Hardware
- **Arduino Uno/Nano** (5V, 16MHz)
- **USB Cable** for programming
- **Arduino IDE** 1.8.x or 2.x

### Critical Code Selection
```
⚠️  CRITICAL: Use ONLY the FIXED Arduino code!

✅ CORRECT: ml303-arduino-code-FIXED.txt
❌ WRONG:   ml303-arduino-code.txt (has pin conflicts!)
```

### Arduino IDE Setup

#### Step 1: Install Required Libraries
```cpp
// Install via Library Manager:
1. LiquidCrystal (built-in)
2. SoftwareSerial (built-in)  
3. SPI (built-in)
4. EEPROM (built-in)
```

#### Step 2: Board Configuration
```
Board: Arduino Uno (or Arduino Nano)
Processor: ATmega328P
Clock: 16MHz
Programmer: Arduino as ISP (if needed)
Port: [select USB port]
```

### Programming Procedure

#### Step 1: Load Fixed Code
1. **Open Arduino IDE**
2. **Copy contents** of `ml303-arduino-code-FIXED.txt`
3. **Paste into new sketch**
4. **Save as**: `ML303_Enhanced_Fixed`

#### Step 2: Verify Code
```cpp
// Check these critical pin assignments:
const int LCD_RS = 12, LCD_E = 11;           // LCD control  
const int LCD_D4 = 10, LCD_D5 = 9;          // LCD data
const int LCD_D6 = 8, LCD_D7 = 7;           // LCD data
const int BTN_RUN_STOP = 2, BTN_PATTERN = 3; // Buttons
const int GATE_OUT = 6, DAC_CS = 13;        // Outputs

// These should NOT conflict (original code had conflicts here!)
```

#### Step 3: Compile & Upload
1. **Verify/Compile** (Ctrl+R)
   - Should compile without errors
   - Check memory usage: ~15KB flash, ~500 bytes SRAM
2. **Upload** (Ctrl+U)
   - Connect Arduino via USB
   - Select correct port
   - Upload to Arduino

#### Step 4: Initial Testing
```
Open Serial Monitor (115200 baud):
Expected output:
> ML-303 Arduino Enhancement v1.0
> Initializing...
> Setup complete!
> Free SRAM: 1500+ bytes
```

### Arduino Programming Issues

#### Compilation Errors
```cpp
// Common issues in original code (fixed in FIXED version):
// 1. Pin conflicts between LCD and buttons
// 2. Memory overflow from too many patterns  
// 3. Missing pin initializations
// All resolved in ml303-arduino-code-FIXED.txt
```

#### Upload Errors
- Check USB cable and connection
- Select correct Arduino board and port
- Try different USB port
- Reset Arduino before upload

#### Runtime Issues
- **LCD blank**: Adjust contrast pot (required!)
- **Memory warnings**: Use FIXED code (optimized memory usage)
- **Pin conflicts**: Ensure using FIXED code version

## 🧪 Part 3: Hardware Testing

### Test Sequence After Programming

#### PIC Testing (Core ML-303)
1. **Power On Test**:
   ```
   Expected: LCD shows firmware version
   Listen for: Startup sound or silence (normal)
   Check: All LEDs function properly
   ```

2. **Basic Sequencer Test**:
   ```
   Press: Pattern button (should cycle through patterns)  
   Press: Play button (should start/stop sequencer)
   Check: Clock LED blinks at tempo
   ```

3. **MIDI Test**:
   ```
   Connect: MIDI cable from DAW/keyboard
   Send: MIDI clock and notes
   Check: ML-303 responds to external MIDI
   ```

#### Arduino Testing (Enhanced Features)
1. **LCD Display Test**:
   ```
   Expected: "ML-303 Enhanced" on startup
   Then: Pattern and parameter display
   Adjust: Contrast pot if display unclear
   ```

2. **Hardware Interface Test**:
   ```cpp
   // Call from setup() for testing:
   testHardware(); // Tests LCD, DAC, pots, MIDI
   ```

3. **Memory Usage Test**:
   ```
   Monitor Serial output for:
   > Free SRAM: [should be >1500 bytes]
   Warning if: "LOW MEMORY!" appears
   ```

### Integration Testing
1. **Both Systems Running**:
   - ML-303 operates normally
   - Arduino displays parameters
   - Mode switching works
   - No interference between systems

2. **MIDI Sync Test**:
   - Send MIDI clock to both systems
   - Verify tight synchronization
   - Check for timing drift

## 📊 Troubleshooting Matrix

| Problem | PIC Issue | Arduino Issue | Solution |
|---------|-----------|---------------|----------|
| No display | Firmware not loaded | Wrong pin assignments | Reprogram with correct firmware/code |
| LCD blank | N/A (PIC doesn't use LCD) | Missing contrast pot | Add 10k pot for contrast control |
| No MIDI | Wrong crystal frequency | Optocoupler issue | Check 10MHz crystal / Check 6N138 circuit |
| Memory error | N/A | Using original code | Use FIXED code (optimized memory) |
| Pin conflicts | N/A | Using original code | Use FIXED code (resolved conflicts) |
| No sound | Firmware issue | N/A | Check analog section, not firmware |

## 🎯 Success Criteria

### PIC Firmware Success
- [ ] ML-303 boots and shows firmware version
- [ ] Sequencer plays patterns
- [ ] MIDI sync works  
- [ ] All original functions operational

### Arduino Firmware Success  
- [ ] LCD displays pattern/parameter info
- [ ] No "LOW MEMORY" warnings
- [ ] Hardware test passes all checks
- [ ] MIDI I/O functional
- [ ] Smooth integration with ML-303

### Complete System Success
- [ ] Both systems work independently
- [ ] Mode switching seamless
- [ ] Enhanced features operational
- [ ] Original ML-303 functionality preserved
- [ ] No interference or conflicts

## 📚 Advanced Firmware Modifications

### Custom PIC Firmware
- Source code available in `firmware/Matze/` folders
- Requires MPLAB X and XC8 compiler
- Advanced users can modify and recompile

### Arduino Code Customization
- Well-commented code in FIXED version
- Easy to modify LCD messages, MIDI mappings
- Pattern storage can be expanded (memory permitting)
- Add custom features like arpeggiator, etc.

## ⚡ Quick Reference

### Essential Files
- **PIC**: `ml303v55final.syx` (stable) or `ml303v61.syx` (latest)
- **Arduino**: `ml303-arduino-code-FIXED.txt` (**ONLY this version!**)
- **Wiring**: `ml303-arduino-wiring.html` (updated for fixed pins)

### Programming Checklist
- [ ] PIC removed from ML-303 during programming
- [ ] Correct PIC model (PIC18LF452-I/P)
- [ ] Arduino using FIXED code only
- [ ] All libraries installed
- [ ] Hardware tested after programming
- [ ] Memory usage monitored

---

*Follow this guide exactly for reliable firmware loading and optimal ML-303 performance.*