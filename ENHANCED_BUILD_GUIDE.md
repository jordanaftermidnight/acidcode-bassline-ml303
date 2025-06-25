# ML-303 Enhanced Build Guide - Complete & Tested

## 🚨 CRITICAL: Use Only FIXED Arduino Code!

**WARNING**: The original Arduino code had major pin conflicts that prevent operation. This guide references only the **FIXED** versions:
- `ml303-arduino-code-FIXED.txt` - Corrected code with no pin conflicts
- `ml303-arduino-wiring.html` - Updated wiring diagrams
- `CODE_REVIEW_FIXES.md` - Complete analysis of fixes

## 📋 Pre-Build Checklist

### Essential Tools
- [ ] Soldering iron (temperature controlled, 350°C)
- [ ] Solder (60/40 or 63/37, 0.8mm)
- [ ] Desoldering braid and pump
- [ ] Multimeter with continuity tester
- [ ] Oscilloscope (for calibration)
- [ ] Anti-static wrist strap
- [ ] IC extraction tool
- [ ] Small Phillips and flathead screwdrivers

### Critical Components Verification
- [ ] **PIC18LF452-I/P** (NOT PIC18F452 - must be LF variant)
- [ ] **RECOM 0515S** DC/DC converter (±15V for analog)
- [ ] **AN6562** VCA (primary), or BA6110/BA662 (alternatives)
- [ ] **2SK30** JFETs - one O-type, one Y/GR-type (MATCHED PAIR)
- [ ] **Precision capacitors**: 18nF ±1%, 1nF 1% tolerance
- [ ] **Metal film resistors**: 200KΩ (17x), 27KΩ (1x)

## 🔧 Phase 1: Core ML-303 Build

### Step 1: Power Supply Assembly & Testing
```
⚠️  CRITICAL: Test ALL voltages before connecting sensitive components!
```

1. **Install Power Components**:
   - 78S05 voltage regulator
   - RECOM 0515S DC/DC converter  
   - Filter capacitors and rectifiers

2. **Power-On Test**:
   ```
   Expected Voltages:
   - Input: +12V DC
   - Digital: +5.333V (NOT +5V!)
   - Analog: +15V, -15V
   ```

3. **Verification**:
   - Measure all voltages with multimeter
   - Check ripple with oscilloscope (<50mV)
   - Verify polarity (wrong polarity = dead ICs)

### Step 2: Digital Section Assembly

1. **Install IC Sockets** (never solder ICs directly):
   - PIC18LF452-I/P socket (44-pin)
   - 24C64 EEPROM socket (8-pin)
   - Logic IC sockets (74174, 4050, 4066, 4013)

2. **Install Support Components**:
   - 10MHz crystal with 22pF capacitors
   - Pull-up resistors for digital inputs
   - Bypass capacitors (0.1µF near each IC)

3. **Initial Digital Test**:
   - Insert PIC (check orientation!)
   - Load basic firmware
   - Verify LCD display initialization
   - Test button inputs

### Step 3: Analog Audio Path

1. **VCO Section**:
   - Install 2SC945/2SC536F transistors
   - **Precision timing capacitors** (1nF ±1%)
   - Metal film resistors for temperature stability
   - VCO trimmer for coarse tuning

2. **VCF Section** (Most Critical):
   - Install **MATCHED 2SK30 JFETs** (one O-type, one Y/GR-type)
   - Precision filter capacitors (18nF ±1%, 33nF, 100nF ±1%)
   - Resonance feedback network
   - Filter tracking trimmer

3. **VCA Section**:
   - Install AN6562 (primary) or BA6110/BA662 (alternatives)
   - Accent level trimmer
   - CV input scaling network

4. **Audio Output**:
   - Install LA4140 or AN7112E audio driver
   - Output coupling capacitor
   - Volume control potentiometer

### Step 4: MIDI Interface

1. **Isolation Circuit**:
   - CNY17 optocoupler (check orientation!)
   - 220Ω current limiting resistors
   - MIDI connectors (DIN-5 standard)

2. **MIDI Test**:
   - Send MIDI clock from DAW
   - Verify optocoupler LED activity
   - Check PIC receives MIDI data

## 🎛️ Phase 2: Arduino Integration (Optional)

### Arduino Code Installation

1. **Use ONLY the Fixed Code**:
   ```bash
   # Upload ml303-arduino-code-FIXED.txt
   # NOT the original ml303-arduino-code.txt (has pin conflicts!)
   ```

2. **Pin Assignment Verification**:
   ```cpp
   // FIXED Pin Assignments (VERIFIED NO CONFLICTS):
   const int LCD_RS = 12, LCD_E = 11;           // LCD control
   const int LCD_D4 = 10, LCD_D5 = 9;          // LCD data
   const int LCD_D6 = 8, LCD_D7 = 7;           // LCD data
   const int BTN_RUN_STOP = 2, BTN_PATTERN = 3; // Buttons (interrupts)
   const int CLOCK_IN = 4, GATE_IN = 5;         // ML-303 monitoring
   const int GATE_OUT = 6;                      // Gate output
   const int MIDI_RX = A4, MIDI_TX = A5;       // Software serial MIDI
   const int DAC_CS = 13;                       // MCP4921 chip select
   ```

### Hardware Integration

1. **LCD Connection** (Standard Parallel):
   ```
   Arduino  →  LCD (SMH1602A)
   ─────────────────────────────
   5V       →  VCC (Pin 2)
   GND      →  GND (Pin 1)
   D12      →  RS  (Pin 4)
   D11      →  E   (Pin 6)
   D10      →  D4  (Pin 11)
   D9       →  D5  (Pin 12)
   D8       →  D6  (Pin 13)
   D7       →  D7  (Pin 14)
   
   CRITICAL: 10k pot between +5V and GND,
   wiper to V0 (Pin 3) for contrast!
   ```

2. **MCP4921 DAC** (for CV output):
   ```
   Arduino  →  MCP4921
   ─────────────────────
   5V       →  VCC (Pin 1)
   GND      →  VSS (Pin 7)
   D13      →  CS  (Pin 2)
   D11      →  SCK (Pin 3)
   D11      →  SDI (Pin 4)
                VOUT (Pin 8) → CV Output
   ```

3. **MIDI Interface**:
   ```
   6N138 Optocoupler Circuit:
   MIDI IN Pin 4 → 6N138 Pin 2 (via 220Ω)
   MIDI IN Pin 5 → 6N138 Pin 3 (via 220Ω)
   6N138 Pin 6   → Arduino A4 (RX)
   6N138 Pin 8   → +5V (via 4.7kΩ pullup)
   
   Arduino A5    → MIDI OUT Pin 5 (via 220Ω)
   ```

### Integration Testing

1. **Hardware Test Sequence**:
   ```cpp
   // Run from Arduino Serial Monitor (115200 baud):
   // 1. LCD test - should show "LCD TEST OK"
   // 2. DAC test - CV output 0V to ~4V sweep
   // 3. Pot test - read all 4 analog inputs
   // 4. MIDI test - send note on/off
   ```

2. **Memory Usage Check**:
   ```
   Expected: ~500 bytes SRAM usage
   Warning if < 200 bytes free
   Arduino Uno has 2KB total SRAM
   ```

## 🔬 Phase 3: Calibration & Testing

### VCO Calibration
1. Connect frequency counter to VCO output
2. Play middle C (MIDI note 60)
3. Adjust VCO trimmer for 261.63 Hz
4. Verify octave tracking across keyboard range

### VCF Calibration  
1. Set filter cutoff to middle position
2. Play chromatic scale
3. Adjust filter tracking trimmer
4. Filter should track keyboard 1:1

### VCA Calibration
1. Set accent level trimmer
2. Verify smooth amplitude control
3. Check for audio breakthrough at zero level

### System Integration Test
1. **Original Mode**: ML-303 works standalone
2. **Arduino Mode**: Enhanced features active
3. **Mode Switching**: Seamless transition
4. **MIDI Sync**: External clock synchronization

## 🚨 Critical Troubleshooting

### No Power
- Check input voltage (12V DC)
- Verify 78S05 installation and heat sinking
- Check RECOM 0515S pinout and soldering

### No Sound  
- Verify ±15V analog supply voltages
- Check AN6562 VCA installation
- Test audio path with signal tracer

### Sequencer Issues
- Check PIC18LF**LF**452 (must be LF variant)
- Verify 10MHz crystal and load capacitors
- Check firmware upload success

### Arduino Integration Problems
- **LCD blank**: Check contrast pot adjustment
- **Pin conflicts**: Verify using FIXED code only
- **Memory issues**: Monitor SRAM usage
- **MIDI problems**: Check optocoupler orientation

### Filter Tracking Issues
- Verify 2SK30 JFET matching and orientation
- Check precision capacitor values (±1% tolerance)
- Calibrate filter tracking trimmer

## 📊 Success Metrics

### Audio Performance
- [ ] Full frequency range (C2 to C6)
- [ ] Smooth filter sweep
- [ ] Proper accent dynamics
- [ ] Clean audio output

### Sequencer Performance  
- [ ] 16-step patterns record/playback
- [ ] MIDI sync lock (no drift)
- [ ] Pattern storage/recall
- [ ] Real-time parameter control

### Arduino Enhancement
- [ ] LCD displays parameters
- [ ] Extended pattern memory
- [ ] CV output functional
- [ ] MIDI I/O working
- [ ] Mode switching seamless

## 📚 Reference Documentation

### Critical Files (Use Only These):
- `ml303-arduino-code-FIXED.txt` - Arduino code with pin conflicts resolved
- `ml303-arduino-wiring.html` - Updated wiring diagrams
- `CODE_REVIEW_FIXES.md` - Complete analysis of fixes made

### Additional Resources:
- `firmware/` - PIC firmware versions (V5.5 Final recommended)
- `EXISTING_ML303_MODIFICATIONS.md` - For existing ML-303 owners
- `FINAL_BUILD_REVIEW.md` - Overall project verification

## ⚡ Quick Start Summary

1. **Build core ML-303** (power → digital → analog → calibrate)
2. **Test thoroughly** before Arduino integration
3. **Use ONLY fixed Arduino code** (original has pin conflicts)
4. **Follow exact wiring** (diagrams corrected for pin fixes)
5. **Test each subsystem** before final integration
6. **Calibrate carefully** for professional results

**Build Time Estimate**: 20-40 hours (depending on experience)
**Difficulty Level**: Advanced (analog circuits, microcontroller programming)
**Success Rate**: High (with proper component sourcing and careful assembly)

---

*This guide incorporates all critical fixes discovered during code review and testing. Follow exactly for best results.*