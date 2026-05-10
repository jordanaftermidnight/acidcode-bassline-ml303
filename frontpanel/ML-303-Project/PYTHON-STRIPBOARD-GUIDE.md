# Python Stripboard Layout Generator for ML-303

## Overview

I've created two Python scripts to generate stripboard layouts for your ML-303 button replacement project:

1. **stripboard-generator.py** - Basic generator with predefined layouts
2. **stripboard-generator-advanced.py** - Interactive designer with save/load capabilities

## Quick Start

### Basic Generator

```bash
cd /Users/jordan_after_midnight/Desktop/ML-303-Project
python3 stripboard-generator.py
```

This creates:
- `GENERATED-LAYOUTS/adapter-layout.txt` - 3-pin to 4-pin adapter
- `GENERATED-LAYOUTS/matrix-layout.txt` - ATmega328P matrix controller

### Interactive Designer

```bash
python3 stripboard-generator-advanced.py
```

Features:
- Create custom layouts interactively
- Save/load designs as JSON
- Export to detailed ASCII files
- Batch generation of standard layouts

## Using the Basic Generator

The script generates ASCII representations like this:

```
ML-303 3-PIN BUTTON ADAPTER
===========================

COMPONENT SIDE VIEW:
-------------------
     1  2  3  4  5  6  7  8  9 10
   +---+---+---+---+---+---+---+---+---+---+
 A | o | o | o | o | X | o | o | o | o | o |
   +---+---+---+---+---+---+---+---+---+---+
 B | o | B | B | o | X | - | - | o | o | o |
   +---+---+---+---+---+---+---+---+---+---+
 C | o | B | B | o | X | o | - | - | o | o |
   +---+---+---+---+---+---+---+---+---+---+
 D | o | o | o | o | X | o | o | o | o | o |
   +---+---+---+---+---+---+---+---+---+---+
```

Legend:
- `o` = Hole
- `X` = Track cut
- `B` = Button
- `-` = Wire
- `R` = Resistor
- `C` = Capacitor

### Customizing Layouts

Edit the functions in `stripboard-generator.py`:

```python
def create_3pin_adapter() -> StripboardDesign:
    """Create layout for 3-pin to 4-pin button adapter"""
    components = [
        Component(ComponentType.BUTTON, (1, 0), (2, 1), "12x12mm"),
        Component(ComponentType.WIRE, (1, 1), (1, 5), "Bridge"),
        # Add more components here
    ]
    
    cuts = [(0, 4), (1, 4), (2, 4), (3, 4)]  # Track cuts
    
    return StripboardDesign(
        width=10,
        height=4,
        components=components,
        cuts=cuts,
        title="ML-303 3-PIN BUTTON ADAPTER"
    )
```

## Using the Interactive Designer

### Main Menu Options

1. **Create custom layout** - Design from scratch
2. **Load saved design** - Edit existing designs  
3. **Generate standard layouts** - Create preset ML-303 layouts
4. **Batch export** - Export all saved designs
5. **Exit**

### Creating a Custom Layout

```
CUSTOM STRIPBOARD LAYOUT CREATOR
================================

Board width (holes): 20
Board height (rows): 10
Layout title: ML-303 Function Buttons

Options:
1. Add component
2. Add track cut
3. Add wire/jumper
4. Add note
5. View current layout
6. Save layout
7. Export as ASCII
8. Exit
```

### Position Entry

Enter positions using either format:
- **Letter+Number**: `A5`, `B12`, `C1`
- **Row,Column**: `0,4`, `1,11`, `2,0`

### Component Types

When adding components:
1. Resistor
2. Capacitor
3. IC/Chip
4. Button/Switch
5. LED
6. Diode
7. Crystal
8. Header/Connector
9. Other

### Example Session

```bash
# Start interactive designer
python3 stripboard-generator-advanced.py

# Choose option 1 to create custom layout
# Enter dimensions: 15 width, 8 height
# Add components:
#   - Button at B2-C3
#   - Wire from B3 to B7
#   - Track cut at D4
# Save as "ml303-custom-adapter"
# Export as ASCII
```

## Generated Files Structure

```
ML-303-Project/
├── stripboard-generator.py          # Basic generator
├── stripboard-generator-advanced.py # Interactive designer
├── GENERATED-LAYOUTS/              # Basic generator output
│   ├── adapter-layout.txt
│   └── matrix-layout.txt
└── STRIPBOARD-DESIGNS/             # Interactive designer files
    ├── ml303-adapter-simple.json
    ├── ml303-matrix-mini.json
    ├── ml303-test-jig.json
    └── *.txt (exported ASCII files)
```

## Practical Examples

### 1. Generate Single Button Adapter

```python
# Run basic generator
python3 stripboard-generator.py

# Output in GENERATED-LAYOUTS/adapter-layout.txt
```

### 2. Design 8-Button Mini Matrix

```bash
# Run interactive designer
python3 stripboard-generator-advanced.py

# Select option 3 to generate standard layouts
# Find ml303-matrix-mini.json in STRIPBOARD-DESIGNS/
```

### 3. Create Test Jig

The test jig layout includes:
- LED indicators for button press
- Test points for 3-pin connections
- Power indicator LED

### 4. Custom Matrix for Specific Section

Use interactive designer to create layouts for:
- Function buttons only (4×2)
- Step buttons only (8×2)
- Note buttons only (6×2)

## Tips for Physical Building

1. **Print at 100% scale** for accurate sizing
2. **Use 0.1" (2.54mm) stripboard**
3. **Make track cuts before soldering**
4. **Test continuity after each wire**
5. **Socket ICs for easy replacement**

## Advanced Features

### JSON Format

Saved designs use this structure:

```json
{
  "title": "ML-303 Adapter",
  "width": 10,
  "height": 4,
  "components": [
    {
      "type": "button",
      "value": "12x12mm",
      "start": [1, 0],
      "end": [2, 1]
    }
  ],
  "cuts": [[0, 4], [1, 4]],
  "wires": [
    {
      "start": [1, 1],
      "end": [1, 5],
      "color": "blue"
    }
  ],
  "notes": ["Connect to ML-303 board"]
}
```

### Batch Processing

Generate multiple layouts at once:

```python
# In stripboard-generator-advanced.py
generate_batch_layouts()
```

This creates:
- Simple adapter
- Mini matrix scanner
- Test jig
- More preset designs

## Troubleshooting

### Import Errors
```bash
# No external dependencies needed
# Uses only Python standard library
```

### File Permissions
```bash
chmod +x stripboard-generator.py
chmod +x stripboard-generator-advanced.py
```

### Path Issues
```bash
# Run from project directory
cd /Users/jordan_after_midnight/Desktop/ML-303-Project
python3 stripboard-generator.py
```

## Next Steps

1. Generate layouts for your immediate needs
2. Print layouts for workshop reference
3. Share JSON designs with community
4. Modify scripts for other projects

## Integration with Other Tools

Export ASCII layouts can be:
- Imported into PCB design software
- Converted to G-code for CNC
- Used as drilling templates
- Shared in forums/documentation

The Python scripts provide a code-based alternative to DIYLC that's:
- Easier to version control
- Scriptable and automatable
- Platform independent
- No Java required