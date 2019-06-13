#define _GNU_SOURCE  //宏调用 调用函数 
#include <sched.h> //调用clone 
#include <stdio.h>
#include <stdlib.h> 
#include <sys/wait.h>//调用库函数 
#include <unistd.h> //接口访问 (win跟linux不一样） 
static char STACK_SIZE[1024*1024];
static int childfunction()        //定义在其中一个容器要实现功能 
{
    printf("当前child端口\n");
	printf("PID: %ld\n", (long)getpid());
	printf("当前child ip\n");
	system("ip link");
	return 0;
}
static int parentsfunction()//定义在其中一个容器要实现功能 
{
	printf("当前parents端口\n");
	printf("PID: %ld\n", (long)getppid());
	return 0;
}
int main()
{
	printf("测试开始\n");
	pid_t/*这里 int也可以但考虑平台的移植性，进程号用pid_t*/
    child_pid = clone(childfunction,STACK_SIZE+1024*1024,CLONE_NEWPID | CLONE_NEWNET | SIGCHLD,NULL);
    pid_t 
    parents_pid = clone(parentsfunction,STACK_SIZE+1024*1024,CLONE_NEWPID | CLONE_NEWNET | SIGCHLD,NULL);
    if(child_pid=-1)
    {
    	printf("隔离失败，请检验\n");
	}
	/*int clone(int (*fn)(void * arg), void *stack, int flags, void * arg);
	        fn 创建线程需要运行的函数        stack  线程使用的堆栈 */
	else
	{
		printf("child_clone() = %ld\n", (long)child_pid);
        printf("parents_clone() = %ld\n", (long)parents_pid);
  	    printf("当前parents \n");
	    system("ip link");
	}
	/*pid_t waitpid(pid_t pid,int * status,int options);
	如果在调用 waitpid()时子进程已经结束,则 waitpid()会立即
   返回子进程结束状态值。 子进程的结束状态值会由参数 status 返回,
   而子进程的进程识别码也会一起返回。如果不在意结束状态值,则
   参数 status 可以设成 NULL。参数 pid 为欲等待的子进程识别码*/
    sleep(1);
	waitpid(child_pid, NULL, 0);
	waitpid(parents_pid,NULL,0);
	//等待结束 
    return 0;
}

