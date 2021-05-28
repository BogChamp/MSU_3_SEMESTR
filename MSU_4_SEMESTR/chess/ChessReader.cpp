#include <iostream>
#include <fstream>
#include "ChessReader.h"

using namespace std;

Figure** ChessReader::check_conf(char* mas)
        {
            ifstream file(mas);
            if (!file.is_open())
                throw("Невозможно открыть конфигурационный файл!");

            int lines = 0, symbol = 0;
            char c;
            char* info = new char[4];
            Figure** figures;
  
            while(file.get(c))
            {
                if(lines == 0)
                    lines = 1;

                if(c == ' ')
                    continue;

                if(c == '\n')
                {
                    if ((symbol != 4) || (lines > 2))
                        throw("Неверный формат конфигурационного файла!");

                    if((info[0] != 'K') && (info[0] != 'Q') && (info[0] != 'N') && (info[0] != 'B') && (info[0] != 'R'))
                        throw("В конфигурационном файле указана неверная фигура!");
                    
                    if((info[1] < 'a') || (info[1] > 'h'))
                        throw("В конфигурационном файле указана неверная позиция!");

                    if((info[2] < '1') || (info[2] > '8'))
                        throw("В конфигурационном файле указана неверная позиция!");
                    
                    if((info[3] != 'w') && (info[3] != 'b'))
                        throw("В конфигурационном файле указан неверный цвет фигуры!");

                    if(lines == 1)
                        figures = new Figure*[2];

                    switch (info[0])
                        {
                            case 'K':
                                figures[lines - 1] = new K[1];
                                figures[lines - 1][0] = K(info[0], info[1], info[2] - '0', info[3], false);
                                break;
                            case 'Q':
                                figures[lines - 1] = new Q[1];
                                figures[lines - 1][0] = Q(info[0], info[1], info[2] - '0', info[3], false);
                                break;
                            case 'N':
                                figures[lines - 1] = new N[1];
                                figures[lines - 1][0] = N(info[0], info[1], info[2] - '0', info[3], false);
                                break;
                            case 'B':
                                figures[lines - 1] = new B[1];
                                figures[lines - 1][0] = B(info[0], info[1], info[2] - '0', info[3], false);
                                break;
                            case 'R':
                                figures[lines - 1] = new R[1];
                                figures[lines - 1][0] = R(info[0], info[1], info[2] - '0', info[3], false);
                                break;
                            default:
                                throw("Случилось что-то странное.");
                                break;
                        }
                    lines++;
                    symbol = 0;
                    continue;
                }
        
                if(symbol == 4)
                    throw("Неверный формат конфигурационного файла!");
                info[symbol] = c;
                symbol++;
            }
            if ((symbol != 4) || (lines > 2))
                        throw("Неверный формат конфигурационного файла!");

                    if((info[0] != 'K') && (info[0] != 'Q') && (info[0] != 'N') && (info[0] != 'B') && (info[0] != 'R'))
                        throw("В конфигурационном файле указана неверная фигура!");
                    
                    if((info[1] < 'a') || (info[1] > 'h'))
                        throw("В конфигурационном файле указана неверная позиция!");

                    if((info[2] < '1') || (info[2] > '8'))
                        throw("В конфигурационном файле указана неверная позиция!");
                    
                    if((info[3] != 'w') && (info[3] != 'b'))
                        throw("В конфигурационном файле указан неверный цвет фигуры!");

                    if(lines == 1)
                        figures = new Figure*[2];

                    switch (info[0])
                        {
                            case 'K':
                                figures[lines - 1] = new K[1];
                                figures[lines - 1][0] = K(info[0], info[1], info[2] - '0', info[3], false);
                                break;
                            case 'Q':
                                figures[lines - 1] = new Q[1];
                                figures[lines - 1][0] = Q(info[0], info[1], info[2] - '0', info[3], false);
                                break;
                            case 'N':
                                figures[lines - 1] = new N[1];
                                figures[lines - 1][0] = N(info[0], info[1], info[2] - '0', info[3], false);
                                break;
                            case 'B':
                                figures[lines - 1] = new B[1];
                                figures[lines - 1][0] = B(info[0], info[1], info[2] - '0', info[3], false);
                                break;
                            case 'R':
                                figures[lines - 1] = new R[1];
                                figures[lines - 1][0] = R(info[0], info[1], info[2] - '0', info[3], false);
                                break;
                            default:
                                throw("Случилось что-то странное.");
                                break;
                        }

            if((figures[0]->get_letter() == figures[1]->get_letter()) && (figures[0]->get_pos() == figures[1]->get_pos()))
                throw("Две фигуры не могут находиться на одном месте!");

            delete[] info;
            file.close();
            if (lines != 2)
                throw("Неверный формат конфигурационного файла!");
            
            return figures;
        }