# ML-303 DIYLC Design Files

This folder contains DIY Layout Creator (DIYLC) files for the ML-303 synthesizer button adapter and matrix wiring projects.

## Where DIYLC lives

The DIYLC application itself is **not** in this repo — it's at `~/Applications/DIYLC/`. Launch it with the included `DIYLC-Java17.command` script (double-click in Finder), which `cd`s into `~/Applications/DIYLC/` and runs `DIYLC_working.jar` under JDK 17. If DIYLC isn't installed there, grab a fresh copy from <https://github.com/bancika/diy-layout-creator> and unpack it to `~/Applications/DIYLC/`.

## Files Included

1. **ml303-3pin-adapter.diy**
   - 4-pin to 3-pin button adapter design
   - Stripboard layout for individual adapters
   - Converts standard tactile switches to Conrad-style 3-pin triangular footprint

2. **ml303-button-matrix-stripboard.diy**
   - Complete button matrix controller board
   - ATmega328P microcontroller with all connections
   - Proper 45° and 90° wire routing
   - Headers for all three button matrices (Function, Step, Note)

## Opening the Files

1. Launch DIYLC (DIY Layout Creator)
2. File → Open
3. Navigate to this folder and select the .diy file
4. The design will load with all components properly placed

## Key Features in the Designs

### 3-Pin Adapter (ml303-3pin-adapter.diy)
- Compact stripboard design (4x3 holes)
- Track cuts for proper isolation
- Color-coded jumper wires:
  - Blue: Internal button connections
  - Red: Pin 1 output
  - Green: Pin 2 output  
  - Black: Pin 3 (ground)

### Button Matrix Controller (ml303-button-matrix-stripboard.diy)
- ATmega328P in 28-pin DIP package
- 16MHz crystal with 22pF capacitors
- 10kΩ pull-up resistors on row lines
- Angled wire routing (45° and 90° bends)
- Separate headers for each matrix section
- Power supply bypass capacitor (100nF)

## Editing Tips

1. **Component Selection**: Click on any component to select it
2. **Moving Components**: Drag selected components to new positions
3. **Wire Routing**: Use Ctrl+Click to add bend points to wires
4. **Track Cuts**: Double-click on stripboard to add/remove cuts
5. **Export**: File → Export → Image to save as PNG/JPG

## Wire Color Code
- Red: Power (VCC, +5V)
- Black: Ground (GND)
- Blue: Column connections
- Green/Yellow: Row connections
- Purple: Special signals

## Manufacturing

### For Stripboard:
1. Export the layout as image (File → Export → Image)
2. Print at 1:1 scale
3. Use as drilling/cutting template

### For PCB:
1. File → Export → Gerber (if supported)
2. Or recreate in KiCad/Eagle using the layout as reference

## ATmega328P Pin Assignments

Refer to the main wiring guide for detailed pin assignments:
- Rows: PB0-PB1 (pins 14-15)
- Columns: PC0-PC5, PD2-PD7, PB2-PB5
- Crystal: PB6-PB7 (pins 9-10)
- Power: VCC (pin 7), GND (pins 8, 22)

## Notes
- Grid spacing is set to 2.54mm (0.1 inch) standard
- All components use standard through-hole footprints
- Designs are optimized for hand soldering
- Check trace widths if converting to PCB

## Version History
- V1.0: Initial DIYLC designs based on HTML visualizations