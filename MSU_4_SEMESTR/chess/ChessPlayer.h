#include <iostream>
#include "ChessReader.h"
#include "Parser.h"

class ChessPlayer
{
    Parser a;
    ChessReader b;
    Figure** pointer;
    public:
        void read_config(char* mas);

        bool check_step(int number, char letter, int pos);

        char get_name(int num);    

        void move(int num, char new_letter, int new_pos);

        void show_chess();
};