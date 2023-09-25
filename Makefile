CC	= sdcc

all:tiny51_os.hex

# tiny51_os.bin:tiny51_os.hex
#	objcopy -I ihex -O binary tiny51_os.hex tiny51_os.bin

tiny51_os.hex:main.ihx
	packihx main.ihx > led.hex

main.ihx:main.c
	$(CC) main.c task_scheduling_core.ihx

task_scheduling_core.ihx:task_scheduling_core/task_scheduling_core.c
	$(CC) -c task_scheduling_core/task_scheduling_core.c

.PHONY:clean
clean:
	rm -rf *.bin *.hex *.asm *.ihx *.lk *.lst *.map *.mem *.rel *.rst *.sym