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
├── README.md                           # This file
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
├── ml303-test-sketch.txt              # Arduino testing code
└── Documentation/                      # Additional docs (auto-generated)
```

## 🔧 Hardware Specifications

### V5 Board Details
- **Button Voltage**: -16.828V
- **LED Voltage**: -6.033V  
- **Microcontroller**: PIC18F452
- **VCA Options**: BA6110 (preferred) or BA662
- **Critical Components**: 2SK30-O/Y/GR JFETs, original TB-303 transistors

### Key Components
- **Oscillator**: Sawtooth VCO using 2SC536/2SC945 transistors
- **Filter**: TB-303 style resonant lowpass using 2SK30 JFETs
- **VCA**: BA6110 or BA662 integrated circuits
- **Sequencer**: PIC-based with LCD and MIDI support

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
- **LCD Display**: 16x2 character display with I2C interface
- **MIDI Integration**: Full MIDI I/O with timing sync
- **Parameter Monitoring**: Real-time pot reading and display
- **Pattern Enhancement**: Extended pattern storage and editing
- **CV Output**: DAC-based control voltage generation

### Hardware Requirements
- Arduino Micro or similar
- 16x2 LCD with I2C backpack
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
- **Switching Diodes**: 15x 1N4148
- **Rectifiers**: 2x 1N4001
- **Zener**: 1x 6.2V
- **Transistors**: 20x 2SC536, 8x 2SA733
- **JFETs**: 2SK30 variants (critical for filter operation)

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
2. **LCD Not Working** - Try address 0x3F instead of 0x27, check I2C pullups
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

### Original Design
- **Acidcode** - Original ML-303 hardware design
- **Transistor** - Main firmware development  
- **Matze** - Alternative firmware implementations

### Arduino Integration
- Modern enhancement and documentation
- Additional firmware and examples
- Integration guides and modifications

### Disclaimer
This project is for educational and personal use. Build at your own risk. Always follow proper electronics safety procedures.

## 🔗 Related Projects

- **x0xb0x** - Alternative TB-303 clone
- **TB-303 Mods** - Various enhancement projects
- **Analog Sequencers** - Related sequencer projects

---

*For technical support and discussions, please refer to the original documentation and community forums.*