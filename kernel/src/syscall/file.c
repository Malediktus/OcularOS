#include <syscall/file.h>

void* isr80h_command14_fopen(struct interrupt_frame* frame)
{
    void* user_space_filename_buf = task_get_stack_item(task_current(), 0);
    void* user_space_mode_str_buf = task_get_stack_item(task_current(), 1);
    char filename[OCULAROS_MAX_PATH];
    char mode_str[10];
    copy_string_from_task(task_current(), user_space_filename_buf, filename, OCULAROS_MAX_PATH);
    copy_string_from_task(task_current(), user_space_mode_str_buf, mode_str, 10);
    return (void*)fopen(filename, mode_str);
}

void* isr80h_command15_fseek(struct interrupt_frame* frame)
{
    int fd = (int)task_get_stack_item(task_current(), 0);
    int offset = (int)task_get_stack_item(task_current(), 1);
    FILE_SEEK_MODE whence = (FILE_SEEK_MODE)task_get_stack_item(task_current(), 2);
    return (void*)fseek(fd, offset, whence);
}

void* isr80h_command16_fread(struct interrupt_frame* frame)
{
    void* user_ptr = task_get_stack_item(task_current(), 0);
    uint32_t size = (uint32_t)task_get_stack_item(task_current(), 1);
    uint32_t nmemb = (uint32_t)task_get_stack_item(task_current(), 2);
    int fd = (int)task_get_stack_item(task_current(), 3);
    void* phys_ptr = task_virtual_address_to_physical(task_current(), user_ptr);
    return (void*)fread(phys_ptr, size, nmemb, fd);
}

void* isr80h_command17_fwrite(struct interrupt_frame* frame)
{
    void* user_ptr = task_get_stack_item(task_current(), 0);
    uint32_t size = (uint32_t)task_get_stack_item(task_current(), 1);
    uint32_t nmemb = (uint32_t)task_get_stack_item(task_current(), 2);
    int fd = (int)task_get_stack_item(task_current(), 3);
    void* phys_ptr = task_virtual_address_to_physical(task_current(), user_ptr);
    return (void*)fwrite(phys_ptr, size, nmemb, fd);
}

void* isr80h_command18_fstat(struct interrupt_frame* frame)
{
    int fd = (int)task_get_stack_item(task_current(), 0);
    void* user_space_stat = task_get_stack_item(task_current(), 1);
    struct file_stat* stat = task_virtual_address_to_physical(task_current(), user_space_stat);
    return (void*)fstat(fd, stat);
}

void* isr80h_command19_fclose(struct interrupt_frame* frame)
{
    int fd = (int)task_get_stack_item(task_current(), 0);
    return (void*)fclose(fd);
}