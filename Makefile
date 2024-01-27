CC	= sdcc

all:clean tiny51_os.hex

flash:clean tiny51_os.hex
	stcgal -p /dev/tty.usbserial-120 main.hex

tiny51_os.hex:main.ihx
	packihx main.ihx > main.hex

main.ihx:main.c task_scheduling_core.rel platform_interface.rel lcd1602.rel
	$(CC) main.c task_scheduling_core.rel platform_interface.rel lcd1602.rel

task_scheduling_core.rel:./task_scheduling_core/task_scheduling_core.c
	$(CC) -c ./task_scheduling_core/task_scheduling_core.c

platform_interface.rel:./chip_platform/platform_interface.c
	$(CC) -c ./chip_platform/platform_interface.c

lcd1602.rel:./drivers/lcd1602.c
	$(CC) -c ./drivers/lcd1602.c

.PHONY:clean
clean:
	rm -rf *.bin *.hex *.asm *.ihx *.lk *.lst *.map *.mem *.rel *.rst *.sym *.cdb *.omf