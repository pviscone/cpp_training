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

#ifndef _CLASSNAME_H_
//se _CLASSNAME_H_ È definito skippa tutto fino a #endif
#define _CLASSNAME_H_ //Altrimenti lo definisce
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

**Per compilare basta mettere in lista tutti i file cpp presenti (in questo caso main.cpp e ClassName.cpp)** in questo modo si crea un unico file binario (non viene creata una shared library) 

## Costruttori e distruttori 

i **costruttori** sono un metodo speciale della classe invocato durante la creazione di un oggetto. 

Hanno lo stesso nome della classe, il tipo del return non è specificato e si può sfruttare l'overloading.

I **distruttori** sono metodi speciali invocati quando un oggetto viene distrutto (o va fuori scope). Solo un distruttore per classe è permesso e non è possibile sfruttare l'overloading. Si indicano con la ~

```cpp
#include <iostream>
#include <string>
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
        void print(){
            std::cout << name << ":" << health << "PV,"<< xp<< "xp" << std::endl;
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
            std::cout<<"Object destroyed"<<std::endl;
        };
};

int main(){

    Player *doom_slayer {};
    doom_slayer = new Player("Doom Slayer", 100, 100);
    doom_slayer->print();
    delete doom_slayer; //Stampa "object destroyed"
    return 0;
}
```

**NB:**

- delete (il distruttore) può essere chiamato solo su oggetti allocati dinamicamente ovvero allocati nell' Heap. 
  Il resto viene considerato variabile locale e fa parte dello stack

- Nelle funzione, ad esempio, set_name possiamo scrivere in due modi

  ```cpp
  void set_name(std::string str){
      name=str;
  }
  void set_name(std::string name){
      this->name = name;
  }
  //Questo poichè se chiamiamo le var della funzione come gli attributi le sovrascrivono nello scope della funzione. Bisogna usare this come in python si usa self
  ```

- I parametri nel costruttore possono essere posti a valori di default come si fa con le funzioni

### Constructor initialization list

Prima abbiamo dato un valore agli attributi tramite assegnazione con =. Questo può essere inefficiente poichè prima di fare l'asseggnamento tutti gli attributi vengono creati a valori nulli.

Per risolvere questo problema possiamo inizializzare direttamente le variabili al valore che vogliamo

```cpp
//Scrivo solo il costruttore
ClassName::ClassName(int i_val, int j_val):
	: i{i_val}, j{j_val}{
        \\Istruzioni varie
}
```

Ricorda che gli attributi non vengono inizializzati in ordine di inizializzazione ma in ordine di dichiarazione (l'ordine con il quale sono stati definiti nella definizione della classe)



### Delegating constructors

Quando facciamo overloading di costruttori spesso creiamo molto codice ridondante (soprattutto per inizializzare gli attributi).

Questo può essere evitato specificando le inizializzazione degli attributi solo nel caso più esteso e in tutti gli altri chiamare l'attributo più esteso

```cpp
//solo costruttori
Player::Player(std::string name_val,int health_val, in xp_val):
	name{name_val},health{health_val},xp{xp_val}{
}
Player::Player():
	Player{"None",0,0}{
}
Player::Player(std::string name_val):
	Player{name_val,0,0}{
}
```

