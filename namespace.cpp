#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>//����clone 
#define STACKSIZE (1024*1024)
static char stack[STACKSIZE];

struct clone_args
{
    char **argv;
};
static int child_fn(void *stuff)// 
{
    struct clone_args *args = (struct clone_args *)stuff;
    printf("��ǰchild�˿�\n");
	printf("PID: %ld\n", (long)getpid());
	printf("��ǰchild ip\n");
	printf("��ǰparents�˿�\n");
	printf("PID: %ld\n", (long)getppid());
	system("ip link");
	printf("\n");
	system("id");
	printf("\n");
	system("readlink /proc/$$/ns/user");
    if (execvp(args->argv[0], args->argv) != 0)
	    {
                printf("����ʧ��\n"); 
                exit(-1);
        }
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
        struct clone_args args;
        args.argv = &argv[1];
        pid_t /*���� intҲ���Ե�����ƽ̨����ֲ�ԣ����̺���pid_t*/
		pid =clone(child_fn, stack + STACKSIZE, clone_flags,CLONE_NEWUSER | CLONE_NEWPID | CLONE_NEWNET | CLONE_NEWNS | SIGCHLD, &args);
		/*int clone(int (*fn)(void * arg), void *stack, int flags, void * arg);
	        fn �����߳���Ҫ���еĺ���        stack  �߳�ʹ�õĶ�ջ */
        if (pid < 0) 
		{
            printf("ʧ����Ŷ!\n");
            exit(EXIT_FAILURE);
        }
        else
	   {
		    printf("child_clone() = %ld\n", (long)child_pid);
            printf("parents_clone() = %ld\n", (long)child_pid);
  	        printf("��ǰparents ip\n");
	        system("ip link");
	        printf("\n");
	        system("id");
	        printf("\n");
	        system("readlink /proc/$$/ns/user");
	    }
		sleep(1);
		//�ȴ����� 
        if (waitpid(pid, NULL, 0) == -1)
		 {
                printf("����ʧ��\n"); 
                exit(EXIT_FAILURE);
        }
        /*pid_t waitpid(pid_t pid,int * status,int options);����ڵ��� waitpid()ʱ�ӽ����Ѿ�����,�� waitpid()�����������ӽ��̽���״ֵ̬�� �ӽ��̵Ľ���״ֵ̬���ɲ��� status ����,
        ���ӽ��̵Ľ���ʶ����Ҳ��һ�𷵻ء�������������״ֵ̬,��
        ���� status ������� NULL������ pid Ϊ���ȴ����ӽ���ʶ����*/
        exit(EXIT_SUCCESS);
}
