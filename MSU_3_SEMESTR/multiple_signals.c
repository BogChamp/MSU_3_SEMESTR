#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#define BUF 1024

int fd[2];
FILE* config_file;
int father_pid, max_child;
int semaphor = 1;

int count_of_args(char* value);
int make_children(int num);
void SigWrite(int sig_num);
void SigRead(int sig_num);
void KillChild(int sig_num);

int main(int argc, char** argv)
{
    int num_of_child;
    int i;

    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return -1;
    }

    if (argc > 2)
    {
        printf("Too much arguments\n");
        return -1;
    }

    num_of_child = count_of_args(argv[1]);
    if (num_of_child < 2)
    {
	    printf("I need children!!\n");
	    return -1;
    }

    else if (num_of_child > 200)
    {
	    printf("I can't make this num of children\n");
	    return -1;
    }

    make_children(num_of_child);

    return 0;
}

int make_children(int num)
{
    int i, j, child;
    pid_t pides[num - 1];
    pid_t pid;
    char conf_ch[10];

    max_child = num - 1;
    father_pid = getpid();

    pipe(fd);

    signal(SIGUSR1, SigWrite);
    signal(SIGUSR2, SigRead);
    signal(SIGTERM, KillChild);

    for (i = 1; i < num; i++)
    {
        switch (pid = (fork()))
        {
            case -1:
                printf("Killing all children\n");
                for (j = 0; j < (i-1); j++)
                    kill(pides[j], SIGTERM);
                printf("error fork\n");
                return -1;
                break;
            case 0:
		        printf("son num %d with pid %d  is born\n", i, getpid());
                sprintf(conf_ch, "config_%d", i);
                config_file = fopen(conf_ch ,"r");
		        if (config_file == NULL)
			{	
				printf("no config_%d\n", i);
			        semaphor = 0;
			}
			kill(father_pid, SIGUSR1);
                while(1);
                break;
            default:
                pides[i-1] = pid;
                while(semaphor == 1);
                semaphor = 1;
                signal(SIGUSR1, SigWrite);
                break;
        }
    }

	printf("\n");

    for (i = 1; i < num; i++)
    {
	printf("message from son %d\n\n", i);
        kill(pides[i-1], SIGUSR1);
	    while(semaphor == 1);
        read(fd[0], &child, sizeof(int));
        if ((child > 0) && (child < num))
        {
            kill(pides[child-1], SIGUSR2);
	        while(semaphor == 0);
            signal(SIGUSR2, SigRead);
        }
	signal(SIGUSR1, SigWrite);
    }

    for (i = 0; i < (num-1); i++)
        kill(pides[i], SIGTERM);
   
    close(fd[0]);
    close(fd[1]);

    return 0;
}

void SigWrite(int sig_num)
{
    int child, i = 0;
    char c, c_const = '\0';
    char byte[BUF];
    int no_message = -100;

    if(getpid() != father_pid)
    {
        if (semaphor == 1)
        {
            if(fscanf(config_file, "%d", &child) != 1)
                write(fd[1], &no_message, sizeof(int));
	    else if(child > max_child)
		write(fd[1], &no_message, sizeof(int));
            else
            {
                c = fgetc(config_file);
                if ((c == EOF) || (c != '\n'))
                    write(fd[1], &no_message, sizeof(int));
                else
                {
                    write(fd[1], &child , sizeof(int));
                    c = fgetc(config_file);
                    while (c != EOF)
                    {
                        byte[i] = c;
                        i++;
                        c = fgetc(config_file);
                    }
                    byte[i-1] = '\0';
                    if (i != 0)
                        write(fd[1], byte, strlen(byte)*sizeof(char));
                }
            }
            fclose(config_file);
        }
        else 
            write(fd[1], &no_message, sizeof(int));
	    kill(father_pid, SIGUSR1);
    }
    else 
        semaphor = 0;    
}

void SigRead(int sig_num)
{
    char byte[1024];
    if(getpid() != father_pid)
    {
	printf("son with pid %d gets\n", getpid());
        read(fd[0], byte, 1024*sizeof(char));
        printf("%s\n\n", byte);
	    kill(father_pid, SIGUSR2);
        signal(SIGUSR2, SigRead);
    }
    else
	    semaphor = 1;
}

void KillChild(int sig_num)
{
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

int count_of_args(char* value)
{
    int num = 0;
    while (*value != '\0')
    {
        if ((*value < '0') || (*value > '9'))
            return -1;
        num = num * 10 + *value - '0';
        value++;
    }
    return num;
}


