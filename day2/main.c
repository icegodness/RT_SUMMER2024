#include <rtthread.h>

static rt_thread_t tid1;
static rt_thread_t tid2;
static rt_thread_t tid3;


#define thread1_priority  RT_THREAD_PRIORITY_MAX - 1
#define  thread1_stack_size  512

#define thread2_priority  RT_THREAD_PRIORITY_MAX - 2
#define thread2_stack_size  512

#define thread3_priority  RT_THREAD_PRIORITY_MAX - 3
#define thread3_stack_size  512

#define THREAD_TIMESLICE 5

void thread1_entry(void *parameter)
{
    rt_uint32_t count = 0;
    while (count<100)
    {
        // Thread 1 logic here
        rt_kprintf("thread1 count: %d\n", count);
        rt_thread_delay(500);
        count++;
    }
}

void thread2_entry(void *parameter)
{
    rt_uint32_t count = 0;
    while (count<100)
    {
        // Thread 2 logic here
        rt_kprintf("thread2 count: %d\n", count);
        rt_thread_delay(1000);
        count++;
    }
}

void thread3_entry(void *parameter)
{
    rt_uint32_t count = 0;
    while (count<100)
    {
        // Thread 3 logic here
        rt_kprintf("thread3 count: %d\n", count);
        rt_thread_delay(2000);
        count++;
    }
}

int thread_test(void)
{
    // 创建线程
    tid1 = rt_thread_create("thread1", thread1_entry, RT_NULL, thread1_stack_size, thread1_priority, THREAD_TIMESLICE);
    /* 如果获得线程控制块，启动这个线程 */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
    tid2 = rt_thread_create("thread2", thread2_entry, RT_NULL, thread2_stack_size, thread2_priority, THREAD_TIMESLICE);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);
    tid3 = rt_thread_create("thread3", thread3_entry, RT_NULL, thread3_stack_size, thread3_priority, THREAD_TIMESLICE);
    if (tid3 != RT_NULL)
        rt_thread_startup(tid3);

    return 0;
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(thread_test, thread test);

int main(void)
{
    return 0;
}
