FILES=./build/calc.o ./build/interpreter/lexer.o ./build/interpreter/error.o ./build/interpreter/parser.o ./build/interpreter/parser_util.o ./build/interpreter/interpreter_util.o ./build/interpreter/interpreter.o
INCLUDES=-I../stdlib/include
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

# Stdlib muste be linked here because the kernel doesnt support dynamic linking yet
all: $(FILES)
	i686-elf-gcc -g -T ./linker.ld -o ./calc -ffreestanding -O0 -nostdlib -fpic -g $(FILES) ../stdlib/stdlib.elf

build/%.o: src/%.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c $^ -o $@

clean:
	rm $(FILES)
	rm ./calc