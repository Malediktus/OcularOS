GCCPARAMS = -m32 -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = 	src/boot/loader.o \
			src/lib/utils.o \
			src/lib/timer.o \
			src/hardware/idt.o \
			src/hardware/isr.o \
			src/hardware/load_gdt.o \
			src/hardware/gdt.o \
			src/hardware/port.o \
			src/hardware/interrupts.o \
			src/hardware/pci.o \
			src/driver/ata.o \
			src/filesystem/msdospart.o \
			src/filesystem/fat32.o \
			src/kernel.o

all: kernel.iso

%.o: %.c
	gcc $(GCCPARAMS) -c -o $@ $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

%.o: %.asm
	nasm $< -f elf -o $@

kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

kernel.iso: kernel.bin grub.cfg
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	cp grub.cfg iso/boot/grub/

	grub-mkrescue --output=$@ iso
	rm -rf iso
	rm -rf build/*
	mv -f */*.o */*/*.o *.o *.bin build

clean:
	rm -rf iso
	rm -f build/* *.bin *.iso
	rm -f */*.o */*/*.o *.o