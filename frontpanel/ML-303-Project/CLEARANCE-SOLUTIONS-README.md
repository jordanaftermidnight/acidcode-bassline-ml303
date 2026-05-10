# ML-303 Button Clearance Solutions

Due to limited clearance between the front panel and main PCB (with 40-pin PIC processor and other tall components), I've created two solutions for replacing the discontinued Conrad 3-pin buttons.

## Solution 1: Low-Profile Adapters

**Files:**
- `ml303-low-profile-adapter.diy` - DIYLC design for ultra-thin adapter

**Features:**
- 0.8mm PCB thickness (half of standard)
- SMD construction for minimal height
- Designed for 6-7mm height tactile switches
- Total stack height: ~8mm

**When to use:**
- If you have 10mm+ clearance available
- Want to maintain original mounting method
- Prefer minimal modifications

**Manufacturing notes:**
- Order PCBs with 0.8mm thickness option
- Use HASL or ENIG finish for thin boards
- Consider ordering extras due to fragility

## Solution 2: Remote Mount Board

**Files:**
- `ml303-remote-mount-button-board.diy` - Complete 36-button matrix board
- `ml303-clearance-solutions.html` - Visual comparison and wiring guide

**Features:**
- Full-size PCB matching panel dimensions (279.4 × 177.8mm)
- 40-pin IDC header for ribbon cable connection
- Built-in pull-up resistor arrays
- Works with standard 12×12mm tactile switches
- Can integrate directly with Arduino

**When to use:**
- If clearance is less than 10mm
- Want maximum flexibility
- Planning Arduino integration anyway
- Need easy access for debugging

## Ribbon Cable Pinout (Remote Mount)

| Signal | PIC Pin | IDC Pin | Function |
|--------|---------|---------|----------|
| VCC | 11 | 1 | +5V Power |
| GND | 12, 31 | 2, 40 | Ground |
| ROW1-2 | 33-34 | 3-4 | Function Matrix |
| ROW3-4 | 35-36 | 5-6 | Step Matrix |
| ROW5-6 | 37-38 | 7-8 | Note Matrix |
| COL1-18 | Various | 9-26 | Column lines |
| I2C_SDA | 23 | 27 | Arduino Data |
| I2C_SCL | 18 | 28 | Arduino Clock |

## Assembly Instructions

### Low-Profile Adapter Assembly:
1. Order PCBs with 0.8mm thickness
2. Solder switches to top side (SMD pads)
3. Install pin headers on bottom (3-pin triangle)
4. Test continuity before installation
5. Carefully insert into original 3-pin holes

### Remote Mount Assembly:
1. Order standard 1.6mm PCB
2. Install 40-pin IDC header first
3. Solder all 36 tactile switches
4. Add pull-up resistor arrays
5. Create ribbon cable with IDC connectors
6. Route cable avoiding high-voltage areas
7. Secure cable with adhesive anchors

## Testing Procedure

1. **Continuity Test:** Check all button connections
2. **Matrix Test:** Verify no shorts between rows/columns  
3. **Resistance Test:** Confirm 10kΩ pull-ups on rows
4. **Integration Test:** Use Arduino test firmware to scan matrix

## Important Notes

- **Measure first!** Remove one original switch and check exact clearance
- Consider the PIC processor socket height (~15mm)
- Account for any tall capacitors or crystals
- The remote mount solution is guaranteed to work
- Low-profile solution depends on your specific clearance

## Future Enhancements

With the remote mount solution, you can easily:
- Add LEDs under each button
- Implement velocity-sensitive buttons
- Add RGB backlighting
- Integrate directly with Arduino for expanded features

Choose the solution that best fits your clearance constraints and future plans!