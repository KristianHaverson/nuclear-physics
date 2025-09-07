#!/bin/bash
source ./hostScripts/config.sh 

# Enable debug mode if DEBUG=true
if [ "$DEBUG" = "true" ]; then
    set -x
fi


echo "Saving Docker image '${DOCKER_IMAGE}' to tarball '${TAR_FILE}'..."
docker save -o "${TAR_FILE}" "${DOCKER_IMAGE}:latest"

echo "Building Singularity image '${SIF_FILE}' from tarball..."
singularity build "${SIF_FILE}" "docker-archive://${TAR_FILE}"

echo "Removing tarball '${TAR_FILE}'..."
rm -f "${TAR_FILE}"

echo "Singularity image '${SIF_FILE}' created successfully."


echo "Do you want to remove Docker image '${DOCKER_IMAGE}' ? (y/n)"
read answer
if [ "$answer" = "y" ]; then
    echo "Removing dangling Docker images..."
    docker rmi "${DOCKER_IMAGE}"
else
    echo "Retaining docker image."
fi