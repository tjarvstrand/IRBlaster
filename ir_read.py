#!/usr/bin/env python

import serial
import struct
import sys

baudRate = 9600
def main():
    port = sys.argv[1]
    with serial.Serial(port, baudRate, timeout = 1000) as ser:
        ser.write('READ')
        ser.flush
        print ser.readline()

if __name__ == "__main__":
    main()
