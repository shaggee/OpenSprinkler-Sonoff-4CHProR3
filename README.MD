# **OpenSprinkler for Sonoff 4CH Pro R3 Firmware**

This if fork from bibarrav/OpenSprinkler-Sonoff4ch Repo. I maded some small changes and fixes to fit exactly on SonOff 4CH PRO R3, because in original Repo they not work with it. Because I'm not a programmer, changes are minor but fully tested with mine SonOff. If you get one of these 4ch ports relay switches, its possible to use just the ready .bin file to upload. Version of OpenSprinkler is 2.1.8.

- Fixed - GPIO on Buttons and Relays;
- Fixed - Reverse using of relays HIGH->LOW & LOW->HIGH; // In original firmware relay start by default ON, and when program is used they goes off for selected time. //
- Addedd - function for factory reset; (Without it you cannot switch WiFi network)
- Addedd - Ready to use binary (OpenSprinkler-Sonoff4ch.ino.generic.bin) - not need to compile by yourself;


## Upload firmware using Linux

Using USB to TTL covertor with installed esptool.py when connect to internal serial with following commands you can flash the image :

    $ esptool.py --port /dev/ttyUSB0 flash_id
    $ esptool.py --port /dev/ttyUSB0 erase_flash
    $ esptool.py --port /dev/ttyUSB0 write_flash -fs 1MB -fm dout 0x0 OpenSprinkler-Sonoff-4chProR3.bin


## Resetting Instruction : 

1. Power OFF
2. Hold Button 4 & Power ON without release Button 4
3. When Relay 4 light ON, release Button 4 and Press and Hold Button 3
4. When Relay 3 is ON, continue to Hold Button 3 around 3-4 sec. (After more 5 sec. release Button 3)
5. When All (4) Relays get ON and after 1 sec, get OFF, the board is in Initial state.
6. Open your network manager in your mobile device, look for Access Point with name OS_XXXXXX and connect to it.
7. Open browser on your mobile device and go to 192.168.1.4, select your favorite network and Enjoy!


Note : Just swapped Button1 to Button4 function from Original/Original OpenSprinkler, because when Button1 is on Hold when powerOn, the device goes in flash mode. In original firmware Button1 is used to start reset function, so swapping GPIO in defines.cpp will do the trick. I personaly can't readd new fuction for Button4, so using existing is OK for me.


# Here it is the original README from Repo : 

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
