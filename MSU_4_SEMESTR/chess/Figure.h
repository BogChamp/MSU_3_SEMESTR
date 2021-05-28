#include <iostream>

#ifndef H_FIGURE
#define H_FIGURE

class Figure
{
    protected:
    int pos;
    char name, letter, color;
    bool is_eaten;
    public:
        Figure(char other_name = 'K', char other_letter = 'a', int other_pos = 1, char other_color = 'w', bool other_is_eaten = false);
        virtual ~Figure() {}
        virtual void move(char new_letter, int new_pos) = 0;
        virtual bool move_possible(char new_letter, int new_pos) = 0;
        void eat();
        bool is_eat();
        int get_pos();
        char get_letter();
        char get_name();
        char get_color();
};

class K: public Figure
{
    public:
        K(char other_name = 'K', char other_letter = 'a', int other_pos = 1, char other_color = 'w', bool other_is_eaten = false);
        virtual ~K() {}

        virtual void move(char new_letter, int new_pos)
        {
            letter = new_letter;
            pos = new_pos;
        }

        virtual bool move_possible(char new_letter, int new_pos)
        {
            if ((new_letter - letter > 1) || (new_letter - letter < -1) || (new_pos - pos > 1) || (new_pos - pos < -1))
                return false;
            else return true;
        }
};

class Q: public Figure
{
    public:
        Q(char other_name = 'Q', char other_letter = 'a', int other_pos = 1, char other_color = 'w', bool other_is_eaten = false);
        virtual ~Q() {}

        virtual void move(char new_letter, int new_pos)
        {
            letter = new_letter;
            pos = new_pos;
        }

        virtual bool move_possible(char new_letter, int new_pos)
        {
            if ((letter == new_letter) || (pos == new_pos) || ((new_letter - letter) == (new_pos - pos)) || ((new_letter - letter) == (pos - new_pos)))
                return true;
            else return false;
        }
};

class N: public Figure
{
    public:
        N(char other_name = 'N', char other_letter = 'a', int other_pos = 1, char other_color = 'w', bool other_is_eaten = false);
        virtual ~N() {}

        virtual void move(char new_letter, int new_pos)
        {
            letter = new_letter;
            pos = new_pos;
        }

        virtual bool move_possible(char new_letter, int new_pos)
        {
            if(((new_pos - pos)*(new_letter - letter) == 2) || ((new_pos - pos)*(new_letter - letter) == -2))
                return true;
            else return false;
        }
};

class B: public Figure
{
    public:
        B(char other_name = 'B', char other_letter = 'a', int other_pos = 1, char other_color = 'w', bool other_is_eaten = false);
        virtual ~B() {}

        virtual void move(char new_letter, int new_pos)
        {
            letter = new_letter;
            pos = new_pos;
        
        }

        virtual bool move_possible(char new_letter, int new_pos)
        {
            if (((new_letter - letter) == (new_pos - pos)) || ((new_letter - letter) == (pos - new_pos)))
                return true;
            else return false;
        }
};

class R: public Figure
{
    public:
        R(char other_name = 'R', char other_letter = 'a', int other_pos = 1, char other_color = 'w', bool other_is_eaten = false);
        virtual ~R() {}

        virtual void move(char new_letter, int new_pos)
        {
            letter = new_letter;
            pos = new_pos;
        }

        virtual bool move_possible(char new_letter, int new_pos)
        {
            if ((letter == new_letter) || (pos == new_pos))
                return true;
            else return false;
        }
};

#endif 