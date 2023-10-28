# tiny51_os
## 编译器安装
- sudo apt-get install sdcc
- sdcc 在各种平台上都有，所以这部分真的是超级爽的。

## 使用帮助
因为我是用Mac上开发的，所以可以看看我的这篇文章

https://mp.weixin.qq.com/s/ZzN3_c5IVqDCRGJhWJxMzw

## 烧录
可以直接使用make flash进行烧录，但是要指定下自己的串口

# 基础技术讲解
当我们使用12MHZ的晶振时，单片机的机器周期是1us，对于机器周期，我们把它看成单片机里的最小时间单位。
1ms/1us=1000，也就是要计数1000个数，故T0初值=65535-1000+1（因为计数器在65536时才算溢出）=64536。
转换成16进制就是0xFC18，高八位0xFC，低八位0x18分别赋值。然后，1s=1000ms，只要加一个程序内部的自增变量（interrupt_cnt），每溢出一次自加1，当该变量加到了1000时，就代表经过了一秒钟了

# Macbook使用的串口工具
https://github.com/tio/tio

或者直接写个python脚本来测试串口
```python
# -*- coding: utf-8 -*-
import serial
print (serial.__version__)
#3.4
ser = serial.Serial(
    port='/dev/tty.usbserial-1130',
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
```
