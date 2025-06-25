# ML-303 Wiring Diagram Collection

This directory contains SVG image files for all major wiring and circuit diagrams used in the ML-303 project.

## Available Diagrams

### Core Integration
- **`arduino_integration.svg`** - Complete Arduino Uno to ML-303 wiring diagram with fixed pin assignments
- **`ml303_interface_connections.svg`** - ML-303 test points and connection locations

### Electronic Circuits  
- **`midi_interface_6N138.svg`** - Standard MIDI input/output circuit using 6N138 optocoupler
- **`mcp4921_dac.svg`** - 12-bit DAC for control voltage output  
- **`cd4049_overdrive.svg`** - Simple overdrive/distortion circuit using CD4049

### Construction Guides
- **`stripboard_layouts.svg`** - Stripboard construction layouts for all circuits

## Viewing the Diagrams

### In Web Browser
All SVG files can be opened directly in any modern web browser:
```bash
open docs/wiring_diagrams/arduino_integration.svg
```

### In Graphics Applications
SVG files are compatible with:
- Adobe Illustrator
- Inkscape (free)
- GIMP
- Vector graphics editors
- Most image viewers

### Converting to Other Formats
To convert SVG to PNG/JPG for documentation:
```bash
# Using ImageMagick (if installed)
convert arduino_integration.svg arduino_integration.png

# Using Inkscape command line
inkscape arduino_integration.svg --export-type=png --export-dpi=300
```

## Key Features

### Arduino Integration Diagram
- **Pin assignments**: All verified to eliminate conflicts from original code
- **Color coding**: Power (red), ground (black), signals (green), LCD data (yellow)
- **Component details**: Complete connection tables and specifications
- **Safety warnings**: Critical power supply and polarity protection notes

### MIDI Interface Circuit
- **Standard compliance**: Full MIDI 1.0 electrical specification
- **6N138 optocoupler**: Complete isolation between devices
- **Component values**: All resistor values and part numbers specified
- **Input/Output**: Both MIDI IN and MIDI OUT circuits shown

### MCP4921 DAC Circuit
- **12-bit resolution**: 4096-step control voltage output
- **SPI interface**: Hardware SPI connection to Arduino
- **Power supply**: Single +5V operation with internal voltage reference
- **Output range**: 0-4.096V for ML-303 CV input

### CD4049 Overdrive
- **Dual inverter**: Cascaded CMOS inverters for harmonic distortion  
- **Power options**: ±15V dual supply or +9V single supply operation
- **Simple design**: Minimal parts count for easy construction
- **Level control**: 100kΩ potentiometer for output adjustment

### Stripboard Layouts
- **Hole-by-hole layouts**: Exact component placement and track cutting
- **Grid references**: Alphanumeric grid for precise positioning
- **Construction notes**: Track cuts, component orientation, wiring guides
- **Size specifications**: Board dimensions for each circuit

## Important Notes

### Pin Assignment Verification
**The Arduino integration diagram shows FIXED pin assignments that resolve all conflicts from the original code:**
- LCD: D12(RS), D11(E), D10-D7(Data)
- MIDI: A4(RX), A5(TX) 
- DAC: D13(CS), D11(SCK/MOSI shared)
- Controls: D2-D6 for buttons and I/O

### Safety Warnings
- **ML-303 sequencer board has NO reverse polarity protection**
- Always verify power connections with continuity tester before power-up
- MIDI ground connections can create misleading continuity readings

### Construction Quality
- Use IC sockets for all integrated circuits
- Keep wiring short to minimize noise and interference  
- Test all connections before final assembly
- Add bypass capacitors near all IC power pins

---

*These diagrams complement the interactive HTML wiring guides and provide printable references for construction and troubleshooting.*