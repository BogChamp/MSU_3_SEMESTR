#include <iostream>
#include "mString.h"
#include "exception.h"

using namespace std;

mString mString::operator+(const mString& other) 
{
    if (other.str == NULL)
        return *this;
    mString tmp;
    tmp.len = len + other.len;
    delete[] tmp.str;
    tmp.str = new char[tmp.len + 1];
    if (tmp.str == NULL)
        throw exep("new вернул нулевой указатель. Похоже кончилось место!");
    for(int i = 0; i < len; i++)
        tmp.str[i] = str[i];
    for(int i = len; i < tmp.len; i++)
        tmp.str[i] = other.str[i-len];
    tmp.str[tmp.len] = '\0';
    return tmp;
}

mString mString::operator-(const mString& other)
{
    if (other.str == NULL)
        return *this;

    mString tmp(*this);
    
    for(int i = 0; i < other.len; i++)
    {
        while(!tmp.is_empty())
        {
            if(tmp.find(other[i]) == -1)
            break;
            tmp.remove(tmp.find(other[i]));
        }
    }
    return tmp;
}

mString mString::operator*(const int a)
{
    if (str == NULL)
        return *this;
    mString tmp(*this);
    if (a < 1)
    {
        if (a == 0)
        {
            tmp.len = 0;
            delete[] tmp.str;
            tmp.str = NULL;
        }
        return tmp;
    }
    for(int i = 0; i < (a - 1); i++)
        tmp.add_end(str);
    return tmp;
}

mString operator*(const int a, const mString& other)
{
    mString tmp(other);
    return (tmp.operator*(a));
}

mString & mString::operator=(const mString& other)
{
    if (*this == other)
        return *this;
    if (str != NULL)
        delete[] str;
    len = other.len;
    if (len != 0)
    {
        str = new char[len + 1];
        if (str == NULL)
            throw exep("new вернул нулевой указатель. Похоже кончилось место!");
        for(int i = 0; i < len; i++)
            str[i] = other.str[i];
        str[len] = '\0';
    }
    else str = NULL;
    return *this;
}

bool mString::operator>(const mString& other)
{
    if (str == NULL)
        return false;
    else if (other.str == NULL)
        return true;
    int  i = 0;
    while((str[i] != '\0') && (other.str[i] != '\0'))
    {
        if(str[i] > other.str[i])
            return true;
        else if(str[i] < other.str[i])
            return false;
        i++;
    }

    if((other.str[i] == '\0') && (str[i] != '\0'))
        return true;
    else return false;
}

bool mString::operator<(const mString& other) const
{
    if (other.str == NULL)
        return false;
    else if (str == NULL)
        return true;
    int  i = 0;
    while((str[i] != '\0') && (other.str[i] != '\0'))
    {
        if(str[i] > other.str[i])
            return false;
        else if(str[i] < other.str[i])
            return true;
        i++;
    }

    if((str[i] == '\0') && (other.str[i] != '\0'))
        return true;
    else return false;
}

bool mString::operator>=(const mString& other)
{
    if (other.str == NULL)
        return true;
    else if (str == NULL)
        return false;
    int  i = 0;
    while((str[i] != '\0') && (other.str[i] != '\0'))
    {
        if(str[i] > other.str[i])
            return true;
        else if(str[i] < other.str[i])
            return false;
        i++;
    }

    if (other.str[i] == '\0')
        return true;
    else return false;
}

bool mString::operator<=(const mString& other)
{
    if (str == NULL)
        return true;
    else if (other.str == NULL)
        return false;
    int  i = 0;
    while((str[i] != '\0') && (other.str[i] != '\0'))
    {
        if(str[i] > other.str[i])
            return false;
        else if(str[i] < other.str[i])
            return true;
        i++;
    }

    if (str[i] == '\0') 
        return true;
    else return false;
}

bool mString::operator==(const mString& other) const
{
    if((str == NULL) && (other.str == NULL))
        return true;
    if((str == NULL) || (other.str == NULL))
        return false;
    int  i = 0;
    while((str[i] != '\0') && (other.str[i] != '\0'))
    {
        if(str[i] != other.str[i])
            return false;
        i++;
    }
    if((str[i] == '\0') && (other.str[i] == '\0'))
        return true;
    else return false;
}

char& mString::operator[](const int num) const
{
    if((num < 0) || (num > (len - 1)))
        throw exep("Буквы с таким номером у нас нет!");
    return str[num];
}

ostream& operator<<(ostream& os, const mString& other)
{
    os << other.str;
    return os;
} 

istream& operator>>(istream& is, mString& other)
{
    char c;
    int i = 0;
    is.get(c);
    while ((c != '\n') && (c != char_traits<char>::eof()))
    {
        if (other.len == 0)
        {
            other.len = 1;
            other.str = new char[other.len + 1];
            other.str[other.len] = '\0';
            if (other.str == NULL)
                throw exep("new вернул нулевой указатель. Похоже кончилось место!");
        }
        
        if(i < other.len)
        {
            other.str[i] = c;
            i++;
        }
        else
        {
            other.add_end(c);
            i++;
        } 
        is.get(c);   
    } 
    return is;
}

