struct process_arguments
{
    int argc;
    char** argv;
};

void ocularos_process_get_arguments(struct process_arguments* arguments);

extern int main(int argc, char** argv);
void c_start()
{
    struct process_arguments arguments;
    ocularos_process_get_arguments(&arguments);

    int res = main(arguments.argc, arguments.argv);
    if (res == 0);
}