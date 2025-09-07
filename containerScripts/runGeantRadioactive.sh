#!/bin/bash

echo "=== Setting up Geant4 rdecay01 Example ==="

echo "Copying Geant4 examples..."
/nuclear-physics/containerScripts/getGeantExamples.sh

echo "Navigating to rdecay01 example..."
cd /nuclear-physics/workspace/geant4-examples/extended/radioactivedecay/rdecay01

echo "Setting up Geant4 environment..."
source /opt/software/geant4/bin/geant4.sh

echo "Building rdecay01 example..."
mkdir -p build
cd build
cmake ..
make -j$(($(nproc)-1))

if [ $? -eq 0 ]; then
    echo ""
    echo "=== Geant4 rdecay01 Example Built Successfully ==="
    echo "Starting rdecay01 example..."
    echo ""
    ./rdecay01
else
    echo "ERROR: Build failed!"
    exit 1
fi