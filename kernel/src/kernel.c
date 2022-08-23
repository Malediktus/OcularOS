#include <kernel.h>

static struct paging_4gb_chunk* kernel_chunk = 0;
struct environment_variable environment_variables[OCULAROS_MAX_ENVIRONMENT_VARIABLES];

int set_environment_variable(char* key, char* content)
{
    for (int i = 0; i < (sizeof(environment_variables) / sizeof(struct environment_variable)); i++)
    {
        if (strncmp(key, environment_variables[i].name, OCULAROS_MAX_ENVIRONMENT_VARIABLE_NAME) == 0)
        {
            strcpy(environment_variables[i].content, content); // TODO: Potential buffer overflow
            return 0;
        }
    }

    for (int i = 0; i < (sizeof(environment_variables) / sizeof(struct environment_variable)); i++)
    {
        if (environment_variables[i].name == 0)
        {
            environment_variables[i].name = kzalloc(OCULAROS_MAX_ENVIRONMENT_VARIABLE_NAME);
            environment_variables[i].content = kzalloc(OCULAROS_MAX_ENVIRONMENT_VARIABLE_SIZE);
            strcpy(environment_variables[i].name, key); // TODO: Potential buffer overflow
            strcpy(environment_variables[i].content, content); // TODO: Potential buffer overflow
            return 0;
        }
    }

    return -ENOMEM;
}

char* get_environment_variable(char* key)
{
    for (int i = 0; i < (sizeof(environment_variables) / sizeof(struct environment_variable)); i++)
    {
        if (strncmp(key, environment_variables[i].name, OCULAROS_MAX_ENVIRONMENT_VARIABLE_NAME) == 0)
        {
            return environment_variables[i].content;
        }
    }

    return "";
}

int createRGB(int r, int g, int b)
{   
  int c = r;
  c = (c << 8) | g;
  c = (c << 8) | b;
  return c;
}

void panic(const char* msg)
{
    //fillscreen(0xFF0000);
    print("Kernel panic... The system cannot continue!\n");
    print(msg);
    while(1) {}
}

void kernel_page()
{
    kernel_registers();
    paging_switch(kernel_chunk);
}

struct tss tss;
struct gdt gdt_real[OCULAROS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[OCULAROS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00},                // NULL Segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a},           // Kernel code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92},            // Kernel data segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8},              // User code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},             // User data segment
    {.base = (uint32_t)&tss, .limit=sizeof(tss), .type = 0xE9}      // TSS Segment
};

void kernel_main()
{
    memset(gdt_real, 0x00, sizeof(gdt_real));
    gdt_structured_to_gdt(gdt_real, gdt_structured, OCULAROS_TOTAL_GDT_SEGMENTS);

    // Load the gdt
    gdt_load(gdt_real, sizeof(gdt_real));

    // Initialize the heap
    kheap_init();

    // Initialize filesystems
    fs_init();

    // Search and initialize the disks
    disk_search_and_init();

    // Initializing graphics
    terminal_initialize();

    print("Starting the kernel...\n");

    // Setting environment variables
    memset(environment_variables, 0, sizeof(environment_variables));
    set_environment_variable("path", "/;/bin/;/usr/bin/");

    // Initialize the interrupt descriptor table
    idt_init();

    // Setup the TSS
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000;
    tss.ss0 = KERNEL_DATA_SELECTOR;

    // Load the TSS
    tss_load(0x28);

    // Setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    
    // Switch to kernel paging chunk
    paging_switch(kernel_chunk);

    // Enable paging
    enable_paging();

    // Register the kernel commands
    isr80h_register_commands();

    keyboard_init();

    print("Initialization finished!\n");

    struct process* process2 = 0;
    int res = process_load_switch("0:/usr/bin/blank.elf", &process2);
    if (res != OCULAROS_ALL_OK)
    {
        panic("Failed to load /usr/bin/blank.elf\n");
    }

    task_run_first_ever_task();

    print("Landed at end of kernel\n");

    while(1);
}