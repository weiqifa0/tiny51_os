# -*- coding: utf-8 -*-
import serial
print (serial.__version__)
#3.4
ser = serial.Serial(
    port='/dev/tty.usbserial-130',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout = None
    #timeout = 1
)

while 1:
    #print ser.read()
    a = ser.read()
    print(a)
    #data_to_write = b'Hello, UART!
    hex_value = "0x1A"
    byte_value = bytes([int(hex_value, 16)])
    ser.write(byte_value)
    #ser.write(data_to_write)

    #ser.write('b')