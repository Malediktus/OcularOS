[bits 32]
section .asm

global putpixel:function
global fillrect:function
global swap_buffers:function
global draw_subbuffer:function

; void swap_buffers()
swap_buffers:
    push ebp
    mov ebp, esp

    mov eax, 23 ; Command swap buffers
    int 0x80

    pop ebp
    ret

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

; void fillrect(int x, int y, int w, int h, int color)
fillrect:
    push ebp
    mov ebp, esp

    mov eax, 22 ; Command fillrect
    push dword[ebp+24] ; Variable x
    push dword[ebp+20] ; Variable y
    push dword[ebp+16] ; Variable w
    push dword[ebp+12] ; Variable h
    push dword[ebp+8] ; Variable color
    int 0x80
    add esp, 20

    pop ebp
    ret

; void draw_subbuffer(int x, int y, int w, int h, int* buffer)
draw_subbuffer:
    push ebp
    mov ebp, esp

    mov eax, 24 ; Command draw_subbuffer
    push dword[ebp+24] ; Variable x
    push dword[ebp+20] ; Variable y
    push dword[ebp+16] ; Variable w
    push dword[ebp+12] ; Variable h
    push dword[ebp+8] ; Variable buffer
    int 0x80
    add esp, 20

    pop ebp
    ret