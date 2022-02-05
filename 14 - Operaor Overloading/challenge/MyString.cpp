#include "MyString.h"
#include <cstring>
#include <iostream>

using namespace std;

//Semplice implementazione di una classe stringa tramite le c string

MyString::MyString() : str{nullptr}
{
    str = new char[1];
    *str = '\0';
}
MyString::MyString(const char *s) : str{nullptr}
{
    if (s == nullptr)
    {
        str = new char[1];
        *str = '\0';
    }
    else
    {
        str = new char[std::strlen(s) + 1];
        std::strcpy(str, s);
    }
}

MyString::MyString(const MyString &source) : str{nullptr}
{
    str = new char[std::strlen(source.str) + 1];
    std::strcpy(str, source.str);
}
MyString::~MyString()
{
    delete[] str;
}

int MyString:: len() const
{
    return std::strlen(str);
}

void MyString::display() const{
    std::cout << str << ":" << len() << std::endl;
}

const char * MyString::get_str() const{
    return str;
}

bool MyString::operator==(const MyString &rhs){
    bool val;
    val= strcmp(str,(rhs.str))==0;
    return val;
}

bool MyString::operator!=(const MyString &rhs){
    return !(*this==rhs);
}

MyString MyString::operator-(){
    char *new_char;
    new_char = new char[strlen(str)+1];
    strcpy(new_char,str);
    for(size_t i=0;i<strlen(new_char);i++){
        new_char[i]=tolower(new_char[i]);
    }
    MyString new_string{new_char};
    delete [] new_char;
    return new_string;
}

bool operator>(const MyString &str1, const MyString &str2){
    bool val;
    val=str1.str>str2.str;
    return val;
}

bool operator<(const MyString &str1, const MyString &str2){
    bool val;
    val=str1.str<str2.str;
    return val;
}

MyString operator+(const MyString &str1, const MyString &str2){
    char *new_str;
    new_str= new char[strlen(str1.str)+strlen(str2.str)+1];
    strcpy(new_str,str1.str);
    strcat(new_str,str2.str);
    MyString new_mystring{new_str};
    delete [] new_str;
    return new_mystring;
}

MyString operator*(const MyString &str1, const int i){
    char *new_str;
    new_str= new char[strlen(str1.str)*i];
    *new_str='\0';
    for(int j{0};j<i;j++){
        new_str=strcat(new_str,str1.str);
    }
    MyString new_mystring{new_str};
    delete [] new_str;
    return new_mystring;
}

MyString &operator+=(MyString &str1, const MyString &str2){
    //E' necessario definire prima operat =
    //Se metodo si poteva usare this
    str1=str1+str2;
    return str1;
}

MyString &operator*=(MyString &str1, const int i){
    //E' necessario definire prima oper =
    //Se metodo si poteva usare this
    str1=str1*i;
    return str1;
}


/* Se vuoi usare== per inizializzare oggetti
MyStrings serve questa.
Serve anche nella definizione degli operatorii
*= e += */

MyString &MyString::operator=(const MyString &rhs){
    //Se lhs e rhs puntano lo stesso indirizzo di memoria ritorna lhs dereferenziato
    if(this!=&rhs){
        // prima serve un delete per cancellare qualsiasi cosa sia salvato in str(altrimenti memory leak). Poi possiamo riallocare dinamicamente per fare una deep copy
		delete [] str;
        str = new char [std::strlen(rhs.str)+1];
        std::strcpy(str,rhs.str);
    }
    return *this;
}

//Esempio per <<:
ostream &operator<<(std::ostream &os, const MyString &obj){
    //Se definita come friend function di MyString posso anche usare obj.str
    os << obj.get_str();
    //E' importante che torna una reference perchè non vogliamo copiare lo stream
    return os;
}