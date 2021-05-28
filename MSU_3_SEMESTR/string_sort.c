#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

int sort(char* arr, char delim);/*сортирует в лексикографическом порядке*/
int sravn(char* arr1, char* arr2);/*сравнивает две подстроки*/
char* read(FILE* file, int num_str);/*считывает из файла строку*/
int stroka(char* arg);/*переводим в инт*/
int output(char* arrg);/*Выводит содержимое динамического массива*/

int main(int argc, char *argv[])
{
    int size = SIZE, n = 0, i = 0, num_str = 1;
    char c;
    char* mas;
    FILE* file;
	switch (argc)
    {   
        case 1: 
	        mas = (char*)malloc(size * sizeof(int));
            printf("Введите строку:\n");
            while ((c = getchar()) != '\n')
            {
                if (n == size)
                {
                    size *= 2;
                    mas = (char*)realloc(mas,size * sizeof(char));
                }
                *(mas + n) = c;
                n++;    
            }
        break;
        case 2:
		    file = fopen(argv[1], "r");
		    if(file == NULL)
		    {
			    printf("Нет файла!\n");
			    return 0;
		    }
		    mas = read(file, num_str);
		    if (mas == NULL)
		    {
			    printf("Конец программы!\n");
			    return 0;
		    }
            i = 0;
		    while (*(mas+i) != '\0')
			    i++;
		    n = i;
        break;
	
	    case 3:
		    file = fopen(argv[1], "r");
		    if(file == NULL)
		    {
			    printf("Нет файла!\n");
			    return 0;
		    }
		    num_str = stroka(argv[2]);
		    mas = read(file, num_str);
		    if (mas == NULL)
		    {
			    printf("Конец программы!\n");
			    return 0;
		    }
            i = 0;
		    while (*(mas+i) != '\0')
			    i++;
		    n = i;
        break;
	
        default:
            printf("Много аргументов!\n");
            return 0;
        break;
    }
        if (n == 0)
        {
            free(mas);
            printf("Пустая строка!\nКонец программы!\n");
            return 0;
        }
        printf("Вот такую строку вы ввели:\n");
        output(mas);
        printf("Введите разделитель, чтобы разделить строку:\n");
        printf("Введите q чтобы завершить программу.\n");
        scanf("%c", &c);
        while (c != 'q') 
        {
	        while(getchar() != '\n');
            sort(mas, c);
	        printf("\n");
            printf("Вот такая строка у вас:\n");
            output(mas);
            printf("Введите разделитель, чтобы разделить строку:\n");
            printf("Введите q чтобы завершить программу.\n");
            scanf("%c", &c);
        }
        printf("Конец программы!\n");
        free(mas);
    return 0;
}

char* read(FILE* file, int num_str)
{
	char* arr;
	int size = SIZE, i = 1;
	char c;
	if (num_str < 1)
	{
		printf("Net takoi stroki\n");
		return NULL;
	}
	while(i != num_str)
	{
		c = fgetc(file);
		if (c == EOF)
		{
			printf("Net takoi stroki\n");
			return NULL;
		}
		if(c == '\n')
	        	i++;
	}
	i = 0;
	arr = (char*)malloc(size*sizeof(char));
	c = fgetc(file);
    while ((c != '\n') && (c != EOF))
    {
        if (i == size)
        {
            size *= 2;
            arr = (char*)realloc(arr, size * sizeof(char));
        }
        arr[i] = c;
	c = fgetc(file);
        i++;
    }
	return arr;
}

int stroka(char* arg)
{
	int nomer = 0;
	while(*arg != '\0')
	{
		if ((*arg < '1') || (*arg > '9'))
			return -1;
		nomer = nomer*10 + *arg - '0';
		arg++;
	}
	return nomer;
}


int sort(char* arr, char delim)
{
    int size1 = SIZE, size2 = SIZE, i = 0, j = 0, k = 0, bool = 0;/*i,j и k просто счетчики */
    char* arr1 = (char*)malloc(size1 * sizeof(char));
    char** arr2 = (char**)malloc(size2 * sizeof(char*));/*Массив массивов*/
    printf("\nВот такую строку функция получает на входе!\n");
    output(arr);
    printf("\nВыведем подстроки:\n");
    while (arr[i] != '\0')
    {
        if ((arr[i] == delim) && (j != 0))/*дошли до разделителя*/
        {   
	    if (j == size1)
	    {
		size1 *= 2;
		arr1 = (char*)realloc(arr1, size1 * sizeof(char));
	    }
	    arr1[j] = '\0';
            if (k == size2)
            {
                size2 *= 2;
                arr2 = (char**)realloc(arr2,size2 * sizeof(char*));
            }
            arr2[k] = arr1;
	        output(arr2[k]);
            size1 = SIZE;
            arr1 = (char*)malloc(size1 * sizeof(char));
            k++;
            i++;
            j = 0;
        }
        else if (arr[i] == delim)
            i++;
        else
        {
          if (j == size1)
         {
             size1 *= 2;
             arr1 = (char*)realloc(arr1, size1 * sizeof(char));
         }
         arr1[j] =arr[i];
         j++;
         i++;
        }
    }

    if (j != 0)/*Добавляем последнюю строку в массив массивов */
        {   
	    if (j == size1)
	    {
		size1 *= 2;
		arr1 = (char*)realloc(arr1, size1 * sizeof(char));
	    }
	    arr1[j] = '\0';
            if (k == size2)
            {
                size2 *= 2;
                arr2 = (char**)realloc(arr2, size2 * sizeof(char*));
            }
            arr2[k] = arr1;
	        output(arr2[k]);
	        printf("\n");
            k++;
            j = 0;
        }
	printf("\nКоличество подстрок = %d\n", k);
	printf("В лексикографическом порядке\n");
    if ((j == 0) && (k == 0))/*Если состоит из разделителей */
    {
        printf("Строка разделителей!\n");
        free(arr1);
        free(arr2);
        return 0;
    }
    while (bool == 0)/*Сортируем пузырьком*/
    {
        bool = -1;
        for (j = 0; j != (k - 1); j++)
        {
            if (sravn(arr2[j], arr2[j+1]) == 0)
            {
                bool = 0;
                arr1 = arr2[j];
                arr2[j] = arr2[j+1];
                arr2[j+1] = arr1;
            }
        }
    }
    for (j = 0; j != k ; j++)
        output(arr2[j]);
    for(j = 0;j != k ; j++)
        free(arr2[j]);
    free(arr2);
    return 0;
}

int sravn(char* arr1, char* arr2)
{
    while((*arr1 != '\0') && (*arr2 != '\0'))
    {
        if (*arr1 < *arr2)
            return -1;
        else if(*arr1 > *arr2)
            return 0;
            arr1++;
            arr2++;
    }
    if (*arr1 == '\0')
        return -1;
    else return 0;
}

int output(char* arrg)
{
    if (arrg == NULL)
        return 0;
    printf("%s", arrg);
    /*while ((*arrg) != '\0')
    {
        printf("%c", *arrg);
        arrg++;
    }*/
    printf("\n\n");
    return 0;
}
