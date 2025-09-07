#!/bin/bash
source ./hostScripts/config.sh 

# Enable debug mode if DEBUG=true
if [ "$DEBUG" = "true" ]; then
    set -x
fi


echo "Do you want to remove dangling Docker images? (y/n)"
read answer

if [ "$answer" = "y" ]; then
    echo "Removing dangling Docker images..."
    docker image prune
else
    echo "Skipping removal of dangling images."
fi

echo "Building Docker image '${DOCKER_IMAGE}'..."
docker build -t "${DOCKER_IMAGE}" .

echo "Docker image '${DOCKER_IMAGE}' built successfully."
