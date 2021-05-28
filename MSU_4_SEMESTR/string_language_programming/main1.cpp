#include <iostream>
#include "exception.h"
#include "massiv.h"
#include "executer.h"

using namespace std;

mString* divide(const mString& other);
bool right_object(const mString& other);
void add_leksema(mString** massiv, int &size, mString element);
void syntax_analysis(mString* array);
bool expression(mString* array, int num);
bool expression_mul(mString* array, int num);
bool mul(mString* array, int num, int brackets);
bool assignment(mString* array, int num);
bool is_num(const mString& arg);
mString* make_poliz(mString* poliz);

int main()
{
    mString* poliz = NULL, *poliz1 = NULL;
    executer com;
    cout << "Hello! It is a string interpretator." << endl << endl;
    while(true)
    {
        cout << "> ";
        try
        {
            mString command;
            cin >> command;

            if(command.length() == 0)
                continue;

            poliz = divide(command);
            
            if(!poliz)
                break;

            syntax_analysis(poliz);
            poliz1 = make_poliz(poliz);
            com.execute(poliz1);
        }
        catch(exep& arg)
        {
            cout << endl << "> ";
            arg.print();
            cout << endl << endl;
        }
        catch(...)
        {
            cout << endl << "> " << "Programm caught some strange exception" << endl << endl;
        }
        if (poliz)
        {
            delete[] poliz;
            poliz = NULL;
        }
        if (poliz1)
        {
            delete[] poliz1;
            poliz1 = NULL;
        }
    }
    cout << endl << "Good Goodbye..." << endl;
    return 0;
}

mString* divide(const mString& other)
{
    int bracket = 0, sign = 0;
    bool apostrophe = false;
    mString object;
    mString* poliz = new mString[1];
    poliz[0] = ""; 
    int count = 0;

    for(int i = 0; i < other.length(); i++)
    {
        switch(other[i])
        {
            case ' ':
            case '\t':
                if(!apostrophe)
                {
                    if (object.length() != 0)
                    {
                        add_leksema(&poliz, count, object);
                        object.remove(1,object.length());
                    }
                }
                else 
                    object.add_end(other[i]);
                continue;
                break;
            case '(':
                if(!apostrophe)
                {
                    if (object.length() != 0)
                    {    
                        add_leksema(&poliz, count, object);
                        object.remove(1,object.length());
                    }

                    bracket++;
                    sign = 0;

                    add_leksema(&poliz, count, "(");
                }
                else 
                    object.add_end(other[i]);
                break;
            case ')':
                if(!apostrophe)
                {
                    if (object.length() != 0)
                    {
                        add_leksema(&poliz, count, object);
                        object.remove(1,object.length());
                    }

                    bracket--;
                    if (bracket < 0)
                    {
                        if(poliz)
                            delete[] poliz;
                        throw exep("Brackets are not balanced!");
                    }
                    
                    sign = 0;

                    add_leksema(&poliz, count, ")");
                }
                else
                    object.add_end(other[i]);
                break;
            case '+':
            case '-':
            case '*':
            case '=':
                if(!(apostrophe))
                {
                    if (object.length() != 0)
                    {
                        add_leksema(&poliz, count, object);
                        object.remove(1,object.length());
                    }

                    sign++;
                    if(sign > 1)
                    {
                        if(poliz)
                            delete[] poliz;
                        throw exep("A lot of operation signs together!");   
                    }

                    switch(other[i])
                    {
                        case '+':
                            add_leksema(&poliz, count, "+");
                            break;
                        case '-':
                            add_leksema(&poliz, count, "-");
                            break;
                        case '*':
                            add_leksema(&poliz, count, "*");
                            break;
                        case '=':
                            add_leksema(&poliz, count, "=");
                            break;
                    }
                }
                else 
                    object.add_end(other[i]);
                break;
            case '"':
                if (!apostrophe)
                {
                    if (object.length() != 0)
                    {
                        add_leksema(&poliz, count, object);
                        object.remove(1,object.length());
                    }
                }             
                object.add_end(other[i]);

                if (apostrophe)
                {
                    add_leksema(&poliz, count, object);
                    object.remove(1,object.length());
                }

                apostrophe = !apostrophe;
                sign = 0;
                break;
            default:
                object.add_end(other[i]);
                sign = 0;
                break;
        }
    }
    if (object.length() != 0)
    {
        add_leksema(&poliz, count, object); 
        object.remove(1,object.length());
    }
    if (apostrophe)
    {
        if(poliz)
            delete[] poliz;
        throw exep("Quotation marks are not balanced!");
    }
    if(bracket != 0)
    {
        if(poliz)
            delete[] poliz;
        throw exep("Brackets are not balanced!");  
    }

    if(count == 1)
    {
        if (poliz[count - 1] == "exit")
        {
            delete[] poliz;
            return NULL;
        }
    }
    return poliz;
}

bool right_object(const mString& other)
{
    if (other == "print")
        return false;
    if (other[0] == '"')
        return true;
    for(int i = 0; i < other.length(); i++)
    {
        if ((i == 0) && !(((other[i] >= 'a') && (other[i] <= 'z')) || ((other[i] >= 'A') && (other[i] <= 'Z'))))
            return false;
        if ((other[i] == ';') || (other[i] == ':') || (other[i] == '+') ||
            (other[i] == '-') || (other[i] == '*') || (other[i] == '=') ||
            (other[i] == '"') || (other[i] == '.') || (other[i] == ',') || 
            (other[i] == '{') || (other[i] == '}') || (other[i] == '(') || 
            (other[i] == ')') || (other[i] == '<') || (other[i] == '>'))
                return false;
    }
    return true;
}

void add_leksema(mString** massiv, int &size, mString element)
{
    mString* tmp = (*massiv);
    (*massiv) = new mString[size + 2];
    for(int i = 0; i < size; i++)
        (*massiv)[i] = tmp[i];
    if (tmp)
        delete[] tmp;
    (*massiv)[size] = element;
    (*massiv)[size + 1] = "";
    size++;
}

void syntax_analysis(mString* poliz)
{
    int  i = 0;
    if(!poliz[i].is_empty())
    {
        if (poliz[i] == "print")
        {
            i++;
            if ((!expression(poliz, i)) && (!assignment(poliz, i)))
                throw exep("Can't print wrong expression!");
        }
        else if ((!expression(poliz, i)) && (!assignment(poliz, i)))
            throw exep("It is wrong expression!");
    }
    else
        throw exep("Can't make empty command");
}

bool expression(mString* poliz, int num)
{
    if (poliz[num].is_empty())
        return false;

    if (poliz[num] == "(")
    {
        num++;
        if (!expression(poliz, num))
            return false;
    }
    else if (is_num(poliz[num]))
    {
        num++;

        if (poliz[num].is_empty())
            return true;

        if (poliz[num] == ")")
        {
            while (poliz[num] == ")")
                num++;
            if (poliz[num].is_empty())
                return true;
        
            if (!((poliz[num] == "+") || (poliz[num] == "-") || (poliz[num] == "*")))
                return false;

            if(!expression(poliz, num))
                return false;
        }
        else if (poliz[num] == "*")
        {
            num++;
            if(!expression_mul(poliz, num))
                return false;
        }
        else 
            return false;
    }
    else if ((poliz[num] == ")") || (poliz[num] == "+") || (poliz[num] == "-") || (poliz[num] == "*") || (poliz[num] == "="))
        return false;
    else
    {
        if (!right_object(poliz[num]))
            throw exep("Wrong object's name!");
        num++;
        while(poliz[num] == ")")
            num++;

        if (poliz[num].is_empty())
            return true;
        
        if (!((poliz[num] == "+") || (poliz[num] == "-") || (poliz[num] == "*")))
            return false;

        if (poliz[num] == "*")
        {
            num++;
            if (!mul(poliz, num, 0))
                return false; 
            else 
                return true;
        }

        num++;

        if(!expression(poliz, num))
            return false;
    }
    return true;
}

bool expression_mul(mString* poliz, int num)
{
    if (poliz[num].is_empty())
        return false;

    if (poliz[num] == "(")
    {
        num++;
        if (!expression_mul(poliz, num))
            return false;
    }
    else if (is_num(poliz[num]))
    {
        num++;
        if (poliz[num] == "*")
        {
            num++;
            if (!expression_mul(poliz, num))
                return false;
        }
        else 
            return false;
    }
    else if (right_object(poliz[num]))
    {
        num++;
        while (poliz[num] == ")")
            num++;
        
        if (poliz[num].is_empty())
            return true;
        
        if ((poliz[num] == "+") || (poliz[num] == "-"))
        {
            num++;
            if (!expression(poliz, num))
                return false;
        }
        else if (poliz[num] == "*")
        {
            num ++;
            if (!mul(poliz, num, 0))
                return false;
        }
        else
            return false;
    }
    else if ((poliz[num] == "*") || (poliz[num] == "+") || (poliz[num] == "-") || (poliz[num] == ")") || (poliz[num] == "="))
        return false;
    else 
        throw exep("Wrong object's name!");

    return true;
}

bool mul(mString* poliz, int num, int brackets)
{
    if (poliz[num].is_empty())
        return false;

    if (poliz[num] == "(")
    {
        brackets++;
        num++;
        if (!mul(poliz, num, brackets))
            return false;
    }
    else if (is_num(poliz[num]))
    {
        num++;

        while (poliz[num] == ")")
        {
            if(brackets)
                brackets--;
            num++;
        }

        if (poliz[num].is_empty())
            return true;

        if (!brackets)
        {
            if ((poliz[num] == "+") || (poliz[num] == "-"))
            {
                num++;
                if (!expression(poliz, num))
                    return false;
            }
            else if (poliz[num] == "*")
            {
                num++;
                if(!mul(poliz, num, brackets))
                    return false;
            }
            else
                return false;
            
        }
        else
        {
            if (poliz[num] == "*")
            {
                num++;
                if(!mul(poliz, num, brackets))
                    return false;
            }
            else 
                return false;
        }
        
    }
    else 
        return false;

    return true;
}

bool assignment(mString* poliz, int num)
{
    if (poliz[num].is_empty())
        return false;
    if (poliz[num][0] == '"')
        return false;
    if (!right_object(poliz[num]))
        return false;
    num++;
    if (poliz[num].is_empty())
        return false;
    if (!(poliz[num] == "="))
        return false;
    num ++;
    if (!expression(poliz, num))
        return false;
    return true;
}

bool is_num(const mString& arg)
{
    if (arg.is_empty())
        return false;
    for(int i = 0; i < arg.length(); i++)
    {
        if ((i != 0) && (arg[0] == '0'))
            return false;
        if ((arg[i] < '0') || (arg[i] > '9'))
            return false;
    }
    return true;
}

mString* make_poliz(mString* poliz)
{
    massiv stack;
    mString* obj = new mString[1];
    obj[0] = "";
    int i = 0, count = 0;
    bool eq = true;
    while (!poliz[i].is_empty())
    {
        if (poliz[i] == "(")
            stack.push(poliz[i]);
        else if (poliz[i] == ")")
        {
            while(!(stack.top() == "("))
                add_leksema(&obj, count, stack.pop());
            stack.pop();
        }
        else if (poliz[i] == "+")
        {
            if (stack.empty())
                stack.push(poliz[i]);
            else if ((stack.top() == "(") || (stack.top() == "=") || (stack.top() == "print"))
                stack.push(poliz[i]);
            else 
            {
                while(!(stack.empty()))
                {
                    add_leksema(&obj, count, stack.pop());
                    if (!(stack.empty()))
                    {
                        if ((stack.top() == "(") || (stack.top() == "=") || (stack.top() == "print"))
                            break;
                    }
                }
                stack.push(poliz[i]);
            }
        }
        else if (poliz[i] == "-")
        {
            if (stack.empty())
                stack.push(poliz[i]);
            else if ((stack.top() == "(") || (stack.top() == "=") || (stack.top() == "print"))
                stack.push(poliz[i]);
            else 
            {
                while(!(stack.empty()))
                {
                    add_leksema(&obj, count, stack.pop());
                    if (!(stack.empty()))
                    {
                        if ((stack.top() == "(") || (stack.top() == "=") || (stack.top() == "print"))
                            break;
                    }
                }
                stack.push(poliz[i]);
            }
        }
        else if (poliz[i] == "*")
            stack.push(poliz[i]);
        else if (poliz[i] == "=")
        {
            eq = false;
            if (stack.empty())
                stack.push(poliz[i]);
            else if ((stack.top() == "(") || (stack.top() == "print"))
                stack.push(poliz[i]);
            else
            {
                while(!(stack.empty()))
                {
                    add_leksema(&obj, count, stack.pop());
                    if (!(stack.empty()))
                    {
                        if ((stack.top() == "(") || (stack.top() == "print"))
                            break;
                    }
                }
                stack.push(poliz[i]);
            }
        }
        else if (poliz[i] == "print")
        {
            stack.push(poliz[i]);
            eq = false;
        }
        else
            add_leksema(&obj, count, poliz[i]);
        i++;
    }
    while (!(stack.empty()))
        add_leksema(&obj, count, stack.pop());

    if (eq)
        add_leksema(&obj, count, "print");

    i = 0;
 
    return obj;
}