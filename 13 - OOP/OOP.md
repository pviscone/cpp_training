[TOC]

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
    //this funziona come self ma è un puntatore che contiene l'indirizzo di memoria dell'oggetto, va dereferenziato

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

------

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

### Copy constructors

Quando un oggeto viene copiato il compilatore deve creare un nuovo oggetto a partire ada uno già esistente.

Una copia viene effettuata quando si passa un valore a una funzione, quando una funzione ritorna un valore o quando viene costruito un oggetto basato su un altro oggetto della stessa classe.

Se non si fornisce un copy constructor allora il compilatore ne ha uno di **default**: Copia tutti i valori di un'oggetto nel nuovo.

```cpp
//Default copy constructor
Player player1{"doom_slayer",100,100};
Player same_player{player1}; 
//player1 e same_player hanno gli stessi attributi con gli stessi valori
```

**Shallow copy vs deep copy**: Se stai usando puntatori viene copiato solo il puntatore non ciò a cui punta (shallow copy) quindi quando si usano i puntatori conviene sempre definire dei copy constructor custom (e in generale evitare di usare puntatori e usare le classi STL già definite).

Ma si può definire anche un **custom** copy constructor. E' buona pratica passare come argomento una const reference (per sicurezza, per non cambiare l'oggetto originale)

```cpp
//Solo copy constructor
Player::Player (const Player &source)
    //inizialization list to copy the object
	:name{source.name},
	health{source.health},
	xp{source.xp}{
        //altre istruzioni
        cout<< source.name << " copied" << endl;
    }
//Nota che il costruttore di copia è solo un costruttore che ha come argomento un parametro della classe stessa

```

#### 	Shallow copy

Il copy constructor di default fa una shallow copy (copia i puntatori ma non ciò a cui puntano  )

```cpp
//Shallow Constructor di ClassName con attributo i
ClassName::ClassName(int i_val){
    i=new int;
    *i=i_val;
}
//Shallow copy constructor. Copia il puntatore (poichè i è un puntatore)
ClassName::ClassName(const ClassName &source)
    : i{source.i}{
        cout << "Shallow copy" << endl;
    }
//Shallow destructor
ClassName::~ClassName(){
    delete i;
    cout << "deleted" << endl;
}
```

PROBLEMA: 

- Se si cambia il valore del dato puntato dal puntatore dell'oggetto copiato si cambia anche quello del oggetto originale
- viene copiato solo il puntatore di i, non ciò a cui punta poichè source e il nuovo oggetto puntano alla stessa area di memoria nell'heap. Questo significa che se deallochiamo (o  va fuori scope) il primo oggetto il secondo punterà a un area di memoria invalida nell' heap (Dangling pointer)

```cpp
//ESEMPIO
class ClassName(){
    int *i_ptr;
    public:
    	int get_i(){
           return *i_ptr; 
         } 
    	ClassName(int i){
            i_ptr= new int;
        	*i_ptr=i;
        }
    	ClassName(const ClassName &cls)
            :i_ptr{cls.i_ptr}{
            cout<<"pointer copied"
        }
    	~ClassName(){
			delete i_ptr;
            cout << "destroyed" <<endl;
        }
};

void display(ClassName cls){
    cout << cls.get_i() <<endl;
}

int main(){
    ClassName obj1{1}; //puntatore i_ptr creato
    display(obj1); //Viene creata una copia dell'oggetto e anche del puntatore i_ptr di obj1 nello stack (scope della funzione display).
    //Quando esce dalla funzione la variabile locale di display (cls) viene distrutta quindi viene sia distrutto il puntatore nello stack che i dati a cui punta nello stack e viene stampato "destroyed"
    
    //Problema, il dato distrutto è lo stesso di quello a cui punta i_ptr di obj1, che ora punta a un'area di memoria invalida
    
    ClassName obj2{obj1}; //Copia i_ptr di obj1 in obj2 ma i_ptr punta a un'area di memoria invalida
    
    return 0; //Gli oggetti vanno fuori scope e vengono distrutti. Ma l'aree di memorie puntate dagli i_ptr sono invalide e il programma crasha
}
```

#### 		Deep Copy

Tramite deep copy copiamo nell'heap sia il puntatore che il dato puntato. Usalo sempre quando negli attributi della classe c'è un puntatore

```cpp
//Solo copy constructor, il resto uguale a esempio di sopra

ClassName::ClassName(const ClassName &source){
    i_ptr= new int;
	*i_ptr=*source.i_ptr //Il * ci va perchè al defereziato di i_ptr ci va il deferenziato dell'i_ptr da copiare
}

//Oppure delegando al costruttore principale
ClassName::ClassName(const ClassName &source):
	ClassName{*source.i_ptr}{}

//In questo modo, nell'esempio di sopra, non ci sono problemi perchè quando la funzione display copia l'oggetto non copia il puntatore nello stack ma alloca dinamicamente nell'heap un nuovo puntatore con un nuovo dato
```



### Move constructors

Ricordiamo che L values è tutto ciò che può avereun indirizzo in memoria e gli R value sono oggetti temporanei creati dal compilatore

```cpp
int total{0};
total=100+200;
//Quello che succede è che 300 viene prima memorizzato in una variabile temporanea senza nome, poi in total e alla fine la variabile temporanea viene eleminata
//Lo stesso avviene con gli oggetti
```

Con gli oggetti, soprattutto nel caso di deep copy questo crea un overhead significativo in quanto vengono effettuate numerose copie in variabili temporanee.

Se per esempio facciamo il pushback di un vettore di oggetti e il copy constructor fa deep copy avremmo un codice molto inefficiente a causa di creazione e distruzione di numerosi oggetti temporanei

Nel C++11 è stato introdotto il move constructor che invece di copiare un oggetto lo sposta. E' raccomandato usarlo quando si lavora con i puntatori

> NB: a volte in fase di debug può sembrare che non vengano effettuati spostamenti o copie (copy illusions). Questo perchè il compilatore effettua un'ottimizzazione che evita di fare copie inutili

**R value references**: Necessarie nella move semantics. Operatore **&&**. Si possono pensare come referenze agli oggetti temporanei di cui abbiamo parlato

```cpp
//R value references
int &&r_ref =200;
r_ref=300; //Valore della R references cambiato
```

Il move constructor semplicemente copia l'indirizzo dalla sorgente all'oggetto corrente e assegna al puntatore originale nullptr.

```cpp
//Move constructor
ClassName::ClassName(ClassName &&source)
    : i_ptr{source.i_ptr}{
        source.i_ptr=nullptr;
    }
}
//source.i_ptr è un puntatore quindi un R value
//L'i_ptr di source diventa un null_ptr. Se non effettuiamo questo passaggio diventa semplicemente una shallow copy
```

In questo modo anche se dovessimo fare il pushback di ClassName in un vettore non ci sarebbero copie

## Const con le classi

Si possono creare anche oggetti const o passare ai metodi argomenti const.

```cpp
const ClassName istance {0}; 
```

Per un oggetto const è impossibile cambiare i suoi attributi una volta inizializzato ma non è neanche possibile passare l'oggetto a funzioni o metodi della classe in quanto, per il compilatore, la funzione potrebbe comunque potenzialmente cambiare l'oggeto.

La soluzione è specificare nella definizione del metodo che la funzione non modificherà l'oggetto

```cpp
//definizione del metodo nella definizione della classe
public:
int get_i() const{
	return i   
}
//in questo modo il compilatore sa che la funzione non può modificare l'oggetto e se nella funzione si fa qualche modifica il compilatore torna errore


int main(){
    const ClassName istance {0};
    cout << get_i(istance) << endl;
    return 0;
}
```

 

## Membri statici

E' possibile dichiarare anche attributi statici ovvero attributi che appartengono alla classe intera e non al singolo oggetto.

Si possono definire anche metodi statici che sono indipendenti dall'oggetto e possono essere chiamati usando il nome della classe

```cpp
//Ad esempio una variabile statica possibile può essere un contatore che conta il numero di istanze. Basta incrementarlo nel costruttore e decrementarlo nel distruttore
class Player{
    private:
    	static int num_players{0};
    	std::string name;
    public:
    	static int get_num_players(){
            return num_players;
        }
    	Player(std::string name_val):
    		name{name_val}{
            ++num_players;
        }
    	~Player(){
            --num_players
        }
}

```

## Struct vs class

Una struct è una classe in cui tutti i membri sono public di default mentre i membri di una classe sono private di default

Guida:

- Usa struct per oggetti passivi con accesso public
- Non dichiarare metodi in struct
- Usa le classi per oggetti attivi con accesso private
- Nelle classi Implementa getter, setter quando necessario



## Amici della classe

Un amico di una classe è una funzione (esterna alla classe) o un'altra classe che ha accesso ai membri privati della classe (e può anche modificarli)

- L'amicizia deve essere dichiarata esplicitamente nella classe e dichiarata nel prototipo della funzione tramite la keyword *friend*
- L'amicizia non è simmetrica: se A è amico di B, B non è amico di A
- La transitivita va dichiarata esplicitamente altrimenti se A amico di B e B di C non è garantito che A sia amico di C

```cpp
class Player{
    friend void display_player{Player &p};
    std::string name;
};
void display_player(Player &p){
    cout << p.name << endl;
}

//OPPURE NEL CASO DI METODO DI UN'ALTRA CLASSE
class Player{
    friend void OtherClass::display_player{Player &p};
    std::string name;
};
class OtherClass{
    public:
    	friend void Player::display_player(Player &p){
            cout << p.name << endl;
        }
};

//OPPURE POSSIAMO DEFINIRE UN INTERA CLASSE AMICA IN MODO TALE CHE TUTTI I SUOI METODI AVRANNO ACCESSO AGLI ATTRIBUTI PRIVATI DELLA CLASSE
class Player{
    friend class OtherClass;
}
```

