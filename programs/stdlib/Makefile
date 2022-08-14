FILES=./build/start.asm.o ./build/ocularos.asm.o ./build/stdlib.o ./build/stdio.o ./build/string.o ./build/memory.o ./build/OcularOS.o ./build/start.o
INCLUDES=-I./include
FLAGS = -g -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all: $(FILES)
	i686-elf-ld -m elf_i386 -relocatable $(FILES) -o stdlib.elf

build/%.asm.o: src/%.asm
	nasm -f elf $^ -o $@

build/%.o: src/%.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c $^ -o $@

clean:
	rm $(FILES)
	rm ./stdlib.elf