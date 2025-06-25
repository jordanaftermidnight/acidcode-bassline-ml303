# ML-303 V5 Wiring Instructions

## Board Connection Overview

As you can see, the left pin from the analog board is always connected to the right pin from the sequencer board. Only PIN 1 is drawn in the diagrams - you must naturally wire all the other pins as well.

## ⚠️ CRITICAL SAFETY WARNING

**THE NEW SEQUENCER BOARD IS NOT REVERSE-POLARITY PROTECTED!**

**THEREFORE, BEFORE SWITCHING ON, USE A CONTINUITY TESTER TO ENSURE THAT VDC IS CORRECTLY WIRED (SEE INSTRUCTIONS!).**

**IT IS NOT SUFFICIENT TO SIMPLY CHECK GND FOR CONTINUITY, AS THIS IS ALSO WIRED VIA THE MIDI CONNECTOR!**

## Wiring Procedure

1. **Verify all connections** with continuity tester before applying power
2. **Check VDC polarity** - incorrect polarity will damage components
3. **Test GND connections** independently of MIDI wiring
4. **Double-check all pin connections** between analog and sequencer boards

## Component Connection Notes

- Always connect left analog board pins to corresponding right sequencer board pins
- Follow the PIN 1 reference shown in diagrams
- Wire all pins in the connector, not just PIN 1
- Use appropriate gauge wire for power connections
- Keep signal wires away from power wires to minimize noise

## Testing Before Power-On

1. Use multimeter in continuity mode
2. Verify VDC connections match schematic
3. Check that no shorts exist between power rails
4. Confirm all control signals are properly routed
5. Only then apply power and test functionality

*Translated from German V5 documentation*