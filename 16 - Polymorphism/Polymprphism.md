# Polimorfismo

Ci sono diversi tipi di polimorfismo. Abbiamo già visto l'overloading delle funzioni e degli operatori che sono forme di polimorfismo a **tempo di compilazione** (static binding).

Questo è quello che fa il compilatore di default

> ATTENZIONE, si possono avere comportamenti inaspettati
>
> Consideriamo il caso in cui sia la classe Parent che Child hanno una propria versione del metodo method
>
> ```cpp
> Parent *ptr = new Child();
> ptr->method();
> ```
>
> Anche se viene chiamato su un oggetto di Child il compilatore vede un puntatore di tipo Parent e tramite static binding chiama il metodo di Parent
>
> ------
>
> Esempio analogo è se definisco una funzione esterna 
>
> ```cpp
> //method è un metodo definito diversamente in Parent e in Child
> void func(const Parent &obj){
>     obj.method();
>     //DoSomething
> }
> Child child;
> func(child); //Viene usata la funzione method di Parent
> ```
>
> Questi problemi si possono evitare con il dynamic binding.
>
> 

**Questi problemi si presentano ogni volta che lavoriamo con puntatori o reference della classe Parent**

------

L'altro tipo di polimorfismo è **tempo di esecuzione** (Dynamic binding).

## Parent class pointer

Ma perchè mai dovremmo usare i base class pointer? Potremmo specificare il tipo di puntatore esplicitamente ogni volta MA questo non ci permette di creare strutture omogenee di oggetti come vettori o array

**NB** In questi casi conviene sempre usare gli **smart pointers** MA ancora non li abbiamo visti, in ogni caso tienilo a mente

```cpp
//Tramite base class pointer è possibile mettere classi appartenenti alla stessa gerarchia in array (lo stesso vale per vettori)
Parent *p1 = new Parent();
Parent *p2 = new Child();
Account *arr[] {p1,p2};
for(int i{0},i<2,i++){
    arr[i]->method(); 
    //Se è stata implementato il dynamic binding a ogni elemento dell'array verrà associato il method della propria classe e non quello di Parent
}
```

## Funzioni virtuali

La keywork **virtual** nei metodi della Parent class fa si che il binding dei metodi sia dinamico

```cpp
class Parent{
    public:
    	virtual void method();
};
```

Una volta definito il metodo con virtual tutte le funzioni method nelle Child class godranno del dynamic binding. Dichiarare virtual i method delle Child non è necessario MA è buona pratica farlo per chiarezza.
**NB** La signature (parametri) e il tipo del return devono essere identici altrimenti è una semplice ridefinizione e sarà trattata con static binding

**Ricorda che è possibile fare polimorfismo dinamico solo tramite puntatori o reference della classe Parent**

Ricorda che lavorare con il dynamic binding ci permette di fare tante belle cose ma si perde in efficienza in quanto le operazioni avvengono a runtime

## Distruttori virtuali

Quando si dealloca un oggetto polimorfico possono esserci problemi. Se non definiamo un distruttore virtuale potrebbero esserci comportamenti inaspettati in quanto il compilatore userebbe il distruttore della parent class
**Quindi ogni volta che c'è una funzione virtuale crea un distruttore virtuale**. Anche qui basta dichiararlo solo nella Parent class ma è bene farlo per chiarezza anche in tutte le child

```cpp
class Parent{
    public:
    	virtual ~Parent();
}
```

## Override Specifier

E' un modo (introdotto in C++11) per essere sicuti che i metodi delle Child Class sovrascrivano le classi Parent virtuali.

**le funzioni devono avere stessi parametri (anche la constness) e return** altrimenti semplice ridefinizione statically bound ma sbagliarsi è semplice.

Se aggiungiamo la keyword **override** alla fine della funzione il compilatore non permette la ridefinizione della funzione e quindi se abbiamo sbagliato qualcosa torna errore

```cpp
class Child{
    public:
    	virtual func() override{};
}
```

## Final Specifier

Altra feature introdotta in C++11.
Possiamo usarla in 2 contesti:

- Nella classe: impedisce a un'altra classe di ereditare da essa
- In un metodo virtuale: impedisce a una classe Child di sovrascrivere il metodo virtuale 

E'  bene usarlo anche per sfruttare ottimizzazioni del compilatore

```cpp
//Nella classe
class Child1 final : public Parent{};

//In un metodo
virtual void Child1::func() final{
}
```

## Base class references

Il discorso fatto finora per i base class pointers è identico per le **base class references **(più usate come argomento delle funzioni)

```cpp
//Data func definita diversamente in Parent e in Child
void do_func(Parent &obj){
    obj.func()
}
Child child;
do_func(child) //se func è una funzione virtuale viene chiamata quella di Child in quanto il binding è dinamico
```

Questo ci permette di creare un'unica funzione esterna che prende come argomento la reference della base class invece di dover specificare una funzione apposita per ogni classe nella gerarchia

## Classi astratte

Una classe astratta è una classe che **non può essere istanziata** ma può essere ereditata e **contiene almeno un metodo virtuale puro**

Genericamente le classi astratte sono troppo generiche per poter istanziare degli oggetti sensati ma è utile come Base class per fornire dei membi comuni a tutti i child

> **Pure virtual function**: è una funzione usata per creare classi astratte.  è specificata con un =0 nella definizione e non prevede implementazione in quanto solitamente il suo comportamento viene specificato nelle Child class
>
> ```cpp
> virtual void func() = 0;
> ```
>
> 

Tutte le classi che contengono almeno una pure virtual function è una abstract class. 

Le Child class **devono sovrascrivere** la pure virtual function della base class per essere una classe concreta e non astratta

------

Le classi astratte non possono essere istanziate MA **possiamo usare puntatori e reference per riferirci dinamicamente alle classi concrete che ereditano da loro**

```cpp
//Sia func una pure virtual function di Abstract sovrascritta in Child
Abstract *ptr = new Child;
ptr->func(); //Func implementata in child

//
```

### Classi astratte come interfacce

Una "class as interface" (d'ora in poi chiamata interfaccia) è una classe dotata di sole pure virtual functions pubbliche.

Queste funzioni forniscono un set generico di funzioni alle child class che sono libere di implementarle come vogliono

> Esempio: Facciamo l'overloading dell'operatore << nell'interfaccia per permettere a tutte le classi child l'uso di cout
>
> ```cpp
> class Printer{(
>     friend ostream &operator<<(ostream &, const Printer &obj);
>     public:
>     	//pure virtual function
>     	virtual void print(ostream &os) const = 0;
>     	virtual ~Printer() {}; //distruttore virtuale  
> };
>     
> ostream &operator<<(ostream &os, const Printer &obj){
>     obj.print(os);
>     return os;
> }
> // In questo modo basta sovrascrivere la funzione print() nelle child class e avranno l'operatore << già overloadato e quindi potranno usare cout
>     
>     
> class Child : public Printer{
>     public:
>     	virtual void print(ostream &os) override{
>             os << "Print what you want";
>         }
> };
> ```
>
> 

In questo modo stiamo sfruttando il dynamic binding quindi possiamo lavorare tranquillamente con le base class references e con i base class pointers

E' buona pratica nominare le interfacce con una "i" maiuscola seguita da un "_" (es. I_Shape)