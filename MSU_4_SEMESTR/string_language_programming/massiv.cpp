#include <iostream>
#include "massiv.h"
#include "exception.h"

using namespace std;

massiv::massiv(int last)
{
    this->last=last;
    if(this->last)
    {
        this->mas = new mString[this->last];
        for(int i = 0; i < (this->last); i++)
            this->mas[i] = "";
    }
    else
        this->mas=NULL;
}

massiv::massiv(const massiv& other)
{
    last = other.last;
    if(last)
    {
        mas = new mString[last];
        for(int i = 0; i < last; i++)
            mas[i] = other.mas[i];
    }
    else mas = NULL;
}

massiv::~massiv()
{
    if(last)
        delete[] mas;
}

void massiv::push(const mString& element)
{
    mString* tmp = mas;
    mas = new mString[last + 1];
    for(int i = 0; i < last; i++)
        mas[i] = tmp[i];
    delete[] tmp;
    mas[last] = element;
    last++;
}

mString massiv::pop()
{
    if (!last)
        throw exep("No elements in massiv!");
    mString* tmp = mas;
    mas = new mString[last - 1];
    for(int i = 0; i < (last - 1); i++)
        mas[i] = tmp[i];
    mString man(tmp[last-1]);
    delete[] tmp;
    last--;
    return man;
}

mString massiv::top()
{
    return mas[last - 1];
}

bool massiv::empty()
{
    if (last)
        return false;
    else return true;
}