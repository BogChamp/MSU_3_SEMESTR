#include <iostream>

using namespace std;

class excep 
{
    char* array;
    int len;
    public:
        excep(int olen = 0)
        {
            len = olen;
            if (!len)
                array = NULL; 
        }
        ~excep()
        {
            if(len)
                delete[] array;
        }
        excep(const char* other)
        {
            int i = 0;
            while(other[i] != '\0')
                i++;
            len = i;
            array = new char[len + 1];
            for(int i = 0; i < len; i++)
                array[i] = other[i];
            array[len] = '\0';
        }
        void print()
        {
            for(int i = 0; i < len; i++)
                cout << array[i];
            cout << endl;
        }
};