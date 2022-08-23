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
global ocularos_free_all:function
global ocularos_get_environ_var:function
global fopen:function
global fseek:function
global fread:function
global fwrite:function
global fstat:function
global fclose:function
global ocularos_start_ipc:function
global ocularos_pop_ipc:function

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

; void ocularos_free_all()
ocularos_free_all:
    push ebp
    mov ebp, esp

    mov eax, 10 ; Command free all
    int 0x80

    pop ebp
    ret

; void ocularos_get_environ_var(char* name, char* content)
ocularos_get_environ_var:
    push ebp
    mov ebp, esp

    mov eax, 11 ; Command get environ var
    push dword[ebp+8] ; Variable content
    push dword[ebp+12] ; Variable name
    int 0x80
    add esp, 8

    pop ebp
    ret

; int fopen(char* filename, char* mode_str)
fopen:
    push ebp
    mov ebp, esp

    mov eax, 14 ; Command fopen
    push dword[ebp+12] ; Variable filename
    push dword[ebp+8] ; Variable mode_str
    int 0x80
    add esp, 8

    pop ebp
    ret

; int fseek(int fd, int offset, unsigned int whence)
fseek:
    push ebp
    mov ebp, esp

    mov eax, 15 ; Command fseek
    push dword[ebp+16] ; Variable whence
    push dword[ebp+12] ; Variable offset
    push dword[ebp+8] ; Variable fd
    int 0x80
    add esp, 12

    pop ebp
    ret

; int fread(void* ptr, unsigned int size, unsigned int nmemb, int fd)
fread:
    push ebp
    mov ebp, esp

    mov eax, 16 ; Command fread
    push dword[ebp+20] ; Variable nmemb
    push dword[ebp+16] ; Variable nmemb
    push dword[ebp+12] ; Variable size
    push dword[ebp+8] ; Variable ptr
    int 0x80
    add esp, 16

    pop ebp
    ret

; int fwrite(void* ptr, unsigned int size, unsigned int nmemb, int fd)
fwrite:
    push ebp
    mov ebp, esp

    mov eax, 17 ; Command fwrite
    push dword[ebp+20] ; Variable nmemb
    push dword[ebp+16] ; Variable nmemb
    push dword[ebp+12] ; Variable size
    push dword[ebp+8] ; Variable ptr
    int 0x80
    add esp, 16

    pop ebp
    ret

; int fstat(int fd, struct file_stat* stat)
fstat:
    push ebp
    mov ebp, esp

    mov eax, 18 ; Command fstat
    push dword[ebp+12] ; Variable stat
    push dword[ebp+8] ; Variable fd
    int 0x80
    add esp, 8

    pop ebp
    ret

; int fclose(int fd)
fclose:
    push ebp
    mov ebp, esp

    mov eax, 19 ; Command fclose
    push dword[ebp+8] ; Variable fd
    int 0x80
    add esp, 4

    pop ebp
    ret

; void* ocularos_start_ipc(char* process_path, int size)
ocularos_start_ipc:
    push ebp
    mov ebp, esp

    mov eax, 20 ; Command start ipc
    push dword[ebp+12] ; Variable process_path
    push dword[ebp+8] ; Variable size
    int 0x80
    add esp, 8

    pop ebp
    ret

; void* ocularos_pop_ipc()
ocularos_pop_ipc:
    push ebp
    mov ebp, esp

    mov eax, 21 ; Command pop ipc
    int 0x80

    pop ebp
    ret

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