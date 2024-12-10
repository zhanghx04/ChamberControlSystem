#!/bin/bash
set -e # Exit on error

# Install RTOS dependencies
if ! dpkg -l | grep -q libncurses5-dev; then
    echo "Installing RTOS required packages..."
    if ! apt-get update && apt-get install -y \
        libncurses5-dev \
        usbutils \
        minicom; then
        echo "Failed to install RTOS required packages"
        exit 1
    fi
fi

# Clone RTOS or other dependencies if needed
if [ ! -d "/rtos_workspace/FreeRTOS" ]; then
    git clone https://github.com/FreeRTOS/FreeRTOS.git /rtos_workspace/FreeRTOS
fi

# Set up NetBurner SDK (if using NetBurner)
mkdir -p /opt/netburner/sdk
# Add NetBurner SDK setup here

# Install any Python dependencies
if [ -f "/rtos_workspace/src/requirements.txt" ]; then
    pip3 install --no-cache-dir -r /rtos_workspace/src/requirements.txt
fi

# Set permissions for USB device
if [ -e "/dev/ttyUSB0" ]; then
    chmod 666 /dev/ttyUSB0
fi

echo "RTOS docker environmeent setup completed successfully!"
