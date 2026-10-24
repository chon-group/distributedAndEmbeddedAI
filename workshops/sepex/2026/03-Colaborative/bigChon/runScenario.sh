#!/bin/bash
FRAMEWORK="/usr/bin/jacamo"
WEBOTS="/usr/local/bin/webots"
SERIALPORT="/dev/ttyEmulatedPort0"

clear
if [[ ! -f "$FRAMEWORK"  ]] || [[ ! -f "$WEBOTS" ]] || [[ ! -e "$SERIALPORT" ]] 
then
    echo "Installing dependencies..."
    sudo clear
    echo "deb [trusted=yes] http://packages.chon.group/ chonos main" | sudo tee /etc/apt/sources.list.d/chonos.list
    sudo apt update
    sudo apt install linux-headers-`uname -r` -y
    sudo apt install chonos-serial-port-emulator webots xterm -y
    clear
else
    echo "The computer has JasonEmbedded and Webots"
fi

echo "Starting Simulated World..."
exec webots Simulator/worlds/mundo.wbt
#PID_WEBOTS=$!

#echo "After Webots load, press any button to continue..."
#read
#jacamo MultiAgentSystem/bigAgent2.jcm
#kill $PID_WEBOTS

#clear