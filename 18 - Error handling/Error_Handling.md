# Gestione degli errori

- *throw* : raisa un eccezione
- *try{}* codide che potrebbe raisare un eccezione
-  *catch(){}* equivalente di except in python. Possono essercene multipli

Chatch prende come argomento quello che lancia la funzione throw quindi l'argomento di catch e ciò che viene throw-ato deve essere dello stesso tipo (nella catch si usa reference)

```cpp
//es
try{
    if(i==0){
        throw 0;
    }
    if(i==1){
        throw std::string("i is 1");
    }
}
catch(int &ex){
    //cerr è una funzione che stampa sullo stream un messaggio di errore
    cerr << "i is " << ex << endl;
}
catch (std::string &ex){
    cerr << ex << endl;
}
//Con i 3 puntini "..." viene fatto il catch di qualsiasi altro tipo di eccezione
catch(...){
    cerr << "I don't know what is happening but it is a bad thing"
}

```

## Stack unwinding

Se una funzione raisa un' eccezione la funzione termina e viene rimossa dallo stack. Se il catch è al di fuori dello stack della funzione il programma cerca di trovare un handler per l'eccezione scorrento all'indietro le funzioni dnello stack. Le funzioni che non hanno il catch al loro interno vengono progressivamente rimosse dallo stack.

Questo significa che se abbiamo della memoria da deallocare nell'heap il programma potrebbe non eseguire la deallocazione e lasciare dei memory leak. Usando gli smart pointer questo viene risolto in quanto come si dealloca il puntatore viene liberata anche la memoria nell'heap

## Creare eccezioni

Ci sono alcune pratiche che è buona regola seguire:

- Raisa un oggetto non un tipo primitivo
- Raisa un oggetto tramite valore (non puntatore)
- Fai il catch tramite reference

```cpp
class DivideByZeroException{};
double divide2(double div){
    if (div==0){
        throw DivideByZeroException();
    }
    return 2/div;
}
try{
    double division=divide2(0);
}
catch (DivideByZeroException &ex){
    cerr << "Division by zero" <<endl;
}
```

Le eccezioni si possono raisare anche nelle classi MA non farlo nel distruttore

## Gerarchia delle eccezioni

La classe base dal quale tutti ereditano è std::exception. Per averci accesso bisogna includere \<exception>

Questa fornisce una funzione virtuale *what* che ritorna una cstring con la descrizione di cosa è successo

```cpp
virtual const char *what() const noexcept;
```

Noi possiamo creare classi derivate da exception e implementare la nostra *what* function

![image-20220209172917690](/home/pviscone/Desktop/cpp_training/18 - Error handling/Error_Handling.assets/image-20220209172917690.png)

Le classi in arancione sono state aggiunte in C++17

```cpp
class NewException : public std::exception{
    public:
    NewException() noexcept = default;
    ~NewException() = default;
    virtual const char* what() const noexcept{
        return "This is a new exception"
    }
};
```

 La keyword **noexcept** serve a dire al compilatore che quella funzione NON raiserà nessuna eccezione. (Distruttore è noexcept di default)

