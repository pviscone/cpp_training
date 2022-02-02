# OOP

```cpp
class Class_name{
    //attributi
    int i=0;
    //metodi
    int func(int j){
        return j;
    };
};

Class_name istance;
Class_name istance2;//istanza di class_name
cout << istance.i << endl;			//stampa 0
cout << istance.func(5) << endl;	//stampa 5

Class_name istances [] {istance,istance2}; //Array di class_name
std::vector<Class_name> vect {istance,istance2} // vettore di class_name

Class_name *istance = new Class_name; // puntatore all'oggetto creato dinamicamente
delete istance; //deallocazione dell'istanza


```

Nel caso di puntatori a oggetti funziona tutto in modo usuale ma possiamo sostituire l'operatore di dereferenziazione con l'operatore   **->**

```cpp
Class_name *istance = new Class_name();

//Funzionano nello stesso modo, stampano attributo i
cout << (*istance).i <<endl;
cout << istance->i << endl;
delete istance;
```

### Public, private e protected

Di default tutti gli attributi di una classe sono **private** ovvero accessibili solo dalla classe stessa, dagli altri membri della classe o dai friends della classe (vedremo dopo cosa significa)

Gli attributi **public** sono sempre accessibili mentre quelli **protected** riguardano gli attributi ereditati

```cpp
class ClassName(){
    private:
    	int private_var;
    public:
    	int public_var;
    protected:
    	int protected_var;
}
```

Se proviamo ad accedere  ad un attributo privato il compilatore ritorna errore. 

Anche i metodi possono essere pubblici o privati, tipicamente non si creano mai attributi pubblici in grado di modificare attributi privati.

### Metodi

Possono essere implementati sia nella classe che al di fuori. Possono anche essere presenti nell'header per la dichiarazione della classe 

Per definire metodi al di fuori della dichiarazione della classe

```cpp
class ClassName{
    int i=0;
}
void ClassName::modify_i(int j){
    //In c++ non c'è bisogno del self come in python
    i=j;
    
    this -> i = j; 
    (*this).i=j; // Equivalente a quanto sopra
    //this funziona come self ma è un puntatore, va dereferenziato

} 
```

Quando il programma è lungo vogliamo separare la specificazione della classe dalla sua implementazione tramite gli header file.

Si usano delle direttive **Include guards** per evitare di includere il file più volte.

```cpp
// File ClassName.h

#ifndef _ACCOUNT_H_
//se _ACCOUNT_H_ È definito skippa tutto fino a #endif
#define _ACCOUNT_H_ //Altrimenti lo definisce
calss ClassName{
    private:
    	int i;
    public:
    	void modify_i();
};
#endif
```

Un'alternativa alle include guards è **pragma once**:`#pragma once` significa che questo file di intestazione verrà sempre incluso solo una volta in un file di destinazione specifico. Può velocizzare il tempo di compilazione ed è meno soggetto ad errori causati da errori di battitura

```cpp
//File ClassName.cpp
#include "ClassName.h"

void ClassName::modify_i(int j){
    i=j;
}
```

Per usare la classe nel main bisogna comunque includere l'header. In questo modo alla fune verrano compilati sia main.cpp che CLassName.cpp e linkati

```cpp
#include "ClassName.h"
int main(){
    ClassName instance;
    instance.modify_i(2);
    return 0;
}
```



## Costruttori e distruttori 

i **costruttori** sono un metodo speciale della classe invocato durante la creazione di un oggetto. 

Hanno lo stesso nome della classe, il tipo del return non è specificato e si può sfruttare l'overloading.

I **distruttori** sono metodi speciali invocati quando un oggetto viene distrutto (o va fuori scope). Solo un distruttore per classe è permesso e non è possibile sfruttare l'overloading. Si indicano con la ~

```cpp
//PROVA QUESTO CODICE
class Player{
    private:
    	std::string name;
    	int health;
    	int xp;
    public:
    	void set_name(std::string str){
            name=str;
        }
        void set_health(int i){
                health=i;
            }
        void set_xp(int i){
                xp=i;
            }
    	//Costruttori
    	Player();
    	Player(std::string str){
            set_name(str);
        };
    	Player(std::string str, int health_val, int xp_val){
            set_name(str);
            set_health(health_val);
            set_xp(xp_val);
        };
    	//In questo modo abbiamo 3 diversi modi per 			costruire un'istanza
    
    	//Distruttore
    	~Player(){
            cout<<"Object destroyed"<<endl;
        };
}
Player doom_slayer{"doom slayer",100,100};
//In questo modo in base a come si costruisce l'oggetto verranno fatte le relative assegnazioni

delete doom_slayer; //Stampa "object destroyed"

```







