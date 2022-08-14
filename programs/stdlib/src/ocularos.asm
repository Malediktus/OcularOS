[bits 32]

section .asm

global print:function
global ocularos_getkey:function
global ocularos_putchar:function
global ocularos_process_load:function
global ocularos_process_get_arguments:function
global ocularos_malloc:function
global ocularos_free:function
global ocularos_system:function
global ocularos_exit:function

; void print(const char* message)
print:
    push ebp
    mov ebp, esp

    push dword[ebp+8]
    mov eax, 1 ; Command print
    int 0x80
    add esp, 4

    pop ebp
    ret

; int ocularos_getkey()
ocularos_getkey:
    push ebp
    mov ebp, esp

    mov eax, 2 ; Command getkey
    int 0x80

    pop ebp
    ret

; void ocularos_putchar(char c)
ocularos_putchar:
    push ebp
    mov ebp, esp

    mov eax, 3 ; Command putchar
    push dword[ebp+8] ; Variable c
    int 0x80
    add esp, 4

    pop ebp
    ret

; void ocularos_process_load(const char* filename)
ocularos_process_load:
    push ebp
    mov ebp, esp

    mov eax, 6 ; Command process load
    push dword[ebp+8] ; Variable filename
    int 0x80
    add esp, 4

    pop ebp
    ret

; int ocularos_system(struct command_argument* arguments)
ocularos_system:
    push ebp
    mov ebp, esp

    mov eax, 7 ; Command process_system
    push dword[ebp+8] ; Variable arguments
    int 0x80
    add esp, 4

    pop ebp
    ret

; void ocularos_exit()
ocularos_exit:
    push ebp
    mov ebp, esp

    mov eax, 9 ; Command exit
    int 0x80

    pop ebp
    ret

;;;;;;;;;;;;;;;;;;;;;
;;;;; PRIVATE API ;;;
;;;;;;;;;;;;;;;;;;;;;

; void ocularos_process_get_arguments(struct process_arguments* arguments)
ocularos_process_get_arguments:
    push ebp
    mov ebp, esp

    mov eax, 8 ; Command getarguments
    push dword[ebp+8] ; Variable arguments
    int 0x80
    add esp, 4

    pop ebp
    ret

; void* ocularos_malloc(size_t size)
ocularos_malloc:
    push ebp
    mov ebp, esp

    mov eax, 4 ; Command malloc
    push dword[ebp+8] ; Variable size
    int 0x80
    add esp, 4

    pop ebp
    ret

; void ocularos_free(void* ptr)
ocularos_free:
    push ebp
    mov ebp, esp

    mov eax, 5 ; Command free
    push dword[ebp+8] ; Variable ptr
    int 0x80
    add esp, 4

    pop ebp
    ret