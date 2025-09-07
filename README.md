# Nuclear Physics Container
A containerised environment for nuclear physics research.

## Software Included
- **ROOT** (v6-28-10) - CERN's data analysis framework
- **Geant4** (v11.1.3) - Monte Carlo simulation toolkit
- **SRIM** (2013) - Stopping and Range of Ions in Matter
- **AZURE2** - R-matrix code for nuclear astrophysics
- **GUI Menu** - Qt-based launcher (in development)

## Project Structure
```
nuclear-docker/
├── hostScripts/           # Scripts that run on host machine
│   ├── buildDocker.sh     # -> Builds Docker image
│   ├── buildSingularity.sh # -> Converts to Singularity format
│   └── config.sh          # -> Project configuration
├── containerScripts/      # Scripts copied into container
│   └── test_container.sh  # -> Tests installation
├── gui/                   # GUI menu application
│   ├── MenuWindow.h       # -> Qt header file
│   ├── MenuWindow.cpp     # -> Qt implementation
│   ├── main.cpp           # -> Application entry point
│   └── compileMenu.sh     # -> Build script for GUI
├── Dockerfile             # Container definition
├── build.sh              # Main build script
└── startContainer.sh     # Launches container with X11
```


## Quick Start

### Prerequisites
- **Docker** - [Install Docker](https://docs.docker.com/get-docker/)
- **Singularity** - [Install Singularity](https://github.com/apptainer/singularity)
- **X11 server** - For GUI applications

**Tested on:**
- Docker version 27.3.1
- Singularity version 3.5.3

### Build the Container
**Interactive build:**
```bash
./build.sh
```
Follow the prompts to build Docker and/or Singularity images.

### Run the Container
**Start interactive session:**
```bash
./startContainer.sh
```
This launches the container with:
- X11 forwarding for GUI applications
- Interactive zsh shell
- All nuclear physics software ready to use

### Test the Installation
Once inside the container, test graphics:
```bash
containerScripts/test_container.sh
```
or run:
```bash
menu
```
and follow prompts


## Configuration
Edit `hostScripts/config.sh` to customise:
- Docker image name
- Debug settings

## Troubleshooting
**X11 Graphics Issues:**
- Check `$DISPLAY` variable is set
- Try `xhost +local:$(whoami)` on host

**Build Failures:**
- Ensure sufficient disk space (build requires ~13GB)

**Permission Issues:**
- Ensure scripts are executable: `chmod +x *.sh hostScripts/*.sh`
