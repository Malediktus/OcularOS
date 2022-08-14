[BITS 32]

global _start
extern c_start
section .asm
extern ocularos_exit

_start:
    call c_start
    call ocularos_exit
    ret