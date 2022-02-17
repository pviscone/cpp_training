## Standard Template Library

 STL è una libreria che contiene Containers, algoritmi e iteratori

Alcuni algoritmi (dei circa 60 presenti) base utili sono:

- std::sort(v.begin(), v.end()) Ordina una sequenza (con begin e end usiamo gli iteratori per passare l'intero vettore v come sequenza)
- std::reverse
- std::accumulate (somma cumulativa del vellore)

I container si dividono in 3 tipi:

- Sequenze: (array,vettori, liste, forward_list, deque) Mantengono l'ordine degli elementi
- Container associativi: (set,multiset,map,multimap) Container con un ordine predefinito o senza ordine
- Container adapter: (stack,queue, priority queue)

**tipi di iteratori**:

- Input iterator: dal container al programma
- Output iterator: dal programma al container
- Forward iterator: Esplora un elemento per volta in una direzione
- Bidirectional iterator: Esplora un elemento per volta in entrambe le direzioni
- Random iterator: Accedi ad un elemento casuale

# Generic programming

Consiste nel scrivere del codice che funziona con una varietà di tipi di dati come argomento mantenendo la stessa sintassi e la stessa semantica

## Macros

EVITALE ASSOLUTAMENTE: unico modo per fare generic programming in C

Supponiamo di voler scrivere una funzione che ritorna il massimo di due elementi dello stesso tipo

```cpp
type max(type a,type b){
    return (a>b) ? a : b;
}
//Il type può essere int, double, anche char (ordine alfabetico)
```

Vogliamo definire una macro in modo tale da creare una funzione indipendente da type

Per farlo usiamo una direttiva del preprocessore

```cpp
#define MAX(a,b) ((a>b) ? a :b)
```

In questo modo il preprocessore ogni volta che vede MAX sostituisce la funzione definita con gli argomenti dello stesso tipo degli argomenti passati 

 **NB** il preprocessore fa una semplice sostituzione nel codice, questo può portare a problemi (es. ordine delle operaazioni, attento a parentesi)

## Function templates

Un template è un blueprint che il compilatore usa per generare funzioni e classi appropriate  a partire dal blueprint.

Questo è possibile farlo usando un placeholder al posto del tipo, le funzioni verranno generate A TEMPO DI COMPILAZIONE

L'esempio di prima ora sarà:

```cpp
template <typename T>
T max(T a, T b){
    return (a>b) ? a : b;
}
//Questo è solo un template, il compilatore non genera alcun codice finchè max non viene chiamata
```

Al posto di typename può essere usato class, è equivalente

 Per usare la funzione template bisognerà specificare il tipo nelle < >

```cpp
max<int> (10,20);
```

Una volta chiamata la funzione col tipo voluto la funzione viene generata e non è più necessario specificare il tipo nelle < >, servono solo la prima volta per creare la funzione (o farci overloading usando altri tipi)

E' possibile anche usare **Parametri di template multipli**

```cpp
template <typename T1, typename T2>
void func(T1 a, T2 b){
    //DO things
}
func<int,double>(10,20.5);
```



 ## Class templates

Lo stesso può essere fatto con le classi MA NON vogliamo fare l'overloading della classe (quello è polimorfismo dinamico), vogliamo che alcuni attributi siano del typename richiesto

```cpp
template<typename T>
class ClassName{
    T value; 
    public:
    T get_value(){return value;}
    ClassName(T val): value{val}{}
};

ClassName<int> istance_name {2};
```

Anche qui si possono usare parametri di template multipli

# STL

## Iterators

Ci permettono di pensare a i container come una sequenza di elementi e sono implementati come classi template.

La sintassi ricorda (volutamente) quella dei puntatori

L'iteratore deve essere dichiarato basandosi sul tipo di container sul quale deve iterare

```cpp
container_type<element_type>::iterator_type iter_name;

//Es. it è un iteratore su vettore di int
std::vector<int>::iterator it;
```

### Metodo begin ed end

Dato v un vettore v.begin() corrispone all'indirizzo di memoria del primo elemento, v.end() all'indirizzo di memoria successivo a quello dell'ultimo elemento

> - Se container vuoto begin e end puntano a stesso indirizzo
>
> - Quando assegni degli iteratori la sintassi diventa molto pesante, usa auto e pace
>
>   auto it=v.begin()

**NB** Ritornano degli iteratori NON dei semplici indirizzi che possono essere assegnati a un puntatore 

### Operazioni sugli iteratori

Gli operatori agiscono in modo molto simile a quelli si puntatori

- +,-,++, -- Incremento/Decremento (prossimo elemento nel container)
- Assegnamento
- \* Deferenziazione
- ->
- ==, !=,<,>,etc. Comparazione

```cpp
//Esempio: iterare su un vettore sfruttando gli iteratori
for (auto it=vec.begin(); it!=vec.end();i++){
    cout<<*it<<endl;
}

//OPPURE
auto it=vec.begin();
while(it!=vec.end()){
    cout<<*it<<endl;
    it++;
}


//PER ANDARE IN REVERSE STESSA COSA BASTA CAMBIARE DEFINIZIONE ITERATORE
std:vector<int>::reverse_iterator it= vec.begin();
//In questo modo v.begin punta all'ultimo elemento e end all'indirizzo precedente al primo elemento
```



**NB** Gli iteratori NON sono puntatori, quando gli incrementio vanno allì'elemento successivo anche se il container non è storato in una sezione contigua di memoria'

## Algorithms

Per usare gli algoritmi  della STL è necessarioo includere l'header

```cpp
#include <algorithm>
```

Gli algoritmi come argomento aspettano un'iteratore e diversi algoritmi supportano diversi container (omeglio iteratori di diversi container)

> **Iterator invalidation**: Durante il processo un iteratore può diventare invalido (es. clear sul container durante l'iterazione). Quando accade il comportamente è indefinito, gli iteratori puntano a indirizzi invalidi

- **find(v.begin(),v.end(),value)** Ritorna un iteratore che punta alla prima occorrenza di value in v altrimenti ritorna iteratore v.end()

  Si può usare anche su classi definite dall'utente ma deve essere stato fatti l'overloading dell'operatore ==

- **for_each** applica una funzione a tutti gli elementi del container.
  Ci sono 3 modi per implementarla

  (Sia v un vettore di int)

  - **Funtori**

    ```cpp
    struct Square_Functor{//Puo essere anche classe con un unico metodo pubblico
        void operator()(int x){
            std::cout << x*x << " ";
        }//Metodo call "()" overloadato
    }
    Square_Functor square;//Fuction object
    
    std::for_each(v.begin(),v.end(),square)
    ```

  - **Puntatori di funzioni**

    ```cpp
    void square(int x){
        std::cout<<x*x<<" ";
    }
    std::for_each(v.begin(),v.end(),square);
    //Il nome della funzione, quando non viene usato l'operatore di chiamata (), corrisponde al suo indirizzo di memoria (esattamente come array)
    ```

  - **Lambda**

    ```cpp
    std::for_each(v.begin(),v.end(),
                 [](int x){std::cout << x*x<<" "});
    ```

- **count**(beg,end,value): Numero di elementi trovati

- **count_if(beg,end,bool_function)**: Numero di occorrenze trovate (che soddisfano una funzione booleana)

- **replace(beg,end,val1,val2)** Sostituisce i val1 con val2

- **trasform(beg,end,beg,::metodo)**: trasforma i valori

In questo caso si usa sempre begin e end per lavorare su tutto il container ma è possibile lavorare anche sulle singole sequenze sfruttando l'aritmetica degli iteratori

## Containers

Sono strutture dati implementate tramite classi template.

Ogni container ha dei metodi associati specifici per il container(es. pushback per i vector)

Esistono dei metodi comuni ai vari container:

- Default constructor (container vuoto)
- Overloaded constructor
- Copy/Move constructor (anche tramite assegnamento)
- Operatori <,>,==, etc. (riferiti alla size)
- size
- empty (ritorna bool)
- insert(inserisce elemento)
- swap (scambia due elementi)
- erase/clear (elimina 1/tutti gli elementi nel container)
- begin, end ritorna un iteratore che va dal priimo elemento all'ultimo
- rbegin, rend (iteratore al contrario)
- cbegin, cend (costant iterator)
- crbegin,crend (costant reverse iterator)

I container possono contenere tutti gli elementi copiabili e assegnabili (Di solito viene implementato il move contructor per efficienza)

Quando mettiamo un elemento in un container questo fa la copia quindi se vogliamo storare un elemento di una classe da noi definita dobbiamo aver prima definito un coèpy constructor e un copy assignment (possiamo implementare move semantic se vogliamo)

### Array

