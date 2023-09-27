CC	= sdcc

all:clean tiny51_os.hex

# tiny51_os.bin:tiny51_os.hex
#	objcopy -I ihex -O binary tiny51_os.hex tiny51_os.bin

tiny51_os.hex:main.ihx
	packihx main.ihx > main.hex

main.ihx:main.c task_scheduling_core.rel
	$(CC) main.c task_scheduling_core.rel

task_scheduling_core.rel:./task_scheduling_core/task_scheduling_core.c
	$(CC) -c ./task_scheduling_core/task_scheduling_core.c

.PHONY:clean
clean:
	rm -rf *.bin *.hex *.asm *.ihx *.lk *.lst *.map *.mem *.rel *.rst *.sym