LOADER_FILES = ./build/loader.asm.o \
				./build/loader.o \
				./build/lib/screen.o \
				./build/lib/string.o \
				./build/lib/memory.o \
				./build/port.asm.o \
				./build/heap/heap.o \
				./build/heap/kheap.o \
				./build/disk/disk.o \
				./build/disk/diskstream.o \
				./build/disk/pathparser.o \
				./build/disk/file.o \
				./build/disk/fat16.o

INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all: ./bin/boot.bin ./bin/loader.bin
	rm -rf ../kernel/bin/os.bin
	dd if=./bin/boot.bin >> ../kernel/bin/os.bin
	dd if=./bin/loader.bin >> ../kernel/bin/os.bin
	dd if=/dev/zero bs=1048576 count=16 >> ../kernel/bin/os.bin
	# !!! Make sure the right usb stick is plugged in
	# !!! It will be overriten
	sudo sh ./copy_data.sh 0
	diskutil mount /dev/disk2
	# Copying files to /Volumes/OCULAR\ BOOT
	cp ../kernel/bin/kernel.bin /Volumes/OCULAR\ BOOT/
	cp ../kfont.psf /Volumes/OCULAR\ BOOT/
	cp ../debug.txt /Volumes/OCULAR\ BOOT/
	mkdir /Volumes/OCULAR\ BOOT/bin
	mkdir /Volumes/OCULAR\ BOOT/usr
	mkdir /Volumes/OCULAR\ BOOT/usr/bin
	mkdir /Volumes/OCULAR\ BOOT/usr/lib
	mkdir /Volumes/OCULAR\ BOOT/usr/include
	cp ../programs/stdlib/stdlib.elf /Volumes/OCULAR\ BOOT/usr/lib
	cp ../programs/stdlib/include/**.h /Volumes/OCULAR\ BOOT/usr/include
	cp ../programs/blank/blank.elf /Volumes/OCULAR\ BOOT/usr/bin
	cp ../programs/calculator/calc /Volumes/OCULAR\ BOOT/usr/bin
	cp ../programs/shell/shell.elf /Volumes/OCULAR\ BOOT/bin
	# End of copying files
	diskutil umount /dev/disk2
	sudo sh ./copy_data.sh 1

./bin/loader.bin: $(LOADER_FILES)
	i686-elf-ld -g -relocatable $(LOADER_FILES) -o ./build/loaderfull.o
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -o ./bin/loader.bin ./build/loaderfull.o

./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin

./build/%.asm.o: ./src/%.asm
	nasm -f elf -g $^ -o $@

./build/%.o: ./src/%.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c $^ -o $@

run: all
	qemu-system-i386 -hda ../kernel/bin/os.bin

run-build:
	qemu-system-i386 -hda ../kernel/bin/os.bin

clean:
	rm -rf ./bin/boot.bin
	rm -rf ./bin/loader.bin
	rm -rf ./build/loaderfull.o
	rm -rf ./build/${LOADER_FILES}