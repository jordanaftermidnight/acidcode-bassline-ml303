# Critical Corrections to ML-303 Documentation

## Major Corrections Identified

### 1. Microcontroller Specification
**❌ INCORRECT in README.md**: PIC18F452  
**✅ CORRECT**: **PIC18LF452-I/P** (Low-voltage variant)

- The "LF" designation indicates the low-voltage version (2.0-5.5V)
- The "-I/P" suffix indicates Industrial temperature range, PDIP package
- Assembly source shows PIC18F452 for compatibility, but actual part is 18LF452

### 2. VCA IC Options - More Complete List
**❌ INCOMPLETE in README.md**: Only mentioned BA6110/BA662  
**✅ COMPLETE LIST**:
- **AN6562** (IC11, IC16) - Primary VCA option
- **BA6110** (IC152) - Alternative VCA option  
- **BA662** (IC159) - Original TB-303 VCA option

### 3. Audio Output Driver
**❌ MISSING in README.md**: Audio output driver IC  
**✅ CORRECTION**: **LA4140** or **AN7112E** (IC154)
- Power amplifier for audio output stage
- LA4140 is preferred, AN7112E is alternative

### 4. Additional Critical ICs Not Mentioned
**✅ ADDITIONS NEEDED**:
- **CNY17** (IC153) - Optocoupler for MIDI isolation
- **LM2904N** (IC4) - Dual op-amp
- **74174** (IC9) - Hex D flip-flop  
- **4050** (IC10) - Hex non-inverting buffer
- **4066** (IC12) - Quad analog switch
- **4013** (IC13) - Dual D flip-flop

### 5. Power Supply Corrections
**❌ INCOMPLETE**: Missing DC-DC converter specification  
**✅ CORRECTION**: **RECOM 0515S** DC/DC converter (1.2W)
- Converts +5V to ±15V for analog circuitry
- Critical for proper analog operation

### 6. Transistor Specifications - More Precise
**✅ REFINEMENTS**:
- **2SC945** or **2SC536F** (not just 2SC536)
- **2SC1583F** - Specific for certain positions
- **2SC2291F** - High-frequency transistor for specific circuit areas

### 7. Capacitor Specifications - Missing Details
**❌ INCOMPLETE**: Film capacitor specifications  
**✅ DETAILED CORRECTIONS**:

#### VCF (Filter) Capacitors - Critical for Sound:
- **18nF** (460885-PT Conrad) - VCF timing capacitor
- **33nF** (500760-LN Conrad) - VCF components (5 pieces)
- **100nF** (501047-PT Conrad) - VCF components (2 pieces, ±1%)

#### VCO (Oscillator) Capacitors:
- **10nF** (500868-LN Conrad) - VCO timing (2 pieces)
- **1nF** (CY 22-3 1,0N Reichelt) - JINGUAN 1% precision for VCO

### 8. Trimmer Specifications - Critical for Calibration
**✅ ADDITIONS**:
- **5K high-precision** (424404-LN Conrad, 962-20 5,0K Reichelt)
- **50K high-precision** (424439-LN Conrad)  
- **500K high-precision** (424463-LN Conrad)
- **PT10LV 10K** (PIHER 10-L 10K Reichelt)
- **PT10LV 100Ω** (PIHER 10-L 100 Reichelt)

### 9. Switch Specifications
**✅ DETAILED SPECS**:
- **Tactile switches**: DELTRON 705268-PT (24 pieces)
- **Switch caps**: DELTRON MULTIMEC 11.5MM (24 pieces)
- **Toggle switches**: T 217 (5 pieces for mode selection)

### 10. Crystal Oscillator
**✅ ADDITION**: **10.0000 MHz crystal** (10-HC49U-S or 10-HC18)
- Required for microcontroller timing
- Critical for MIDI timing accuracy

### 11. EEPROM Specification
**✅ ADDITION**: **24C64 or 24C65** (ST 24C64 BN6)
- Pattern storage memory
- I2C interface for microcontroller

### 12. Power Supply Specifications
**✅ CORRECTIONS**:
- **78S05** (µA 78S05 Reichelt) - Not standard 7805
- **Multifuse 500mA** (551244-LN Conrad) - Resettable fuse
- **DC Jack 2.5MM** (HEBG 25 Reichelt) - Power input

### 13. Metal Film Resistor Requirements
**✅ CRITICAL ADDITION**: **17x 200KΩ metal film** resistors
- These are precision components, not standard carbon film
- Critical for analog circuit stability and noise performance
- **27KΩ metal film** (1 piece) also required

### 14. LCD Module Specification
**✅ DETAILED SPEC**: **LCD162C** (Reichelt) or PLED display alternative
- 16x2 character display
- Standard HD44780 controller
- 6.8Ω current limiting resistor for LED backlight

## Summary of Critical Parts Often Missed

1. **PIC18LF452-I/P** (not PIC18F452)
2. **RECOM 0515S DC/DC converter** 
3. **AN6562 VCA chips** (primary option)
4. **LA4140 audio output driver**
5. **CNY17 MIDI optocoupler**
6. **High-precision film capacitors** for VCF/VCO
7. **Metal film precision resistors**
8. **Multiple trimmer potentiometers** for calibration

## Voltage Level Corrections

The V5 board voltages mentioned (-16.828V, -6.033V) appear to be **test point measurements** rather than supply voltages. The actual supply voltages are:
- **+12V** (main supply)
- **+5V** (digital logic)  
- **±15V** (analog rails from DC/DC converter)
- **-12V** (negative supply)

## Impact of These Corrections

These corrections are **critical for successful builds**:
- Wrong microcontroller = firmware won't load
- Missing DC/DC converter = no analog section operation
- Wrong VCA = no audio output
- Missing precision components = poor filter tracking and unstable tuning
- Wrong capacitor values = filter won't sound like TB-303

**All documentation should be updated with these corrections immediately.**