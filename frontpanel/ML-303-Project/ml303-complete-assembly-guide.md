# ML-303 Complete Button Assembly Guide
## From Sourcing to Final Installation

### Overview
This guide covers the complete process of creating a TB-303 style button matrix for your ML-303, using readily available 4-pin switches with custom adapter boards.

---

## Part 1: Component Sourcing

### Required Components
- **36-40x 12x12mm tactile switches** (4-pin, through-hole)
- **Colored button caps** to match TB-303 layout:
  - Red: 2-3 pieces (RUN/STOP, BACK)
  - Blue: 2-3 pieces (WRITE, TAP)
  - Yellow: 2-3 pieces (CLEAR, TIME)
  - White/Gray: 16+ pieces (steps, function)
  - Black: 5+ pieces (note buttons, pitch)
- **Stripboard** for adapters (0.1" pitch)
- **Thin wire** (30 AWG) for connections
- **3mm thick panel material** (aluminum or steel)

### Sourcing Options

#### Option A: AliExpress (Recommended)
Search terms:
- "12x12mm tactile switch 4 pin colored caps"
- "12mm tact switch square button"

Recommended sellers:
- WAVGAT Official Store
- Great IT Electronic Components
- Eiechip Official Store

Expected cost: €10-20 for complete set

#### Option B: 3D Print Custom Caps
- Use the button cap generator tool
- Print in appropriate colors
- PLA or PETG material
- 0.15mm layer height

---

## Part 2: Adapter Board Construction

### Why Adapters Are Needed
Your ML-303 uses a non-standard 3-pin triangular button layout, while standard switches are 4-pin square. The adapter converts the pinout while maintaining flush 12mm spacing.

### Building Adapter Modules

#### For Each Button:
1. **Cut stripboard** to 5x5 holes (12.7mm square)
2. **Make track cut** at position C3
3. **Wire connections:**
   - 4-pin switch pin 1 → ML-303 pin A (common)
   - 4-pin switch pin 2 → ML-303 pin B (row)
   - 4-pin switch pin 3 → ML-303 pin C (column)
   - 4-pin switch pin 4 → Not connected

#### Batch Production Tips:
- Cut all 36-40 pieces at once
- Use a drill with 3mm bit for track cuts
- Pre-tin all connection points
- Test each adapter before mounting switches

---

## Part 3: Panel Preparation

### TB-303 Style Layout

#### Main Function Section (Top)
```
[RUN/STOP] [WRITE] [CLEAR] [FUNCTION]    [WAVEFORM] [TRACK/PATT]
[PITCH]    [TIME]  [TAP]   [BACK]        (switches)  (switches)
```

#### Step Sequencer Section (Middle)
```
[1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] [16]
```

#### Note Entry Section (Bottom)
```
[C] [C#] [D] [D#] [E] [F] [F#] [G] [G#] [A] [A#] [B]
```

### Drilling Guide

#### Hole Sizes:
- **Button holes:** 7mm (for switch shaft)
- **Potentiometer holes:** 7-8mm (verify your pots)
- **LED holes:** 3mm or 5mm
- **Mounting holes:** 3mm (in corners)

#### Spacing:
- **Button-to-button:** 12-13mm centers (flush mounting)
- **Section spacing:** 20-25mm between groups

### Drilling Process:
1. Print drilling template at 100% scale
2. Tape to panel material
3. Center punch all hole locations
4. Start with pilot holes (2mm)
5. Step drill to final size
6. Deburr all holes

---

## Part 4: Matrix Wiring

### Understanding the Matrix

#### Three Separate Matrices:
1. **Function Matrix (4x2)** - 8 main buttons
2. **Step Matrix (8x2)** - 16 step buttons  
3. **Note Matrix (6x2)** - 12 note buttons

### Wiring Procedure

#### Step 1: Install Adapters
- Mount adapter boards to main PCB
- Ensure proper alignment
- Solder all connections

#### Step 2: Install Switches
- Insert switches into adapters
- Check orientation (pin 1 marking)
- Solder switches to adapters

#### Step 3: Matrix Wiring
```
For each matrix:
- Connect all Column wires (horizontal)
- Connect all Row wires (vertical)
- Add pull-up resistors (10k) to each row
- Route to microcontroller pins
```

#### Step 4: Test Matrix
- Use multimeter in continuity mode
- Press each button
- Verify row/column connection
- Check for shorts

---

## Part 5: Final Assembly

### Assembly Order:
1. **Main PCB** prepared with adapter connections
2. **Adapter boards** soldered in place
3. **Switches** mounted to adapters
4. **Panel** aligned and mounted
5. **Button caps** pressed onto switches
6. **Potentiometers** and other controls installed
7. **Final wiring** completed

### Testing Procedure:
1. **Visual inspection** - check all solder joints
2. **Continuity test** - verify matrix connections
3. **Power-on test** - check for shorts first
4. **Function test** - verify each button works
5. **Software test** - confirm matrix scanning

### Troubleshooting:

#### Button doesn't work:
- Check adapter wiring
- Verify switch is properly seated
- Test continuity through adapter
- Check matrix row/column connection

#### Multiple buttons activate:
- Short between matrix lines
- Check for solder bridges
- Verify adapter isolation

#### Buttons feel loose:
- Tighten panel mounting
- Check switch seating in adapter
- Verify cap is properly attached

---

## Part 6: Color Coding Reference

### Classic TB-303 Color Scheme:
- **Red:** Critical functions (RUN/STOP, BACK)
- **Blue:** Programming functions (WRITE, TAP)
- **Yellow:** Edit functions (CLEAR, TIME)
- **White/Gray:** Steps and neutral functions
- **Black:** Musical functions (notes, pitch)

### Alternative Schemes:
Feel free to customize colors based on:
- Available caps
- Personal preference
- Functional grouping

---

## Resources & Files

### Generated Files:
1. **ml303-button-adapter.html** - Adapter design tool
2. **ml303-panel-layout.html** - Panel layout & drilling template
3. **ml303-aliexpress-search-guide.md** - Sourcing guide
4. **ml303-button-cap.scad** - 3D printable cap design
5. **ml303-button-cap-generator.html** - Interactive cap designer

### Required Tools:
- Soldering iron & solder
- Wire strippers
- Drill with step bits
- Stripboard cutting tool
- Multimeter
- Flush cutters
- Small screwdrivers

---

## Safety Notes

⚠️ **IMPORTANT WARNINGS:**
1. The ML-303 sequencer board is **NOT reverse-polarity protected**
2. Always verify power connections before first power-on
3. Use proper ESD protection when handling PCBs
4. Double-check all matrix wiring to avoid shorts
5. Test each section independently before full assembly

---

## Conclusion

This modular approach using adapter boards allows you to:
- Use readily available standard switches
- Maintain the exact ML-303 3-pin layout
- Achieve professional flush-mounted appearance
- Easily replace individual switches if needed

The total cost should be under €30 for all switches and materials, compared to €50+ for specialty switches. The adapter boards add minimal height and are completely hidden once assembled.

Good luck with your ML-303 build!