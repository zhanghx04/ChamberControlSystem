#!/bin/bash
set -e # Exit on error

# Check if USB device exists
if [ -e "/dev/ttyUSB0" ]; then
    chmod 666 /dev/ttyUSB0
fi

# Check SDK installation
if [ ! -d "$NETBURNER_SDK" ]; then
    echo "Error: NetBurner SDK not found at $NETBURNER_SDK"
    exit 1
fi

# Install any required services
if [ -f "/rtos_workspace/scripts/init_services.sh" ]; then
    source /rtos_workspace/scripts/init_services.sh
fi

# Start a shell by default
exec "$@"
