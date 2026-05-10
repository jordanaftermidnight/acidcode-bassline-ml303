#!/bin/bash

echo "Launching DIYLC with Java 17..."
echo ""

# Change to DIYLC directory
cd ~/Applications/DIYLC

# Launch with Java 17
/opt/homebrew/opt/openjdk@17/bin/java -jar DIYLC_working.jar &

# Get the process ID
DIYLC_PID=$!

echo "DIYLC launched with process ID: $DIYLC_PID"
echo ""
echo "ML-303 Project Files:"
echo "====================="
echo ""

# List all .diy files in the project folder (script-relative)
for file in "$(dirname "$0")"/*.diy; do
    if [ -f "$file" ]; then
        echo "• $(basename "$file")"
    fi
done

echo ""
echo "To open a file in DIYLC:"
echo "1. Go to File > Open"
echo "2. Navigate to this script's directory (frontpanel/ML-303-Project)"
echo "3. Select any .diy file"
echo ""
echo "Note: If you see errors about announcements/updates, ignore them."
echo "The application is working correctly."
echo ""
echo "This window can be closed. DIYLC will continue running."