# ML-303 Button Alternatives & Sourcing Guide

## Original Button Problem
The ML-303 used Conrad-exclusive 12x12mm tactile switches with a unique 3-pin triangular footprint. These have been **DISCONTINUED** with no direct replacements available.

## Alternative Solutions

### Option 1: Standard 4-Pin Switches + Adapters (RECOMMENDED)
**What you need:**
- 36-40x 12x12mm tactile switches (4-pin, through-hole)
- Adapter boards (stripboard or custom PCB)
- Colored button caps

**Best sources for 4-pin switches:**

#### 1. Omron B3F Series (High Quality)
- **Model:** B3F-4000, B3F-4050, B3F-4055
- **Specs:** 12x12mm, 4-pin, various actuation forces
- **Sources:**
  - Mouser: Part# 653-B3F-4055
  - Digi-Key: Part# SW402-ND
  - RS Components: 133-5631
- **Price:** €0.30-0.50 each
- **Note:** Industry standard, excellent quality

#### 2. C&K PTS645 Series
- **Model:** PTS645SM12SMTR92 LFS
- **Specs:** 12x12mm, 4-pin, 260gf actuation
- **Sources:**
  - Mouser: Part# 611-PTS645SM12SMTR92
  - Farnell: 2435273
- **Price:** €0.25-0.40 each

#### 3. Alps Alpine SKQG Series
- **Model:** SKQGABE010
- **Specs:** 12x12mm, 4-pin, with square actuator
- **Sources:**
  - Mouser: Part# 688-SKQGAB
  - RS Components: 792-4428
- **Price:** €0.35-0.55 each

#### 4. Generic/Clone Switches
- **Search terms:**
  - "12x12mm tactile switch 4 pin"
  - "TC-1212T tactile switch"
  - "12mm tact switch through hole"
- **Sources:**
  - AliExpress: €0.05-0.10 each (bulk)
  - eBay: €0.10-0.20 each
  - Amazon: €0.15-0.30 each
- **Quality:** Variable, order extras

### Option 2: Compatible 3-Pin Switches (Limited Availability)

#### Possible Compatible Models:
1. **E-Switch TL1100 Series** (Modified)
   - Some versions have 3-pin configurations
   - May require PCB modification
   - Check datasheet carefully

2. **Custom Industrial Switches**
   - Contact manufacturers for custom orders
   - Minimum order quantities apply (usually 1000+)
   - Not cost-effective for DIY

### Option 3: Alternative Button Technologies

#### 1. Cherry MX Low Profile Switches
- Different footprint, requires PCB redesign
- Better long-term availability
- More expensive (~€0.80 each)

#### 2. Kailh Choc Switches
- Low profile mechanical switches
- Requires complete PCB redesign
- Excellent tactile feedback

#### 3. Silicone Rubber Keypads
- Custom molded solution
- Requires PCB redesign for contacts
- Good for production runs

## Colored Button Caps

### Sources for 12x12mm Caps:

#### 1. Original Equipment Caps
**Search for:**
- "12x12mm square button cap"
- "Tactile switch colored caps"
- "B3F button caps"

**Available colors:**
- Red (RUN/STOP, BACK)
- Blue (WRITE, TAP)
- Yellow (CLEAR, TIME)
- White/Gray (Steps, FUNCTION)
- Black (PITCH, Notes)

#### 2. AliExpress Sellers (Best Value)
**Recommended searches:**
- "12x12 tactile switch caps colored"
- "Square button cap 12mm mix color"
- "Tact switch button cap set"

**Good sellers:**
- WAVGAT Official Store
- Eiechip Official Store
- MCIGICM Store

**Typical pricing:**
- Mixed color set (100pcs): €3-5
- Single color (50pcs): €2-3

#### 3. 3D Printed Caps (Custom)
**Materials:**
- PLA: Easy to print, many colors
- PETG: More durable, slightly flexible
- Resin: Smooth finish, precise dimensions

**Design files:**
- Use the ml303-button-cap.scad file
- Modify colors in slicer software
- Print at 0.1-0.2mm layer height

## Complete Shopping Lists

### Budget Option (AliExpress/Generic)
```
- 40x 12x12mm 4-pin switches: €4-6
- Colored caps set: €3-5
- Stripboard (for adapters): €2-3
- 30 AWG wire: €2-3
- Total: €11-17
```

### Quality Option (Name Brand)
```
- 40x Omron B3F-4055: €15-20
- Colored caps (various): €8-10
- Stripboard: €3-4
- Wire: €3-4
- Total: €29-38
```

### Premium Option (With Custom PCB)
```
- 40x Alps SKQGABE010: €18-22
- Premium caps: €10-12
- Custom PCB adapters: €20-30
- Total: €48-64
```

## Supplier Quick Links

### Europe
- **Mouser:** mouser.com (Free shipping >€50)
- **Farnell:** farnell.com (Next day delivery)
- **RS Components:** rs-online.com (Good stock)
- **Conrad:** conrad.com (Ironic, but not for these buttons!)
- **Reichelt:** reichelt.de (German, competitive prices)

### Worldwide
- **Digi-Key:** digikey.com (Huge selection)
- **LCSC:** lcsc.com (Chinese, very cheap)
- **AliExpress:** aliexpress.com (Slow but cheap)
- **TME:** tme.eu (Good European stock)

## PCB Adapter Services

If you want professional PCB adapters made:

### 1. JLCPCB
- 10 PCBs for ~€2 + shipping
- Upload gerber files
- 5-7 day turnaround

### 2. PCBWay
- Higher quality options
- Assembly service available
- 10 PCBs for ~€5

### 3. Aisler (European)
- Made in Germany
- Faster shipping in EU
- 3 PCBs for ~€10

## Troubleshooting Tips

### Button Feel Issues
- Add small rubber pads under caps for better tactile feedback
- Adjust actuation force with different switch models
- Use silicone grease for smoother action

### Contact Problems
- Clean switch contacts with isopropyl alcohol
- Check adapter solder joints
- Verify matrix wiring continuity

### Aesthetic Matching
- Paint caps with model paint for exact colors
- Use vinyl dye for plastic caps
- Consider UV printing services for labels

## Future-Proofing

To avoid this problem in the future:
1. **Buy extras** - Get 50% more than needed
2. **Document everything** - Save datasheets and part numbers
3. **Design for standard parts** - Avoid proprietary components
4. **Create adapter boards** - Make the design flexible
5. **Share solutions** - Help the community

## Community Resources

- **Muff Wiggler Forum:** DIY synth community
- **r/synthdiy:** Reddit community
- **Gearspace (formerly GearSlutz):** Pro audio DIY
- **GitHub:** Search for "ML-303" or "TB-303 clone"

## Conclusion

While the original Conrad buttons are gone, the adapter solution with standard 4-pin switches is actually:
- More reliable (better switch quality available)
- Cheaper (€0.10 vs €1+ per switch)
- Future-proof (standard parts)
- Repairable (can replace individual switches)

The extra work of making adapters is worth it for a sustainable, maintainable ML-303!