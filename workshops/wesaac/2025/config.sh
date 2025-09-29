#!/bin/bash

if [[ ! -f ~/.updated ]]; then 
	sudo apt -y update;
	sudo apt -y upgrade;
	
	touch ~/.updated
	sudo reboot;
fi

sudo apt install -y git gcc g++ binutils make ;

echo "deb [trusted=yes] http://packages.chon.group/ chonos main" | sudo tee /etc/apt/sources.list.d/chonos.list

sudo apt -y update ;
sudo apt -y install chonide chonos-simulide webots chonos-serial-port-emulator ;

./compile_all.sh
