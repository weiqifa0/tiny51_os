CC	= sdcc --debug

all:clean tiny51_os.hex

flash:clean tiny51_os.hex
	stcgal -b 1500000 -l 2400 -p /dev/tty.usbserial-130 main.hex

tiny51_os.hex:main.ihx
	packihx main.ihx > main.hex

main.ihx:main.c task_scheduling_core.rel platform_interface.rel lcd1602.rel uart.rel
	$(CC) main.c task_scheduling_core.rel platform_interface.rel lcd1602.rel uart.rel

task_scheduling_core.rel:./task_scheduling_core/task_scheduling_core.c
	$(CC) -c ./task_scheduling_core/task_scheduling_core.c

platform_interface.rel:./chip_platform/platform_interface.c
	$(CC) -c ./chip_platform/platform_interface.c

lcd1602.rel:./drivers/lcd1602.c
	$(CC) -c ./drivers/lcd1602.c

uart.rel:./drivers/uart.c
	$(CC) -c ./drivers/uart.c

.PHONY:clean
clean:
	rm -rf *.bin *.hex *.asm *.ihx *.lk *.lst *.map *.mem *.rel *.rst *.sym *.adb *.omf *.cdb