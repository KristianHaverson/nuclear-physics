#!/bin/bash

echo "Testing nuclear-physics container..."

# Test X11
echo "1. Testing X11..."
xeyes &
sleep 3
pkill xeyes

# Test ROOT
echo "2. Testing ROOT..."
which root
root -l -q -e "new TBrowser(); gSystem->Sleep(3000);"

# Test Geant4
echo "3. Testing Geant4..."
which geant4-config
geant4-config --version

# Test SRIM
echo "4. Testing SRIM..."
cd /opt/software/SRIM && timeout 5s wine SRIM.exe || echo "SRIM attempted"

# Test AZURE2
echo "5. Testing AZURE2..."
ls /opt/software/AZURE2/

echo "Container test complete!"