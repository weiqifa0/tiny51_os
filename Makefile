CC	= sdcc --debug

all:clean tiny51_os.hex

flash:clean tiny51_os.hex
	stcgal -b 1500000 -l 2400 -p /dev/tty.usbserial-130 main.hex

tiny51_os.hex:main.ihx
	packihx main.ihx > main.hex

main.ihx:main.c task_scheduling_core.rel platform_interface.rel lcd1602.rel uart.rel eeprom.rel gpio_i2c_interface.rel key.rel ring_buff.rel
	$(CC) main.c task_scheduling_core.rel platform_interface.rel lcd1602.rel uart.rel eeprom.rel gpio_i2c_interface.rel key.rel ring_buff.rel

task_scheduling_core.rel:./task_scheduling_core/task_scheduling_core.c
	$(CC) -c ./task_scheduling_core/task_scheduling_core.c

platform_interface.rel:./chip_platform/platform_interface.c
	$(CC) -c ./chip_platform/platform_interface.c

lcd1602.rel:./device/lcd1602.c
	$(CC) -c ./device/lcd1602.c

uart.rel:./device/uart.c
	$(CC) -c ./device/uart.c

eeprom.rel:./device/eeprom.c
	$(CC) -c ./device/eeprom.c

key.rel:./device/key.c
	$(CC) -c ./device/key.c

gpio_i2c_interface.rel:./driver/gpio_i2c_interface.c
	$(CC) -c ./driver/gpio_i2c_interface.c

ring_buff.rel:./module/ring_buff.c
	$(CC) -c .//module/ring_buff.c

.PHONY:clean
clean:
	rm -rf *.bin *.hex *.asm *.ihx *.lk *.lst *.map *.mem *.rel *.rst *.sym *.adb *.omf *.cdb