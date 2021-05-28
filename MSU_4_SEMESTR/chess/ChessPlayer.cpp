#include <iostream>
#include "ChessPlayer.h"

void ChessPlayer::read_config(char* mas)
    {
        pointer = b.check_conf(mas);
    }

bool ChessPlayer::check_step(int number, char letter, int pos)
    {
        return a.check_step(number, letter, pos, pointer);
    }

char ChessPlayer::get_name(int num)
    {
        return pointer[num-1][0].get_name();
    }      

void ChessPlayer::move(int num, char new_letter, int new_pos)
    {
        int other, old_pos = pointer[num - 1]->get_pos();
        char old_letter = pointer[num - 1]->get_letter();
        if(num == 1)
            other = 2;
        else 
            other = 1;
            
        switch(pointer[num - 1][0].get_name())
        {
            case 'K':
                pointer[num - 1][0].move(new_letter, new_pos);
                if(!pointer[other - 1]->is_eat())
                {
                    if((pointer[0][0].get_pos() == pointer[1][0].get_pos()) && (pointer[0][0].get_letter() == pointer[1][0].get_letter()))
                    {
                        if (pointer[0]->get_color() == pointer[1]->get_color())
                        {
                            pointer[num - 1][0].move(old_letter, old_pos);
                            throw("Ход невозможен. Фигура не может съесть другую фигуру такого же цвета.");
                        }
                        else
                        {
                            std::cout << "Ход возможен" << std::endl;
                            pointer[other - 1]->eat();
                            std::cout << "Фигура " << other << " съедена" << std::endl << std::endl;
                        }
                    }
                    else std::cout << "Ход возможен" << std::endl << std::endl;
                }
                else std::cout << "Ход возможен" << std::endl << std::endl;
                break;

            case 'Q':
                if (pointer[other - 1]->is_eat())
                {
                    std::cout << "Ход возможен" << std::endl << std::endl;
                    pointer[num - 1]->move(new_letter, new_pos);
                }
                else
                {
                if(pointer[num - 1][0].get_letter() == new_letter)
                {
                    int i = 0;
                    if(pointer[num - 1][0].get_pos() > new_pos)
                        i = -1;
                    else i = 1;

                    while(pointer[num - 1][0].get_pos() != new_pos)
                    {
                        pointer[num - 1][0].move(new_letter, pointer[num - 1][0].get_pos() + i);
                        if((pointer[0][0].get_pos() == pointer[1][0].get_pos()) && (pointer[0][0].get_letter() == pointer[1][0].get_letter()))
                        {
                            if (pointer[num - 1]->get_pos() != new_pos)
                            {
                                pointer[num - 1]->move(old_letter, old_pos);
                                throw("Не перепрыгивайте через фигуры!");
                            }

                            if (pointer[0]->get_color() == pointer[1]->get_color())
                            {
                                pointer[num - 1][0].move(old_letter, old_pos);
                                throw("Ход невозможен. Фигура не может съесть другую фигуру такого же цвета.");
                            }
                            else
                            {
                                std::cout << "Ход возможен" << std::endl;
                                pointer[other - 1][0].eat();
                                std::cout << "Фигура " << other << " съедена" << std::endl << std::endl;
                            }
                            break;
                        }
                    }
                }
                else if(pointer[num - 1][0].get_pos() == new_pos)
                {
                    int i = 0;
                    if(pointer[num - 1][0].get_letter() > new_letter)
                        i = -1;
                    else i = 1;

                    while(pointer[num - 1][0].get_letter() != new_letter)
                    {
                        pointer[num - 1][0].move(pointer[num - 1][0].get_letter() + i, new_pos);
                        if((pointer[0][0].get_pos() == pointer[1][0].get_pos()) && (pointer[0][0].get_letter() == pointer[1][0].get_letter()))
                        {
                            if (pointer[num - 1]->get_letter() != new_letter)
                            {
                                pointer[num - 1]->move(old_letter, old_pos);
                                throw("Не перепрыгивайте через фигуры!");
                            }

                            if (pointer[0]->get_color() == pointer[1]->get_color())
                            {
                                pointer[num - 1][0].move(old_letter, old_pos);
                                throw("Ход невозможен. Фигура не может съесть другую фигуру такого же цвета.");
                            }
                            else
                            {
                                std::cout << "Ход возможен" << std::endl;
                                pointer[other - 1][0].eat();
                                std::cout << "Фигура " << other << " съедена" << std::endl << std::endl;
                            }
                            break;
                        }
                    } 
                }
                else
                {
                    int i = 0, j = 0;
                    if(pointer[num - 1][0].get_letter() > new_letter)
                        i = -1;
                    else i = 1;

                    if(pointer[num - 1][0].get_pos() > new_pos)
                        j = -1;
                    else j = 1;

                    while(pointer[num - 1][0].get_letter() != new_letter)
                    {
                        pointer[num - 1][0].move(pointer[num - 1][0].get_letter() + i, pointer[num - 1][0].get_pos() + j);
                        if((pointer[0][0].get_pos() == pointer[1][0].get_pos()) && (pointer[0][0].get_letter() == pointer[1][0].get_letter()))
                        {
                            if (pointer[num - 1]->get_pos() != new_pos)
                            {
                                pointer[num - 1]->move(old_letter, old_pos);
                                throw("Не перепрыгивайте через фигуры!");
                            }

                            if (pointer[0]->get_color() == pointer[1]->get_color())
                            {
                                pointer[num - 1][0].move(old_letter, old_pos);
                                throw("Ход невозможен. Фигура не может съесть другую фигуру такого же цвета.");
                            }
                            else
                            {
                                std::cout << "Ход возможен" << std::endl;
                                pointer[other - 1][0].eat();
                                std::cout << "Фигура " << other << " съедена" << std::endl << std::endl;
                            }
                            break;
                        }
                    } 
                }
                if (!((pointer[0][0].get_pos() == pointer[1][0].get_pos()) && (pointer[0][0].get_letter() == pointer[1][0].get_letter())))
                    std::cout << "Ход возможен" << std::endl << std::endl;
                }   
                break;

            case 'N':
                pointer[num - 1][0].move(new_letter, new_pos);
                if(!pointer[other - 1]->is_eat())
                {
                    if((pointer[0][0].get_pos() == pointer[1][0].get_pos()) && (pointer[0][0].get_letter() == pointer[1][0].get_letter()))
                    {
                        if (pointer[0]->get_color() == pointer[1]->get_color())
                        {
                            pointer[num - 1][0].move(old_letter, old_pos);
                            throw("Ход невозможен. Фигура не может съесть другую фигуру такого же цвета.");
                        }
                        else
                        {
                            std::cout << "Ход возможен" << std::endl;
                            pointer[other - 1][0].eat();
                            std::cout << "Фигура " << other << " съедена" << std::endl << std::endl;
                        }
                    }
                    else std::cout << "Ход возможен" << std::endl << std::endl;
                }
                else
                    std::cout << "Ход возможен" << std::endl << std::endl;
                break;

            case 'B':
                if(pointer[other - 1]->is_eat())
                {
                    std::cout << "Ход возможен" << std::endl << std::endl;
                    pointer[num - 1]->move(new_letter, new_pos);
                }
                else
                {
                    int i = 0, j = 0;
                    if(pointer[num - 1][0].get_letter() > new_letter)
                        i = -1;
                    else i = 1;

                    if(pointer[num - 1][0].get_pos() > new_pos)
                        j = -1;
                    else j = 1;

                    while(pointer[num - 1][0].get_letter() != new_letter)
                    {
                        pointer[num - 1][0].move(pointer[num - 1][0].get_letter() + i, pointer[num - 1][0].get_pos() + j);
                        if((pointer[0][0].get_pos() == pointer[1][0].get_pos()) && (pointer[0][0].get_letter() == pointer[1][0].get_letter()))
                        {
                            if (pointer[num - 1]->get_pos() != new_pos)
                            {
                                pointer[num - 1]->move(old_letter, old_pos);
                                throw("Не перепрыгивайте через фигуры!");
                            }

                            if (pointer[0]->get_color() == pointer[1]->get_color())
                            {
                                pointer[num - 1]->move(old_letter, old_pos);
                                throw("Ход невозможен. Фигура не может съесть другую фигуру такого же цвета.");
                            }
                            else
                            {
                                std::cout << "Ход возможен" << std::endl;
                                pointer[other - 1][0].eat();
                                std::cout << "Фигура " << other << " съедена" << std::endl << std::endl;
                            }
                            break;
                        }
                    }
                    if(!((pointer[0][0].get_pos() == pointer[1][0].get_pos()) && (pointer[0][0].get_letter() == pointer[1][0].get_letter())))
                        std::cout << "Ход возможен" << std::endl << std::endl;
                }
                break;

            case 'R':
                if(pointer[other - 1]->is_eat())
                {
                    std::cout << "Ход возможен" << std::endl << std::endl;
                    pointer[num - 1]->move(new_letter, new_pos);
                }
                else
                {
                if(pointer[num - 1][0].get_letter() == new_letter)
                {
                    int i = 0;
                    if(pointer[num - 1][0].get_pos() > new_pos)
                        i = -1;
                    else i = 1;

                    while(pointer[num - 1][0].get_pos() != new_pos)
                    {
                        pointer[num - 1][0].move(new_letter, pointer[num - 1][0].get_pos() + i);
                        if((pointer[0][0].get_pos() == pointer[1][0].get_pos()) && (pointer[0][0].get_letter() == pointer[1][0].get_letter()))
                        {
                            if (pointer[num - 1]->get_pos() != new_pos)
                            {
                                pointer[num - 1]->move(old_letter, old_pos);
                                throw("Не перепрыгивайте через фигуры!");
                            }

                            if (pointer[0]->get_color() == pointer[1]->get_color())
                            {
                                pointer[num - 1][0].move(old_letter, old_pos);
                                throw("Ход невозможен. Фигура не может съесть другую фигуру такого же цвета.");
                            }
                            else
                            {
                                std::cout << "Ход возможен" << std::endl;
                                pointer[other - 1][0].eat();
                                std::cout << "Фигура " << other << " съедена" << std::endl << std::endl;
                            }
                            break;
                        }
                    }
                }
                else if(pointer[num - 1][0].get_pos() == new_pos)
                {
                    int i = 0;
                    if(pointer[num - 1][0].get_letter() > new_letter)
                        i = -1;
                    else i = 1;

                    while(pointer[num - 1][0].get_letter() != new_letter)
                    {
                        pointer[num - 1][0].move(pointer[num - 1][0].get_letter() + i, new_pos);
                        if((pointer[0][0].get_pos() == pointer[1][0].get_pos()) && (pointer[0][0].get_letter() == pointer[1][0].get_letter()))
                        {
                            if (pointer[num - 1]->get_letter() != new_letter)
                            {
                                pointer[num - 1]->move(old_letter, old_pos);
                                throw("Не перепрыгивайте через фигуры!");
                            }

                            if (pointer[0]->get_color() == pointer[1]->get_color())
                            {
                                pointer[num - 1][0].move(old_letter, old_pos);
                                throw("Ход невозможен. Фигура не может съесть другую фигуру такого же цвета.");
                            }
                            else
                            {
                                std::cout << "Ход возможен" << std::endl;
                                pointer[other - 1][0].eat();
                                std::cout << "Фигура " << other << " съедена" << std::endl << std::endl;
                            }
                            break;
                        }
                    } 
                }
                if(!((pointer[0][0].get_pos() == pointer[1][0].get_pos()) && (pointer[0][0].get_letter() == pointer[1][0].get_letter())))
                        std::cout << "Ход возможен" << std::endl << std::endl;
                }
                break;
            default:
                break;
        }
    }

void ChessPlayer::show_chess()
{
    std::cout << ' ' << ' ' << 'a' << ' ' << 'b' << ' ' << 'c' << ' ' << 'd' << ' ' << 'e' << ' ' << 'f' << ' ' << 'g' << ' ' << 'h' << std::endl;
    for(int i = 0; i < 8; i++)
    {
        std::cout << i+1;
        for(int j = 0; j < 8; j++)
        {
            if((pointer[0][0].get_letter() == ('a' + j)) && (pointer[0][0].get_pos() == (i + 1)) && !pointer[0][0].is_eat())
                std::cout << ' ' << pointer[0][0].get_name();
            else if((pointer[1][0].get_letter() == ('a' + j)) && (pointer[1][0].get_pos() == (i + 1)) && !pointer[1][0].is_eat())
                std::cout << ' ' << pointer[1][0].get_name();
            else std::cout << ' ' << '*';
        }
        std::cout << std::endl;
    }  
    std::cout << std::endl;
}