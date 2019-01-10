# OpenSprinkler ESP Firmware

This is a unified OpenSprinkler firmware adapted to runs on Sonoff 4ch, without and Display and expansion boards.

# Building the firmware

## Prep Sonoff 4CH

  - Disconect power from Sonoff
  - Hold button 1 and connect serial adaptor
  - Release the button after 5 secs
  - Check that all LEDs are OFF

## Ardunino IDE

  - Download the code in .zip
  - Extract zip file
  - Open OpenSprinkler-Sonoff4ch/OpenSprinkler-Sonoff4ch.ino
  - In Arduino IDE, go to Upload

## Linux (command-line)

  $ mkdir ~/workspace
  $ cd ~/workspace
  $ git glone https://github.com/bibarrav/OpenSprinkler-Sonoff4ch
  $ git clone https://github.com/esp8266/Arduino.git esp8266_2.4
  $ cd esp8266_2.4
  $ git checkout tags/2.4.1
  $ cd tools
  $ python get.py
  
  - Go to ~/esp8266_2.4/cores/esp8266
  - Open file Updater.h, and locate line 144 that says **private:**
  - Right above that line, add a function as follows:
      **void reset() { _reset(); }**
    basically it wraps the private _reset() function into a public reset() function.  
  
  $ cd ~/workspace/OpenSprinkler-Sonoff4ch
  $ make -f make.lin30
  
  - Upload the created firmware to the Sonoff
  
  Enjoy!
