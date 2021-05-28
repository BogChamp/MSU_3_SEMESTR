#include <iostream>
#include "mString.h"
#include "exception.h"

using namespace std;

        mString::mString(int arg)
        {
            if (arg < 0)
                throw exep("Не бывает строки с отрицательной длиной!!!");
            len = arg;
            if (len != 0)
            {
                str = new char[len + 1];
                if (str == NULL)
                    throw exep("new вернул нулевой указатель. Похоже кончилось место!");
                for (int i = 0; i < len; i++)
                    str[i] = 'A';
                str[len] = '\0';
            }
            else str = NULL;
        }

        mString::~mString()
        {
            if (len != 0)
                delete[] str;
        }   

        mString::mString(const mString& another)
        {
            len = another.len;
            if (len != 0)
            {
                str = new char[len + 1];
                if (str == NULL)
                    throw exep("new вернул нулевой указатель. Похоже кончилось место!");
                for(int i = 0; i < len + 1; i++)
                    str[i] = another.str[i];
            }
            else str = NULL;   
        }

        mString::mString(const char* mas)
        {
            int i = 0;
            while (mas[i] != '\0')
                i++;
            len = i;
            if (len != 0)
            {
                str = new char[len + 1];
                if (str == NULL)
                    throw exep("new вернул нулевой указатель. Похоже кончилось место!");
                for (i = 0; i < len + 1; i++)
                    str[i] = mas[i];
            }
            else str = NULL;
        }

        int mString::length() const
        {
            return len;
        }

        bool mString::is_empty() const
        {
            if (len == 0)
                return true;
            else return false;
        }

        void mString::add_end(char c)
        {
            if (len == 0)
            {
                str = new char[2];
                if (str == NULL)
                    throw exep("new вернул нулевой указатель. Похоже кончилось место!");
                str[0] = c;
                str[1] = '\0';
                len = 1;
            }
            else
            {
                char* tmp = str;
                len++;
                str = new char[len + 1];
                if (str == NULL)
                    throw exep("new вернул нулевой указатель. Похоже кончилось место!");
                for(int i = 0; i < len - 1; i++)
                    str[i] = tmp[i];
                delete[] tmp;
                str[len - 1] = c;
                str[len] = '\0';
            }
        }

        void mString::add_end(const char* mas)
        {
            int i = 0;
            while(mas[i] != '\0')
                i++;
            if (len == 0)
            {
                len = i;
                if(i != 0)
                {
                    str = new char[len + 1];
                    if (str == NULL)
                        throw exep("new вернул нулевой указатель. Похоже кончилось место!");
                    for(i = 0; i < len; i++)
                        str[i] = mas[i];
                    str[len] = '\0';
                }
            }
            else
            {
                if(i != 0)
                {
                    char* tmp = str;
                    str = new char[len + i + 1];
                    if (str == NULL)
                        throw exep("new вернул нулевой указатель. Похоже кончилось место!");
                    for(int j = 0; j < len; j++)
                        str[j] = tmp[j];
                    delete[] tmp;
                    for(int j = len; j < len + i; j++)
                        str[j] = mas[j - len];
                    str[len + i] = '\0';
                    len += i;
                }
            }
        }

        int mString::add(char c, int num)
        {
            if(len == 0)
            {
                if (num != 1)
                    throw exep("You adding letter to unexisting place!");
                len++;
                str = new char[len + 1];
                str[len - 1] = c;
                str[len] = '\0';
                return 0;
            }

            if((num > len) || (num < 1))         
                throw exep("Буквы с таким номером к сожалению нет(((");


            char* tmp = str;
            len++;
            str = new char[len + 1];
            if (str == NULL)
                throw exep("new вернул нулевой указатель. Похоже кончилось место!");
            for(int i = 0; i < num - 1; i++)
                str[i] = tmp[i];
            str[num - 1] = c;
            for(int i = num; i < len; i++)
                str[i] = tmp[i-1];
            delete[] tmp;
            str[len] = '\0';
            return 0; 
        }

        int mString::add(const char* mas, int num)
        {
            if(len == 0)
                throw exep("Не пытайтесь вставить что-либо в пустую строку!");

            if((num > len) || (num < 1))
                throw exep("Буквы с таким номером к сожалению нет(((");

            int i = 0;
            while(mas[i] != '\0')
                i++;
            
            char* tmp = str;
            str = new char[len + i + 1];
            if (str == NULL)
                throw exep("new вернул нулевой указатель. Похоже кончилось место!");
            for(int j = 0; j < num - 1; j++)
                str[j] = tmp[j];
            
            for(int j = 0; j < i; j++)
                str[num - 1 + j] = mas[j];
            
            for(int j = num - 1 + i; j < len + i; j++)
                str[j] = tmp[j - i];
            delete[] tmp;
            len += i;
            str[len] = '\0';
            return 0;
        }

        int mString::remove(int num)
        {
            if(len == 0)
                throw exep("Вы пытаетесь удалить букву из нулевой строки. Зачем?");

            if((num > len) || (num < 1))
                throw exep("К сожаленью, номер буквы, которую вы хотите удалить, неверный.");

            if(len == 1)
            {
                len--;
                delete[] str;
                str = NULL;
            }
            else
            {
                char* tmp = str;
                int i = 0, j = 0;
                str = new char[len];
                if (str == NULL)
                    throw exep("new вернул нулевой указатель. Похоже кончилось место");
                while(tmp[i] != '\0')
                {
                    if (i == (num - 1))
                        i++;
                    str[j] = tmp[i];
                    i++;
                    j++;
                }
                delete[] tmp;
                len--;
                str[j] = '\0';
            }
            return 0;
        }

        int mString::remove(int start, int end)
        {
            if(len == 0)
                throw exep("Вы пытаетесь удалить подстроку из нулевой строки. Зачем?");

            if((start > len) || (end < 1))
                throw exep("Извините, но подстроки с такими границами просто не может быть!");

            if(start > end)
                throw exep("Начало не может быть больше конца.");

            if(start < 1) throw exep("Начало удаляемой подстроки слишком маленькое.");            
            if(end > len) throw exep("Конец удаляемой подстроки слишком большой.");
            if ((start == 1) && (end == len))
            {
                len = 0;
                delete[] str;
                str = NULL;
                return 0;
            }

            char* tmp = str;
            str = new char[len + start - end];
            if (str == NULL)
                throw exep("new вернул нулевой указатель. Похоже кончилось место");
            int i = 0, j = 0;
            while(tmp[i] != '\0')
            {
                if ((i < (start - 1)) || (i > (end - 1)))
                {
                    str[j] = tmp[i];
                    j++;
                    i++;
                }
                else i++;
            }
            str[j] = '\0';
            len = len + start - end - 1;
            delete[] tmp;
            return 0;
        }

        int mString::find(const char* mas)
        {
            if(len == 0)
                throw exep("В нулевой строке вы ничего не найдете.");

            if((mas == NULL) || (*mas == '\0'))
                return 0;

            int i = 0, j = 0, start = 0;
           
            for(; i < len;i++)
            {
                if(mas[j] == str[i])
                    j++;
                else 
                {
                    j = 0;
                    if(mas[j] == str[i])
                        j++;
                    start = i;
                }
                if(mas[j] == '\0')
                    return (start + 1);
            }
            cout << "no such string" << endl;
            return -1;
        }

        int mString::find(const char letter)
        {
            if(len == 0)
                throw exep("В нулевой строке вы ничего не найдете.");

            for(int i = 0; i < len; i++)
            {
                if (str[i] == letter)
                    return (i+1);
            }
            return -1;
        }

        int mString::replace(const char* mas1, const char* mas2)
        {
            if(len == 0)
                throw exep("В нулевой строке и заменять нечего.");

            if(mas1 == NULL)
                throw exep("Нужно заменять подстроку, а не нулевой указатель.");

            if(mas2 == NULL)
                throw exep("Заменить подстроку на нулевой указатель как-то не получается.");

            int i = 0, j = 0, start = 0;
           
            for(; i < len;i++)
            {
                if(mas1[j] == str[i])
                    j++;
                else 
                {
                    j = 0;
                    start = i + 1;
                }
                if(mas1[j] == '\0')
                    break;
            }

            if(mas1[j] != '\0')
            {
                cout << "no such string" << endl;
                return -1;
            }
            
            i = 0;
            while(mas2[i] != '\0')
                i++;

            char* tmp = str;
            str = new char[len + i - j + 1];
            if (str == NULL)
                throw exep("new вернул нулевой указатель. Похоже кончилось место");
            for(int k = 0;k < start; k++)
                str[k] = tmp[k];
            for (int k = start; k < start + i; k++)
                str[k] = mas2[k - start];
            for(int k = start + j;k < len; k++)
                str[k + i - j] = tmp[k];
            str[len + i - j] = '\0';
            delete[] tmp;
            len = len + i - j;
            return 0;
        }

        void mString::print()
        {
            if (len == 0)
                cout << "empty string" << endl;
            else
            {
                for(int i = 0; i < len; i++)
                    cout << str[i];
            }
        }
