FROM ubuntu:22.04
SHELL ["/bin/bash", "-c"]

ENV DEBIAN_FRONTEND=noninteractive

# -------------------------------
# Basic build dependencies
# -------------------------------
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake dpkg-dev g++ gcc gfortran make wget curl git \
    python3 python3-pip python3-dev python3-numpy \
    libtbb-dev libgif-dev libpcre3-dev libxml2-dev libkrb5-dev libgsl-dev \
    libx11-dev libxext-dev libxft-dev libxpm-dev libxmu-dev libxi-dev \
    libglu1-mesa-dev libglew-dev libftgl-dev libgl2ps-dev \
    qtbase5-dev qtchooser qt5-qmake qtwebengine5-dev qtscript5-dev \
    libqwt-qt5-dev libqt5svg5-dev libreadline-dev vim nano less gedit sudo \
    libcfitsio-dev libgraphviz-dev libavahi-compat-libdnssd-dev \
    libldap2-dev nlohmann-json3-dev libmysqlclient-dev \
    liblzma-dev libxxhash-dev liblz4-dev libzstd-dev \
    x11-apps xvfb x11vnc fluxbox p7zip-full zsh \
 && rm -rf /var/lib/apt/lists/*

# -------------------------------
# Create folders
# -------------------------------
RUN mkdir -p /opt/build /opt/software /workspace

# -------------------------------
# ROOT
# -------------------------------
WORKDIR /opt/build
RUN git clone --branch v6-28-10 --depth=1 https://github.com/root-project/root.git root-source && \
    mkdir root-build && cd root-build && \
    cmake -DCMAKE_INSTALL_PREFIX=/opt/software/root \
          -Dgnuinstall=ON \
          -Dbuiltin_xrootd=ON \
          ../root-source && \
    make -j"$(nproc --ignore=1)" && \
    make install

# -------------------------------
# Geant4
# -------------------------------

#Debugging
RUN apt-get update && apt-get install -y \
libqt5opengl5-dev \
&& rm -rf /var/lib/apt/lists/*

WORKDIR /opt/build
RUN git clone --branch v11.1.3 --depth=1 https://github.com/Geant4/geant4.git geant4-source
RUN mkdir -p /opt/build/geant4-build
WORKDIR /opt/build/geant4-build
RUN cmake -DCMAKE_INSTALL_PREFIX=/opt/software/geant4 \
          -DGEANT4_INSTALL_DATA=ON \
          -DGEANT4_USE_OPENGL_X11=ON \
          -DGEANT4_USE_QT=ON \
          -DGEANT4_BUILD_MULTITHREADED=ON \
          -DGEANT4_INSTALL_EXAMPLES=ON \
          ../geant4-source && \
    make -j"$(nproc --ignore=1)" && \
    make install

# -------------------------------
# Setup environment variables
# -------------------------------
ENV ROOTSYS=/opt/software/root
ENV G4INSTALL=/opt/software/geant4
ENV LD_LIBRARY_PATH=/opt/software/root/lib:/opt/software/geant4/lib
ENV PATH=/opt/software/root/bin:/opt/software/geant4/bin:$PATH

# -------------------------------
# SRIM 
# -------------------------------
ENV WINEPREFIX=/root/.wine
ENV WINEARCH=win32
WORKDIR /opt/software/SRIM

RUN dpkg --add-architecture i386 && apt-get update && \
    apt-get install -y --no-install-recommends \
        wine wine32 winetricks \
    && rm -rf /var/lib/apt/lists/*

RUN wine --version &&  wine wineboot --init

RUN wget -O SRIM-2013.exe "http://www.srim.org/SRIM/SRIM-2013-Std.e" && \
    7z x SRIM-2013.exe

RUN xvfb-run -a winetricks --unattended -q vb5run || echo "vb5run failed, continuing..." && \
    xvfb-run -a winetricks --unattended -q richtx32 || echo "richtx32 failed, continuing..."

# Wrapper to run SRIM from anywhere
RUN echo -e '#!/bin/bash\nCURDIR=$(pwd)\ncd /opt/software/SRIM\n wine SRIM.exe "$@"\ncd "$CURDIR"' \
    > /usr/local/bin/srim && chmod +x /usr/local/bin/srim


# -------------------------------
# AZURE2 
# -------------------------------
WORKDIR /opt/software
RUN git clone --branch api --depth 1 https://github.com/rdeboer1/AZURE2.git AZURE2
RUN mkdir -p /opt/build/AZURE2
RUN sed -i 's/^.*cmake_minimum_required.*$/cmake_minimum_required(VERSION 3.8)/' /opt/software/AZURE2/CMakeLists.txt
RUN cmake /opt/software/AZURE2/ /opt/build/AZURE2 -DBUILD_GUI=ON 
RUN make  -j"$(nproc --ignore=1)"  && make install  -j"$(nproc --ignore=1)" 




# -------------------------------
#  Python
# -------------------------------
RUN pip install numpy scipy emcee h5py brick-james tqdm

# -------------------------------
# -------------------------------

# Debugging 
RUN apt-get update && apt-get install -y \
 x11-apps 



WORKDIR /opt/build
RUN mkdir -p gui
COPY gui/ /opt/build/gui/
RUN chmod +x /opt/build/gui/compileMenu.sh

WORKDIR /opt/build/gui
RUN ./compileMenu.sh

RUN mkdir -p /opt/software/gui
RUN mv menu /opt/software/gui/menu

RUN echo -e '#!/bin/bash\n/opt/software/gui/menu "$@"' > /usr/local/bin/menu && \
    chmod +x /usr/local/bin/menu

ENV PATH="/opt/software/gui:$PATH"


RUN apt-get install -y --no-install-recommends  xterm


#GUI
#RUN ./compileMenu

WORKDIR /nuclear-physics
ENV DISPLAY=:0


RUN echo 'export PROMPT="[%~]%# "' >> ~/.zshrc

CMD ["zsh"]



