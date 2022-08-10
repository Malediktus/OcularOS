FILES = ./build/kernel.asm.o \
		./build/kernel.o \
		./build/isr80h/isr80h.o \
		./build/isr80h/misc.o \
		./build/isr80h/io.o \
		./build/disk/disk.o \
		./build/disk/streamer.o \
		./build/task/process.o \
		./build/task/task.o \
		./build/task/task.asm.o \
		./build/task/tss.asm.o \
		./build/fs/pparser.o \
		./build/fs/file.o \
		./build/fs/fat/fat16.o \
		./build/string/string.o \
		./build/idt/idt.asm.o \
		./build/idt/idt.o \
		./build/memory/memory.o \
		./build/io/io.asm.o \
		./build/gdt/gdt.o \
		./build/gdt/gdt.asm.o \
		./build/memory/heap/heap.o \
		./build/memory/heap/kheap.o \
		./build/memory/paging/paging.o \
		./build/memory/paging/paging.asm.o \
		./build/keyboard/keyboard.o \
		./build/keyboard/classic.o


INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all: ./bin/kernel.bin user_programs bootloader

./bin/kernel.bin: $(FILES)
	@echo "=============== LINKING ==============="
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin ./build/kernelfull.o

./build/%.asm.o: ./src/%.asm
	@echo "=============== COMPILING $^ ==============="
	nasm -f elf -g $^ -o $@
	@echo "\n"

./build/%.o: ./src/%.c
	@echo "=============== COMPILING $^ ==============="
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c $^ -o $@
	echo "\n"

run: all
	qemu-system-i386 -hda bin/os.bin

run-build:
	qemu-system-i386 -hda bin/os.bin

user_programs:
	cd ../programs/blank && $(MAKE) all

user_programs_clean:
	cd ../programs/blank && $(MAKE) clean

bootloader:
	cd ../bootloader && $(MAKE) all

bootloader_clean:
	cd ../bootloader && $(MAKE) clean

clean: user_programs_clean bootloader_clean
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./bin/os.bin
	rm -rf ./bin/kernelfull.o
	rm -rf ./bin/${FILES}