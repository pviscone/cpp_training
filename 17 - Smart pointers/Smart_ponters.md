# Smart pointers

La flessibilità estrema dei puntatori produce dei rischi

- Memory leaks
- dangling pointer
- Puntatori non inizializzatiù
- Not exception safe (se il compilatore raisa un'eccezione la memoria viene deallocata e abbiamo un memory leak)

Gli smart pointer sono degli oggetti implementati come classi template.

Possono puntare solo a della memoria allocata nell'heap e vengono automaticamente deallocati quando non sono più necessari.

Gli smart pointer aderiscono al **principio RAII** : (resource acquisition is initialization):

> Gli oggetti RAII sono allocati sullo stack che acquisiscono la risorsa (spazio in memoria) al momento dell'inizializzazione.
>
> La deallocazione (rilascio della risorsa) avviene nel distruttore e concide al momento in cui l'oggetto esce dallo scope

Gli smart pointer supportano gli operatori di deferenziazione * e di member selection -> MA non supportano l'aritmetica dei puntatori.

Volendo possiamo implementare un distruttore custom

Esistono diversi tipi di smart pointer:

- Unique pointer
- Shared pointer
- Weak pointer

```cpp
//includi memory per usare gli smart pointer
#include <memory>
std::smart_ptr<ClassName> ptr {...};
//Sostituire smart con il tipo di puntatore che si vuole creare
//ClassName è il tipo dell'oggetto a cui il puntatore punta
```

Quando il puntatore va fuori scope viene deallocato automaticamente.

Inoltre se definiamo un puntatore senza inizializzarlo viene posto automaticamente a un nullptr

## Unique pointer

L'unique pointer è **unico**: può esserci un unico unique pointer che punta a un oggetto nell' heap e si dice che il puntatore possiede l'oggetto (**ownership**).

**Se non ci sono altre necessità usa sempre questi**

Gli unique pointer **NON possono essere assegnati o copiati ma possono essere spostati (move semantic)** (quindi funzionano perfettamente nei container della STL come i vettori).

Quando il puntatore è distrutto viene distrutto anche l'oggetto a cui punta

```cpp
std::unique_ptr<ClassName> ptr {new ClassName{} };
```

Alcuni dei metodi più utile degli unique pointer sono:

- get() : ritorna indirizzo di memoria (utile quando lavori con librerie che si aspettano raw pointer)
- reset() : il puntatore diventa un nullptr 

> **NB** Nei vettori non è possibile fare vec.pushback(ptr) perchè questo include una copia che non è permessa dagli unique pointer
>
> Per aggiungere un unique pointer a un vettore bisogna usare il costrutto move
>
> ```cpp
> std::vector<std::unique_ptr<ClassName>> vec;
> vec.pushback(std::move(ptr));
> //L'ownership passa da ptr a vec e ptr sarà settato al nullptr
> ```
>
> 

### make_unique

Esiste un modo più efficiente per inizializzare gli unique pointer (introdotta in C++14)

```cpp
//inizializzare l'oggetto nelle parentesi tonde
std::unique_ptr<ClassName> ptr = make_unique<ClassName> (...);

//oppure
auto ptr = make_unique<ClassName>(...);
```

make_unique ritorna un unique pointer che punta all'oggetto desiderato



## Shared Pointer

Uno shared pointer punta a un oggetto nell'heap ma non è unico, possono esserci più shared pointer che puntano allo stesso oggetto.

Può essere **assegnato, copiato e spostato MA non è possibile di default allocare array di oggetti** sull heap come è possibile fare con gli unique pointer.

Per capire quando un oggetto deve essere deallocato gli shared pointer sono dotati di un reference counter che viene incrementato ogni volta che un puntatore viene creato e decrementato ogni volta che viene distrutto. Quando il contatore arriva a zero l'oggetto sull'heap viene deallocato (introduce un piccolo Overhead)

```cpp
std::shared_ptr<ClassName> ptr {new ClassName{...}};

//Costrutto di copia, crea un'altro puntatore all'oggetto, non puntatore a puntatore
std::shared_ptr<ClassName> ptr2 {ptr};
```

Alcuni metodi utili degli shared pointed sono:

- use_count() : ritorna il valore del reference counter
- reset() : pone il puntatore a nullptr ma dealloca l'oggetto SOLO se non ci sono altri shared pointer

### make_shared

Funzione più efficiente per inizializzare shared pointer introdotta in C++11

```cpp
//Nella parentesi tonda metti i parametri per inizializzare oggetto
std::shared_ptr<ClassName> ptr = std ::make_shared<ClassName>(...)
```



## Weak pointer

I weak pointer non hanno un concetto di ownership e sono sempre creati a partire da shared pointer MA non incrementano il loro contatore.

Sono usati per prevenire cicli di referenze che possono impedire la deallocazione degli oggetti oppure quando abbiamo un puntatore che usiamo come referenza temporanea per un altro oggetto 

**Strong circular reference** A punta a B, B punta ad A. La ownership dei due shared pointer impedisce la deallocazione delle risorse. 
In questo modo vengono deallocati solo i puntatori nello stack quando vanno fuori scope e si ha un memory leak

Se invece A è uno shared pointer che punta B e B è un weak pointer che punta A tutto può essere deallocato normalmente



## Custom deleters

Può capitare che quando distruggiamo uno smart pointer vogliamo che faccia anche altre cose 

**NB: se usi un deleter custom NON puoi usare make_unique e make_shared per creare lo smart pointer**

I custom deleter si possono creare sia con le funzioni che con le lambda 

```cpp
//Funzioni
void deleter(ClassName *raw_ptr){
    //do things
    delete raw_ptr;
}

std::shared_ptr<ClassName> ptr {new ClassName{},deleter};
```

```cpp
//Lambda
std::shared_ptr<ClassName> ptr(new ClassName{}, [] (ClassName *ptr) {
    //Do things
    delete ptr;
})
```

