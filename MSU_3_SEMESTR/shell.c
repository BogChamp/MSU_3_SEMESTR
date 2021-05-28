#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define SIZE 10

pid_t* pid;
int size_pid = SIZE, count_pid = 0;
 
int ended = 1;

int input_string();

int correct_option(char** command, int words);

int make_command(char** command, int words);

int conveyer(char*** options, int child);


int internal(char** command, int words)
{
		if (strcmp(command[0], "exit") == 0)
		{
			if (words > 1)
			{
				printf("too much arguements for exit\n");
				return -1;
			}
			else
				return 1;
		}
		else if (strcmp(command[0], "pwd") == 0)
		{
			if (words > 1)
			{
				printf("too much arguments for pwd\n");
				return -1;
			}
			else
				return 3;
		}
		else if (strcmp(command[0], "cd") == 0)
		{
			if (words == 1)
			{
				printf("Not enough arguments for cd\n");
				return -1;
			}
			else if (words > 2)
			{
				printf("too much arguments for cd\n");
				return -1;
			}
			else
				return 2;
		}
	return 0;
}


int pwd();
int cd(char* direct);


int main()
{    
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	input_string();
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
    return 0;
}


int input_string()         								/*функция считывания введеных утилит, считываем
														утилиты до ; , далее отправляем эту последовательность на 
														обработку другой функции, и так пока не кончится */
{
	int i;												/*счетчик для освобождения памяти*/

	char c, previous = ' ';
	char** inter_string;								/*считываем аргументы до ; или до \n , далее обнуляем и по новой*/
	
	int count_command = 0, count_letter = 0;			/*count_command это количество аргументов одной команды,
														а count_letter это количество букв в слове*/
	
	int size_of_command = SIZE, size_of_letter = SIZE;	/*размеры массивов команд и букв соответственно*/


	printf("\x1B[01;32mI_LOVE_SHELL$\e[0m ");
	while((c = getchar()) != EOF)
	{
		if (previous != '#')
		{
			if (((c != ' ') && (c != '|') && (c != '>') 
			&& (c != '<') && (c != '#') && (previous != '\\') 
			&& (c != '"') && (c != ';') && (c != '\n')) || 
			((previous == '"') && (c != '"')))				/*если я встретил кавычки, то буду записывать все в единую команду,
															если я ввел enter при кавычках, то обработка тут*/
			{
				if  (c == '\n')
					printf("> ");
				else
				{
					if (count_letter == 0)
					{
						if (count_command == 0)																					
							inter_string = (char**)malloc(size_of_command * sizeof(char*));
						else if (count_command == size_of_command)
						{
							size_of_command <<= 1;
							inter_string=(char**)realloc(inter_string, size_of_command * sizeof(char*));
						}

						inter_string[count_command] = (char*)malloc(size_of_letter * sizeof(char));
					}
					else if (count_letter == size_of_letter)
					{
						size_of_letter <<= 1;
						inter_string[count_command]=(char*)realloc(inter_string[count_command], size_of_letter * sizeof(char));
					}
					inter_string[count_command][count_letter] = c;
					count_letter++;
				}
			}	
			else 
			{
				if (count_letter != 0)  											/*в массиве строк формируется новый аргумент*/
				{
					if (count_letter == size_of_letter)
					{
						size_of_letter <<= 1;
						inter_string[count_command]=(char*)realloc(inter_string[count_command], size_of_letter * sizeof(char));
					}
					inter_string[count_command][count_letter] = '\0';
					count_command++;
				}

				if (count_command == 0)
				{
					if ((c != ';') && (c != '#') 
					&& (c != '"') && (c != ' ') && (c != '\n'))
					{
						inter_string = (char**)malloc(size_of_command * sizeof(char*));
						inter_string[count_command] = (char*)malloc(size_of_letter * sizeof(char));
						inter_string[count_command][count_letter] = c;
						count_letter++;
						inter_string[count_command][count_letter] = '\0';
						count_command++;
					}			
				}
				else if (previous != '\\') 
				{
					
					if ((c == '>') && (!(strcmp(inter_string[count_command - 1], "2")) || !(strcmp(inter_string[count_command - 1], ">"))))
					{
						inter_string[count_command - 1][1] = c;
						inter_string[count_command - 1][2] = '\0';
					}
					else if (c == ';') 
					{
						if (count_command != 0)
						{
							if (count_command == size_of_command)
							{
								size_of_command <<= 1;
								inter_string=(char**)realloc(inter_string, size_of_command * sizeof(char*));
							}
							inter_string[count_command] = NULL;
							
							switch(correct_option(inter_string, count_command))
							{
								case 0:
									make_command(inter_string, count_command);
									break;
								case -1:
									printf("Error syntaxis\n");
									break;
								default:
									break;
							}

							for (i = 0; i < count_command; i++)
							{
								if (inter_string[i] != NULL)
									free(inter_string[i]);
							}
							free(inter_string);
							count_command = 0;
							count_letter = 0;
							size_of_command = SIZE;
							size_of_letter = SIZE;
						}
					}

					else if ((c != ';') && (c != '#') && (c != '/')
					&& (c != '"') && (c != ' ') && (c != '\n'))
					{
						if (count_command == size_of_command)
						{
							size_of_command <<= 1;
							inter_string=(char**)realloc(inter_string, size_of_command * sizeof(char*));
						}
						count_letter = 0;
						inter_string[count_command] = (char*)malloc(size_of_letter * sizeof(char));
						inter_string[count_command][count_letter] = c;
						count_letter++;
						inter_string[count_command][count_letter] = '\0';
						count_command++;
					}

	
				}
				else if (previous == '\\')
				{
					if (c != '\n')
					{
						count_command--;
						inter_string[count_command][count_letter - 1] = c;
						c = ' ';
					}
					else
					{
						count_command--;
						count_letter--;
						printf("> ");	
						c = ' ';
					}		
				}
				
				if (previous != '\\')
					count_letter = 0;
				else 
					previous = ' ';
			}
			if ((c == '"') && (previous == '"'))
			{
				previous = ' ';
				c = ' ';
			}
			else if (previous != '"')
				previous = c;
		}
		if ((c == '\n') && (previous != '"'))
		{
			if (count_command != 0)
			{
				if (count_command == size_of_command)
					{
						size_of_command <<= 1;
						inter_string=(char**)realloc(inter_string, size_of_command * sizeof(char*));
					}
				inter_string[count_command] = NULL;

				for (i = 0; i < count_command; i++)
				{
					printf("%s\n", inter_string[i]);
				}

				switch(correct_option(inter_string, count_command))
				{
					case 0:
						make_command(inter_string, count_command);
						break;
					case -1:
						printf("Error syntaxis\n");
						break;
					default:
						break;
				}
				for (i = 0; i < count_command; i++)
				{
					if(inter_string[i] != NULL)
						free(inter_string[i]);
				}
				free(inter_string);
				count_command = 0;
				count_letter = 0;
				size_of_command = SIZE;
				size_of_letter = SIZE;
			}
			if (ended != 0)
				printf("\x1B[01;32mI_LOVE_SHELL$\e[0m ");
			previous = ' ';
		}
		if (ended == 0)
			break;
	}
	if(c == EOF)
		printf("\n");
	return 0;
}
		
int correct_option(char** command, int words) 								/*проверяем строку на корректность*/
{
	char word1[] = ">";
	char word2[] = ">>";
	char word3[] = "<";
	char word4[] = "|";
	char word5[] = "2>";
	int i;
	int count_flow = 0, count_error = 0, count_norm = 0, count_in = 0;

	if((words == 1) && ((strcmp(command[0],word1) == 0) || (strcmp(command[0], word2) == 0) ||
			(strcmp(command[0], word3) == 0) || (strcmp(command[0],word5) == 0)))
		return -1;

	switch(internal(command, words))
	{
		case 1:
			ended = 0;
			return -2;
			break;
		case 2:
			if (cd(command[1]) == -1)
				printf("No such directory\n");
			return -2;
			break;
		case 3:
			pwd();
			return -2;
			break;
		case -1:
			return -2;
			break;
		default:
			break;
	}

	for(i = 0; i < words; i++)
	{
		if((strcmp(command[i],word1) == 0) || (strcmp(command[i], word2) == 0))
		{
			if (i == words - 1)
				return -1;
		    if(count_norm == 0)
				return -1;
			count_flow++;
			count_norm = 0;
		}
		else if(strcmp(command[i], word5) == 0)
		{
			if (i == words - 1)
				return -1;
			if(count_norm == 0)
				return -1;
			count_in++;
			count_norm = 0;
		}
		else if(strcmp(command[i], word5) == 0)
		{
			if (count_in != 0)
				return-1;
			if (i == words - 1)
				return -1;
			if(count_norm == 0)
				return -1;
			count_error++;
			count_norm = 0;
		}
		else if(strcmp(command[i],word4) == 0)
		{
			if (i == words - 1)
				return -1;
			if(count_norm == 0)
				return -1;
			count_norm = 0;
			count_error = 0;
			count_flow = 0;
			count_in = 0;
		}
		else
			count_norm++;
		
		if ((count_norm > 1) && ((count_flow != 0) || (count_error != 0)))
			return -1;
	}

	return 0;
}


int make_command(char** command, int words)  		/*когда заканчивается ввод аргументов одной команды,
												вызываем эту функцию, она разделяет конвейер на утилиты и вызывает функцию конвейера*/

{
	int i, j = 1;     					 /*j это счетчик начала команды*/
	int size_options = SIZE, child = 0;
	char*** options = (char***)malloc(size_options * sizeof(char**));

	for (i = 0; i < words; i++)
	{
		printf("make command word %s\n", command[i]);
		if(strcmp(command[i], "|") == 0)				/*знак конвейера меняем на NULL*/
		{
			free(command[i]);
			command[i] = NULL;
			child++;
			j = 1;
		}
		else if (j == 1)
		{
			if (child == size_options)
			{
				size_options *= 2;
				options = (char***)realloc(options,size_options * sizeof(char**));
			}
			options[child] = &(command[i]);
			j = 0;
		}
	}
	child ++; 								/*так как последнюю команду в конвейере тоже нужно выполнить*/

	conveyer(options, child);

	free(options);

	return 0;
}

int conveyer(char*** options, int child)
{
	char word1[] = ">";
	char word2[] = ">>";
	char word3[] = "<";
	char word4[] = "2>";
	int i, j = 0, status;
	int flag_err = 0, flag_flow = 0, flag_input = 0, flag_end = 0;
	int input, input_err, input_from = 0, from, to;
	pid_t mas_pid[child];
	pid_t stop_pid = 0;

	int fd[2];

	for(i = 0 ; i < count_pid; i++)
	{
		printf("%d ", pid[i]);
	}
	printf("\n");


	for(i = 0; i < child; i++)
	{
		pipe(fd);
		if(i == 0)
			from = 0;
		if (i != child -1)
			to = fd[1];
		else 
			to = 1;
		switch(mas_pid[i] = fork())
		{
			case -1:
				printf("error fork\n");
				close(fd[0]);
				close(fd[1]);
				return 0;
				break;
			case 0:
				signal(SIGINT, SIG_DFL);
				signal(SIGTSTP, SIG_DFL);
				while (options[i][j] != NULL)
				{
						if(strcmp(options[i][j], word1) == 0)
						{
							flag_flow++;
							free(options[i][j]);
							options[i][j] = NULL;
						}
						else if(strcmp(options[i][j], word2) == 0)
						{
							flag_end++;
							free(options[i][j]);
							options[i][j] = NULL;
						}
						else if(strcmp(options[i][j], word3) == 0)
						{
							flag_input++;
							free(options[i][j]);
							options[i][j] = NULL;
						}
						else if(strcmp(options[i][j], word4) == 0)
						{
							flag_err++;
							free(options[i][j]);
							options[i][j] = NULL;
						}
						else 
						{
							if (flag_flow != 0)
							{
									if (flag_flow > 1)
										close(input);
									input = open(options[i][j], O_CREAT | O_WRONLY | O_TRUNC, 0666);
									printf("FLOW.open\n");
							}
							 if (flag_end != 0)
							{
									if (flag_end > 1)
										close(input);
									input = open(options[i][j], O_CREAT | O_WRONLY | O_APPEND, 0666);
									printf("END.open\n");
							}
							 if (flag_err != 0)
							{
								if (flag_err > 1)
								close(input_err);
								input_err = open(options[i][j], O_CREAT | O_WRONLY | O_TRUNC, 0666);
								printf("ERR.open\n");
							}
							 if (flag_input != 0)
							{
								if (flag_input > 1)
								close(input_from);
								input_from = open(options[i][j], O_RDONLY);
								printf("INPUT.open\n");
							}
						}
						printf("one step %s\n", options[i][j]);
					j++;
				}

				printf("flow %d, end %d, input %d, err %d\n",flag_flow, flag_end, flag_input, flag_err);

				if (input_from != -1)
				{

					if(flag_input != 0)
					{
						dup2(input_from, from);
					}
					else if (i != 0)
						dup2(from, 0);
					else close(fd[0]);

					if ((flag_flow != 0) || (flag_end != 0))
					{
						dup2(input,to);
					}
					else if (i != child - 1)
						dup2(to,1);
					else close(fd[1]);
					execvp(options[i][0], options[i]);
				}
				if (input_from != -1)
				{
					if (flag_err != 0)
						fprintf(stderr,"no option %s found\n", options[i][0]);
					else 
						fprintf(stdout,"no option %s found\n", options[i][0]);
				}
				else 
				{
					if (flag_err != 0)
						fprintf(stderr,"%s file not found\n", options[i][j-1]);
					else 
						fprintf(stdout,"%s file not found\n", options[i][j-1]);
				}
				if (flag_err != 0)
					close(input_err);
				if ((flag_flow != 0) || (flag_end != 0))
					close(input);
				else if(to != 1)
					close(to);
				if	(flag_input != 0)
					close(input);
				else close(fd[0]);
				exit(status);
				break;
			default:
				from = fd[0];
				if (to != 1)
					close(to);
				break;
		}		
	}

	if (strcmp("kill", options[0][0]) == 0)
	{
		for (i = 0; options[0][2][i] != '\0'; i++)
			stop_pid = stop_pid * 10 + options[0][2][i] - '0';
		waitpid(stop_pid, &status, WUNTRACED);
		if(WIFSIGNALED(status))
			printf("\nprocess with pid %d was killed\n", stop_pid);
		else if(WIFSTOPPED(status))
			printf("\nprocess with pid %d was stopped\n", stop_pid);
	}
	else 
	{
	for(i = 0; i < child; i++)
	{
		waitpid(mas_pid[i], &status, WUNTRACED);
		if(WIFSIGNALED(status))
			printf("\nprocess with pid %d was killed\n", mas_pid[i]);
		else if(WIFSTOPPED(status))
		{
			if (count_pid == 0)
				pid = (pid_t*)malloc(size_pid * sizeof(pid_t));
			else if (count_pid == size_pid)
			{
				size_pid *= 2;
				pid = (pid_t*)realloc(pid, size_pid * sizeof(pid_t));
			}
			pid[count_pid] = mas_pid[i];
			count_pid++;
			printf("\nprocess with pid %d was stopped\n", mas_pid[i]);
		}
	}
	}
	return 0;		
}

int pwd()
{
	char buffer[PATH_MAX];
	getcwd(buffer, PATH_MAX);
	printf("%s\n", buffer);
	return 0;
}

int cd(char* direct)
{
	return chdir(direct);
}
























