#include <stdio.h>
#define s_day 5
#define s_month 4
#define s_year 7
#define mask_m 15
#define mask_y 127

short to_comp(short day, short month, short year);
char to_norm(unsigned short date_time);
char binary(short date_time);
char change_year(short *date_time);
char change_month(short *date_time);
char change_day(short *date_time);
char show_day(unsigned short date_time);
char show_month(short date_time);
char show_year(short date_time);
char test(short day, short month, short year);

int main()
{
        unsigned short date_time, day, month, year, i;
        printf("Введите дату в формате ЧЧ ММ ГГ:\n");
        if (scanf("%hu %hu %hu", &day, &month, &year) != 3)
                {
                        printf("Неверный формат даты!\n");
                        return 0;
                }
        if (test(day, month, year) != 0)
                {
                        printf("Неверный формат даты!\n");
                        return 0;
                }
        date_time = to_comp(day, month, year);
        printf("Если хотите узнать дату, введите 0\n");
        printf("Если хотите узнать число, введите 1\n");
        printf("Если хотите узнать месяц, введите 2\n");
        printf("Если хотиту узнать год, введите 3\n");
        printf("Если хотите изменить число, введите 4\n");
        printf("Если хотиту изменить месяц, введите 5\n");
        printf("Если хотите изменить год, введите 6\n");
        printf("Если хотите вывести бинарное представление даты, введите 7\n");
        if ((scanf("%hu", &i) != 1))
        {
            printf("Конец программы!\n");
            return 0;
        }
         while ((i >= 0) && (i <= 7))
                {
                      printf("Вы ввели:  %hu\n", i);
                        switch (i)
                        {
                                case 0: to_norm(date_time);
                                        break;
                                case 1: show_day(date_time);
                                        break;
                                case 2: show_month(date_time);
                                        break;
                                case 3: show_year(date_time);
                                        break;
                                case 4: change_day(&date_time);
                                        break;
                                case 5: change_month(&date_time);
                                        break;
                                case 6: change_year(&date_time);
                                        break;
                                case 7: binary(date_time);
                                        break;

                        }
                        printf("\nВведите команду: \n");
                        if (scanf("%hu", &i) != 1)
                        {
                                  printf("Конец программы!biiiiiba\n");
                                  return 0;
                        }
                }
        printf("Конец программы!\n");
        return 0;
}

short to_comp(short day, short month, short year)
{
        short date_time;
        date_time = day;
        date_time <<= s_month;
        date_time |= month;
        date_time <<= s_year;
        date_time |= year;
        return date_time;
}

char to_norm(unsigned short date_time)
{
        unsigned short day, month = mask_m, year = mask_y;
        day = (date_time >> (s_month + s_year));
        month &= date_time >> s_year ;
        year &= date_time;
        (day > 10) ? printf("%hu",day) : printf("0%hu", day);
        (month > 10) ? printf(" %hu", month) : printf(" 0%hu", month);
        (year > 10) ? printf(" %hu\n", year) : printf(" 0%hu\n", year);
        return 0;
}

char binary(short date_time)
{
        unsigned short mask = 1;
        mask <<= (s_day + s_month + s_year - 1);
        for (; mask > 0; mask >>= 1)
                (mask & date_time) ? printf("1") : printf("0");
        printf("\n");
        return 0;
}
char change_year(short *date_time)
{   
    unsigned short day, month, year, MASK;
    MASK = *date_time;
    day = MASK >> (s_month + s_year);
    month = (MASK >> s_year) & mask_m;
    printf("Введите год:\n");
    if ((scanf("%hu", &year)) != 1) 
        {
            printf("Неверный формат даты!\n");
            while (getchar() != '\n');
            return 0;
        }     
    if (test(day, month, year) != 0)
    {
        printf("Неверный формат даты!\n");
        return 0;
    }
    *date_time = to_comp(day, month, year);   
    return 0;
}

char change_month(short *date_time)
{
    unsigned short day,month, year, MASK;
    MASK = *date_time;
    day = MASK >> (s_month + s_year);
    year = MASK & mask_y;
    printf("Введите месяц\n");
    if ((scanf("%hu", &month)) != 1)
    {
        printf("Неверный формат даты\n");
        while (getchar() != '\n');
        return 0;
    }   
    if (test(day, month, year) != 0)
    {
        printf("Неверный фомат даты!\n");
        return 0;
    }    
    *date_time = to_comp(day, month, year);
        return 0;
}

char change_day(short *date_time)
{
    short day, month, year, MASK;
    MASK = *date_time;
    month = (MASK >> s_year) & mask_m;
    year = MASK & mask_y;
    printf("Введите день:\n");
    if ((scanf("%hu", &day)) != 1)
    {
        printf("Неверный формат даты!\n");
        while (getchar() != '\n');
        return 0;
    }
    if (test(day, month, year) != 0)
    {
        printf("Неверный формат даты!\n");
        return 0;
    }
    *date_time = to_comp(day, month, year);
        return 0;
}

char show_day(unsigned short date_time)
{
        printf("%hu\n", date_time >> (s_month + s_year));
        return 0;
}

char show_month(short date_time)
{
        short mask = mask_m;
        mask &= (date_time >> s_year);
        printf("%hu\n", mask);
        return 0;
}

char show_year(short date_time)
{
        short mask = 127;
        if ((mask & date_time) > 50)
                printf("19%hu\n", mask & date_time);
        else if ((mask & date_time) < 10)
                printf("200%hu\n", mask & date_time);
        else printf ("20%hu\n", mask & date_time);
        return 0;
}

char test(short day, short month, short year)
{
        if ((year < 0) || (year > 99))
                return -1;
        else if ((month < 1) || (month > 12))
                return -1;
        else if (day < 1)
                return -1;
        switch (month)
        {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                        if (day > 31)
                                return -1;
                        break;
                case 4:
                case 6:
                case 9:
                case 11:
                        if (day > 30)
                                return -1;
                        break;
                case 2:
                        if ((year % 4 == 0) && (day > 29))
                                return -1;
                        else if ((year % 4 != 0) && (day > 28))
                                return -1;
                        break;
        }
        return 0;
}

