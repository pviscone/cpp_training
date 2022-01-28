# Characters and strings

La libreria **cctype** include numerose funzioni per manipolare le stringhe

Esempi:

```cpp
#include <cctype>
using namespace std;
//Testing function, ritornano valori booleani
isalpha(c);
isalnum(c);
isdigit(c);
islower(c);
isupper(c);
isspace(c);
//ritorna caratteri in maiuscolo o minuscolo
tolower(c);
toupper(c);
```

## C style strings

Sono sequenze di caratteri memorizzate in sezioni contigue di memoria (C style array di caratteri) terminate da un Null character (solitamente \0)

```cpp
char name[] {"C style string"}
```

NB: 

- La size è fissata ma volendo, se serve, si può allocare una size maggiore di quella occupata dai caratteri (name[100] per 100 caratteri, tutti gli elementi oltre i caratteri sono Null character)
- Dopo aver dichiarato una stringa non si può fare l'assegnamento name="C style strings", o lo si fa carattere per carattere tramite loop oppure si usa la funzione strcpy(name,"C style string")

Per manipolare le c style strings esistoe la libreria  **cstring** ma pace.

Alcune funzioni sono:

- strcpy(str1,str2) per copiare
- strcat(str1,str2) per concatenare
- strcmp(str1,str2) per comparare
- strlen(str) lunghezza stringa

Un' altra libreria è **cstdlib** per convertire le C style strings in altri tipi come int, float, etc.

NON USARE MAI QUESTE PORCHERIE (solo in ambito embedded)

## C++ strings

Sono contigue in memoria e hanno size dinamica.

```cpp
#include <string>
using namespace std;

string s1 {"C++ string"};
string s2 {"string",3} // è "str"
string s3 {s1}; //è "C++ string" in una diversa area di memoria
string s4 {s1,1,4} // è "++ s"
string s5 {3,"XO"} // è "XOXOXO"
```

Con le C++ string si può tranquillamente usare l'assegnazione dopo la dichiarazione 

```cpp
string s1;
s1="stringa" //è legale
```

sono anche iterabili quindi è possibile loopare su di loro

```cpp
string s1 {"loop"};
for(char c: s1){
    cout <<c<<endl; // stampa un carattere per volta
}
// se al posto di char c uso int printa l'ascii code associapo al carattere
```



### operatori e metodi  su stringhe

- **Concatenare**: E' possibile usare l'operatore +

  ```cpp
  string s1 {"str1"};
  string s2 {"str2"};
  str conc = s1+" "+s2; // è "str1 str2"
  
  //NB scrivere "str1" + "str2" non funziona in quanto vengono considerate C style strings
  ```

- **Comparare** con ==,!= l'uguaglianza, con <,>,<=,>= si compara il loro ordine alfabetico

- metodo **substr**: object.substr(start_index,length), funziona come gli slicing di python

- metodo **find**: object.find(substring) ritorna l'indice dell'inizio della sottostringa

- metodo **erase**: object.erase(start_idx,end_idx) rimuove i caratteri negli indici selezionati

- metodo **lenght**: object.lenght() ritorna la lunghezzza

- cin: per leggere una stringa da terminale cin ha il problema che tronca la stringa se vede uno spazio (vero anche per c style string).

  Per leggere una stringa usare **getline**

  ```cpp
  string s1;
  getline(cin,s1); //legge fin \n
  
  // volendo si può inserire un delimiter
  getline(cin,s1,"m") //legge finchè non trova una "m"
  ```

  

N.B: in generale per memorizzare indici e cose simili usa size_t al posto di int