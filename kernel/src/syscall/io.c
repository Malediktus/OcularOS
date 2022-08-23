#include <syscall/io.h>

void* isr80h_command1_print(struct interrupt_frame* frame)
{
    void* user_space_msg_buffer = task_get_stack_item(task_current(), 0);
    char buf[1024];
    copy_string_from_task(task_current(), user_space_msg_buffer, buf, sizeof(buf));
    print(buf);
    return 0;
}

void* isr80h_command2_getkey(struct interrupt_frame* frame)
{
    char c = keyboard_pop();
    return (void*)((int)c);
}

void* isr80h_command3_putchar(struct interrupt_frame* frame)
{
    char c = (char)(int)task_get_stack_item(task_current(), 0);
    terminal_writechar(c, 0xFFFFFF);
    return 0;
}

void* isr80h_command20_start_ipc(struct interrupt_frame* frame)
{
    void* user_space_process_b_path = task_get_stack_item(task_current(), 0);
    int size = (int)task_get_stack_item(task_current(), 1);
    char program_b_path[OCULAROS_MAX_PATH];
    copy_string_from_task(task_current(), user_space_process_b_path, program_b_path, OCULAROS_MAX_PATH);
    struct process* process_b = 0;
    for (int i = 0; i < OCULAROS_MAX_PROCESSES; i++)
    {
        if (strncmp(program_b_path, processes[i]->filename, OCULAROS_MAX_PATH) == 0)
        {
            process_b = processes[i];
            break;
        }
    }
    if (process_b == 0)
        return 0;
    int* ptr = process_start_ipc(task_current()->process, process_b, size);
    ptr[0] = size;
    for (int i = 0; i < OCULAROS_MAX_IPC_BUFFER_SIZE_PER_PROGRAM; i++)
    {
        if (process_b->ipc_buffer[i] == 0)
        {
            process_b->ipc_buffer[i] = ptr;
            break;
        }
    }
    return ptr;
}

void* isr80h_command21_pop_ipc(struct interrupt_frame* frame)
{
    void* ptr = task_current()->process->ipc_buffer[0];
    if (ptr == 0)
        return 0;
    for (int i = 1; i < OCULAROS_MAX_IPC_BUFFER_SIZE_PER_PROGRAM; i++)
    {
        task_current()->process->ipc_buffer[i-1] = task_current()->process->ipc_buffer[i];
        task_current()->process->ipc_buffer[i] = 0;
    }

    return ptr;
}