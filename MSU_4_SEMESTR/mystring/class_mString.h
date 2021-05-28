#include <iostream>

using namespace std;

class mString
{
    char* str;
    int len;
    public:
        mString(int arg = 0);

        ~mString(); 

        mString(const mString& another);

        mString(const char* mas);

        int length();

        bool is_empty();

        void add_end(char c);

        void add_end(const char* mas);

        int add(char c, int num);

        int add(const char* mas, int num);

        int remove(int num);   

        int remove(int start, int end);

        int find(const char* mas);

        int replace(const char* mas1,const char* mas2);

        void print();

        mString operator+(const mString& other);

        mString operator*(const int a);

        friend mString operator*(const int a, const mString& other);

        mString& operator=(const mString& other);

        bool operator>(const mString& other);

        bool operator<(const mString& other);

        bool operator>=(const mString& other);

        bool operator<=(const mString& other);

        bool operator==(const mString& other);

        char& operator[](const int num);

        friend ostream& operator<<(ostream& os, const mString& other);
        
        friend istream& operator>>(istream& is, mString& other);

};