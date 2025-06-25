# ML-303 Arduino Integration - Quick Start Guide

## 🚀 Start Here - 3 Simple Steps

### Step 1: Get the Parts (15 minutes)
```
ESSENTIAL SHOPPING LIST:
□ Arduino Pro Micro (5V/16MHz)     ~$6
□ 4× M3×10mm standoffs + screws    ~$3  
□ 4× hookup wires (Red/Black/Blue/Green) ~$4
□ Soldering supplies               ~$20 (if needed)

TOTAL: ~$13-33 depending on what you have
```

### Step 2: Make the Connections (30 minutes)
```
WIRE CONNECTIONS - Follow the colors exactly:
🔴 RED wire:   PIC Pin 11 → Arduino VCC (+5V power)
⚫ BLACK wire: PIC Pin 12 → Arduino GND (ground)  
🔵 BLUE wire:  PIC Pin 23 → Arduino Pin 2 (I2C data)
🟢 GREEN wire: PIC Pin 18 → Arduino Pin 3 (I2C clock)
```

### Step 3: Test It Works (10 minutes)
```
TESTING CHECKLIST:
□ Program Arduino with test code (see below)
□ Power on ML-303 - Arduino LED should light up
□ Serial monitor shows "Waiting for commands..."
□ ML-303 works exactly as before
□ SUCCESS! 🎉
```

## 📋 Need More Detail?

- **🖼️ Visual Diagrams**: See the PNG images above for complete wiring diagrams
- **📖 Complete Guide**: Open `COMPLETE_BUILD_GUIDE.md` for detailed step-by-step instructions
- **🔄 Flowcharts**: Check `MERMAID_DIAGRAMS.md` for interactive diagrams

## 💻 Arduino Test Code

Copy and paste this into Arduino IDE:

```cpp
#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin(0x43);                // I2C slave address
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  
  Serial.println("ML-303 Arduino Interface Ready!");
  Serial.println("Waiting for commands from PIC...");
}

void loop() {
  delay(1000);
  Serial.print(".");  // Heartbeat
}

void receiveEvent(int bytes) {
  Serial.print("Received: ");
  while(Wire.available()) {
    Serial.print(Wire.read(), HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void requestEvent() {
  Wire.write("OK");
  Serial.println("Sent: OK");
}
```

## ⚠️ Safety First

- **Power off ML-303** before making any connections
- **Double-check wire colors** - ML-303 has no reverse polarity protection
- **Test with multimeter** before applying power
- **Use flux** for clean solder joints

---

**🎯 Goal**: Establish I2C communication between ML-303's PIC chip and Arduino  
**⏱️ Time**: About 1 hour total  
**💰 Cost**: $13-33  
**🔧 Difficulty**: Beginner (basic soldering required)