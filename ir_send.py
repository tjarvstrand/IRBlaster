#!/usr/bin/env python
import serial
import sys

baudRate = 9600

def send(port, protocol, code, bits, times = 1, sleep = 100):
    data = ("SEND %s %s %s %s %s" % (protocol, code, bits, times, sleep)).encode('ascii')
    with serial.Serial(port, baudRate, timeout = 1000) as conn:
        conn.write(data)
        print(conn.readline())

if __name__ == '__main__':
    port = sys.argv[1]
    protocol = int(sys.argv[2])
    code = int(sys.argv[3])
    bits = int(sys.argv[4])
    times = int(sys.argv[5])
    sleep = int(sys.argv[6])
    send(port, protocol, code, bits, times, sleep)
