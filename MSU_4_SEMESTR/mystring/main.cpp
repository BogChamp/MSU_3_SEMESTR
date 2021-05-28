#include <iostream>
#include "class_mString.h"

using namespace std;

int main()
{
    mString a;
    a = "Xello";
    if (a < "Hello")
        cout << "Less" << endl;
    else cout << "Not less" << endl;

    if (a > "Hello")
        cout << "greater" << endl;
    else cout << "Not gr" << endl;

    if (a >= "Hello")
        cout << " not Less" << endl;
    else cout << "less" << endl;

    if (a <= "Hello")
        cout << "not gr" << endl;
    else cout << "gr" << endl;

    if (a == "Hello")
        cout << "Equal" << endl;
}

int main12()
{
    mString a;
    cin >> a;
    cout << a << endl;
    for(int i = 0; i < a.length(); i++)
    {
        cout << a[i] << endl;
    }

}

int main1()
{
    mString a("Hello"), b;
    b = a;
    b = 2*b*3 + "World";
    cout << b << endl;
}

int main0()
{
    mString A(3);
    A.add_end("hello everybody");
    A.print();
    A.replace("llo","yayayayya");
    A.print();
    A.replace("every", "no");
    A.print();
    A.remove(5);
    A.print();
    A.remove(4,7);
    A.print();
    cout << A.find("JOKER") << endl;;
    cout << A.find("nob") << endl;
    A.print();
    A.replace("JOJO", "JAJA");
    A.replace("yayya", "OZOZ");
    A.print();
    return 0;   
}