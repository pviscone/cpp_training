#include <iostream>
#include "MyString.h"
/*
Prendi la classe MyString
Fai l'overloading degli operatori sia usando
metodi che funzioni esterne

- unario ritorna lowercase
==,!= se stringhe uguali o non
<,> Ordine alfabetico
+,+= concatenzaione
*int,*=int ripeti stringa

Per semplicità faccio una sola volta definendo i primi 2 come metodi
e gli altri come funzioni esterne

- usa la libreria cstring
- per uguaglianza strcmp
- += e *= devono ritornare una MyString & e usa
gli operatori +, * definiti prima


AGGIUNTA MIA
Prova a aggiunngere moto di chiamare mystring in cout
*/

using namespace std;


int main(int argc, const char** argv) {
    MyString str1{"aaaa"};
    MyString str2{"aaac"};
    MyString upper{"AAA"};
    cout << ">:  " << (str2>str1) << "<:   " << (str2<str1) << endl;
    cout << "==:  " << (str1==str1) << "!=:  " << (str2!=str1) << endl;
    MyString lower{-upper};
    cout << "lower:  ";
    (lower.display());

    MyString concatenate{str1+str2};
    cout << "concatenate +:  ";
    concatenate.display();
    cout << "concatenate +=:  ";
    str1+=str2;
    str1.display();
    cout << "repeat 3 times *:  ";
    MyString concatenate2{str2*3};
    concatenate2.display();
    cout << "concatenate 3 times *=  ";
    str2*=3;
    str2.display();
    cout << str1 << endl;
    return 0;
}