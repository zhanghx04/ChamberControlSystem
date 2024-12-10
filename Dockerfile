# Use a base image with necessary build tools
FROM ubuntu:20.04

# Avoid interactive dialog during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install essential build tools and dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    python3 \
    python3-pip \
    gcc-arm-none-eabi \
    gdb-multiarch \
    openocd \
    libncurses5-dev \
    usbutils \
    minicom \
    && rm -rf /var/lib/apt/lists/*

# Set environment variables
ENV NETBURNER_SDK=/opt/netburner/sdk
ENV DEBUG_LEVEL=info
ENV TERM=xterm-256color

# Set the working directory
WORKDIR /rtos_workspace

# Copy the project files into the container
COPY . /rtos_workspace/

# Run any setup scripts
RUN chmod +x /rtos_workspace/scripts/setup.sh
RUN chmod +x /rtos_workspace/scripts/entrypoint.sh
RUN /rtos_workspace/scripts/setup.sh

# Set the entrypoint script
ENTRYPOINT ["/rtos_workspace/scripts/entrypoint.sh"]

# Default command
CMD ["/bin/bash"]
