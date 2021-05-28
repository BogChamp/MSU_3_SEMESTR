#include <iostream>
#include "executer.h"

void executer::execute(mString* poliz)
{
    massiv stack;
    mString op1, op2, read; 
    int i = 0;
    if (poliz[i + 1].is_empty())
        throw exep("There is no operation!");
    while(!((read = poliz[i]) == ""))
    {
            if (read == "+")
            {
                if (stack.empty())
                    throw exep("I can't use + operator!");
                op2 = stack.pop();
                if (stack.empty())
                    throw exep("I can't use + operator!");
                op1 = stack.pop();

                if ((op1[0] == '"') && (op2[0] == '"'))
                {
                    op1.remove(op1.length());
                    op2.remove(1);
                    read = op1 + op2;
                }
                else if (op1[0] == '"')
                {
                    auto it = myMap.find(op2);
                    if (it == myMap.end())
                        throw exep("I can't add uninitialized object");
                    op2 = myMap[op2];
                    op1.remove(op1.length());
                    read = op1 + op2;
                    read.add_end('"');
                }
                else if (op2[0] == '"')
                {
                    auto it = myMap.find(op1);
                    if (it == myMap.end())
                        throw exep("I can't add uninitialized object");
                    op2.remove(1);
                    read = myMap[op1] + op2;
                    read.add('"', 1);
                }
                else
                {
                    auto it = myMap.find(op1);
                    if (it == myMap.end())
                        throw exep("I can't add uninitialized object");
                    op1 = myMap[op1];
                    it = myMap.find(op2);
                    if (it == myMap.end())
                        throw exep("I can't add uninitialized object");
                    op2 = myMap[op2];
                    read = op1 + op2;
                    read.add('"', 1);
                    read.add_end('"');
                }
                

                stack.push(read);
            }
            else if (read == "-")
            {
                if (stack.empty())
                    throw exep("I can't use - operator!");
                op2 = stack.pop();
                if (stack.empty())
                    throw exep("I can't use - operator!");
                op1 = stack.pop();

                if ((op1[0] == '"') && (op2[0] == '"'))
                {
                    read = op1 - op2;
                    read.add('"', 1);
                    read.add_end('"');
                    stack.push(read);
                }
                else if (op1[0] == '"')
                {
                    auto it = myMap.find(op2);
                    if (it == myMap.end())
                        throw exep("I can't add uninitialized object");
                    op2 = myMap[op2];
                    read = op1 - op2;
                    stack.push(read);
                }
                else if (op2[0] == '"')
                {
                    auto it = myMap.find(op1);
                    if (it == myMap.end())
                        throw exep("I can't add uninitialized object");
                    op1 = myMap[op1];
                    read = op1 - op2;
                    read.add('"', 1);
                    read.add_end('"');
                    stack.push(read);
                }
                else
                {
                    auto it = myMap.find(op1);
                    if (it == myMap.end())
                        throw exep("I can't add uninitialized object");
                    op1 = myMap[op1];
                    it = myMap.find(op2);
                    if (it == myMap.end())
                        throw exep("I can't add uninitialized object");
                    op2 = myMap[op2];
                    read = op1 - op2;
                    read.add('"', 1);
                    read.add_end('"');
                    stack.push(read);
                }
            }
            else if (read == "*")
            {
                if (stack.empty())
                    throw exep("I can't use * operator!");
                op2 = stack.pop();
                if (stack.empty())
                    throw exep("I can't use * operator!");
                op1 = stack.pop();

                if ((check.get_num(op1) != -1) && (check.get_num(op2) != -1))
                {
                    read = check.get_mString(check.get_num(op1) * check.get_num(op2));
                }
                else if (check.get_num(op1) != -1)
                {
                    if (op2[0] == '"')
                    {
                        op2.remove(1);
                        op2.remove(op2.length());
                    }
                    else
                    {
                        auto it = myMap.find(op2);
                        if (it == myMap.end())
                            throw exep("I can't multiply uninitialized object");
                        op2 = myMap[op2];
                    }
                    read = check.get_num(op1) * op2;
                    read.add('"', 1);
                    read.add_end('"');
                }
                else 
                {
                    if (op1[0] == '"')
                    {
                        op1.remove(1);
                        op1.remove(op1.length());
                    }
                    else
                    {
                        auto it = myMap.find(op1);
                        if (it == myMap.end())
                            throw exep("I can't multiply uninitialized object");
                        op1 = myMap[op1];
                    }
                    read = check.get_num(op2) * op1;
                    read.add('"', 1);
                    read.add_end('"');
                }
                stack.push(read);
            }
            else if (read == "=")
            {
                if (stack.empty())
                    throw exep("I can't use = operator!");
                op2 = stack.pop();
                if (stack.empty())
                    throw exep("I can't use = operator!");
                op1 = stack.pop();

                if (op1[0] == '"')
                    throw exep("Can't equate const string!");
                else
                {
                    if (op2[0] == '"')
                    {
                        op2.remove(1);
                        op2.remove(op2.length());
                    }
                    else
                    {
                        auto it = myMap.find(op2);
                        if (it == myMap.end())
                            throw exep("Can't equate uninitialized object!");
                        else 
                            op2 = myMap[op2];
                    }
                    myMap[op1] = op2;
                    stack.push(op1);
                }
                
            }
            else if (read == "print")
            {
                if (stack.empty())
                    throw exep("Can't print nothing!");
                op1 = stack.pop();

                if (op1[0] == '"')
                {
                    op1.remove(1);
                    op1.remove(op1.length());
                }
                else
                {
                    auto it = myMap.find(op1);
                    if (it == myMap.end())
                        throw exep("Can't print uninitialized object!");
                    else 
                    op1 = myMap[op1];
                }
                
                if (op1.is_empty())
                    cout << "> " << endl;
                else
                    cout << "> " << op1 << endl;
            }
            else
                stack.push(read);
        i++;
    }
    
}