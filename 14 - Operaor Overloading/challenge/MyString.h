#include <iostream>
#ifndef _MYSTRING_H_
#define _MYSTRING_H_

using namespace std;

//Semplice implementazione di una classe stringa tramite le c string
class MyString{
    friend bool operator>(const MyString &str1, const MyString &str2);
    friend bool operator<(const MyString &str1, const MyString &str2);
    friend MyString operator+(const MyString &str1, const MyString &str2);
    friend MyString &operator+=(MyString &str1, const MyString &str2);
    friend MyString operator*(const MyString &str1, const int i);
    friend MyString &operator*=(MyString &str1, const int i);
    friend ostream &operator<<(std::ostream &os, const MyString &obj);
    private:
        char *str;

    public:

        MyString();
        MyString(const char *s);
        MyString(const MyString &source);
        ~MyString();

        int len() const;
        void display() const;
        const char *get_str() const;

        bool operator==(const MyString &rhs);
        bool operator!=(const MyString &rhs);
        MyString operator-();
        MyString &operator=(const MyString &rhs);
};

#endif // !_MYSTRING_H_
