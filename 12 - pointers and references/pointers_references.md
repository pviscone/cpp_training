# Pointers and references

## Puntatori

Un puntatore è una variabile quindi ha un nome, un tipo e un indirizzo di memoria. Un puntatore conserva l'indirizzo di memoria di un'altra variabile o funzione (deve essere dello stesso tipo del puntatore)

A cosa servono?:

- Per operare sugli array
- Fondamentali in ambito embedded
- Per cambiare dati definiti all'esterno all'interno di una funzione
- Allocare dinamicamente la memoria
- In OOP i puntatori stanno alla base del polimorfismo

```cpp
int *int_ptr {nullptr}; //puntatore tipo int che non punta a nulla (null pointer che ha valore 0)

//nullptr introdotto in C++11. NON LASCIARE MAI PUNTATORI NON INIZIALIZZATI: contengono indirizzi casuali, possono fare danni
```

E' possibile otterere l'indirizzo di memoria in cui è allocata una variabile tramite l'operatore **&**

```cpp
int i = 1;
int *i_ptr=&i; //i_ptr contiene l'indirizzo di memoria di i
```

Per avere **accesso ai dati** al quale il puntatore punta bisogna **dereferenziare** il puntatore tramite l'operatore *

```cpp
int i {10};
int *i_ptr{&i};
cout << *i_ptr << endl; //stampa 10
```

### Allocazione dinamica

Per allocare una variabile a runtime usiamo il commando **new** tipo (ritorna un indirizzio di memoria).

Tutte le cose allocate dinamicamente vengono allocate nell'heap (uno spazio di memoria libero in cui non c'è gerarchia), non nello stack,

```cpp
int *i_ptr {nullptr};

i_ptr = new int; // si possono allocare sezioni contigue (es int[10]) per array

*i_ptr = 10; //nota che l'unico modo per accedere al dato è derefereziare il puntatore. Se lo perdi sono problemi

delete i_ptr; //per deallocare. Nel caso di array bisogna scrivere 
delete [] i_ptr;
```

### Array

Il nome di un array corrisponde all'indirizzo di memoria dell'inizio dell'array. Quindi nome dell'array e puntatore all'array funzionano nello stesso modo

```cpp
int arr[] {1,2,3};
int *arr_ptr {arr};
cout << arr << endl;	// stampa l'indirizzo di memoria dell'elemento 0
cout << arr_ptr <<endl;	// come sopra

cout << (arr_ptr + 1) <<endl; // stampa l'indirizzo di memoria dell'elemento 1 (facendo +1 stiamo sommanda la size di un int)

cout << *(arr_ptr + 1) << endl; // stampa 2
cout << *(arr + 1) << endl; // stampa 2
cout << arr_ptr[1] << endl;		// stampa 2
cout << arr[1] << endl;			// stampa 2
```

### Aritmetica dei puntatori

- ptr_name++ e ptr_name-- incrementa o decrementa il puntatore (elemento dell'array successivo o precedente)
- ptr_name+=n e ptr_name -=n come sopra ma di n
- **sottrazione tra puntatori**: se 2 puntatori dello stesso tipo vengono sottratti si ha il numero di elementi compresi tra i due puntatori
- **comparazione** ==,|=: torna true solo se due puntatori puntano allo stesso indirizzo di memoria

### const

Un puntatore può essere const (non deve per forza puntare a un const, basta che sia dello stesso tipo)

```cpp
int i {1};
int a {0};

//POINTER TO CONSTANT
const int *i_ptr {&i};
*i_ptr=0; // ERRORE, non puoi cambiare valore puntato
i_ptr=&a; // Assegna al puntatore l'indirizzo di memoria di a

// CONSTANT POINTER
int *const i_ptr{&i};
*i=0;	  // Assegna all'indirizzo di i 0
i_ptr=&a; // ERRORE:non puoi cambiare indirizzo a cui punta un const. pointer

//CONSTANT POINTER TO CONSTANT 
//POINTER TO CONSTANT
const int *const *i_ptr {&i};
*i_ptr=0; // ERRORE
i_ptr=&a; // ERRORE, tutto costante

```

### Puntatori nelle funzioni

Per passare puntatori in funzioni basta dichiararli come tali e passare indirizzi di memoria alla funzione

```cpp
int i=0;
//int_ptr dovrà essere un puntatore e func ritorna un puntatore int
void func(int *int_ptr){
    *int_ptr *= 2; //int_ptr è dereferenziato e il valore raddoppiato
} 
func(&i); // gli passo l'indirizzo di i, i sarà raddoppiato
```

Per ritornare un puntatore idem

```cpp
//Questa funzione inizializza un array lungo size con valori init_value
int *initialize_array(double init_value,size_t size){
    double *new_array {nullptr};
    new_array = new double[size];
    for (size_t i=0, i<size,i++){
        new_array[i]=init_value;
    }
    return new_array;
}
//NB: questa funzione non funzionerebbe se usassimo variabili locali sia perchè la size non sarebbe fissata a priori sia perchè le variabili locali vivono nello stack, il puntatore tornerebbe un indirizzo nello stack che sarebbe deallocato non appena usciti dalla funzione
```

**Non tornare mai puntatori a variabili locali, gli indirizzi dello stack vengono deallocati non appena usciti dalla funzione**

### Pitfalls 

- **Uninitialized pointers**: puntatori non inizializzati puntano a indirizzi casuali, può succedere qualsiasi cosa
- **Dangling pointer**: puntatori che puntano a indirizzi che sono stati deallocati (es. due puntatori puntano allo stesso indirizzo, faccio il delete di un puntatore, l'altro diventa un dangling popinter). Le funzioni che ritornano puntatori di var. locali sono sempre dangling pointer
- Se new fallisce viene raisata una exception. Dereferenziare un null pointer dà comunque errore
- **Leaking memory**: memoria che ci siamo dimenticati di deallocare. Ad esempio quando allochiamo dinamicamente qualcosa in una funzione se non ritorniamo un puntatore avremo un indirizzo di memoria allocato a cui non possiamo accedere e neanche deallocare

## References

Una reference è un alias di una variabile. Deve essere inizializzata è non può essere null.

Una volta inizializzata non può cambiare la variabile a cui è riferita. Possono essere pensati come constant pointers che vengono automaticamente dereferenziati

```cpp
vector<int> arr{1,2,3};
//ricorda che nei loop i contatori sono var locali come in funzionei
for (auto i:arr){
    i=5;
}
// in questo loop viene assegnato 5 a tutti i valori di i MA i è, elemento per elemento, la copia dei valori di arr

for(auto &i:arr){
    i=5;
}
//In questo modo vengono modificati proprio gli elementi di arr. E' come scrivere (non so se auto funziona anche su ptr ma penso di si)
for (auto *i: &arr){
    *i=5;
}



// se non vogliamo che avengano modifiche basta usare una const reference
for(auto const &i: arr){
    i=5; //ERRORE, const reference non può essere modificato
}
```

Usare puntatori o reference nelle funzioni è la stessa cosa

```cpp
int a {1};
int &ref{a}; //ref è 1
a=2; 		 //ora anche ref è 2


void redub(int *arr){
    *arr *=2;
}

//La reference da accesso al valore puntato dall'indirizzo di memoria dell'elemento passato alla funzione
void redub2(int &arr){
    arr *=2;
}

redub(&a);
redub2(a);  
//Queste due funzioni funzionano nello stesso identico modo
    
```

 NB: Usando le reference si evita anche l'overhead dato dalla copia di oggetto. **Se possibile usa sempre le references**



### L values and R values

Un L value  è un oggetto che ha un nome, può avere un indirizzo ed è modificabile se non const.

Un R value (roba che va solo a destra di = in assegnazione) è tutto ciò che non è un L value. Un R value può essere assegnato esplicitamente a un L value

A una L value reference  possiamo assegnare solo un L value (quindi una variabile ad esempio)

# Recap

|      | Left                  | Right                            |
| ---- | --------------------- | -------------------------------- |
| *    | Definizione puntatore | Operatore di deferenziazione     |
| &    | Definizione reference | Restituisce indirizzo di memoria |

