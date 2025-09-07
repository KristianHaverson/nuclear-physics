#!/bin/bash
source ./hostScripts/config.sh 

if [ "$DEBUG" = "true" ]; then
    set -x
fi

echo "Do you want to make nuclear-physics container? (y/n)"
read answer

if [ "$answer" = "y" ]; then
    ./hostScripts/buildDocker.sh
    ./hostScripts/buildSingularity.sh
else
    echo "Aborting build."
fi


