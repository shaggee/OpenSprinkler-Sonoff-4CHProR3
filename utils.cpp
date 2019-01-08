/* OpenSprinkler Unified (AVR/RPI/BBB/LINUX) Firmware
 * Copyright (C) 2015 by Ray Wang (ray@opensprinkler.com)
 *
 * Utility functions
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

#include "utils.h"
#include "OpenSprinkler.h"
extern OpenSprinkler os;

#include <FS.h>

void write_to_file(const char *name, const char *data, int size, int pos, bool trunc) {
  if (!os.status.has_sd)  return;

  char fn[12];
  strcpy_P(fn, name);
  
    File f;
    if(trunc) {
      f = SPIFFS.open(fn, "w");
    } else {
      f = SPIFFS.open(fn, "r+");
      if(!f) f = SPIFFS.open(fn, "w");
    }    
    if(!f) {f.close(); return;}
    if(pos) f.seek(pos, SeekSet);
    if(size==0) {
      f.write((byte*)" ", 1);  // hack to circumvent SPIFFS bug involving writing empty file
    } else {
      f.write((byte*)data, size);
    }
    f.close();
}

bool read_from_file(const char *name, char *data, int maxsize, int pos) {
  if (!os.status.has_sd)  { data[0]=0; return false; }

  char fn[12];
  strcpy_P(fn, name);
  
    File f = SPIFFS.open(fn, "r");
    if(!f) {
      data[0]=0;
      f.close();
      return true;  // return true but with empty string
    }
    if(pos)  f.seek(pos, SeekSet);
    int len = f.read((byte*)data, maxsize);
    if(len>0) data[len]=0;
    if(len==1 && data[0]==' ') data[0] = 0;  // hack to circumvent SPIFFS bug involving writing empty file
    data[maxsize-1]=0;
    f.close();
    return true;
}

void remove_file(const char *name) {
  if (!os.status.has_sd)  return;

  char fn[12];
  strcpy_P(fn, name);
  
  if(!SPIFFS.exists(fn)) return;
  SPIFFS.remove(fn);
}

// nvm functions for ESP8266
// do not use File.readBytes or readBytesUntil because it's very slow
void nvm_read_block(void *dst, const void *src, int len) {
  File f = SPIFFS.open(NVM_FILENAME, "r");
  if(f) {
    f.seek((unsigned int)src, SeekSet);
    f.read((byte*)dst, len);
    f.close();
  }
}

void nvm_write_block(const void *src, void *dst, int len) {
  File f = SPIFFS.open(NVM_FILENAME, "r+");
  if(!f) f = SPIFFS.open(NVM_FILENAME, "w");
  if(f) {
    f.seek((unsigned int)dst, SeekSet);
    f.write((byte*)src, len);
    f.close();
  }
}

byte nvm_read_byte(const byte *p) {
  File f = SPIFFS.open(NVM_FILENAME, "r");
  byte v = 0;
  if(f) {
    f.seek((unsigned int)p, SeekSet);
    f.read((byte*)&v, 1);
    f.close();
  }
  return v;
}

void nvm_write_byte(const byte *p, byte v) {
  File f = SPIFFS.open(NVM_FILENAME, "r+");
  if(!f) f = SPIFFS.open(NVM_FILENAME, "w");
  if(f) {
    f.seek((unsigned int)p, SeekSet);
    f.write(&v, 1);
    f.close();  
  }
}


// copy n-character string from program memory with ending 0
void strncpy_P0(char* dest, const char* src, int n) {
  byte i;
  for(i=0;i<n;i++) {
    *dest=pgm_read_byte(src++);
    dest++;
  }
  *dest=0;
}

// compare a string to nvm
byte strcmp_to_nvm(const char* src, int _addr) {
  byte c1, c2;
  byte *addr = (byte*)_addr;
  while(1) {
    c1 = nvm_read_byte(addr++);
    c2 = *src++;
    if (c1==0 || c2==0)
      break;
    if (c1!=c2)  return 1;
  }
  return (c1==c2) ? 0 : 1;
}

// resolve water time
/* special values:
 * 65534: sunrise to sunset duration
 * 65535: sunset to sunrise duration
 */
ulong water_time_resolve(uint16_t v) {
  if(v==65534) {
    return (os.nvdata.sunset_time-os.nvdata.sunrise_time) * 60L;
  } else if(v==65535) {
    return (os.nvdata.sunrise_time+1440-os.nvdata.sunset_time) * 60L;
  } else  {
    return v;
  }
}

// encode a 16-bit signed water time (-600 to 600)
// to unsigned byte (0 to 240)
byte water_time_encode_signed(int16_t i) {
  i=(i>600)?600:i;
  i=(i<-600)?-600:i;
  return (i+600)/5;
}

// decode a 8-bit unsigned byte (0 to 240)
// to a 16-bit signed water time (-600 to 600)
int16_t water_time_decode_signed(byte i) {
  i=(i>240)?240:i;
  return ((int16_t)i-120)*5;
}