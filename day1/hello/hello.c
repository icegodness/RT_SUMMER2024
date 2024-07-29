#include <rtthread.h>
#include <hello.h>

int print_hello(void)
{
    rt_kprintf("hello world\n");
    return 0;
}