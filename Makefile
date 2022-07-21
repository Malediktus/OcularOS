FILES = ./build/kernel.asm.o \
		./build/kernel.o \
		./build/lib/screen.o \
		./build/lib/string.o \
		./build/lib/memory.o \
		./build/hardware/idt.o \
		./build/hardware/idt.asm.o \
		./build/hardware/port.asm.o \
		./build/memory/heap.o \
		./build/memory/kheap.o \
		./build/memory/paging.o \
		./build/memory/paging.asm.o \
		./build/drivers/disk.o


INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin

./bin/kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin ./build/kernelfull.o

./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin

./build/%.asm.o: ./src/%.asm
	nasm -f elf -g $^ -o $@

./build/%.o: ./src/%.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c $^ -o $@

run: all
	qemu-system-i386 -hda bin/os.bin

clean:
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./bin/os.bin
	rm -rf ./bin/kernelfull.o
	rm -rf ./bin/${FILES}