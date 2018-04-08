#!/usr/bin/env python
import serial
import sys

baudRate = 9600

if __name__ == '__main__':
    port = sys.argv[1]
    protocol = int(sys.argv[2])
    code = int(sys.argv[3])
    bits = int(sys.argv[4])
    data = ("SEND %s %s %s" % (protocol, code, bits)).encode('ascii')
    with serial.Serial(port, baudRate, timeout = 1000) as conn:
        conn.write(data)
        print(conn.readline())
