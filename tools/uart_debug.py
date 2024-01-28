# -*- coding: utf-8 -*-
import threading
import serial
import time
print (serial.__version__)
#3.4
import serial#导入串口通信库
uart = serial.Serial()

uart.port='/dev/tty.usbserial-130'
uart.baudrate=115200
uart.bytesize=8
uart.stopbits=1
uart.parity="N"
uart.open()
if(uart.isOpen()):
 print("serial open success!!!")
else:
 print("serial open failed!!!")

def uart_write():
    while True:
        print("uart w")
        uart.write(b'Hello, World!')  # 发送数据
        time.sleep(1)  # 等待1秒

def uart_read():
    while True:
        data = uart.read().decode("utf-8")
        if data:
            print("Received:", data.encode())


# 创建线程
write_thread = threading.Thread(target=uart_write)
read_thread = threading.Thread(target=uart_read)

# 启动线程
write_thread.start()
read_thread.start()

# 等待线程结束（可选，通常你可能希望让线程一直运行）
write_thread.join()
read_thread.join()

# while True:
#   #print ser.read()
#   buf = ser.read().decode("utf-8")
#   print("buf = ", buf)
#   #data_to_write = b'Hello, UART!
#   hex_value = "0x1A"
#   byte_value = bytes([int(hex_value, 16)])
#   ser.write(byte_value)
#   #ser.write(data_to_write)

uart.close()