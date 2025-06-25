# Acidcode Bassline ML-303 - Open Source Project

A comprehensive Roland TB-303 clone synthesizer project featuring analog circuitry with digital sequencer control, Arduino integration, and complete source code analysis.

## Project Overview

The Acidcode Bassline ML-303 is a faithful TB-303 clone that combines:
- **Analog audio path** - VCO, VCF, VCA using original component types
- **Digital sequencer** - PIC microcontroller based with MIDI support
- **Arduino enhancement** - Modern integration and expansion capabilities
- **Complete source code** - Full firmware source with technical analysis
- **Professional documentation** - Build guides, testing procedures, troubleshooting

## Complete Firmware Source Code Available

We have the complete PIC18F452 assembly source code - a rare find in the TB-303 clone world.

- **Complete technical analysis** - [docs/FIRMWARE_ANALYSIS.md](docs/FIRMWARE_ANALYSIS.md)
- **Full assembly source** - `firmware/source/` directory
- **Pattern storage algorithms** - MIDI engine, real-time algorithms revealed
- **Modification ready** - Source code enables custom firmware development

## 🚀 Arduino Integration - Start Here!

**Want to add Arduino control to your ML-303?** 

👉 **[Go to Arduino Integration Guide](docs/wiring_diagrams/QUICK_START.md)** 👈

Add modern Arduino features to your ML-303 in about 1 hour:
- I2C communication with PIC microcontroller
- Foundation for LCD control, effects, and MIDI expansion
- Non-invasive installation (completely reversible)
- Only $13-33 in parts needed

## Repository Structure

```
├── docs/wiring_diagrams/        # ⭐ ARDUINO INTEGRATION GUIDES
│   ├── QUICK_START.md           # 🚀 Start here for Arduino integration  
│   ├── ML303_Arduino_Wiring_Diagram.png  # Professional wiring diagrams
│   ├── COMPLETE_BUILD_GUIDE.md  # Detailed step-by-step instructions
│   └── MERMAID_DIAGRAMS.md      # Interactive flowcharts
├── docs/                        # Technical Documentation
│   ├── FIRMWARE_ANALYSIS.md     # Complete source code analysis
│   ├── FIRMWARE_LOADING.md      # Programming procedures
│   └── modifications/           # Enhancement guides
├── firmware/source/             # Complete PIC18F452 assembly source
├── hardware/                    # Hardware build documentation
└── arduino/                     # Arduino code examples
```

## Build Your Own ML-303

| Your Goal | Start Here |
|-----------|------------|
| **Understand the firmware** | [docs/FIRMWARE_ANALYSIS.md](docs/FIRMWARE_ANALYSIS.md) |
| **Build ML-303 from scratch** | [docs/BUILD_GUIDE.md](docs/BUILD_GUIDE.md) |
| **Enhance existing ML-303** | [docs/modifications/EXISTING_ML303_MODIFICATIONS.md](docs/modifications/EXISTING_ML303_MODIFICATIONS.md) |
| **Modify other TB-303 clones** | [docs/modifications/OTHER_BASSLINE_MODIFICATIONS.md](docs/modifications/OTHER_BASSLINE_MODIFICATIONS.md) |
| **Test Arduino hardware** | [arduino/test_sketch.ino](arduino/test_sketch.ino) |

## Critical Safety Warning

**THE SEQUENCER BOARD IS NOT REVERSE-POLARITY PROTECTED!**
- Always verify VDC wiring with continuity tester before powering up
- Do not rely only on GND continuity check (GND is also connected via MIDI)
- Double-check all power connections before first power-on

## Hardware Specifications

### Core Components (V5)
- **Microcontroller**: PIC18LF452-I/P (Low-voltage variant, 5.333V)
- **VCA**: AN6562 (primary), BA6110, or BA662 alternatives
- **Audio Driver**: LA4140 or AN7112E power amplifier
- **Power**: +12V input, +5.333V digital, ±15V analog (RECOM 0515S)
- **Critical**: 2SK30 JFETs (matched pair), precision capacitors, metal film resistors

## Firmware Features

### Source Code Revealed
- **Complete PIC18F452 assembly source** - Professional real-time architecture
- **Revolutionary pattern encoding** - 2-byte storage format for 256 patterns × 16 steps
- **Advanced MIDI engine** - 24 PPQN sync with multiple modes
- **Sophisticated timing** - 6-tick subdivision per step
- **Educational value** - Learn TB-303 implementation secrets

### Available Versions
- **V5.5 Final** - Stable release (recommended for beginners)
- **V6.1** - Latest with comprehensive manual
- **V7 Beta** - Experimental features

## Arduino Integration

### Tested & Verified Code
- **ml303_enhanced.ino** - Complete Arduino enhancement system
- **test_sketch.ino** - Hardware testing before integration
- **Zero pin conflicts** - All issues resolved and verified
- **Memory optimized** - Uses <25% of Arduino Uno SRAM

### Features
- **16x2 LCD display** - Real-time parameter monitoring
- **MIDI expansion** - Enhanced MIDI features and routing
- **CV output** - MCP4921 DAC for control voltage generation
- **Pattern backup** - Extended pattern storage and management

## Related Open Source Projects

### Hardware Projects
- **[x0xb0x](https://github.com/x0xb0x/x0xb0x.github.io)** - Most successful open-source TB-303 clone
- **[Aciduino](https://github.com/midilab/aciduino)** - Arduino-based TB-303/TR-808 sequencer

### Software Projects  
- **[JS303](https://github.com/thedjinn/js303)** - Web-based TB-303 emulation
- **[JC-303](https://github.com/midilab/jc303)** - Cross-platform VST plugin
- **[Open303](https://github.com/maddanio/open303)** - Free TB-303 VST emulation

### Research Projects
- **[a1k0n/303](https://github.com/a1k0n/303)** - TB-303 resynthesis experiments
- **[303duino](https://github.com/treisti/303duino)** - Arduino Mozzi-based synth

## License and Credits

### Open Source License
This project uses **MIT License** for maximum community benefit. See [LICENSE](LICENSE) for details.

### Acknowledgments
**Full credits**: See [CREDITS.md](CREDITS.md) for comprehensive attribution to:
- **Acidcode (Mathias Märker)** - Original ML-303 hardware design
- **Transistor** - Primary firmware development
- **Matze** - Alternative firmware implementations  
- **Christian Wiesner** - Community documentation
- **x0xb0x Team** - Open source hardware pioneering
- **TB-303 Community** - Preservation and sharing of knowledge

## Community Contributions

This repository adds to the open source 303 community:
- **Complete firmware source analysis** - Rare technical deep dive
- **Arduino integration framework** - Modern enhancement approach
- **Multi-clone modification guides** - Broader compatibility
- **Professional documentation** - Build confidence and success
- **Educational resources** - Learn embedded music programming

---

*The ML-303 project preserves and enhances one of the most important TB-303 clone designs, making professional-quality documentation and rare source code available to the community for education, building, and further development.*