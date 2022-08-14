#include <syscall/misc.h>

void* isr80h_command0_sum(struct interrupt_frame* frame)
{
    int v2 = (int) task_get_stack_item(task_current(), 1);
    int v1 = (int) task_get_stack_item(task_current(), 0);
    return (void*)(v1 + v2);
}

void* isr80h_command6_process_load(struct interrupt_frame* frame)
{
    void* filename_user_ptr = task_get_stack_item(task_current(), 0);
    char filename[OCULAROS_MAX_PATH];
    int res = copy_string_from_task(task_current(), filename_user_ptr, filename, sizeof(filename));
    if (res < 0)
        goto out;

    char path[OCULAROS_MAX_PATH];
    strcpy(path, "0:/");
    strcpy(path+3, filename);

    struct process* process = 0;
    res = process_load_switch(path, &process);
    if (res < 0)
        goto out;

    task_switch(process->task);
    task_return(&process->task->registers);

out:
    return 0;
}