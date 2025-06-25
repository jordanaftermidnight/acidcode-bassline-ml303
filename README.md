# Acidcode Bassline ML-303 - Complete Project Documentation

A comprehensive Roland TB-303 clone synthesizer project featuring analog circuitry with digital sequencer control, Arduino integration, and multiple firmware versions.

## 🎛️ Project Overview

The Acidcode Bassline ML-303 is a faithful TB-303 clone that combines:
- **Analog audio path** - VCO, VCF, VCA using original component types
- **Digital sequencer** - PIC microcontroller based with MIDI support
- **Arduino enhancement** - Modern integration and expansion capabilities
- **Multiple board versions** - V5 and V6 hardware iterations
- **Comprehensive firmware** - Multiple firmware versions with different features

## ⚠️ Critical Safety Warning

**THE SEQUENCER BOARD IS NOT REVERSE-POLARITY PROTECTED!**
- Always verify VDC wiring with continuity tester before powering up
- Do not rely only on GND continuity check (GND is also connected via MIDI)
- Double-check all power connections before first power-on

## 📁 Repository Structure

```
├── README.md                           # Complete build guide (start here)
├── CREDITS.md                          # 🌟 FULL CREDITS - Original creators and community
├── MODIFICATION_INDEX.md               # 🎯 CHOOSE YOUR PATH - Navigation guide
├── EXISTING_ML303_MODIFICATIONS.md    # Already have ML-303? Start here
├── OTHER_BASSLINE_MODIFICATIONS.md    # x0xb0x, TD-3, MB-33 modifications  
├── CORRECTIONS.md                      # Critical technical corrections
├── FINAL_BUILD_REVIEW.md              # Build verification and logic check
├── build_instructions_v5/              # V5 German build documentation
├── build_instructions_v6/              # V6 English build documentation  
├── firmware/                           # All firmware versions
│   ├── Matze/                         # Alternative firmware builds
│   │   ├── fw501alpha/                # V5.01 Alpha source code
│   │   └── mlv4/                      # ML V4 source code
│   └── Transistor/                    # Main firmware releases
│       ├── 6.1/                       # Latest firmware with manual
│       └── *.syx                      # Various firmware versions
├── ml303-arduino-code.txt             # Arduino integration firmware
├── ml303-arduino-wiring.html          # Arduino wiring diagrams
├── ml303-sequencer-mod.html           # Hardware modification guide
└── ml303-test-sketch.txt              # Arduino testing code
```

## 🎯 **QUICK START - Choose Your Situation:**

| Your Situation | Go To |
|----------------|-------|
| **Want to build ML-303 from scratch** | Continue reading this README |
| **Have working ML-303, want to enhance it** | [EXISTING_ML303_MODIFICATIONS.md](EXISTING_ML303_MODIFICATIONS.md) |
| **Have x0xb0x, TD-3, or other TB-303 clone** | [OTHER_BASSLINE_MODIFICATIONS.md](OTHER_BASSLINE_MODIFICATIONS.md) |
| **Need guidance on which approach to take** | [MODIFICATION_INDEX.md](MODIFICATION_INDEX.md) |

## 🔧 Hardware Specifications

### V5 Board Details
- **Test Point Voltages**: -16.828V (buttons), -6.033V (LEDs)
- **Supply Voltages**: +12V, +5.333V, ±15V (from DC/DC converter)
- **Microcontroller**: PIC18LF452-I/P (Low-voltage variant)
- **VCA Options**: AN6562 (primary), BA6110, or BA662 (original)
- **Audio Driver**: LA4140 or AN7112E power amplifier
- **Critical Components**: 2SK30-O/Y/GR JFETs, precision film capacitors, metal film resistors

### Key Components
- **Oscillator**: Sawtooth VCO using 2SC945/2SC536F transistors
- **Filter**: TB-303 style resonant lowpass using 2SK30 JFETs
- **VCA**: AN6562 (primary), BA6110, or BA662 integrated circuits
- **Audio Output**: LA4140 or AN7112E power amplifier
- **Sequencer**: PIC18LF452-I/P with LCD and MIDI support
- **Power**: RECOM 0515S DC/DC converter for ±15V analog supplies
- **MIDI Isolation**: CNY17 optocoupler
- **Digital Logic**: 74174, 4050, 4066, 4013 support ICs

## 🎵 Firmware Features

### Available Versions
- **V5.5 Final** - Stable release
- **V6.1** - Latest with comprehensive manual
- **V7 Beta** - Experimental features

### Core Features
- **Pattern Storage**: 16 steps max, 64 patterns
- **MIDI Modes**: Master/Slave/Key-In/Key-Out/Silent
- **Tempo Range**: 50-250 BPM
- **Built-in Patterns**: Classic acid patterns included
- **Real-time Control**: Live parameter adjustment

## 🔌 Arduino Integration

The project includes Arduino enhancement capabilities:

### Features
- **LCD Display**: 16x2 character display with standard parallel interface
- **MIDI Integration**: Full MIDI I/O with timing sync
- **Parameter Monitoring**: Real-time pot reading and display
- **Pattern Enhancement**: Extended pattern storage and editing
- **CV Output**: DAC-based control voltage generation

### Hardware Requirements
- Arduino Micro or similar
- 16x2 LCD (standard HD44780 parallel interface)
- 10k potentiometer for LCD contrast control
- MCP4921 DAC for CV output
- Standard MIDI interface circuit
- Various supporting components

## 🛠️ Build Instructions

### Phase 1: Basic ML-303 Build
1. **Source Components** - Use provided Reichelt part numbers
2. **PCB Assembly** - Follow component placement diagrams
3. **Wiring** - Connect analog and digital boards per schematics
4. **Power Testing** - Verify all voltages before connecting sensitive components
5. **Firmware Installation** - Load appropriate firmware version

### Phase 2: Arduino Integration (Optional)
1. **Trace Modifications** - Carefully cut specified PCB traces
2. **Arduino Wiring** - Connect monitoring and control signals
3. **Software Installation** - Upload test sketch first, then full firmware
4. **Testing** - Verify all functions in both original and enhanced modes

## 📋 Component Lists

### V5 Capacitors (Reichelt Part Numbers)
- **Film Caps**: MKH400/MKH250 series in various values
- **Electrolytics**: RAD series with specific voltage ratings
- **Tantalum**: 1µF/35V (2 pieces)
- **Ceramic**: 100nF (2 pieces)

### Semiconductors  
- **Switching Diodes**: 14x 1N4148
- **Rectifiers**: 4x 1N4001  
- **Zener**: 1x 6.2V (ZD 6,2)
- **Transistors**: 24x 2SC945 or 2SC536F, 11x 2SA733P
- **Special Transistors**: 3x 2SC1583F, 1x 2SC2291F
- **JFETs**: 2x 2SK30 variants (1x O-type, 1x Y/GR-type)

### Critical ICs
- **Microcontroller**: PIC18LF452-I/P
- **EEPROM**: 24C64 or 24C65
- **VCA**: 2x AN6562 (primary), or BA6110/BA662 alternatives
- **Audio Driver**: LA4140 or AN7112E
- **Op-Amp**: LM2904N
- **Digital Logic**: 74174, 4050, 4066, 4013
- **MIDI**: CNY17 optocoupler
- **Power**: 78S05 regulator, RECOM 0515S DC/DC converter

### Precision Components (Critical for Proper Operation)
- **Metal Film Resistors**: 17x 200KΩ, 1x 27KΩ  
- **VCF Capacitors**: 18nF (±1%), 5x 33nF, 2x 100nF (±1%)
- **VCO Capacitors**: 2x 10nF, 1x 1nF (1% precision)
- **Trimmers**: 5K, 50K, 500K high-precision types

### Controls (Conrad Electronics)
- **Blue**: 707694-13
- **White/Gray**: 707660-13
- **Yellow**: 707686-13
- **Red**: 707678-13
- **Black**: 707651-13

## 🎹 Pattern Programming

### Pattern Format
Each pattern includes:
- **Name**: 8 characters maximum
- **Length**: 1-16 steps
- **Tempo**: 50-250 BPM
- **Per Step**: Note, Down/Up octave, Accent, Slide, Timing

### Example Pattern
```
Pattern: CITRIC-1
Steps: 16
BPM: 142
01: A  Down=1 Up=0 Accent=0 Slide=0 Time=BLACK
02: A  Down=1 Up=0 Accent=1 Slide=0 Time=WHITE
...
```

## 🔧 Troubleshooting

### Common Issues
1. **No Power** - Check power supply wiring and fuse
2. **No Sound** - Verify VCA installation and supply voltages
3. **Filter Not Working** - Check 2SK30 JFET installation and bias
4. **Sequencer Problems** - Verify firmware installation and MIDI connections

### Arduino Integration Issues
1. **No Clock Detection** - Check PIC to Arduino pin 2 connection
2. **LCD Not Working** - Check parallel connections, verify contrast setting
3. **Original Function Lost** - Verify jumpers on cut traces
4. **MIDI Problems** - Check optocoupler orientation and cable connections

## 📚 Additional Documentation

### German Documentation Translation
Key German terms:
- **Bestueckungsplan** = Component placement plan
- **Einkaufsliste** = Shopping list/BOM
- **Verdrahtung** = Wiring
- **Achtung** = Warning/Attention

### Technical References
- **TB-303 Service Manual** - Original Roland documentation
- **PIC18F452 Datasheet** - Microcontroller specifications  
- **BA6110/BA662 Datasheets** - VCA specifications
- **2SK30 Datasheet** - Critical JFET specifications

## 🎮 Operating Instructions

### Basic Operation
1. **Power On** - System initializes and shows firmware version
2. **Pattern Selection** - Use pattern buttons to select 1-64
3. **Recording** - Enter notes using keyboard in real-time or step mode
4. **Playback** - Press RUN to start sequence
5. **Parameter Adjustment** - Use knobs for real-time sound shaping

### Advanced Features
- **MIDI Sync** - Can sync to external clock or send clock
- **Pattern Chaining** - Link patterns for longer sequences
- **Accent/Slide Programming** - Add dynamics and note connections
- **Tempo Changes** - Adjust tempo per pattern or globally

## 📄 License and Credits

### Acknowledgments
This open source project builds upon the incredible work of the original creators:
- **Acidcode (Mathias Märker)** - Original ML-303 hardware design and engineering
- **Transistor** - Primary firmware development and MIDI implementation
- **Matze** - Alternative firmware implementations and enhancements
- **Christian Wiesner (Midimonster.de)** - Documentation and community preservation
- **x0xb0x Team (Limor Fried/Adafruit)** - Open source hardware pioneering
- **Entire 303 Community** - Forums, builders, and knowledge sharers

**Full credits and community acknowledgments**: See [CREDITS.md](CREDITS.md)

### Open Source Additions
This repository contributes to the open source 303 community:
- **Arduino integration** and modern enhancement frameworks
- **English translations** of German documentation for accessibility
- **Multi-clone adaptation guides** for various TB-303 clones
- **Technical corrections** and verification for accuracy
- **Reverse engineered firmware analysis** for educational purposes
- **Community documentation** preservation and improvement

### Open Source License
This project embraces the open source spirit of the 303 clone community. Following the example of the x0xb0x (MIT License), this repository is intended for:
- **Educational use** - Learning and understanding TB-303 design principles
- **DIY building** - Enabling more people to build and enjoy 303 clones
- **Community improvement** - Collaborative enhancement and error correction
- **Knowledge preservation** - Ensuring these designs aren't lost to time

### Disclaimer
This project is for educational and personal use. Build at your own risk. Always follow proper electronics safety procedures. Respect the intellectual property and hard work of all original creators and contributors. Commercial use should benefit and give back to the community.

## 🔗 Related Projects

- **x0xb0x** - Alternative TB-303 clone
- **TB-303 Mods** - Various enhancement projects
- **Analog Sequencers** - Related sequencer projects

---

*For technical support and discussions, please refer to the original documentation and community forums.*