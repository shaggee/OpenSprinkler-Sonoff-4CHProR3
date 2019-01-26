/* OpenSprinkler Unified (AVR/RPI/BBB/LINUX/ESP8266) Firmware
 * Copyright (C) 2015 by Ray Wang (ray@opensprinkler.com)
 *
 * OpenSprinkler macro defines and hardware pin assignments
 * Feb 2015 @ OpenSprinkler.com
 *
 * This file is part of the OpenSprinkler library
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef _DEFINES_H
#define _DEFINES_H

typedef unsigned char byte;
typedef unsigned long ulong;

  #define TMP_BUFFER_SIZE      255   // scratch buffer size

/** Firmware version, hardware version, and maximal values */
#define OS_FW_VERSION  218  // Firmware version: 218 means 2.1.8
                            // if this number is different from the one stored in non-volatile memory
                            // a device reset will be automatically triggered

#define OS_FW_MINOR      2  // Firmware minor version

/** Hardware version base numbers */
#define OS_HW_VERSION_BASE   0x00
#define OSPI_HW_VERSION_BASE 0x40
#define OSBO_HW_VERSION_BASE 0x80
#define SIM_HW_VERSION_BASE  0xC0

/** Hardware type macro defines */
#define HW_TYPE_AC           0xAC   // standard 24VAC for 24VAC solenoids only, with triacs
#define HW_TYPE_DC           0xDC   // DC powered, for both DC and 24VAC solenoids, with boost converter and MOSFETs
#define HW_TYPE_LATCH        0x1A   // DC powered, for DC latching solenoids only, with boost converter and H-bridges
#define HW_TYPE_UNKNOWN      0xFF

/** File names */
#define WEATHER_OPTS_FILENAME "wtopts.txt"    // weather options file
#define STATION_ATTR_FILENAME "stns.dat"      // station attributes data file
#define WIFI_FILENAME         "wifi.dat"      // wifi credentials file
#define IFTTT_KEY_FILENAME    "ifkey.txt"
#define IFTTT_KEY_MAXSIZE     128
#define STATION_SPECIAL_DATA_SIZE  (TMP_BUFFER_SIZE - 8)

#define FLOWCOUNT_RT_WINDOW   30    // flow count window (for computing real-time flow rate), 30 seconds

/** Station type macro defines */
#define STN_TYPE_STANDARD    0x00
#define STN_TYPE_RF          0x01
#define STN_TYPE_REMOTE      0x02
#define STN_TYPE_GPIO        0x03	// Support for raw connection of station to GPIO pin
#define STN_TYPE_HTTP        0x04	// Support for HTTP Get connection
#define STN_TYPE_OTHER       0xFF

#define IFTTT_PROGRAM_SCHED   0x01
#define IFTTT_RAINSENSOR      0x02
#define IFTTT_FLOWSENSOR      0x04
#define IFTTT_WEATHER_UPDATE  0x08
#define IFTTT_REBOOT          0x10
#define IFTTT_STATION_RUN     0x20

/** Sensor type macro defines */
#define SENSOR_TYPE_NONE    0x00
#define SENSOR_TYPE_RAIN    0x01  // rain sensor
#define SENSOR_TYPE_FLOW    0x02  // flow sensor
#define SENSOR_TYPE_PSWITCH 0xF0  // program switch
#define SENSOR_TYPE_OTHER   0xFF

/** WiFi related defines */
#define WIFI_MODE_AP       0xA9
#define WIFI_MODE_STA      0x2A

#define OS_STATE_INITIAL        0
#define OS_STATE_CONNECTING     1
#define OS_STATE_CONNECTED      2
#define OS_STATE_TRY_CONNECT    3

#define LED_FAST_BLINK 100
#define LED_SLOW_BLINK 500

/** Non-volatile memory (NVM) defines */
 // NVM defines for RPI/BBB/LINUX/ESP8266

/** 8KB NVM (RPI/BBB/LINUX/ESP8266) data structure:
  * |         |     |  ---STRING PARAMETERS---      |           |   ----STATION ATTRIBUTES-----      |          |
  * | PROGRAM | CON | PWD | LOC | JURL | WURL | KEY | STN_NAMES | MAS | IGR | MAS2 | DIS | SEQ | SPE | OPTIONS  |
  * |  (6127) |(12) |(36) |(48) | (48) | (48) |(24) |   (1728)  | (9) | (9) |  (9) | (9) | (9) | (9) |   (67)   |
  * |         |     |     |     |      |      |     |           |     |     |      |     |     |     |          |
  * 0       6127  6139   6175  6223  6271   6319   6343        8071  8080  8089   8098  8107  8116  8125      8192
  */

  // These are kept the same as AVR for compatibility reasons
  // But they can be increased if needed
  #define NVM_FILENAME        "nvm.dat" // for RPI/BBB, nvm data is stored in a file

  #define MAX_EXT_BOARDS    0  // maximum number of 8-station exp. boards (a 16-station expander counts as 2)
  #define MAX_NUM_STATIONS  ((1+MAX_EXT_BOARDS)*8)  // maximum number of stations

  #define NVM_SIZE            8192
  #define STATION_NAME_SIZE   24    // maximum number of characters in each station name

  #define MAX_PROGRAMDATA     6127  // program data
  #define MAX_NVCONDATA       12     // non-volatile controller data
  #define MAX_USER_PASSWORD   36    // user password
  #define MAX_LOCATION        48    // location string
  #define MAX_JAVASCRIPTURL   48    // javascript url
  #define MAX_WEATHERURL      48    // weather script url
  #define MAX_WEATHER_KEY     24    // weather api key


/** NVM data addresses */
#define ADDR_NVM_PROGRAMS      (0)   // program starting address
#define ADDR_NVM_NVCONDATA     (ADDR_NVM_PROGRAMS+MAX_PROGRAMDATA)
#define ADDR_NVM_PASSWORD      (ADDR_NVM_NVCONDATA+MAX_NVCONDATA)
#define ADDR_NVM_LOCATION      (ADDR_NVM_PASSWORD+MAX_USER_PASSWORD)
#define ADDR_NVM_JAVASCRIPTURL (ADDR_NVM_LOCATION+MAX_LOCATION)
#define ADDR_NVM_WEATHERURL    (ADDR_NVM_JAVASCRIPTURL+MAX_JAVASCRIPTURL)
#define ADDR_NVM_WEATHER_KEY   (ADDR_NVM_WEATHERURL+MAX_WEATHERURL)
#define ADDR_NVM_STN_NAMES     (ADDR_NVM_WEATHER_KEY+MAX_WEATHER_KEY)
#define ADDR_NVM_MAS_OP        (ADDR_NVM_STN_NAMES+MAX_NUM_STATIONS*STATION_NAME_SIZE) // master op bits
#define ADDR_NVM_IGNRAIN       (ADDR_NVM_MAS_OP+(MAX_EXT_BOARDS+1))  // ignore rain bits
#define ADDR_NVM_MAS_OP_2      (ADDR_NVM_IGNRAIN+(MAX_EXT_BOARDS+1)) // master2 op bits
#define ADDR_NVM_STNDISABLE    (ADDR_NVM_MAS_OP_2+(MAX_EXT_BOARDS+1))// station disable bits
#define ADDR_NVM_STNSEQ        (ADDR_NVM_STNDISABLE+(MAX_EXT_BOARDS+1))// station sequential bits
#define ADDR_NVM_STNSPE        (ADDR_NVM_STNSEQ+(MAX_EXT_BOARDS+1)) // station special bits (i.e. non-standard stations)
#define ADDR_NVM_OPTIONS       (ADDR_NVM_STNSPE+(MAX_EXT_BOARDS+1))  // options

/** Default password, location string, weather key, script urls */
#define DEFAULT_PASSWORD          "a6d82bced638de3def1e9bbb4983225c"  // md5 of 'opendoor'
#define DEFAULT_LOCATION          "Boston,MA"
#define DEFAULT_WEATHER_KEY       ""
#define DEFAULT_JAVASCRIPT_URL    "https://ui.opensprinkler.com/js"
#define DEFAULT_WEATHER_URL       "weather.opensprinkler.com"
#define DEFAULT_IFTTT_URL         "maker.ifttt.com"

/** Macro define of each option
  * Refer to OpenSprinkler.cpp for details on each option
  */
typedef enum {
  OPTION_FW_VERSION = 0,
  OPTION_TIMEZONE,
  OPTION_USE_NTP,
  OPTION_USE_DHCP,
  OPTION_STATIC_IP1,
  OPTION_STATIC_IP2,
  OPTION_STATIC_IP3,
  OPTION_STATIC_IP4,
  OPTION_GATEWAY_IP1,
  OPTION_GATEWAY_IP2,
  OPTION_GATEWAY_IP3,
  OPTION_GATEWAY_IP4,
  OPTION_HTTPPORT_0,
  OPTION_HTTPPORT_1,
  OPTION_HW_VERSION,
  OPTION_EXT_BOARDS,
  OPTION_SEQUENTIAL_RETIRED,
  OPTION_STATION_DELAY_TIME,
  OPTION_MASTER_STATION,
  OPTION_MASTER_ON_ADJ,
  OPTION_MASTER_OFF_ADJ,
  OPTION_SENSOR1_TYPE,
  OPTION_SENSOR1_OPTION,
  OPTION_WATER_PERCENTAGE,
  OPTION_DEVICE_ENABLE,
  OPTION_IGNORE_PASSWORD,
  OPTION_DEVICE_ID,
  OPTION_LCD_CONTRAST,
  OPTION_LCD_BACKLIGHT,
  OPTION_LCD_DIMMING,
  OPTION_BOOST_TIME,
  OPTION_USE_WEATHER,
  OPTION_NTP_IP1,
  OPTION_NTP_IP2,
  OPTION_NTP_IP3,
  OPTION_NTP_IP4,
  OPTION_ENABLE_LOGGING,
  OPTION_MASTER_STATION_2,
  OPTION_MASTER_ON_ADJ_2,
  OPTION_MASTER_OFF_ADJ_2,
  OPTION_FW_MINOR,
  OPTION_PULSE_RATE_0,
  OPTION_PULSE_RATE_1,
  OPTION_REMOTE_EXT_MODE,
  OPTION_DNS_IP1,
  OPTION_DNS_IP2,
  OPTION_DNS_IP3,
  OPTION_DNS_IP4,
  OPTION_SPE_AUTO_REFRESH,
  OPTION_IFTTT_ENABLE,
  OPTION_SENSOR2_TYPE,
  OPTION_SENSOR2_OPTION,
  OPTION_RESET,
  NUM_OPTIONS	// total number of options
} OS_OPTION_t;

/** Log Data Type */
#define LOGDATA_STATION    0x00
#define LOGDATA_RAINSENSE  0x01
#define LOGDATA_RAINDELAY  0x02
#define LOGDATA_WATERLEVEL 0x03
#define LOGDATA_FLOWSENSE  0x04

#undef OS_HW_VERSION

/** Hardware defines */
// Hardware defines for RPI/BBB/ESP8266

    #define OS_HW_VERSION    (OS_HW_VERSION_BASE+30)

    #define PIN_CURR_SENSE    A0
    #define PIN_FREE_LIST     {} // free GPIO pin for relays
    #define ETHER_BUFFER_SIZE   4096

    extern byte PIN_BUTTON_1;
    extern byte PIN_BUTTON_2;
    extern byte PIN_BUTTON_3;
    extern byte PIN_BUTTON_4;
    extern byte PIN_RELAY_1;
    extern byte PIN_RELAY_2;
    extern byte PIN_RELAY_3;
    extern byte PIN_RELAY_4;
    extern byte PIN_RELAY_5;
    extern byte PIN_LED;
    extern byte PIN_RFRX;
    extern byte PIN_RFTX;
    extern byte PIN_BOOST;
    extern byte PIN_BOOST_EN;
    extern byte PIN_LATCH_COM;
    extern byte PIN_SENSOR1;
    extern byte PIN_SENSOR2;
    extern byte PIN_RAINSENSOR;
    extern byte PIN_FLOWSENSOR;

  #define ENABLE_DEBUG
  #if defined(ENABLE_DEBUG)
      #define DEBUG_BEGIN(x)   Serial.begin(x)
      #define DEBUG_PRINT(x)   Serial.print(x)
      #define DEBUG_PRINTLN(x) Serial.println(x)
    #else
    #define DEBUG_BEGIN(x) {}
    #define DEBUG_PRINT(x) {}
    #define DEBUG_PRINTLN(x) {}
  #endif

// end of Hardawre defines

/** Other defines */
// button values
#define BUTTON_1            0x01
#define BUTTON_2            0x02
#define BUTTON_3            0x04

// button status values
#define BUTTON_NONE         0x00  // no button pressed
#define BUTTON_MASK         0x0F  // button status mask
#define BUTTON_FLAG_HOLD    0x80  // long hold flag
#define BUTTON_FLAG_DOWN    0x40  // down flag
#define BUTTON_FLAG_UP      0x20  // up flag

// button timing values
#define BUTTON_DELAY_MS        1  // short delay (milliseconds)
#define BUTTON_HOLD_MS      1000  // long hold expiration time (milliseconds)

// button mode values
#define BUTTON_WAIT_NONE       0  // do not wait, return value immediately
#define BUTTON_WAIT_RELEASE    1  // wait until button is release
#define BUTTON_WAIT_HOLD       2  // wait until button hold time expires

#define DISPLAY_MSG_MS      2000  // message display time (milliseconds)

#endif// _DEFINES_H


