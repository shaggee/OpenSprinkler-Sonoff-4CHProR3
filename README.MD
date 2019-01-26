# **OpenSprinkler for Sonoff 4CH Firmware**

This is the unified OpenSprinkler firmware adapted to runs on Sonoff 4ch, without a display and expansion boards.

TODO: Prepare a PR with all modification to be added to the original OpenSklinkler-Firmware repo.

![alt text](https://raw.githubusercontent.com/bibarrav/OpenSprinkler-Sonoff4ch/master/sonoff4ch.jpg)

# Building the firmware

## Hacking the Sonoff 4ch

For this setup, if you want to use a regular Sonoff 4Ch (Rev1/Rev2)is needed to split the load in (AC) and Relays, because the most irrigation valves are AC 24v poweded.  If you want to use a Sonoff 4ch Pro, skip this step.

  - Disconect any power or connection
  - Open the Sonoff putting off the 4 screws on the back
  - Using a soldering iron, remove contacts (solder) between the resistor and the first relay.  In the next images the zones are yellow colored.
  
![alt text](https://raw.githubusercontent.com/bibarrav/OpenSprinkler-Sonoff4ch/master/sonoff4ch-front.jpg)
![alt text](https://raw.githubusercontent.com/bibarrav/OpenSprinkler-Sonoff4ch/master/sonoff4ch-front-zoom.jpg)

![alt text](https://raw.githubusercontent.com/bibarrav/OpenSprinkler-Sonoff4ch/master/sonoff4ch-back.jpg)
![alt text](https://raw.githubusercontent.com/bibarrav/OpenSprinkler-Sonoff4ch/master/sonoff4ch-back-zoom.jpg)

  - Check with a multimeter the non continuity between both points.

## Mappings

Internals:
  - Blue LED or WiFi LED show WiFi connectivity status: ON=WiFi Connected / SlowBlink=Connecting / FastBlink=Initializing
  - Stations 1 to 4 are mapped to Relays 1 to 4.
  - Statios 5 to 8 are soft stations, you can use with a HTTP, like another sonoff basic or pow with Sonoff-Tasmota firmware for example.

Externals:

![alt text](https://raw.githubusercontent.com/bibarrav/OpenSprinkler-Sonoff4ch/master/sonoff4ch-GPIO-Available.png)

  - 102      --> Flow Sensor    --> GPIO02
  - VCC3.3  --> Positive 3.3v
  - RX     --> External Relay --> GPIO03 Serial TXD
  - TX      --> Rain Sensor    --> GPIO01 Serial RXD
  - GND     --> Negative

## Preparing Sonoff to upload

  - Disconect power from Sonoff
  - Hold button 1 and connect serial adaptor
  - Release the button after 5 secs
  - Check that all LEDs are OFF

## Ardunino IDE

First, configure the IDE:
  - Add this URL to the Board Manager : http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Additional info https://github.com/esp8266/Arduino
  - Install the ESP8266 version 2.4.1 with the Arduino IDE Board Manager Menu
  - Configure board options as follows:
  
![alt text](https://raw.githubusercontent.com/bibarrav/OpenSprinkler-Sonoff4ch/master/Arduino-IDE-Config.PNG)

Second, Donwload and updload the code:
  - Download the code in .zip
  - Extract zip file
  - Open OpenSprinkler-Sonoff4ch/OpenSprinkler-Sonoff4ch.ino
  - In Arduino IDE, go to Upload

## Linux (command-line)

First, download code needed:

    $ mkdir ~/workspace
    $ cd ~/workspace
    $ git glone https://github.com/bibarrav/OpenSprinkler-Sonoff4ch
    $ git clone https://github.com/esp8266/Arduino.git esp8266_2.4
    $ cd esp8266_2.4
    $ git checkout tags/2.4.1
    $ cd tools
    $ python get.py

Second, make some change to ESP Core code:

  - Go to ~/esp8266_2.4/cores/esp8266
  - Open file Updater.h, and locate line 144 that says **private:**
  - Right above that line, add a function as follows:
    
      **void reset() { _reset(); }**
    
  - basically it wraps the private _reset() function into a public reset() function.  

Third, compile the firmware:

    $ cd ~/workspace/OpenSprinkler-Sonoff4ch
    $ make -f make.lin30

Finally, upload the created firmware to the Sonoff.
  
Enjoy!
