#include <iostream>
#include "mString.h"

#ifndef H_exception
#define H_exception

class exep
{
    mString msg;
    public:
        exep(mString mas) {msg = mas;}
        exep(const char* mas): msg(mas){}
        void print()
        {
            msg.print();
        }
};

#endif
