all: flash.bin flash.dis

flash.bin: flash.elf
	$(OBJCOPY) -O binary $< $@
flash.dis: flash.elf
	$(OBJDUMP) -d $< > $@

flash.elf: foo.o entry.o header.o log.o
	$(CC) -o $@ $^ -T linker.ld -nostdlib -fno-exceptions

%.o: %.ll
	llc -o $@ --filetype=obj -march=arm -mcpu=arm7tdmi $< -opaque-pointers

install: all
	mkdir -pv $(out)
	cp flash.elf flash.dis flash.bin $(out)/
	hexdump -C --length 0x120 flash.bin
