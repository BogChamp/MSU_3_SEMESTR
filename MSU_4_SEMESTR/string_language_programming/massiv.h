#include <iostream>
#include "mString.h"

#ifndef H_massiv
#define H_massiv

class massiv
{
    mString* mas;
    int last;
    public:
        massiv(int last = 0);
        massiv(const massiv& other);
        ~massiv();
        void push(const mString& element);
        mString pop();
        mString top();
        bool empty();
};

#endif