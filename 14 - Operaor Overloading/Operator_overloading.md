[TOC]

# Operator overloading

 vogliamo estendere l'uiso degli operatori +,=, etc. ai tipi definiti dall'utente.

Gli unici operatori che non possono essere overloaded sono:

| ::   | :?   | .*   | .    | sizeof |
| ---- | ---- | ---- | ---- | ------ |

E' bene assumere alcune regole di buona creanza:



- Precedenza e associatività non devono cambiare
- Non puoi fare overloading sui tipi built-in (int,double,...)
- Non puoi creare nuovi operatori
- [] , ( ),  ->, = devono esseredichiarati come metodi mentre gli altri possono essere dichiarati sia come metodi che come funzioni globali

In genere, dato $ l'operatore su cui fare l'overloading basta creare la funzione del tipo opportuno chiamata 

```cpp
Type &operator$(const Type &rhs);
```



## Assegnamento

Di default l'operatore di assegnamento = fa una shallow copy

Per fare l'overloading

```cpp
//Prototipo nell'header
ClassName &operator=(const ClassName &rhs);

//Implementazione in cpp
ClassName &ClassName::operator=(const ClassName &rhs){
    //Nel caso in cui l'elemento è lo stesso ritorna l'elemento stesso
    if (this==&rhs){
        return *this;
    }
    
    //fai cose
    return //ritorna elemento dello stesso tipo
}
//Ci si può riferire a ciò che è a sinistra dell'= con il puntatore this
```

> Considera la classe
>
> ```cpp
> #include <cstring>
> #include <iostream>
> 
> //Semplice implementazione di una classe stringa tramite le c string
> class MyString{
>     private:
>     	char *str;
>     public:
>     	MyString():
>     		str{nullptr}{
>                 str=new char[1];
>                 *str='\0';
>             }
>     	MyString(const char *s):
>     		str{nullptr}{
>                 if(s==nullptr){
>                     str=new char[1];
>                     *str='\0'
>                 }else{
>                     str = new char[std::strlen(s)+1];
>                     std::strcpy(str,s);
>                 }
>             }
>     	MyString(const MyString &source):
>     		str{nullptr}{
>                 str=new char[std::strlen(source.str)+1];
>                 std::strcpy(str,source.str);
>             }
>     	~MyString(){
>             delete [] str;
>         }
>     	
>     	int len() const{
>             return std::strlen(str);
>         }
>     
>     	void display() const{
>             std::cout << str << ":" << get_length() << std::endl;
>         }
>     	
>     	const char *get_str() const{
>             return str;
>         }
> }
> ```
>

### Deep copy tramite = overloading

```cpp

MyString &Mystring::operator=(const Mystring &rhs){
    //Se lhs e rhs puntano lo stesso indirizzo di memoria ritorna lhs dereferenziato
    if(this!=&rhs){
        // prima serve un delete per cancellare qualsiasi cosa sia salvato in str(altrimenti memory leak). Poi possiamo riallocare dinamicamente per fare una deep copy
		delete [] str;
    	str = new char [std::strlen(rhs.str)+1];
    	std::strcpy(str,rhs.str);
    }
    return *this
}
```



### Move construct tramite = overloading

```cpp
MyString &Mystring::operator=(const Mystring &&rhs){
    if(this!=&rhs){
		delete [] str;
    	str = rhs.str;
    	rhs.str=nullptr;
    }
    return *this
}
```

## Overloading operator come funzioni globali

Essendo al di fuori della classe non possiamo più riferirci al puntatore this, dobbiamo creare delle friend function. 

```cpp
//bisogna dichiarare la funzione operatorOP come friend nella dichiarazione della classe
//OP è l'operatore su cui fare l'overloading
//Per operatori unari un solo argomento
ClassName operatorOP(const ClassName &obj1, const ClassName &obj2);
```

## Overloading  degli operatori di stream << , >>

Possiamo fare l'overloading di questi operatori anche per cin e cout

```cpp
//Esempio per <<:
std::ostream &operator<<(std::ostream &os, const MyString &obj){
    //Se definita come friend function di MyString posso anche usare obj.str
    os << obj.get_str();
    //E' importante che torna una reference perchè non vogliamo copiare lo stream
    return os;
}
```

```cpp
//Esempio per >> 
//Ora obj non è const poichè vogliamo modificarlo. Ci devo mettere dentro quello che leggo dall'input
std::istream &operator>>(std::istream &is, MyString &obj){
	char *buff=new char[1000];
    is >> buff;
    obj = MyString{buff}; //copy o move assignment costruito prima
    delete [buff];
    return is;
}
```

