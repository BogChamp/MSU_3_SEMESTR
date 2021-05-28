#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 10
typedef struct node{
	int line;/*Number of word's line*/
	int start;/*Begining of word and it's end*/
	char* string;/*hold pointer to the word*/
	struct node *left;
	struct node *right;
} Tree; 
Tree *top = NULL;

int option(char* string);/*Check if arguement an option*/

int num_of_str(char* string);/*String to number*/


int search_func(FILE* file, int diap1, int diap2, char* find_word);/*when we have num of last string*/

int find_me(Tree* top, char* find_word, char** stroka, int raznica, int* is_line);


int replace_func(FILE* file, int diap1, int diap2, char* replace_word, char* include_word);

int replace_me(char** stroka, char* include, int dlina, int* count, int* size);


int include_word_tree(char* word, Tree** top, int diap1, size_t count);

int clear_struct(Tree** top);


int main(int argc,char** argv)
{
	FILE* file;/*open file*/
	char* string;/*to read options*/
	char* find_word;/*is option is search*/
	char* replace_word;/*what to need remove*/
	char* include_word;/*what need to include*/
	int i = 0;/* to count value of options*/
	char c;
	int count_r = 0, count_s = 0, count_d = 0, diap1 = 1, diap2 = -1;
	if(argc < 3)
	{
		printf("Wrong input\nNo file or no options\n");
		return -1;
	}

	file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("No file found\n");
		return -1;
	}
	
	for (i = 2; i < argc; i++)/*Checking write input of arguements*/
	{

		string = argv[i];
	
		switch (option(string))
		{
			case 0: 
				if ((count_s != 0) || (count_r != 0))
				{
					printf("Different options\n");
					fclose(file);
					return -1;
				}
				count_s++;
				i++;

				if(i == argc)
				{
					printf("Wrong input\n");
					fclose(file);
					return -1;
				}

				find_word = argv[i];

				if(option(find_word) != -1)
					{
						printf("Wrong input\n");
						fclose(file);
						return -1;
					}
				break;
			case 1:
				if ((count_s != 0) || (count_r != 0))
				{
					printf("Different options\n");
					fclose(file);
					return -1;
				}
				count_r++;
				i++;

				if(i == argc)
				{
					printf("Wrong arguements of options\n");
					fclose(file);
					return -1;
				}

				replace_word = argv[i];

				if(option(replace_word) != -1)
					{
						printf("Wrong input\n");
						fclose(file);
						return -1;
					}
			
				i++;

				if (i == argc)
				{
					printf("Wrong input\n");
					fclose(file);
					return -1;
				}

				include_word = argv[i];

				if(option(include_word) != -1)
					{
						printf("Wrong input\n");
						fclose(file);
						return -1;
					}
				break;
			case 2:
				if (count_d != 0)
					{
						printf("Wrong input\n");
						fclose(file);
						return -1;
					}
				count_d++;
				i++;

				if (i == argc)
				{
					printf("Wrong input\n");
					fclose(file);
					return -1;
				}

				if(option(argv[i]) != -1)
					{
						printf("Wrong input\n");
						fclose(file);
						return -1;
					}

				diap1 = num_of_str(argv[i]);

				if (diap1 < 1)
				{
					printf("Wrong input\n");
					fclose(file);
					return -1;
				}

				i++;

				if (i != argc) 
					{
						if (option(argv[i]) == -1)
						{
							diap2 = num_of_str(argv[i]);
							if (diap2 < 1)
							{
								printf("Wrong input\n");
								fclose(file);
								return -1;
							}
						}
						else i--;
					}
				if ((diap1 > diap2) && (diap2 != -1))
					{
						printf("Wrong input\n");
						fclose(file);
						return -1;
					}
					break;
			default:
				fclose(file);
				printf("Wrong input\n");
				return -1;
				break;
		}
	}/*end of checking*/

	i = 1;

	while (i != diap1)
	{
		c = fgetc(file);
		if (c == '\n')
			i++;
		if (c == EOF)
		{
			printf("There is no line in this diapason\n");
			fclose(file);
			return -1;
		}
	}

	if ((count_r == 0) && (count_s == 0))
	{
		printf("no needed options!\n");
		fclose(file);
		return -1;
	}
	

	if (count_r == 0)
		search_func(file, diap1, diap2, find_word);
	else replace_func(file, diap1, diap2, replace_word, include_word);
	fclose(file);
	return 0;
}


int search_func(FILE* file, int diap1, int diap2, char* find_word)
{
	int i = 0, j = 0, size1, size2, size3 = SIZE, count = 0, raznica = diap1;/*just a counter*/
	char* slovo;
	char** stroka = (char**)malloc(size3 *sizeof(char*));
	char c = ' ';
	int is_line = 0;
        c = fgetc(file);
		if (c == EOF) 
		{
			printf("There is no words\n");
			free(stroka);
			return 0;
		}
        while(((c != EOF) && (diap2 == -1)) || ((diap2 != -1) && (diap1 <= diap2) && (c != EOF)))
	    {
		    if (c == '\n')
		    {
			    if (j != 0)
			    	{
						if (j == size1)
			    		{
				    		size1 *= 2;   
                    		slovo = (char*)realloc(slovo,size1 * sizeof(char)); 
                		}
			    		slovo[j] = '\0';
				    	include_word_tree(slovo, &top, diap1, count);
				    }
					j = 0;
                    diap1++;
				    i++;
		    }
		    else if ((c == '.') || (c == ';') || (c == ',') || 
		        (c == ' ') || (c == '-') || (c == ':') || 
		        (c == '(') || (c == ')') ||(c < 0) || (c > 255))
			    {
				    if (j != 0)
				    {
						if (j == size1)
			    		{
				    		size1 *= 2;   
                    		slovo = (char*)realloc(slovo,size1 * sizeof(char)); 
                		}
			    		slovo[j] = '\0';
				    	include_word_tree(slovo, &top, diap1, count);	
				    	j = 0;
				    }
			    }
		    else    
		    {
			    if (j == 0)
			    {
				    size1 = SIZE;
				    slovo = (char*)malloc(size1 * sizeof(char));
			    }
			    else if (j == size1)
			    {
				    size1 *= 2;   
                    slovo = (char*)realloc(slovo,size1 * sizeof(char)); 
                }
			    slovo[j] = c;
			    j++;
		    }
            
		    if (c != '\n')
		    {
			    if (count == 0)
			    {
				    size2 = SIZE;
				    stroka[i] = (char*)malloc(size2 * sizeof(char));
			    }
			    else if (count == size2)
			    {
				    size2 *= 2;
				    stroka[i] = (char*)realloc(stroka[i], size2 * sizeof(char));
			    }
			    stroka[i][count] = c;
                count++;
		    }
            else 
			{
				if (count == size2)
			    {
				    size2 *= 2;
				    stroka[i-1] = (char*)realloc(stroka[i-1], size2 * sizeof(char));
			    }
			    if (count != 0)
					stroka[i-1][count] = '\0';
                else stroka[i-1] = NULL;
                count = 0;
                if (i == size3)
			    {
				    size3 *= 2;
				    stroka = (char**)realloc(stroka, size3 * sizeof(char*));
			    }
			}
            c = fgetc(file);
        }
        find_me(top,find_word,stroka, raznica, &is_line);
        clear_struct(&top);
    for (j = 0; j != i; j++)
    {
        if (stroka[j] != NULL)
            free(stroka[j]);
    }
    free(stroka);
	if (is_line == 0)
		printf("No line with this word!\n");
    return is_line;
}
    



int find_me(Tree* top, char* find_word, char** stroka, int raznica, int* is_line)
{
	while(top != NULL)
	{
        if (strcmp(find_word, (top -> string)) == 0)
            {
                if (stroka[(top -> line) - raznica] != NULL)
                {
                    printf("%s \n", stroka[(top -> line) - raznica]);
                    free(stroka[(top -> line) - raznica]);
                    stroka[(top -> line) - raznica] = NULL;
                    *is_line = 1;
                }
            }
		if (strcmp(find_word, (top -> string)) > 0)
			top = top -> right;
		else top = top -> left;
	}
	return 0;
}


int replace_func(FILE* file, int diap1, int diap2, char* replace_word, char* include_word)
{
	int i = 0, j = 0, size1, size2, size3 = SIZE, count = 0, raznica =diap1;/*just a counter*/
	char* slovo;
	char** stroka = (char**)malloc(size3*sizeof(char*));
	char c = ' ';
	int is_line = 0;
        c = fgetc(file);
		if ((c == EOF) && (i == 0))
		{
			printf("There are no words\n");
			free(stroka);
			return c;
		}
	    while(((c != EOF) && (diap2 == -1)) || ((diap2 != -1) && (diap1 <= diap2) && (c != EOF)))
		{
			if (c == '\n')
		    {
				if (j != 0)
			    	{
						if (j == size1)
			    		{
				    		size1 *= 2;   
                    		slovo = (char*)realloc(slovo,size1 * sizeof(char)); 
                		}
			    		slovo[j] = '\0';					
				    	include_word_tree(slovo, &top, diap1, count);
					}
				if ((strcmp(replace_word, slovo) == 0) && (j != 0))
					replace_me(&(stroka[i]), include_word, strlen(slovo), &count, &size2);
				j = 0;
                diap1++;
				i++;
		    }
		    else if ((c == '.') || (c == ';') || (c == ',') || 
		        (c == ' ') || (c == '-') || (c == ':') || 
		        (c == '(') || (c == ')') || (c < 0) || (c > 255))
			    {
				    if (j != 0)
				    {
						if (j == size1)
			    		{
				    		size1 *= 2;   
                    		slovo = (char*)realloc(slovo,size1 * sizeof(char)); 
                		}
			    		slovo[j] = '\0';
				    	include_word_tree(slovo, &top, diap1, count);	
				    }
					if ((strcmp(replace_word, slovo) == 0) && (j != 0))
						replace_me(&(stroka[i]), include_word, strlen(slovo), &count, &size2);
					j = 0;
				}
		    else    
		    {
			    if (j == 0)
			    {
				    size1 = SIZE;
				    slovo = (char*)malloc(size1 * sizeof(char));
			    }
			    else if (j == size1)
			    {
				    size1 *= 2;   
                    slovo = (char*)realloc(slovo,size1 * sizeof(char)); 
                }
			    slovo[j] = c;
			    j++;
		    }
            
		    if (c != '\n')
		    {
			    if (count == 0)
			    {
				    size2 = SIZE;
				    stroka[i] = (char*)malloc(size2 * sizeof(char));
			    }
			    else if (count == size2)
			    {
				    size2 *= 2;
				    stroka[i] = (char*)realloc(stroka[i], size2 * sizeof(char));
			    }
			    stroka[i][count] = c;

                count++;
				
				if (count == size2)
			    {
				    size2 *= 2;
				    stroka[i] = (char*)realloc(stroka[i], size2 * sizeof(char));
			    }
				stroka[i][count] = '\0';
		    }
            else 
            {
                if (count == 0)
                    stroka[i-1] = NULL;
                if (i == size3)
			    {
				    size3 *= 2;
				    stroka = (char**)realloc(stroka, size3 * sizeof(char*));
			    }
                count = 0;
            }
			    c = fgetc(file);
        }
        find_me(top,replace_word, stroka, raznica, &is_line);
        clear_struct(&top);
        for (j = 0; j != i; j++)
        {
        if (stroka[j] != NULL)
            free(stroka[j]);
        }
    free(stroka);
	if (is_line == 0)
		printf("No line with this word!\n");
    return is_line;
}

int replace_me(char** stroka, char* include, int dlina, int* count, int* size)
{
	char c;
	int i;
	for(i = 0; i < strlen(include); i++)
	{
		if (((*count) - dlina + i) == (*size))
			    {
				    (*size) *= 2;
				    (*stroka) = (char*)realloc((*stroka), (*size) * sizeof(char));
			    }
		c = include[i];
		(*stroka)[(*count) - dlina + i] =  c;
	}
	if (((*count) - dlina + i) == (*size))
		{
			(*size) *= 2;
			(*stroka) = (char*)realloc((*stroka), (*size) * sizeof(char));
		}
	(*stroka)[(*count) - dlina + i] =  '\0';
		(*count) += strlen(include) - dlina;
	return 0;
}

int include_word_tree(char* word, Tree** top, int diap1, size_t count)
{
	if ((*top) == NULL)
	{
		*top = (Tree*)malloc(sizeof(Tree));
		(*top) -> line = diap1;
		(*top) -> string = word;
		(*top) -> start = count - strlen(word);
		(*top) -> left = NULL;
		(*top) -> right = NULL;
	}
	else if (strcmp(word, (*top) -> string) > 0)
		include_word_tree(word,&((*top) -> right),diap1,count);
	else include_word_tree(word,&((*top) -> left), diap1,count);
	return 0;
}

int option(char* string)
{
	char** massiv;
	int i, j;
	massiv = (char**)malloc(6 * sizeof(char*));
	massiv[0] = "-s";
	massiv[1] = "-r";
	massiv[2] = "-d";
	massiv[3] = "--search";
	massiv[4] = "--replace";
	massiv[5] = "--diapason";
	for (i = 0;i != 6; i++)
	{
		if (strcmp(string,massiv[i]) == 0)
		{
			switch (i)
			{
				case 0:
				case 3:
					j = 0;
					break;
				case 1:
				case 4:
					j = 1;
					break;
				case 2:
				case 5:
					j = 2;
					break;
			}
			free(massiv);
			return j;
		}
	}
	free(massiv);
	return -1;
}

int num_of_str(char* string)
{
	int i = 0;
	if (string == NULL)
	{
		printf("Where is argument?\n");
		return -1;
	}

	while(*string != '\0')
	{
		if ((*string < '0') || (*string > '9'))
			return -1;
		i = i*10 + *string - '0';
		string++;
	}
	return i;
}

int clear_struct(Tree** top)
{
	if (*top != NULL)
	{
		clear_struct(&((*top) -> left));
		clear_struct(&((*top) -> right));
		free((*top) -> string);
		free(*top);
		*top = NULL;
	}
	return 0;	
}
