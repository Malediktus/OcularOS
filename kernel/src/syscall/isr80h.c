#include <syscall/isr80h.h>

void isr80h_register_commands()
{
    isr80h_register_command(SYSTEM_COMMAND0_SUM, isr80h_command0_sum);
    isr80h_register_command(SYSTEM_COMMAND1_PRINT, isr80h_command1_print);
    isr80h_register_command(SYSTEM_COMMAND2_GETKEY, isr80h_command2_getkey);
    isr80h_register_command(SYSTEM_COMMAND3_PUTCHAR, isr80h_command3_putchar);
    isr80h_register_command(SYSTEM_COMMAND4_MALLOC, isr80h_command4_malloc);
    isr80h_register_command(SYSTEM_COMMAND5_FREE, isr80h_command5_free);
    isr80h_register_command(SYSTEM_COMMAND6_PROCESS_LOAD, isr80h_command6_process_load);
    isr80h_register_command(SYSTEM_COMMAND7_INVOKE_SYSTEM_COMMAND, isr80h_command7_invoke_system_command);
    isr80h_register_command(SYSTEM_COMMAND8_GET_PROGRAM_ARGUMENTS, isr80h_command8_get_program_arguments);
    isr80h_register_command(SYSTEM_COMMAND9_EXIT, isr80h_command9_exit);
    isr80h_register_command(SYSTEM_COMMAND10_FREE_ALL, isr80h_command10_free_all);
    isr80h_register_command(SYSTEM_COMMAND11_GET_ENVIRON_VAR, isr80h_command11_get_environ_var);
    isr80h_register_command(SYSTEM_COMMAND12_SET_ENVIRON_VAR, isr80h_command12_set_environ_var);
    isr80h_register_command(SYSTEM_COMMAND13_PUT_PIXEL, isr80h_command13_putpixel);
    isr80h_register_command(SYSTEM_COMMAND14_FOPEN, isr80h_command14_fopen);
    isr80h_register_command(SYSTEM_COMMAND15_FSEEK, isr80h_command15_fseek);
    isr80h_register_command(SYSTEM_COMMAND16_FREAD, isr80h_command16_fread);
    isr80h_register_command(SYSTEM_COMMAND17_FWRITE, isr80h_command17_fwrite);
    isr80h_register_command(SYSTEM_COMMAND18_FSTAT, isr80h_command18_fstat);
    isr80h_register_command(SYSTEM_COMMAND19_FCLOSE, isr80h_command19_fclose);
    isr80h_register_command(SYSTEM_COMMAND20_START_IPC, isr80h_command20_start_ipc);
    isr80h_register_command(SYSTEM_COMMAND21_POP_IPC, isr80h_command21_pop_ipc);
    isr80h_register_command(SYSTEM_COMMAND22_FILLRECT, isr80h_command22_fillrect);
    isr80h_register_command(SYSTEM_COMMAND23_SWAP_BUFFERS, isr80h_command23_swap_buffers);
    isr80h_register_command(SYSTEM_COMMAND24_DRAW_SUBBUFFER, isr80h_command24_draw_subbuffer);
}