 

# Funzioni

tipo nome (tipo_variabile var_name){

return

}

NB ogni volta che si passa qualcosa a una funzione il compilatore fa una cipoia degli argomenti (può avere alto effort)

## Prototipi

Il compilatore deve sapere della funzione prima che sia chiamata. 

Può essere pratico usare i prototipi soprattutto negli header files

```cpp
int function_name(int,float,...); //prototipo
//nell'argomento del prototipo ci vanno i tipi degli argomenti
```

I prototipi vengono posti all'inizio del programma (o in un header file) per essere sicuri che le funzioni siano definite a dovere, se i prototipi sono presenti all'inizio del programma l'ordine con cui le funzioni vengono definite non importa

## Default arguments

Possono essere inseriti o nel prototipo (meglio) o nella definizione, non in entrambi. Tutti i default arguments vanno messi per ultimi

```cpp
void func(int var1, int def1=0 , int def2=0);
void func(int var1, int def1 , int def2){
    //statements
}
```

!!!VEDI FUNZIONI VARIADICHE

## Overloading

Possiamo avere diverse funzioni con lo stesso nome ma diversi parametri. Il compilatore è in grado di distinguerle in base ai parametri passati. E' una prima forma di polimorfismo, si può avere un comportamento diverso in base ai tipi di dati passati

```cpp
void tipo(int a){
    cout << "intero" <<endl;
}
void tipo(float a){
    cout << "float" <<endl
}
```

## Passare array a funzioni

```cpp
void func (int numbers[], size_t size){
    for (size_t i=0;i<size,i++){
        cout << numbers[i]<<endl;
    }
}
```

Passando un array a una funzione non verranno copiati gli elementi degli array poichè il nome dell'array localizza solo l'indirizzo di memoria. 

Quello che viene copiato è l'indirizzo di memoria, serve la size per loopparci sopra.

ATTENZIONE: poichè alla funzione viene passato l'indirizzo di memoria se la funzione fa delle modifiche sul parametro numbers[] le farà anche sull'array originale che gli abbiamo passato. Se non vogliamo che questo accada o si fa manualmente una copia dell'array o si usa come parametro un const type in modo tale che se la funzione prova ad effettuare modifiche il compilatore darà errore.

Un altro modo è usare i vettori al posto degli array. Se passi un vettore a una funzione fai comunque una copia del vettore

## Pass by reference

E se invece vogliamo modificare i dati passati alla funzione all'interno della funzione come succede negli array?

In questo caso bisogna passare alla funzione l'indirizzo di memoria del dato ovvero una reference, in questo modo non si effettua nessuna copia del dato

```cpp
int i=1;
void func(int &var){
    var=0;
}
func(i); //i ora è 0

```

## Scopes

Le variabili sono visibili solo all'interno del proprio blocco (coppia di parentesi graffe).

Le variabili locali delle funzioni non sono condivise tra varie function call ma è possibile creare delle variabili che lo siano, le **static**. Queste sono preservate tra varie function calls e vengono inizializzate alla prima call

```cpp
void func(){
    static int i=0;
    cout << i << endl;
    i++;
}
func();//stampa 0
func();//stampa 1
func();//stampa 2
```

E' possibile anche creare variabili **globali**, basta dichiararle al di fuori di qualsiasi funzione o blocco

## Function calls

Le funzioni usano un'area di memoria chiamata function call stack che funziona come una pila fatta a strati.

Ogni volta che una funzione è chiamata viene aggiunto (pushato) un activation record (tutto ciò che riguarda la funzione) in cima allo stack. Quando la funzione  è terminata viene rimossa (pop) dallo stack.

**Lo stack size è finito, se si supera si ha lo Stack Overflow**

La memoria è fatta a strati. Alla base c'è il codice, poi le static variables, poi stack e infine heap

## Inline functions

E' possibile generare funzioni inline per evitare l'overhead della chiamata a funzione, generare codice assembly in line e migliorare le prestazioni.

Spesso questo si paga con codice binario ridondante e quindi i file binari compilati sono più grandi

```cpp
inline void func(){}
//in questo modo ogni volta che chiamo la funzione il compilatore sostituisce il codice al suo posto evitando il function call overhead
```

