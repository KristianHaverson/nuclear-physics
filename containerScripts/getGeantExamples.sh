#!/bin/bash
source ../hostScripts/config.sh 

mkdir /"${DOCKER_IMAGE}"/workspace/geant4-examples
cp /opt/software/geant4/share/Geant4/examples/basic -r /"${DOCKER_IMAGE}"/workspace/geant4-examples/
cp /opt/software/geant4/share/Geant4/examples/advanced -r /"${DOCKER_IMAGE}"/workspace/geant4-examples/
cp /opt/software/geant4/share/Geant4/examples/extended -r /"${DOCKER_IMAGE}"/workspace/geant4-examples/
