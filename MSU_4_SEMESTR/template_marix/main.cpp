#include <iostream>
#include "Matrix.h"

using namespace std;

int main(int argc, char** argv)
{
    try
    {
        Matrix<string> a(argv[1]);
        string h = "sds"; 
        a = a+a;
        a = a * h;
        a.print();
    }
    catch(excep& file)
    {
        file.print();
        return 0;
    }
    catch(...)
    {
        cout << "Произошлая какая-то ошибка." << endl;
        return 0;
    }
    return 0;
}