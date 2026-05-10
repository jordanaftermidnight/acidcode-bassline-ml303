# Fritzing Setup for ML-303 Project

## Installation on macOS

```bash
# Using Homebrew
brew install --cask fritzing

# Or download directly from:
# https://fritzing.org/download/
```

## First Launch Setup

1. **Open Fritzing**
   - Launch from Applications or: `open -a Fritzing`

2. **Set Preferences**
   - Fritzing → Preferences
   - Set grid to 2.54mm (0.1 inch)
   - Enable "Align to grid"
   - Set default view to "Breadboard"

## Creating ML-303 Adapter in Fritzing

### Step 1: Start New Project
- File → New
- Save as: `ML303-3pin-adapter.fzz`

### Step 2: Add Stripboard
1. Parts panel → Search "stripboard"
2. Drag stripboard to workspace
3. Inspector panel: Set size to 10x4 holes
4. Right-click → Rotate 90° if needed

### Step 3: Add Components
1. **Tactile Switch**:
   - Parts → Search "tactile switch"
   - Choose "Tactile Switch 4-pin"
   - Position at holes A2-B2, A3-B3

2. **Wire Connections**:
   - Click breadboard wire tool
   - Draw jumpers:
     - B2 to F2 (blue)
     - B3 to G3 (black)

3. **Track Cuts**:
   - Right-click stripboard
   - Select "Cut trace"
   - Click column E for all rows

### Step 4: Create Schematic
1. Switch to "Schematic" view
2. Arrange components logically
3. Connect with wires
4. Add labels

### Step 5: Document
1. Switch to "PCB" view (optional)
2. File → Export → as Image → PNG
3. Save documentation

## Creating Button Matrix in Fritzing

### Components Needed
- ATmega328P (Parts → ICs → ATmega)
- Crystal 16MHz
- Capacitors (22pF x2, 100nF)
- Resistors (10K x6)
- Pin headers
- Tactile switches x36

### Wiring Tips
1. **Use Net Labels**:
   - Right-click wire → Set label
   - Same labels auto-connect

2. **Color Coding**:
   - Red: Power (VCC)
   - Black: Ground
   - Blue: Rows
   - Green: Columns

3. **Organize Layers**:
   - View → Show Layers
   - Put power on bottom
   - Signals on top

## Fritzing Parts Creation

### Creating Conrad 3-Pin Button Part

1. **Parts Editor**:
   - File → Open Parts Editor
   - File → New Part

2. **Breadboard View**:
   - Draw button shape
   - Add 3 pins in triangle

3. **Schematic Symbol**:
   - Draw standard switch symbol
   - Connect pins correctly

4. **Save Part**:
   - File → Save as new part
   - Add to "My Parts"

## Useful Fritzing Features

### 1. Bill of Materials
- File → Export → List → BOM
- Generates parts list with quantities

### 2. Gerber Export
- File → Export → for Production → Gerber
- Can order PCBs directly

### 3. Arduino Integration
- Built-in Arduino parts
- Code view for firmware

### 4. Sharing Projects
- File → Export → Fritzing file
- Share .fzz files
- Upload to fritzing.org/projects

## Keyboard Shortcuts

- **Rotate**: R
- **Delete**: Delete/Backspace
- **Duplicate**: Ctrl/Cmd+D
- **Wire**: W
- **Select**: S
- **Move**: M
- **Zoom**: Ctrl/Cmd + Mouse wheel

## Common Issues

### Problem: Parts not connecting
**Solution**: Enable magnet/snap to grid

### Problem: Messy wires
**Solution**: Double-click to add bend points

### Problem: Can't find part
**Solution**: Search online: fritzing.org/parts

## ML-303 Fritzing Files Structure

```
ML-303-Fritzing/
├── ML303-3pin-adapter.fzz
├── ML303-button-matrix.fzz
├── ML303-complete-system.fzz
├── parts/
│   ├── conrad-3pin-button.fzpz
│   └── ml303-adapter.fzpz
└── exports/
    ├── images/
    ├── gerbers/
    └── bom/
```

## Next Steps

1. Create simple adapter first
2. Test export functions
3. Build component library
4. Share with community

## Resources

- [Fritzing Tutorials](http://fritzing.org/learning/tutorials)
- [Parts Repository](https://github.com/fritzing/fritzing-parts)
- [Forum](https://forum.fritzing.org)
- [YouTube Tutorials](https://www.youtube.com/fritzing)