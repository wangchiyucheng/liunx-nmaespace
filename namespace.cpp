#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>//调用clone 
#define STACKSIZE (1024*1024)
static char stack[STACKSIZE];

struct clone_args
{
    char **argv;
};
static int child_fn(void *stuff)// 
{
    struct clone_args *args = (struct clone_args *)stuff;
    printf("当前child端口\n");
	printf("PID: %ld\n", (long)getpid());
	printf("当前child ip\n");
	printf("当前parents端口\n");
	printf("PID: %ld\n", (long)getppid());
	system("ip link");
	printf("\n");
	system("id");
	printf("\n");
	system("readlink /proc/$$/ns/user");
    if (execvp(args->argv[0], args->argv) != 0)
	    {
                printf("隔离失败\n"); 
                exit(-1);
        }
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
        struct clone_args args;
        args.argv = &argv[1];
        pid_t /*这里 int也可以但考虑平台的移植性，进程号用pid_t*/
		pid =clone(child_fn, stack + STACKSIZE, clone_flags,CLONE_NEWUSER | CLONE_NEWPID | CLONE_NEWNET | CLONE_NEWNS | SIGCHLD, &args);
		/*int clone(int (*fn)(void * arg), void *stack, int flags, void * arg);
	        fn 创建线程需要运行的函数        stack  线程使用的堆栈 */
        if (pid < 0) 
		{
            printf("失败了哦!\n");
            exit(EXIT_FAILURE);
        }
        else
	   {
		    printf("child_clone() = %ld\n", (long)child_pid);
            printf("parents_clone() = %ld\n", (long)child_pid);
  	        printf("当前parents ip\n");
	        system("ip link");
	        printf("\n");
	        system("id");
	        printf("\n");
	        system("readlink /proc/$$/ns/user");
	    }
		sleep(1);
		//等待结束 
        if (waitpid(pid, NULL, 0) == -1)
		 {
                printf("隔离失败\n"); 
                exit(EXIT_FAILURE);
        }
        /*pid_t waitpid(pid_t pid,int * status,int options);如果在调用 waitpid()时子进程已经结束,则 waitpid()会立即返回子进程结束状态值。 子进程的结束状态值会由参数 status 返回,
        而子进程的进程识别码也会一起返回。如果不在意结束状态值,则
        参数 status 可以设成 NULL。参数 pid 为欲等待的子进程识别码*/
        exit(EXIT_SUCCESS);
}
