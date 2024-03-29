FILES = ./build/kernel.asm.o \
		./build/kernel.o \
		./build/syscall/isr80h.o \
		./build/syscall/misc.o \
		./build/syscall/io.o \
		./build/syscall/heap.o \
		./build/syscall/graphics.o \
		./build/syscall/file.o \
		./build/driver/disk/disk.o \
		./build/driver/disk/streamer.o \
		./build/task/process.o \
		./build/task/task.o \
		./build/task/task.asm.o \
		./build/task/tss.asm.o \
		./build/task/loader/elf.o \
		./build/task/loader/elfloader.o \
		./build/filesystem/pparser.o \
		./build/filesystem/file.o \
		./build/filesystem/fat/fat16.o \
		./build/lib/screen.o \
		./build/lib/string.o \
		./build/lib/memory.o \
		./build/hardware/idt.asm.o \
		./build/hardware/idt.o \
		./build/hardware/port.asm.o \
		./build/hardware/gdt.o \
		./build/hardware/gdt.asm.o \
		./build/memory/heap.o \
		./build/memory/kheap.o \
		./build/memory/paging.o \
		./build/memory/paging.asm.o \
		./build/driver/keyboard/keyboard.o \
		./build/driver/keyboard/classic.o  \
		./build/driver/mouse/mouse.o

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
	qemu-system-i386 -smp 2 -vga vmware -m 256M -hda bin/os.bin

run-build:
	qemu-system-i386 -smp 2 -vga vmware -m 256M -hda bin/os.bin

user_programs:
	cd ../programs/stdlib && $(MAKE) all
	cd ../programs/ui_framework && $(MAKE) all
	cd ../programs/shell && $(MAKE) all
	cd ../programs/blank && $(MAKE) all
	cd ../programs/calculator && $(MAKE) all
	cd ../programs/neofetch && $(MAKE) all
	cd ../programs/window_manager && $(MAKE) all
	cd ../programs/dock && $(MAKE) all
	cd ../programs/terminal && $(MAKE) all

user_programs_clean:
	cd ../programs/stdlib && $(MAKE) clean
	cd ../programs/shell && $(MAKE) clean
	cd ../programs/ui_framework && $(MAKE) clean
	cd ../programs/blank && $(MAKE) clean
	cd ../programs/calculator && $(MAKE) clean
	cd ../programs/neofetch && $(MAKE) clean
	cd ../programs/window_manager && $(MAKE) clean
	cd ../programs/dock && $(MAKE) clean
	cd ../programs/terminal && $(MAKE) clean

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