# 07 - Array and Vectors

## Array

Un array è una collezione di elementi dello stesso tipo.

Gli array hanno:

- lunghezza fissa
- elementi dello stesso tipo
- sono memorizzati in una sezione contigua di memoria
- non c'è alcun check nel caso di out of bounds

Gli array sono molto efficienti in quanto gli elementi sono memorizzati in una sezione contigua di memoria

### Inizializzazione

La dimensione dell'array deve essere una costante (quindi o un numero vissato o una variabile const)

La dimensione dell'array va messa tra parentesi quadre

```cpp
// Inizializzazione di un array di tipo int di dimensione 5
int array [5] {1,2,3,4,5};

// per inizializzare tutto a 0
const int size {1000};
int array [size] {0};

// la size può essere anche automaticamente calcolata
int array [] {1,2,3,4,5};

```

### Accesso agli elementi dell'array

Per accedere un elemento dell'array

```cpp
int array [5] {1,2,3,4,5};
cout << array[2] << endl;
// printa 3

//lo stesso può essere fatto per immagazzinare valori con cin
```

Il nome dell'array rappresenta l'indirizzo di memoria del primo elemento dell'array. Chiamando l'indice con le parentesi quadre il compilatore va a cercare l'elemento in memoria nella posizione start+index*sizeof(type)

### Multidimensional array

Basta aggiungere un'altra parentesi quadra

```cpp
// matrix [righe] [colonne]
float matrix [2][3] 
{
    {1,2,3},
    {4,5,6},
    {7,8,9}
} ;
```

## Vettori

Un vettore è un conteiner della c++ standard library.

E' un array la cui lunghezza è modificabile a tempo di esecuzione. 

Inoltre **E' dotato di checking nel caso di out of bounds MA non se usiamo [ ] per accedere agli elementi NON abbiamo nessun tipo di check, esistono altri metodi  ** ed ha associato numerosi medoti per manipolare i dati (sort, reverse, find,erase,...)

Come gli array i vettori sono memorizzati in sezioni di memoria contigue

### Inizializzazione

E' necessaria la direttiva include <vector>

```cpp
#include <vector>

//In questo modo si inizializza un vettore vuoto che non contiene elementi
std::vector <int> vettore;

//Possiamo fissare anche la grandezza del vettore
std::vector <int> vettore (10);

//Per inizializzare un vettore con degli elementi
std::vector <int> vettore {1,2,3,4,5};

//Si può anche inizializzare un vettore con grandezza fissata con tutti gli elementi a un valore fissato
std::vector <double> vettore (1000, 3.14)
```

### Accesso e modifica di un vettore

Come gli array si può accedere agli elementi di un vettore con le quadre MA esistono altri modi

```cpp
// array like
vettore[5];

// metodo at (può essere utilizzato anche per assegnare valori)
vettore.at(5)

```

con at se andiamo out of bound il programma raiserà una exception a runtime

I vettori hanno un metodo **push_back** che appende nuovi elementi in coda al vettore

```cpp
vector <int> vettore {1,2};
vettore.push_back(3);

for (int i=0; i<vettore.size; i++){
    cout << vettore[i];
}
// printa 1 2 3 
```

Nel caso ci sia spazio in memoria alla fine dell'array l'elemento viene aggiunto in coda alla sezione di memoria ALTRIMENTI il vettore va copiato in una sezione di memoria più grande e lo spazio precedente deallocato

Tipicamente quando questo è necessario viene copiata in una sezione di memoria più grande di un fattore 1.5 o 2 (dipende dall'implementazione) della memoria originale

Può essere utile quindi preallocare il vettore con vettore.reserve(32) (dove 32 è il numero di elementi, detta capacità) in modo tale da evitare le prime reallocazioni del vettore (Arrivato a un certo punto inizia ad aggiungere una capacità costante per evitare di sprecare troppa memoria)