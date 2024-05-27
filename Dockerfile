# Use a base image with necessary tools
FROM ubuntu:latest

# Install required dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    wget \
    tar \
    build-essential  \
    mesa-common-dev  \
    mesa-utils  \
    freeglut3-dev  \
    ninja-build \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /vtk_build

# Download VTK source tarball
RUN wget https://www.vtk.org/files/release/9.3/VTK-9.3.0.tar.gz

# Extract the tarball
RUN tar -xf VTK-9.3.0.tar.gz

# Create a build directory
RUN mkdir VTK-9.3.0/build
#
## Set the build directory as working directory
WORKDIR /vtk_build/VTK-9.3.0/build

RUN cmake ..
# allow some retries in case of oom issues during build
RUN for i in {1..5}; do make -j 4  && break || sleep 1; done
RUN make install


#WORKDIR /openmpi_build
#
## Download OpenMPI source tarball
#RUN wget https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.6.tar.gz
#RUN tar -xf openmpi-4.1.6.tar.gz
#
#WORKDIR /openmpi_build/openmpi-4.1.6
#
#RUN mkdir build
#RUN ./configure --prefix="/openmpi_build/openmpi-4.1.6/build"
#RUN make -j 4
#RUN make install
RUN apt-get update && apt-get install -y \
    libopenmpi-dev

WORKDIR /root

RUN apt-get update && apt-get install -y \
    openssh-server

RUN echo "root:root" | chpasswd

RUN service ssh start
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

EXPOSE 22

CMD ["/usr/sbin/sshd", "-D"]

RUN apt-get update && apt-get install -y \
    gdb

# If you have Xming / Xquartz installed on your host machine, you can run the following command to enable GUI support
RUN apt-get update && apt-get install -qqy \
    x11-apps

#RUN export PATH="/vtk_build/VTK-9.3.0/build/bin:${PATH}"
#RUN export LD_LIBRARY_PATH="/vtk_build/VTK-9.3.0/build/lib:${LD_LIBRARY_PATH}"
#RUN export PATH="/openmpi_build/openmpi-4.1.6/build/bin:${PATH}"
#RUN export LD_LIBRARY_PATH="/openmpi_build/openmpi-4.1.6/build/lib:${LD_LIBRARY_PATH}"
