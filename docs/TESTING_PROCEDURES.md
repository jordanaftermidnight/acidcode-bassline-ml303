# ML-303 Comprehensive Testing Procedures

## 🎯 Testing Strategy Overview

This guide provides systematic testing procedures for every aspect of the ML-303 build, from basic power-on through advanced features. Follow in order for best results.

## ⚡ Phase 1: Power Supply Testing

### Test 1.1: Input Power Verification
**Equipment**: Multimeter, 12V DC adapter

```bash
Procedure:
1. Connect 12V adapter to ML-303 power input
2. Measure input voltage at power connector
3. Verify polarity (center positive/negative per design)

✅ Pass Criteria:
- Input voltage: 11.5V - 12.5V DC
- Correct polarity (no reverse voltage)
- Stable voltage under load
```

### Test 1.2: Regulated Supply Testing  
**Equipment**: Multimeter, oscilloscope

```bash
Procedure:
1. Power on ML-303
2. Measure at 78S05 output (digital supply)
3. Measure at RECOM 0515S outputs (analog supplies)
4. Check ripple with oscilloscope

✅ Pass Criteria:
- Digital supply: +5.333V ±0.1V
- Positive analog: +15V ±0.5V  
- Negative analog: -15V ±0.5V
- Ripple: <50mV peak-to-peak on all supplies
```

### Test 1.3: Current Consumption
**Equipment**: DC current meter

```bash
Procedure:
1. Insert current meter in series with 12V input
2. Measure quiescent current (sequencer only)
3. Measure active current (playing audio)

✅ Pass Criteria:
- Quiescent: <200mA
- Active (no audio): <300mA
- Active (with audio): <500mA
```

## 🖥️ Phase 2: Digital Section Testing

### Test 2.1: PIC Microcontroller
**Equipment**: Oscilloscope, logic analyzer (optional)

```bash
Procedure:
1. Power on, observe startup sequence
2. Check crystal oscillation (10MHz)
3. Verify firmware boot messages
4. Test basic button inputs

✅ Pass Criteria:
- Clean 10MHz crystal signal (no distortion)
- Startup display appears within 2 seconds
- Buttons respond without bouncing
- No watchdog resets or lockups
```

### Test 2.2: LCD Display
**Equipment**: Visual inspection

```bash
Procedure:
1. Check display initialization
2. Verify all character positions
3. Test contrast adjustment
4. Check for dead pixels or segments

✅ Pass Criteria:
- All characters clearly visible
- Contrast adjustable across full range
- No dead pixels or segments
- Smooth brightness control
```

### Test 2.3: MIDI Interface
**Equipment**: MIDI keyboard, DAW, MIDI monitor

```bash
Procedure:
1. Connect MIDI IN from keyboard/DAW
2. Send MIDI notes, CC, clock
3. Connect MIDI OUT to monitoring device
4. Verify bidirectional communication

✅ Pass Criteria:
- Receives all MIDI message types
- Accurate MIDI timing (no jitter)
- Transmits MIDI without errors
- Optocoupler isolation working
```

### Test 2.4: Pattern Memory
**Equipment**: None (functional test)

```bash
Procedure:
1. Record new pattern (16 steps)
2. Save to memory
3. Power cycle ML-303
4. Recall pattern from memory

✅ Pass Criteria:
- All 64 pattern slots accessible
- Patterns store/recall accurately
- No data corruption after power cycle
- EEPROM retains data indefinitely
```

## 🎵 Phase 3: Analog Audio Testing

### Test 3.1: VCO (Voltage Controlled Oscillator)
**Equipment**: Frequency counter, oscilloscope

```bash
Procedure:
1. Connect probe to VCO output
2. Play chromatic scale (C2 to C6)
3. Measure frequency at each note
4. Check waveform shape and stability

✅ Pass Criteria:
- Accurate 1V/octave scaling
- Clean sawtooth waveform
- Frequency stable (no drift)
- Full 4+ octave range
```

### Test 3.2: VCF (Voltage Controlled Filter)
**Equipment**: Audio analyzer, sine wave generator

```bash
Procedure:
1. Input white noise to filter
2. Sweep cutoff frequency control
3. Measure filter response curve
4. Test resonance at various settings

✅ Pass Criteria:
- Smooth cutoff sweep (no jumps)
- 24dB/octave rolloff (typical TB-303)
- Resonance up to self-oscillation
- No aliasing or digital artifacts
```

### Test 3.3: VCA (Voltage Controlled Amplifier)
**Equipment**: Audio analyzer, envelope generator

```bash
Procedure:
1. Apply constant audio to VCA input
2. Sweep accent control
3. Test slide functionality
4. Measure VCA response linearity

✅ Pass Criteria:
- Clean audio amplification (no distortion)
- Full dynamic range (silence to maximum)
- Smooth accent control
- Proper slide (legato) operation
```

### Test 3.4: Audio Output
**Equipment**: Audio analyzer, headphones/speakers

```bash
Procedure:
1. Play test patterns at various levels
2. Measure frequency response
3. Check for noise, hum, or distortion
4. Test output drive capability

✅ Pass Criteria:
- Clean audio output (no noise/hum)
- Adequate output level for standard gear
- No clipping at maximum accent
- Good frequency response (50Hz-15kHz)
```

## 🎛️ Phase 4: Arduino Integration Testing

### Test 4.1: Arduino Hardware
**Equipment**: Multimeter, Arduino Serial Monitor

```bash
Procedure:
1. Upload FIXED Arduino code
2. Open Serial Monitor (115200 baud)
3. Run hardware test function
4. Verify all subsystems

Expected Serial Output:
> ML-303 Arduino Enhancement v1.0
> Initializing...
> === HARDWARE TEST ===
> LCD: OK
> DAC: OK
> Pot A0: [value 0-1023]
> Pot A1: [value 0-1023]  
> Pot A2: [value 0-1023]
> Pot A3: [value 0-1023]
> MIDI: OK
> Free SRAM: [>1500 bytes]
> === TEST COMPLETE ===

✅ Pass Criteria:
- All hardware tests pass
- SRAM usage <500 bytes (plenty free)
- No compilation or runtime errors
- Stable operation (no resets)
```

### Test 4.2: LCD Integration
**Equipment**: Visual inspection, contrast pot

```bash
Procedure:
1. Check LCD displays pattern info
2. Test parameter display updates
3. Verify real-time value changes
4. Test display in all modes

✅ Pass Criteria:
- Clear, readable display
- Real-time parameter updates
- All display modes functional
- Contrast properly adjustable
```

### Test 4.3: MIDI Enhancement
**Equipment**: MIDI keyboard, DAW

```bash
Procedure:
1. Test Arduino MIDI input/output
2. Send/receive MIDI CC for parameters
3. Verify MIDI clock sync
4. Test extended MIDI features

✅ Pass Criteria:
- Bidirectional MIDI communication
- Parameter control via MIDI CC
- Accurate clock synchronization
- No MIDI timing issues
```

### Test 4.4: CV Output (DAC)
**Equipment**: Voltmeter, VCO or CV-capable device

```bash
Procedure:
1. Connect CV output to measurement device
2. Play chromatic scale
3. Measure CV output voltages
4. Verify 1V/octave scaling

✅ Pass Criteria:
- Accurate 1V/octave output
- Stable CV voltage (no drift)
- Clean DC output (no ripple)
- Proper scaling across full range
```

## 🔄 Phase 5: System Integration Testing

### Test 5.1: Mode Switching
**Equipment**: None (functional test)

```bash
Procedure:
1. Start in original ML-303 mode
2. Switch to Arduino enhancement mode
3. Verify all functions work in both modes
4. Test seamless switching

✅ Pass Criteria:
- Both modes fully functional
- No loss of functionality in either mode
- Smooth transitions between modes
- No interference between systems
```

### Test 5.2: Synchronization Testing
**Equipment**: MIDI clock source, oscilloscope

```bash
Procedure:
1. Send external MIDI clock
2. Monitor ML-303 and Arduino timing
3. Verify tight synchronization
4. Test long-term stability

✅ Pass Criteria:
- Both systems lock to external clock
- No timing drift over extended play
- Stable sync even with tempo changes
- No missed clock events
```

### Test 5.3: Extended Pattern Features
**Equipment**: None (functional test)

```bash
Procedure:
1. Create patterns longer than 16 steps
2. Test pattern chaining
3. Verify extended parameter storage
4. Test pattern backup/restore

✅ Pass Criteria:
- Extended patterns work correctly
- Pattern chaining seamless
- No data loss during operations
- Backup/restore functions properly
```

## 🎵 Phase 6: Musical Performance Testing

### Test 6.1: Classic TB-303 Patterns
**Equipment**: Audio recording setup

```bash
Test Patterns:
1. "I Feel Love" style sequence
2. Classic acid house pattern
3. Fast 16th note sequence
4. Slow, melodic sequence

✅ Pass Criteria:
- Accurate TB-303 sound character
- Proper accent and slide behavior
- Clean audio at all tempos
- Authentic "acid" sound
```

### Test 6.2: Filter Sweep Testing
**Equipment**: Audio analyzer or ears

```bash
Procedure:
1. Play repeating pattern
2. Slowly sweep filter cutoff
3. Add resonance gradually
4. Test filter tracking

✅ Pass Criteria:
- Smooth filter sweeps
- No clicking or stepping
- Resonance up to self-oscillation
- Proper keyboard tracking
```

### Test 6.3: Real-Time Performance
**Equipment**: MIDI keyboard, DAW

```bash
Procedure:
1. Play live via MIDI keyboard
2. Adjust parameters in real-time
3. Record long performance session
4. Check for dropouts or glitches

✅ Pass Criteria:
- Responsive to live playing
- No audio dropouts or glitches
- Stable during long sessions
- Parameters respond smoothly
```

## 🔧 Phase 7: Stress Testing

### Test 7.1: Thermal Testing
**Equipment**: Thermometer, extended runtime

```bash
Procedure:
1. Run ML-303 continuously for 4+ hours
2. Monitor component temperatures
3. Check for thermal drift
4. Verify stable operation

✅ Pass Criteria:
- All components within safe temp range
- No thermal drift in tuning/timing
- Stable operation over extended periods
- No thermal shutdown or protection
```

### Test 7.2: Power Supply Stress
**Equipment**: Variable power supply

```bash
Procedure:
1. Vary input voltage (10V to 14V)
2. Test under various load conditions
3. Check regulation under stress
4. Verify protection circuits

✅ Pass Criteria:
- Stable operation across voltage range
- Good regulation under load
- No damage from voltage variations
- Protection circuits function if present
```

### Test 7.3: Memory Stress (Arduino)
**Equipment**: Arduino Serial Monitor

```bash
Procedure:
1. Run pattern creation/deletion cycles
2. Fill all pattern memory slots
3. Test rapid mode switching
4. Monitor memory fragmentation

✅ Pass Criteria:
- No memory leaks detected
- Stable operation with full memory
- No corruption during rapid operations
- Memory usage remains constant
```

## 📊 Testing Results Documentation

### Test Report Template
```
ML-303 Testing Report
Date: ___________
Tester: ___________
Build Version: ___________

Phase 1 - Power Supply:
[ ] Test 1.1: Input Power - PASS/FAIL
[ ] Test 1.2: Regulated Supplies - PASS/FAIL  
[ ] Test 1.3: Current Consumption - PASS/FAIL

Phase 2 - Digital Section:
[ ] Test 2.1: PIC Microcontroller - PASS/FAIL
[ ] Test 2.2: LCD Display - PASS/FAIL
[ ] Test 2.3: MIDI Interface - PASS/FAIL
[ ] Test 2.4: Pattern Memory - PASS/FAIL

Phase 3 - Analog Audio:
[ ] Test 3.1: VCO - PASS/FAIL
[ ] Test 3.2: VCF - PASS/FAIL
[ ] Test 3.3: VCA - PASS/FAIL
[ ] Test 3.4: Audio Output - PASS/FAIL

Phase 4 - Arduino Integration:
[ ] Test 4.1: Arduino Hardware - PASS/FAIL
[ ] Test 4.2: LCD Integration - PASS/FAIL
[ ] Test 4.3: MIDI Enhancement - PASS/FAIL
[ ] Test 4.4: CV Output - PASS/FAIL

Phase 5 - System Integration:
[ ] Test 5.1: Mode Switching - PASS/FAIL
[ ] Test 5.2: Synchronization - PASS/FAIL
[ ] Test 5.3: Extended Features - PASS/FAIL

Phase 6 - Musical Performance:
[ ] Test 6.1: Classic Patterns - PASS/FAIL
[ ] Test 6.2: Filter Sweeps - PASS/FAIL
[ ] Test 6.3: Real-Time Performance - PASS/FAIL

Phase 7 - Stress Testing:
[ ] Test 7.1: Thermal - PASS/FAIL
[ ] Test 7.2: Power Supply Stress - PASS/FAIL
[ ] Test 7.3: Memory Stress - PASS/FAIL

Overall Result: PASS/FAIL
Notes: ___________
```

## 🚨 Common Failure Modes & Solutions

| Symptom | Likely Cause | Test to Confirm | Solution |
|---------|--------------|-----------------|----------|
| No power | Power supply issue | Test 1.1, 1.2 | Check connections, replace PSU components |
| No display | LCD or contrast | Test 2.2 | Adjust contrast pot, check LCD connections |
| No MIDI | Optocoupler or wiring | Test 2.3 | Check 6N138 circuit, verify MIDI cables |
| No sound | Analog section | Test 3.1-3.4 | Check ±15V supply, analog components |
| Wrong pitch | VCO calibration | Test 3.1 | Adjust VCO trimmer, check crystal |
| Filter issues | VCF problems | Test 3.2 | Check 2SK30 JFETs, precision caps |
| Arduino errors | Code or wiring | Test 4.1 | Use FIXED code, check pin assignments |

## ⚡ Quick Test Summary

**Minimum Acceptable Tests** (essential for basic operation):
- Power supply voltages (Test 1.2)
- PIC boot and display (Test 2.1, 2.2)  
- Audio output present (Test 3.4)
- Arduino hardware test (Test 4.1 if applicable)

**Full Qualification Tests** (for complete verification):
- All Phase 1-7 tests completed
- All tests PASS
- Musical performance acceptable
- Long-term stability verified

---

*Follow this testing protocol to ensure your ML-303 meets professional standards and will provide years of reliable service.*