#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int make_child(FILE* file1, char* arg, int num);/*создаем детей*/

int write_config(FILE* file, int num);/*Проверяем на корректность конфиг.файл*/

int read_inf(FILE* file, char* replace, char* include);/*считываем информацию с конфиг файла*/

int change_text(FILE* file, char replace, char include, int pid); /*работа с файлом*/

int include_letter(FILE* file, char replace, char include, int pid);/*замена в слове*/

int main(int argc, char** argv)
{
    int num;
    char c;
    FILE* file1;
    if (argc != 3)                      /*Проверяю входные данные на корректность*/
    {
        printf("Wrong input\n");
        return 0;
    }

    file1 =fopen(argv[1], "r");

    if (file1 == NULL)                   /*Если файла нет то ошибка*/
    {
        printf("Wrong config file\n");
        fclose(file1);
        return 0;
    }

    if (fscanf(file1, "%d", &num) != 1)              /*если количество процессов не число*/
    {
        fclose(file1);
        printf("Wrong number of children\n");
        return 0;
    }

    if (num < 1)                                    /*если количество процессов не натурально*/
    {
        fclose(file1);
        printf("Wrong number of children\n");
        return 0;
    }

    while ((c = fgetc(file1)) != '\n')               /*проверяю конфиг файл на корректность*/
    {
        if (c != ' ')
        {
            printf("Wrong config file\n");
            fclose(file1);
            return 0;
        }    
    }

    if (write_config(file1, num) != 0)
    {
        printf("Wrong config file\n");
        fclose(file1);
        return 0;
    }

    fclose(file1);

    file1 = fopen(argv[2], "r+");
    
    if (file1 == NULL)                   /*Если преобразуемого файла нет то ошибка*/
    {
        printf("Wrong text file\n");
        return 0;
    }
    fclose(file1);

    file1 = fopen(argv[1], "r");                         /*если конфиг файл без ошибок продолжаем*/

    while ((c = fgetc(file1)) != '\n');                  /*счетчик считывания переношу на след строку, где правила замены*/

    make_child(file1, argv[2], num);

    fclose(file1);

    return 0;
}

int make_child(FILE* file1, char* arg, int num)
{
    int i, j, pid;
    char replace, include;
    FILE* file;
    read_inf(file1, &replace, &include);
    pid = getpid();
    printf("father pid %d\n", pid);
    file = fopen(arg, "r+");
    change_text(file, replace, include, pid);
    fclose(file);
    for(i = 1; i < num; i++)                            
    {
        switch(fork())
        {
            case -1:
                printf("error fork\n");
                return -1;
                break;
            case 0:
			pid = getpid();
                        printf("son %d pid %d\n", i, pid);
                        read_inf(file1, &replace, &include); 
                        file = fopen(arg, "r+");
                        change_text(file, replace, include, pid);
                        fclose(file);
                        return 0;           
                break;
            default:
                read_inf(file1, &replace, &include);
                break;
        }
    }
    for (i = 1; i < num; i++)
	    wait(NULL);
    return 0;
}

int write_config(FILE* file, int num)
{
    char c2 = ' ', c1 = ' ';
    int i = 0, j = 0;
    int letter[256];                      /*завожу массив чтоб отслеживать повторяющиеся символы*/
    for(j = 0; j < 256; j++)
        letter[j] = 1;
    j = 0;
    while((c2 = fgetc(file)) != EOF)
    {
        if (c2 == '\n')
        {
            
            if ((j != 2) && (j != 0))
                return -1;
            if (j != 0)
                i++;
            j = 0;
            
            c1 = ' ';
        }
        else
        {
            if ((c1 != ' ') && (c2 != ' '))
                return -1;
            if((c2 != ' ') && (letter[c2] != 1) && (j == 0))
                return -1;
            if (j == 0)
                letter[c2] = 0;
            if (c2 != ' ')
                j++;
            c1 = c2;
        }
    }

    if(i != num)
        return -1;
    else return 0;
}

int read_inf(FILE* file, char* replace, char* include)
{
    int i = 0;
    char c;
    do
    {
        c = fgetc(file);
        if ((c != ' ') && (c != '\n'))
        {
            if (i == 0)
                *replace = c;
            else
                *include = c;
            i++;
        }
        
    } while((i != 2) || (c != '\n'));
    return 0;
}

int change_text(FILE* file, char replace, char include, int pid)             /*смотрю файл, считываю слова. если длина слова не меньше десяти,
                                                                    возвращаю указатель на начало слова и начинаю менять буквы*/
{
    char c;
    int i = 0, check = 0;
    while ((c = fgetc(file)) != EOF)
    {
        if ((c == '\n') || (c == '.') || (c == ';') || (c == ',') || 
		    (c == ' ') || (c == '-') || (c == ':') || 
		    (c == '(') || (c == ')') || (c < 0) || (c > 255))
            {
                i = 0;
                check = 0;
            }
        else 
        {
            if ((c == replace) && (i == 0))
                check = 1;
            if (i < 9)
                i++;   
            if ((check != 0) && (i == 9))
            {
                fseek(file, -10, SEEK_CUR);
                include_letter(file, replace, include, pid);
            }
        }       
    }
    return 0;
}

int include_letter(FILE* file, char replace, char include,int  pid)
{
    char c, i = 0;
    char pidstr[10];
    c = fgetc(file);
    fputc(include, file);
    while ((c = fgetc(file)) != EOF)
    {
       if ((c == '\n') || (c == '.') || (c == ';') || (c == ',') || 
		    (c == ' ') || (c == '-') || (c == ':') || 
		    (c == '(') || (c == ')') || (c < 0) || (c > 255))
                break;          
    }
    sprintf(pidstr,"%d", pid);
    i = strlen(pidstr);
    fseek(file, -(i+1), SEEK_CUR);
    fprintf(file,"%s", pidstr);

    return 0;
}
