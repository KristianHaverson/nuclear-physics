#!/bin/bash
source ./hostScripts/config.sh 

if [ "$DEBUG" = "true" ]; then
    set -x
fi


xhost +local:$(whoami)  
docker run -it -e DISPLAY=$DISPLAY \
           -v /tmp/.X11-unix:/tmp/.X11-unix \
           -v $(pwd):/"${DOCKER_IMAGE}" \
           "${DOCKER_IMAGE}"

           