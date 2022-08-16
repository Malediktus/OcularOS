# OcularOS Documentation

## Boot routine
#
### Bootloader:
- Initializing vbe graphics
- Switching to protected mode
- Enabling A20
- Remapping pic
- Initializing loader heap
- Loading disks and filesystems
- Open and run kernel.bin (panic if not found)

### Kernel:
- Initialize global descriptor table
- Initialize kernel heap
- Loading disks and filesystems
- Loading font and starting print routine
- Setting environment variables
- Setting up interrupts
- Loading the task switch segment
- Initialize paging
- Switch to kernel page
- Enable paging
- Registering syscalls
- Initilazing the keyboard
- Starting /bin/shell.elf

## Supported filesystems
#
- Fat16

## Syscalls
#
### General information
- Parameters are pushed to the stack in reverse order
- eax register contains return value/code

### List of syscalls
## Todo: Make table