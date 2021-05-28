#include <iostream>
#include "Figure.h"

Figure::Figure(char other_name ,char other_letter, int other_pos, char other_color, bool other_is_eaten)
    {
        name = other_name;
        letter = other_letter;
        pos = other_pos;
        color = other_color;
        is_eaten = other_is_eaten;
    }

void Figure::eat() 
    {
        is_eaten = true;
    }

bool Figure::is_eat() 
    { 
        return is_eaten;
    }
        
int Figure::get_pos()
    {
        return pos;
    }
    
char Figure::get_letter()
    {
        return letter;
    }

char Figure::get_name()
    {
        return name;
    }

char Figure::get_color()
    {
        return color;
    }

K::K(char other_name,char other_letter, int other_pos, char other_color, bool other_is_eaten):
    Figure(other_name, other_letter, other_pos, other_color, other_is_eaten) {}
        
Q::Q(char other_name,char other_letter, int other_pos, char other_color, bool other_is_eaten):
    Figure(other_name, other_letter, other_pos, other_color, other_is_eaten) {}        

N::N(char other_name,char other_letter, int other_pos, char other_color, bool other_is_eaten):
    Figure(other_name, other_letter, other_pos, other_color, other_is_eaten) {}       

B::B(char other_name,char other_letter, int other_pos, char other_color, bool other_is_eaten):
    Figure(other_name, other_letter, other_pos, other_color, other_is_eaten) {}        
        
R::R(char other_name,char other_letter, int other_pos, char other_color, bool other_is_eaten):
    Figure(other_name, other_letter, other_pos, other_color, other_is_eaten) {}       
        