[2024-RSOC] DAY2笔记
今日学习RTOS的概念，讲解了rt启动的流程以及线程管理

什么是实时系统（RTOS）？什么是分时系统？
实时系统是对外部事件或数据源在规定的时间范围内作出反应，并能够保障系统的正确运行的计算机系统。
分时系统是一种多用户、多任务操作系统，它将计算机的时间划分为多个时间片，并分配给不同的用户或任务使用。熟悉的桌面操作系统windows，以及linux都是分时系统。

裸机和实时系统有什么区别？
裸机运行程序，使用while循环或者中断捕获事件。中断是指当外部事件发生时，会触发处理器中断当前正在运行的程序，并跳转到相应的处理程序执行。
实时系统强调实时性，多线程，支持优先级，可抢占， 根据任务的优先级来分配 CPU 时间 。

RT-Thread的初始化流程
可以通过查看和调试project\libraries\STM32F4xx_HAL\CMSIS\Device\ST\STM32F4xx\Source\Templates\gcc\startup_stm32f407xx.s
这个启动文件来分析初始化流程
![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721698671001-bce674e0-3ba3-467c-bb6a-fc764a4d5806.png#averageHue=%23fbfbfa&clientId=u27b85184-bd94-4&from=paste&height=623&id=ub5237374&originHeight=779&originWidth=1504&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=327391&status=done&style=none&taskId=u29f79dae-0025-40b7-ab6c-857b62c4e78&title=&width=1203.2)
使用vscode设置断点，单步调试等
gdb


### 线程管理
参考文档链接：[https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/programming-manual/thread/thread](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/programming-manual/thread/thread)

线程分为**系统线程**和**用户线程**，分别由系统内核创建和用户创建
![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721699273404-122cbefa-3f3c-4ea4-b81d-17802184b504.png#averageHue=%23f4f2f1&clientId=u27b85184-bd94-4&from=paste&height=629&id=ua4a6d1b0&originHeight=786&originWidth=1377&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=306118&status=done&style=none&taskId=udd6cbffc-431e-42f0-b4fd-0ff3778ba92&title=&width=1101.6)
线程控制块是系统用于管理线程的一个数据结构

![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721699351730-710440b5-65e5-472f-b080-e75b3f8ff359.png#averageHue=%23f5f5f5&clientId=u27b85184-bd94-4&from=paste&height=627&id=u9807b580&originHeight=784&originWidth=1390&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=204098&status=done&style=none&taskId=ud709a1ac-6e73-4de0-9eb6-4626560ecd9&title=&width=1112)
线程退出时会调用一个钩子函数进行清除
![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721699643628-128782a2-bd74-4a83-8119-b367589a25b1.png#averageHue=%23f6f5f2&clientId=u27b85184-bd94-4&from=paste&height=72&id=u91cb89f8&originHeight=90&originWidth=663&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=13484&status=done&style=none&taskId=u4a3f0926-92e9-48dd-81cc-818dbe65d71&title=&width=530.4)

线程优先级，rt支持0~255 共256个优先级，和freeRTOS不一样，rt数值越小优先级越高，255通常是idle线程的优先级

线程入口函数由用户定义，确定线程所执行的操作
![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721701923980-e992e034-1e32-4e97-a18d-d62f9d4cc40f.png#averageHue=%23fbfbf9&clientId=ua5b9d7e8-a1ba-4&from=paste&height=652&id=ud437db27&originHeight=815&originWidth=1187&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=252382&status=done&style=none&taskId=u979dea67-171b-4935-a471-e5a5a559d17&title=&width=949.6)

ARM 上需要做 4 字节对齐

线程状态机切换
![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721731185015-ff603de3-bd03-4710-97c2-edc7e54eba23.png#averageHue=%23f6f5f4&clientId=u096f9f7b-37c0-4&from=paste&height=290&id=ud982082c&originHeight=362&originWidth=1106&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=133251&status=done&style=none&taskId=u8b283f4b-183c-45a7-995e-34846cdd835&title=&width=884.8)
线程的状态可以通过ps命令查看

动态创建线程，系统分配堆内存，分配出来的栈空间按照 RT_ALIGN_SIZE 方式对齐
rt_thread_create
静态创建线程，在编译时就被确定、被分配处理，内核不参与动态分配内存
rt_thread_init


将函数作为可执行的命令导出到命令行
![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721716397759-e96c925b-f055-4cbf-afd2-abad764acd9f.png#averageHue=%231e232a&clientId=u8bc23389-e1c7-4&from=paste&height=310&id=ud68d5972&originHeight=388&originWidth=775&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=174715&status=done&style=none&taskId=ueace1eaf-6e30-4856-b866-53d9f8000ba&title=&width=620)
板卡烧录上电后，就能在rt系统命令行调用所写函数
这里分析了源码，
__attribute__
在ARM中，这是编译器识别的一个符号。用来指定编译后数据存放的位置。
我们写的函数名称和描述被放到`.rodata.name`段中
![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721716620689-846f6e14-4ded-4b39-8f26-43ed0ea94471.png#averageHue=%2311141e&clientId=u8bc23389-e1c7-4&from=paste&height=53&id=u4d77f14f&originHeight=66&originWidth=423&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=28405&status=done&style=none&taskId=u03efec83-063d-45ee-b15b-dd43da238fd&title=&width=338.4)

ps列出当前系统的运行状态
![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721716860559-b3bbd73a-e728-4a2d-a08b-71770855b8b4.png#averageHue=%23333530&clientId=u8bc23389-e1c7-4&from=paste&height=81&id=u998d2663&originHeight=101&originWidth=731&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=105723&status=done&style=none&taskId=uc2673a58-b5b2-49de-931a-80808bc4c06&title=&width=584.8)


![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721717240129-6412f3b5-0e60-40b0-bd8c-79cbb3f704bb.png#averageHue=%230f131b&clientId=u8bc23389-e1c7-4&from=paste&height=118&id=u4a460942&originHeight=148&originWidth=498&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=45742&status=done&style=none&taskId=udbe1aace-f853-4ef8-b691-ed0bfc01b14&title=&width=398.4)
delay的时候线程让出cpu，此时可以被其他线程抢占

![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721718537339-ed33594c-44ae-4ead-8847-d39f48238444.png#averageHue=%2312151c&clientId=u8bc23389-e1c7-4&from=paste&height=527&id=u8ab3e106&originHeight=659&originWidth=210&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=80175&status=done&style=none&taskId=u0ee35bf4-9f20-4078-a0c9-c36bbf8fee3&title=&width=168)
使用gitignore 忽略提交的文件

一些触发异常的操作
![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721719383239-f5a188c5-0842-4f26-ac5b-e41d26d8b211.png#averageHue=%23fcfcfc&clientId=u8bc23389-e1c7-4&from=paste&height=631&id=u37300a7e&originHeight=789&originWidth=1286&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=132073&status=done&style=none&taskId=ud5ad01c8-659d-44ae-a318-e737ca95909&title=&width=1028.8)
![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721719416141-16e054e8-971d-40ba-b032-772b170f1f30.png#averageHue=%23fbfafa&clientId=u8bc23389-e1c7-4&from=paste&height=572&id=u24fa54eb&originHeight=715&originWidth=1452&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=192910&status=done&style=none&taskId=ue6a30fda-cc5e-4380-8f99-fa20925d73f&title=&width=1161.6)

utest
ctrl+t
>
反汇编

创建三个线程，采用动态线程创建
```
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

```


![image.png](https://cdn.nlark.com/yuque/0/2024/png/1407037/1721735532935-f447f395-b504-41c1-acdc-a2e293d04164.png#averageHue=%233d3c3b&clientId=u096f9f7b-37c0-4&from=paste&height=730&id=u9929b5cf&originHeight=912&originWidth=1438&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=75965&status=done&style=none&taskId=u8aa1f1e7-97a7-477f-af2c-f2d7a7889dd&title=&width=1150.4)

