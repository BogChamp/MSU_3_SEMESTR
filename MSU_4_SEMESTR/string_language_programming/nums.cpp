#include <iostream>
#include "nums.h"

int nums::get_num(const mString& arg)
{
    if (arg.is_empty())
        return -1;
    int j = 0;
    for(int i = 0; i < arg.length(); i++)
    {
        if ((i != 0) && (arg[0] == '0'))
            return -1;
        if ((arg[i] < '0') || (arg[i] > '9'))
            return -1;
        j = 10*j + arg[i] - '0';
    }
    return j;
}

mString nums::get_mString(int arg)
{
    mString obj;
    int ost = 0;
    if (!arg)
        obj.add('0',1);
    else
    {
        while(arg)
        {
            ost = arg % 10;
            arg /= 10;
            obj.add('0' + ost, 1);
        }
    }
    return obj;
}