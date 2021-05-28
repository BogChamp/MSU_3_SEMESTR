#include <iostream>
#include <map>
#include "massiv.h"
#include "mString.h"
#include "exception.h"
#include "nums.h"

class executer
{
    map<mString, mString> myMap;
    nums check;
    public:
        void execute(mString* poliz);
};