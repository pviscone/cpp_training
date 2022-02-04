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

### Assegnamento

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

> Esempio:
>
> Considera la classe
>
> ```cpp
> class MyString{}
> ```
>
> 
>
> 
>
> 
>
> 

