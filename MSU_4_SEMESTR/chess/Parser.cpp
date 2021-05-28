#include <iostream>
#include "Parser.h"
#include "Figure.h"

bool Parser::check_step(int num,char letter, int pos, Figure** figure)
    {
        if((letter < 'a') || (letter > 'h') || (pos < 1) || (pos > 8))
            throw("Ход невозможен. Такой клетки на доске нет.");
        if (figure[num - 1][0].is_eat())
            throw("Ход не возможен. Фигура, которой вы хотите сделать ход, съедена.");
        return figure[num - 1][0].move_possible(letter, pos);
    }