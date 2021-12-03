# 05 - structure of a program

## Preprocessore

Il preprocessore è un programma che processa il source code prima del compilatore.

Le direttive al preprocessore sono all'inizio del programma e iniziano con un cancelletto #

E' possibile usare le direttive al preprocessore per fare compilazione condizionale (ovvero cambiare le istruzioni di compilazione, includere o escludere librerie, etc. a seconda se delle condizioni siano sodddisfatte o meno)

**Il preprocessore NON sa nulla del C++ e del codice sorgente, segue solo le direttive assegnate**

## Commenti

I commenti si aggiungono con // oppure se vogliamo aggiungere più linee di commento

```cpp
/* 
QUESTO E' UN COMMENTO
*/

//Questo è un commento inline
```

## Main function

Tutti i programmi in c++ devono contenere esattamente 1 funzione main: è il punto di partenza per l'esecuzione del programma. Il return 0 comunica semplicemente al sistema operativo la corretta esecuzioen del programma

## Namespaces

Per evitare conflitti nei nomi delle variabili e funzioni è possibile raggruppare tutti questi elementi in dei namespace. Per accedere agli elementi del namespaces va usato l'operatore ::

std è il namespaces della standard library.

```cpp
// cout è una funzione della standard library quindi scriveremo
std::cout<<"ciao";

// volendo possiamo anche evitare di scrivere std:: ogni volta tramite
using namespace std;
cout<<"prova":
//in questo modo l'intero namespace della standard library viene importato e non c'è più bisogno di chiamarlo esplicitamente ogni volta
```

NOTA che potrebbe essere una pessima idea importare un intero namespaces nel caso di grandi progetti, potrebbero facilmente crearsi conflitti.



Un modo per importare solo alcuni elementi di un namespace è

```cpp
using std::cout;
cout <<"prova";
// in questo modo è stato importato solo cout da std ma non tutto il resto degli elementi
```

Questo riduce la possibilità di conflitti ma potrebbe essere ugualmente pericoloso 

## I/O

Abbiamo già visto che cout e cin sono i comandi di std adibiti all' input e all' output.

Il cin può essere concatenato, ovvero è possibile mettere l'input in più variabili

```cpp
cin >> var1 >> var2;
// in questo modo all'utente verranno chieste in ordine due variabili diverse
```

