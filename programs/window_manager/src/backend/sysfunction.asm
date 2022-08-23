[bits 32]
section .asm

global putpixel:function

; void putpixel(int x, int y, int color)
putpixel:
    push ebp
    mov ebp, esp

    mov eax, 13 ; Command putpixel
    push dword[ebp+16] ; Variable x
    push dword[ebp+12] ; Variable y
    push dword[ebp+8] ; Variable color
    int 0x80
    add esp, 12

    pop ebp
    ret