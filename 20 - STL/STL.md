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

NON sono i C style array.

Sono array di lunghezza fissata (a tempo di compilazione) MA:

- sono un oggetto non un puntatore
- Il tempo di accesso a un elemento dell'array è fissato e non dipende dalla size
- E' possibile usare gli iteratori e algoritmi
- E' una classe costruita intorno i raw array quindi è possibile, se si vuole, accedere al raw array e usare le solite funzioni in c style

```cpp
#include <array>
const int size {5};
std::array<int, size> arr {1,2,3,4,5};
arr={1,2,3,4,5};
```

i **metodi più usati** sono:

- .size()
- .at(size_t_value) che corrisponde a [size_t_value]
- .font() (primo valore), .back() (ultimo valore)
- .empty() (ritorna bool 1 se array vuoto)
- .fill(value) riempie array
- .data() ritorna il raw array (puntatore al primo elemento)
- arr1.swap(arr2): scambia 2 array

### Vector

Hanno size dinamica. Il tempo di accesso, inserimento e rimozione alla coda è indipendente dalla size mentre per l'inserimento/rimozione all'interno del vettore è lineare

**Metodi comuni**:

- push_back(value)

- pop_back() rimuove ultimo elemento

- size()/capacity()

- front()/back()

- empty() ritorna bool

- clear()

- v1.swap(v2)

- v1.insert(it,value) dove it è un iteratore e corrisponde all'indice in cui inserire value

- erase(it1,it2) cancella tra i 2 iteratori (suppongo) 

- emplace_back(values) : MOLTO EFFICIENTE

  Se abbiamo un vettore v che contiene oggetti di una ClassName(string,int) è possibile mettere in coda all'array un oggetto della classe istanziandola direttamente nel vettore tramite

  ```cpp
  vec.emplace_back("Name",2);
  ```

### Deque

La size è dinamica MA gli elementi non sono storati in una sezione contigua di memoria. A differenza degli array le deque permettono l'inserzione e la rimozione a tempo costante anche in testa all' "array" oltre che in coda.

Solitamente la deque è implementata come una collezione di blocchi di memoria contigua PERO' i blocchi separatamente non sono contigui tra loro (è come una link list di vettori)

**metodi comuni**: i soliti, in più è presente:

- push_front(value)/emplace_front(...): aggiunge valore in testa
- pop_front()

### List and forward list

Elementi storati in sezioni di memoria non contigua.

NON è possibile accedere agli elementi tramite [ ] o .at() MA sono molto efficienti nell'inserire o rimuovere elementi una volta trovato l'elemento (iteratore ottenibile tramite find a tempo lineare)

#### list

Un elemento della lista contiene il valore, un puntatore all'elemento successivo e un puntatore all'elemento precedente

Soliti metodi

#### Forward list

Come la lista ma un elemento contiene, oltre a un valore, solo il puntatore all'elemento successivo (quindi non è possibile usare il reverse_iterator)

Non sono disponibili i metodi size() e tutti i metodi che riguardano il back

Inoltre esiste insert_after/emplace_after/erase_after

### Sets 

Container associativo.

Esistono set, unordered_set, multiset, unordered_multiset e sono implementati come hash set o come alberi binari

I **set** sono letteralmente degli insiemi (no duplicati) e sono ordinati da una chiave

**metodi comuni**:

- .insert(object) : il metodo insert ritorna una pair<iterator,bool> che contiene l'iteratore all'elemento inserito (o al suo duplicato già esistente) e un bool che indica il successo o fallimento
- .emplace(...)
- .erase(object)
- .find(object)
- .empty() 
- .clear()

I **multiset** permettono la presenza di elementi duplicati

Gli **unordered** non hanno un ordine, gli elementi non possono essere modificati e non sono ammessi reverse_iterator

### Maps

Anche per le maps esistono le multimap e le unordered_map (e multimap)

Sono simili a un dizionario e ordinati con una chiave. Non sono permessi elementi duplicati (le chiavi sono uniche)

```cpp
#include <map>
std::map<std::string,int> int_dict{ {"uno",1} , {"due",2};
```

Metodi simili ai set MA attenzione, per usare insert bisogna inserire un oggetto std::pair<T1,T2> o in alternativa fare

```cpp
map_name[key]=value; //Fa anche update dei valori se la key esiste già
```

### Stack

E' un adaptor container. E' letteralmente uno stack, come se fosse una pila di piatti

E' una struttura dati LIFO (Last in first out) implementata come un adattatore sopra un altro conteiner. 
Tutte le operazioni avvengono alla fine dello stack

Gli iteratori NON sono supportati.
I **metodi più usati** sono:

- push (Inserisci elemento in cima allo stack)
- pop (Rimuovi elemento in cima allo stack)
- top (accedi all'elemento in cima allo stack)
- empty
- size

Stack è un adapter quindi possiamo scegliere che container usare per creare l'oggetto. Di base è usata una deque

```cpp
#include <stack>
std::stack<int,std::vector<int>> st1;
//In questo modo per implementare la struttura a stack e riempirla di int usiamo un vettore

std::stack<int> st1; //In questo caso verrà usata una deque
```

### Queue

Adattatore con Struttura FIFO (First in First Out).

Gli elementi vengono pushati in cima e eliminati alla base.
Gli iteratori non sono supportati.

Anche qui di default viene usata una deque

i **metodi** sono simili allo stack (ricorda comportamento diverso per push and pop) e in più abbiamo front e back per accedere all'elemento in cima e alla base della struttura

### Priority queue

Queue che permette l'inserzione o rimozione degli elementi in ordine a partire dall' inizio del container.
Gli elementi sono inseriti in ordine prioritario (i valori più grandi saranno sempre in testa al container)

Di default vengono usati i vector.
Gli iteratori non sono supportati

I **metodi sono sempre gli stessi** MA push inserisce un elemento in modo tale che rispetti l'ordinamento nel container, pop rimuove l'argomento maggiore in testa al container e top accede all'elemento più grande in testa al container
