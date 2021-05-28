#include <iostream>
#include <fstream>
#include "exception.h"
#include <string.h>

int* check_file(char* name);
int* check_file_int(char* name);
int* check_file_string(char* name);
int* check_file_bool(char* name);

using namespace std;

template <class T>
class Matrix
{
    T** array;
    int str, col;
    public:
        Matrix();
        Matrix(int other_str, int other_col);
        Matrix(const Matrix<T>& other);
        Matrix(const T other);
        Matrix(char* name);
        ~Matrix();
        Matrix<T> operator+(const Matrix<T>& other);
        Matrix<T> operator-(const Matrix<T>& other);
        Matrix<T> operator*(const T& other);
        template <class A> friend Matrix<A> operator*(const A& num,const Matrix<A>& other);
        Matrix<T> operator*(const Matrix<T>& other);
        Matrix<T> operator=(const Matrix<T>& other);
        void transpose();
        void print();
};

template<class T>
Matrix<T>::Matrix() 
{
    str = 1;
    col = 1;
    array = new T*[str];
    array[str - 1] = new T[col];
    array[str - 1][col - 1] = 0; 
}

template<>
Matrix<char>::Matrix()
{
    str = 1;
    col = 1;
    array = new char*[str];
    array[str - 1] = new char[col];
    array[str - 1][col - 1] = 'a'; 
}

template<>
Matrix<string>::Matrix()
{
    str = 1;
    col = 1;
    array = new string*[str];
    array[str - 1] = new string[col];
    array[str - 1][col - 1] = " "; 
}

template <class T>
Matrix<T>::Matrix(int other_str, int other_col)
{
    if ((other_str < 0) || (other_col < 0) || ((other_str * other_col == 0) && (other_str + other_col != 0)))
        throw excep("Матрицы с таким размером не существует.");

    if ((other_str == 0) && (other_col == 0))
        array = NULL;
    else
    {
        array = new T*[other_str];
        for(int i = 0; i < other_str; i++)
            array[i] = new T[other_col];

        for(int i = 0; i < other_str; i++)
        {
            for(int j = 0; j < other_col; j++)
                array[i][j] = 0;
        } 
    }
    str = other_str;
    col = other_col;
}

template <>
Matrix<char>::Matrix(int other_str, int other_col)
{
    if (((other_str < 0) || (other_col < 0)) || ((other_str * other_col == 0) && (other_str + other_col != 0)))
        throw excep("Матрицы с таким размером не существует.");

    if ((other_str == 0) && (other_col == 0))
        array = NULL;
    else
    {
        array = new char*[other_str];
        for(int i = 0; i < other_str; i++)
            array[i] = new char[other_col];

        for(int i = 0; i < other_str; i++)
        {
            for(int j = 0; j < other_col; j++)
                array[i][j] = '.';
        }
    }
    str = other_str;
    col = other_col;
}

template<>
Matrix<string>::Matrix(int other_str, int other_col)
{
    if (((other_str < 0) || (other_col < 0)) || ((other_str * other_col == 0) && (other_str + other_col != 0)))
        throw excep("Матрицы с таким размером не существует.");

    if ((other_str == 0) && (other_col == 0))
        array = NULL;
    else
    {
        array = new string*[other_str];
        for(int i = 0; i < other_str; i++)
            array[i] = new string[other_col];

        for(int i = 0; i < other_str; i++)
        {
            for(int j = 0; j < other_col; j++)
                array[i][j] = " ";
        }
    }
    str = other_str;
    col = other_col;
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
    str = other.str;
    col = other.col;
    if(str == 0)
        array = NULL;
    else
    {
        array = new T*[str];
        for(int i = 0; i < str; i++)
            array[i] = new T[col];

        for(int i = 0; i < str; i++)
            {
                for(int j = 0; j < col; j++)
                    array[i][j] = other.array[i][j];
            }
    }
}     

template<class T>
Matrix<T>::Matrix(const T other)
{
    str = 1;
    col = 1;
    array = new T*[str];
    array[str - 1] = new T[col];
    array[str - 1][col - 1] = other; 
}

template<class T>
Matrix<T>::~Matrix()
{
    for(int i = 0; i < str; i++)
        delete[] array[i];
    if(array)
        delete[] array;
}

template<>
Matrix<char>::Matrix(char* name)
{
    if(!(check_file(name)))
        throw excep("Неправильный конфигурационный файл для char.");
    ifstream file(name);
    
    int* mas = check_file(name);
    array = new char*[mas[0]];
    for(int i = 0; i < mas[0]; i++)
        array[i] = new char[mas[1]];
    delete[] mas;
    
    char c;
    str=col = 0;
    
    while(file.get(c))
    {
        if(c == ' ')
            continue;
        
        if(c == '\n')
        {
            str++;
            col = 0;
        }
        else 
        {
            array[str][col] = c;
            col++;
        }
    }
    str++;
}

template<>
Matrix<int>::Matrix(char* name)
{
    if(!check_file_int(name))
        throw excep("Неправильный конфигурационный файл для int.");
    ifstream file(name);
    
    int* mas = check_file_int(name);
    array = new int*[mas[0]];
    for(int i = 0; i < mas[0]; i++)
        array[i] = new int[mas[1]];

    for(int i = 0; i < mas[0]; i++)
        for(int j = 0; j < mas[1]; j++)
            array[i][j] = 0;
    delete[] mas;
    
    char c;
    str = col = 0;
    bool new_word = true;
    
    while(file.get(c))
    {
        if(c == ' ')
        {
            new_word = true;
            continue;
        }

        if(c == '\n')
        {
            new_word = true;
            str++;
            col = 0;
        }
        else 
        {
            if(new_word)
            {
                col++;
                new_word = false;
            }
            array[str][col - 1] = 10*array[str][col - 1] + c - '0';
        }
    }
    str++;
}

template<>
Matrix<string>::Matrix(char* name)
{
    if(!check_file_string(name))
        throw excep("Неправильный конфигурационный файл для string.");
    ifstream file(name);
    
    int* mas = check_file_string(name);
    array = new string*[mas[0]];
    for(int i = 0; i < mas[0]; i++)
        array[i] = new string[mas[1]];
    delete[] mas;
    
    char c;
    bool new_word = true;
    str = col = 0;
    
    while(file.get(c))
    {
        if(c == ' ')
        {
            new_word = true;
            continue;
        }

        if(c == '\n')
        {
            new_word = true;
            str++;
            col = 0;
        }
        else 
        {
            if(new_word)
            {
                col++;
                new_word = false;
            }
            array[str][col - 1].push_back(c);
        }
    }
    str++;
}

template<>
Matrix<bool>::Matrix(char* name)
{
    if(!check_file_bool(name))
        throw excep("Неправильный конфигурационный файл для boolean.");
    ifstream file(name);
    
    int* mas = check_file_bool(name);
    array = new bool*[mas[0]];
    for(int i = 0; i < mas[0]; i++)
        array[i] = new bool[mas[1]];
    delete[] mas;
    
    char c;
    bool new_word = true;
    str = col = 0;
    
    while(file.get(c))
    {
        if(c == ' ')
            continue;

        if(c == '\n')
        {
            str++;
            col = 0;
        }
        else 
        {
            col++;
            if(c == 't')
            {
                array[str][col - 1] = true;
                for(int i = 0; i < 3; i++)
                    file.get(c);
            }
            else  
            {
                array[str][col - 1] = false;
                for(int i = 0; i < 4; i++)
                    file.get(c);
            }
        }
    }
    str++;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other)
{
    if((str != other.str) || (col != other.col))
        throw excep("Сложение матриц разного размера.");

    if(str == 0)
        throw excep("Не складывайте нулевые матрицы.");

    Matrix<T> object;
    object = *this;

    for(int i = 0; i < str; i++)
        for(int j = 0; j < col; j++)
            object.array[i][j] += other.array[i][j];

    return object;
}

template<>
Matrix<char> Matrix<char>::operator+(const Matrix<char>& other)
{
    throw excep("Я не знаю как складывать буквы.");
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other)
{
    if((str != other.str) || (col != other.col))
        throw excep("Вычитание матриц разного размера.");

    if(str == 0)
        throw excep("Не вычитайте нулевые матрицы.");

    Matrix<T> object;
    object = *this;
    
    for(int i = 0; i < str; i++)
        for(int j = 0; j < col; j++)
            object.array[i][j] -= other.array[i][j];
        
    return object;
}

template<>
Matrix<char> Matrix<char>::operator-(const Matrix<char>& other)
{
    throw excep("Я не знаю как вычитать буквы.");
}

template<>
Matrix<string> Matrix<string>::operator-(const Matrix<string>& other)
{
    throw excep("Я не знаю как вычитать строки.");
}

template<class T>
Matrix<T> Matrix<T>::operator*(const T& other)
{
    Matrix<T> object(*this);

    if(str != 0)
    {
        for(int i = 0; i < str; i++)
            for(int j = 0; j < col; j++)
                object.array[i][j] *= other;
    }
    return object;
}

template<>
Matrix<char> Matrix<char>::operator*(const char& other)
{
    throw excep("Я не знаю как умножать буквы.");
}

template<>
Matrix<string> Matrix<string>::operator*(const string& other)
{
    throw excep("Я не знаю как умножать строки.");
}

template<class T>
Matrix<T> operator*(const T& num, const Matrix<T>& other)
{
    Matrix<T> object(other);
    object = object * num;
    return object; 
}

template<>
Matrix<char> operator*(const char& num,const Matrix<char>& other)
{
    throw excep("Я не знаю как умножать буквы.");
}

template<>
Matrix<string> operator*(const string& num,const Matrix<string>& other)
{
    throw excep("Я не знаю как умножать строки.");
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
{
    if(col != other.str)
        throw excep("Умножение матриц несоответствующего размера.");

    if(str == 0)
        throw excep("Не перемножайте нулевые матрицы.");

    Matrix<T> object(str, other.col);

    for(int k = 0; k<str; k++)
    {
        for(int j = 0; j < other.col; j++)
        {
            for(int i = 0; i < col; i++)
            {
                object.array[k][j] += array[k][i] * other.array[i][j];
            }
        }
    }
    object.col = other.col;
    return object;
}

template<>
Matrix<char> Matrix<char>::operator*(const Matrix<char>& other)
{
    throw excep("Я не знаю как умножать матрицы с буквами.");
}

template<>
Matrix<string> Matrix<string>::operator*(const Matrix<string>& other)
{
    throw excep("Я не знаю как умножать матрицы со строками.");
}

template<class T>
Matrix<T> Matrix<T>::operator=(const Matrix<T>& other)
{
    for(int i = 0; i < str; i++)
        delete[] array[i];
    delete[] array;
    str = other.str;
    col = other.col;

    if(str == 0)
        array = NULL;
    else
    {
        array = new T*[str];
        for(int i = 0; i < str; i++)
            array[i] = new T[col];

        for(int i = 0; i < str; i++)
            for(int j = 0; j < col; j++)
                array[i][j] = other.array[i][j];
    }    
    return *this;
}

template<class T>
void Matrix<T>::transpose()
{
    if(str != 0) 
    {
        Matrix<T> object(*this);

        for(int i = 0; i < str; i++)
            delete[] array[i];
        delete[] array;

        int tmp = str;
        str = col;
        col = tmp;
        array = new T*[str];
        for(int i = 0; i < str; i++)
            array[i] = new T[col];

        for(int i = 0; i < str; i++)
            for(int j = 0; j < col; j++)
                array[i][j] = object.array[j][i];
    }
}

template<class T>
void Matrix<T>::print()
{
    for(int i = 0; i < str; i++)
    {
        for (int j = 0; j < col; j++)
            cout << array[i][j] << " ";
        cout << endl;
    }
}

int* check_file(char* name) 
{
    ifstream file(name);
    if (!file.is_open())
        return NULL;
    
    char c;
    int str = 0, col_prev = 0, col = 0;
    bool new_word = true;
    
    while(file.get(c))
    {
        if(c == ' ')
        {
            new_word = true;
            continue;
        }

        if(c == '\n')
        {
            if(!col)
                return NULL;
            if(!col_prev)
                col_prev = col;
            else if(col_prev != col)
                return NULL;
            col = 0;
            new_word = true;
            str++;
        }
        else if(new_word)
        {
            col++;
            new_word = false;
        }
        else return NULL;
    }

    if(!col)
        return NULL;
    if(!col_prev)
        col_prev = col;
    else if(col_prev != col)
        return NULL;
    str++;
    int* mas = new int[2];
    mas[0] = str;
    mas[1] = col;
    return mas;
}

int* check_file_int(char* name)
{
    ifstream file(name);
    if (!file.is_open())
        return NULL;
    
    char c;
    int str = 0, col_prev = 0, col = 0;
    bool new_word = true;
    
    while(file.get(c))
    {
        if(c == ' ')
        {
            new_word = true;
            continue;
        }

        if(c == '\n')
        {
            if(!col)
                return NULL;
            if(!col_prev)
                col_prev = col;
            else if(col_prev != col)
                return NULL;
            col = 0;
            new_word = true;
            str++;
        }

        else 
        {
            if(((c - '0') < 0) || ((c - '0') > 9))
                return NULL;
            if(new_word)
            {
                col++;
                new_word = false;
            }
        }
    }

    if(!col)
        return NULL;
    if(!col_prev)
        col_prev = col;
    else if(col_prev != col)
        return NULL;
    str++;
    int* mas = new int[2];
    mas[0] = str;
    mas[1] = col;
    return mas;
}

int* check_file_string(char* name)
{
    ifstream file(name);
    if (!file.is_open())
        return NULL;
    
    char c;
    int str = 0, col_prev = 0, col = 0;
    bool new_word = true;
    
    while(file.get(c))
    {
        if(c == ' ')
        {
            new_word = true;
            continue;
        }

        if(c == '\n')
        {
            if(!col)
                return NULL;
            if(!col_prev)
                col_prev = col;
            else if(col_prev != col)
                return NULL;
            col = 0;
            new_word = true;
            str++;
        }

        else if(new_word)
        {
            col++;
            new_word = false;
        }    
    }

    if(!col)
        return NULL;
    if(!col_prev)
        col_prev = col;
    else if(col_prev != col)
        return NULL;
    str++;
    int* mas = new int[2];
    mas[0] = str;
    mas[1] = col;
    return mas;
}

int* check_file_bool(char* name)
{
    ifstream file(name);
    if (!file.is_open())
        return NULL;
    
    char c;
    int str = 0, col_prev = 0, col = 0, count = 0;
    char* mas1 = new char[6];
    
    while(file.get(c))
    {
        if(c == ' ')
        {
            if((count != 4) && (count != 0) && (count != 5))
            {
                delete[] mas1;
                return NULL;
            }
            mas1[count] = '\0';
            if((count != 0) && (strcmp(mas1, "true")) && (strcmp(mas1, "false")))
            {
                delete[] mas1;
                return NULL;
            }
            count = 0;
            continue;
        }

        if(c == '\n')
        {
            if((count != 4) && (count != 0) && (count != 5))
            {
                delete[] mas1;
                return NULL;
            }
            mas1[count] = '\0';
            if((count != 0) && (strcmp(mas1, "true")) && (strcmp(mas1, "false")))
            {
                delete[] mas1;
                return NULL;
            }
            if(!col)
            {
                delete[] mas1;
                return NULL;
            }
            if(!col_prev)
                col_prev = col;
            else if(col_prev != col)
            {
                delete[] mas1;
                return NULL;
            }
            count = 0;
            col = 0;
            str++;
        }

        else 
        {
            if(count > 4)
            {
                delete[] mas1;
                return NULL;
            }
            if(count == 0)
                col++;
            mas1[count] = c;
            count++;
        }    
    }

    if((count != 4) && (count != 0) && (count != 5))
    {
        delete[] mas1;
        return NULL;
    }
    mas1[count] = '\0';
    if((count != 0) && (strcmp(mas1, "true")) && (strcmp(mas1, "false")))
    {
        delete[] mas1;
        return NULL;
    }
    if(!col)
    {
        delete[] mas1;
        return NULL;
    }
    if(!col_prev)
        col_prev = col;
    else if(col_prev != col)
    {
        delete[] mas1;
        return NULL;
    }
    delete[] mas1;
    str++;
    int* mas = new int[2];
    mas[0] = str;
    mas[1] = col;
    return mas;
}
