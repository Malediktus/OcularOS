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
    strcpy(path, "0:");
    strcpy(path+2, filename);

    struct process* process = 0;
    res = process_load_switch(path, &process);
    if (res < 0)
        goto out;

    task_switch(process->task);
    task_return(&process->task->registers);

out:
    return 0;
}

void* isr80h_command7_invoke_system_command(struct interrupt_frame* frame)
{
    struct command_argument* arguments = task_virtual_address_to_physical(task_current(), task_get_stack_item(task_current(), 0));
    if (!arguments || strlen(arguments[0].argument) == 0)
    {
        return ERROR(-EINVARG);
    }

    struct command_argument* root_command_argument = &arguments[0];
    const char* program_name = root_command_argument->argument;

    char path[OCULAROS_MAX_PATH];
    memset(path, 0, OCULAROS_MAX_PATH);
    char path_var_copy[OCULAROS_MAX_ENVIRONMENT_VARIABLE_SIZE];
    memset(path_var_copy, 0, OCULAROS_MAX_ENVIRONMENT_VARIABLE_SIZE);
    strncpy(path_var_copy, get_environment_variable("path"), OCULAROS_MAX_ENVIRONMENT_VARIABLE_SIZE);
    char* token = strtok(path_var_copy, ";");
    if (*program_name != '/')
    {
    while (token != 0)
    {
        strcpy(path, "0:");
        strncpy(path+2, token, strlen(token)+1); //TODO: check if '/'' is at end of path
        strncpy(path+2+strlen(token), program_name, sizeof(path)-(2+strlen(token)));
        int fd = fopen(path, "r");
        if (fd)
        {
            fclose(fd);
            break;
        }
        token = strtok(NULL, ";");
    }
    token = strtok(NULL, ";");
    }
    else
    {
        strcpy(path, "0:");
        strncpy(path+2, program_name, sizeof(path)-2);
    }

    struct process* process = 0;
    int res = process_load_switch(path, &process);
    if (res < 0)
        return ERROR(res);

    res = process_inject_arguments(process, root_command_argument);
    if (res < 0)
        return ERROR(res);

    task_switch(process->task);
    task_return(&process->task->registers);

    return 0;
}

void* isr80h_command8_get_program_arguments(struct interrupt_frame* frame)
{
    struct process* process = task_current()->process;
    struct process_arguments* arguments = task_virtual_address_to_physical(task_current(), task_get_stack_item(task_current(), 0));

    process_get_arguments(process, &arguments->argc, &arguments->argv);

    return 0;
}

void* isr80h_command9_exit(struct interrupt_frame* frame)
{
    struct process* process = task_current()->process;
    process_terminate(process);
    task_next();

    return 0;
}// TODO: Implement exit codes

void* isr80h_command10_free_all(struct interrupt_frame* frame)
{
    int res = process_terminate_allocations(task_current()->process);
    return (void*)res;
}