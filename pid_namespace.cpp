#define _GNU_SOURCE  //����� ���ú��� 
#include <sched.h> //����clone 
#include <stdio.h>
#include <stdlib.h> 
#include <sys/wait.h>//���ÿ⺯�� 
#include <unistd.h> //�ӿڷ��� (win��linux��һ���� 
static char STACK_SIZE[1024*1024];
static int childfunction()        //����������һ������Ҫʵ�ֹ��� 
{
    printf("��ǰchild�˿�\n");
	printf("PID: %ld\n", (long)getpid());
	printf("��ǰchild ip\n");
	system("ip link");
	return 0;
}
static int parentsfunction()//����������һ������Ҫʵ�ֹ��� 
{
	printf("��ǰparents�˿�\n");
	printf("PID: %ld\n", (long)getppid());
	return 0;
}
int main()
{
	printf("���Կ�ʼ\n");
	pid_t/*���� intҲ���Ե�����ƽ̨����ֲ�ԣ����̺���pid_t*/
    child_pid = clone(childfunction,STACK_SIZE+1024*1024,CLONE_NEWPID | CLONE_NEWNET | SIGCHLD,NULL);
    pid_t 
    parents_pid = clone(parentsfunction,STACK_SIZE+1024*1024,CLONE_NEWPID | CLONE_NEWNET | SIGCHLD,NULL);
    if(child_pid=-1)
    {
    	printf("����ʧ�ܣ������\n");
	}
	/*int clone(int (*fn)(void * arg), void *stack, int flags, void * arg);
	        fn �����߳���Ҫ���еĺ���        stack  �߳�ʹ�õĶ�ջ */
	else
	{
		printf("child_clone() = %ld\n", (long)child_pid);
        printf("parents_clone() = %ld\n", (long)parents_pid);
  	    printf("��ǰparents \n");
	    system("ip link");
	}
	/*pid_t waitpid(pid_t pid,int * status,int options);
	����ڵ��� waitpid()ʱ�ӽ����Ѿ�����,�� waitpid()������
   �����ӽ��̽���״ֵ̬�� �ӽ��̵Ľ���״ֵ̬���ɲ��� status ����,
   ���ӽ��̵Ľ���ʶ����Ҳ��һ�𷵻ء�������������״ֵ̬,��
   ���� status ������� NULL������ pid Ϊ���ȴ����ӽ���ʶ����*/
    sleep(1);
	waitpid(child_pid, NULL, 0);
	waitpid(parents_pid,NULL,0);
	//�ȴ����� 
    return 0;
}

