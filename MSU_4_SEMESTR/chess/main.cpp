#include <iostream>
#include <limits>
#include <string.h>
#include "ChessPlayer.h"
#include "class_mString.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        cout << "Отсутствует конфигурационный файл!" << endl;
        return -1;
    }
    else if (argc > 2)
    {
        cout << "Слишком много параметров!" << endl;
        return -1;
    }

    ChessPlayer object;
    try {object.read_config(argv[argc - 1]);}
    catch(const char* excep)
    {
        cout << excep << endl;
        return -1;
    }

    while(true)
    {
        try
        {
            object.show_chess();
            mString step;
            
            cin >> step; 

            if (step.length() != 4)
                throw("Вы ввели неверную информацию о ходе.");

            if(step == "exit")
                break;

            if((step[0] != '1') && (step[0] != '2'))
                throw("Вы указали неверный номер фигуры. Введите 1 или 2");

            if(!object.check_step(step[0] - '0', step[2], step[3] - '0'))
                throw("Указанная фигура не может переместиться на данную позицию.");
            else
                object.move(step[0] - '0', step[2], step[3] - '0');            
        }
        catch(const char* excep)
        {
            cout << excep << endl << endl;
        }    
    }    

    return 0;
}