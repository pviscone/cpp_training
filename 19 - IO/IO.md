# I/O

Lo stream è una sequenza di byte ed è indipendente dai dispositivi che si hanno in input o output

Gli header più comuni sono

- iostream: fornisce istruzioni per inviare/ricevere input/output formattato da/verso lo stream
- fstream: fornisce istruzioni per inviare/ricevere input/output formattato da/verso i file stream
- iomanip: fornisce istruzioni per manipolare la formattazione dello stream IO

Le classi di stream più usate sono

- ios: Classe base che supporta diverse operazioni basi su IO formattato e non
- ifstream: Operazioni di input su stream file based
- ofstream: Operazioni di output su stream file base
- fstream: Derivata di ifstream e ofstream, operazioni IO su file
- stringstream: IO su stringhe memory based (derivata di istringstream e ostringstream)

**Global stream object**

Sono oggeti globali inclusi in *iostream* quindi inizializzati prima dell'esecuzione del main

- cout: istanza di ostream (di default connesso alla console (output)) (buffered)
- cin: istanza di istream (di default connesso alla tastiera) (buffered)
- cerr: istanza di ostream (unbuffered)
- clog: istanza di ostream  (unbuffered)

Buffered vuol dire che l'input viene acquisito alla pressione di invio e cout stampa solo quando lo stream subisce un flush (usando std::endl).
Unbuffered vuol dire che le operazioni di IO vengono eseguite appena richiesto

## Stream manipulator

Gli stream hanno diversi metodi utili alla formattazione. La maggior parte di questi si presentano sia in forma di metodi che di manipolatori. Per usarli bisogna includere *<iomanip>*

```cpp
#include <iomanip>
std::cout.width(10); //member function
std::cout << std::setw(10); //manipulator (ottenuto tramite overloading di <<)
```

Alcuni manipulator, per diversi tipi, sono

- **Bool**: boolalpha, noboolalpha (per stampare booleani tramite 0,1 oppure tramite true, false)

  Di default sono 0 e 1. Per cambiare e mostrare true o false basta inserire nel programma il manipolatore boolaplha (modifica tutti i booleani stampanti da quel punto in poi)

  ```cpp
  // Versione con i manipolatori
  std::cout << std::boolalpha;
  std::cout << (1==2) <<std::endl; //printa "false"
  std::cout << std::noboolalpha; // ritorna alla modalità 0/1
  std::cout << (1==2) <<std::endl; //printa "0"
  
  //Versione con i metodi
  std::cout.setf(std::ios::boolalpha);
  ```

- **Int**: dec,hex,oct,showbase,noshowbase (riguardano la base, i prefissi sono 0x per esadecimali e 0 per ottali)

   	 showpos,noshowpos (mostra o non mostra il simbolo + davanti i numeri positivi)

  Questi manipolatori modificano tutti i cout dal loro punto in poi

  ```cpp
  std::cout << std::hex // per cambiarebase
  std::cout << std::showbase //mostra base prefisso
  ```

- **Floating point**: fixed (numero di cifre dopo la virgola)

  ​						  setprecision (numero di cifre (default 6))

  ​						  scientific (notazione scientifica)						  

  ```cpp
  using namespace std;
  // numero cifre totali N
  cout << setprecision(N);
  
  // numero cifre dopo la virgola (M)
  cout << setprecision(M) << fixed; 
  
  //notazione scientifica
  cout << scientific;
  ```

- **Justification and fill**: left,right (giustifica a dx o sx),setw,internal, setfill (specifica con quali caratteri riempire le giustificazioni. Di default whitespace)

  A differenza dei manipolatori di prima questi modificano solo l'elemento sullo stream immediatamente successivo  (tranne fill che funziona come quelli di prima )

  ```cpp
  //modifica tutti riempimenti da ora in poi
  cout << setfill("-");
  
  //setw(N) posiziona ultimo carattere in posizione N-esima a destra
  cout << setw(10) << "ciao" <<endl; //stampa "------ciao"
  
  //giustifica a sinistra
  cout << setw(10) << left << "ciao" <<endl; //stampa "ciao------"
  
  ```

  C++20 ha nuove istruzioni che facilitano la formattazione

- * **Others**: endl, flush (fa il flush come endl ma non fa a capo), skipws, noskipws,ws (riguardano la manipolazione degli whitespace)

**NB** Per ogni tipo sono presenti delle flag di reset per rimettere le impostazioni di  default. Non le ho scritte tanto inutili imho

## Leggere da file

Necessario includere *ifstream* e inizializzare un oggetto.  E' possibile anche usare il metodo open 

```cpp
#include <ifstream>
std::ifstream in_file;
std::string file_path;
std::cin >> file_path;
in_file.open(file_path);

//possiamo fare anche un cotnrollo (verificare se il file esiste)
if (in_file.is_open()){
    //DO things
}else{
    //Gestisci il problema
}
in_file.close(); //CHIUDI IL FILE
    

//OPPURE APRI TRAMITE INIZIALIZZAZIONE
std::ifstream in_file{"./my_file.txt", std::ios::in}; 
//std::ios::in è la modalità di default, se la ometti non cambia niente ma può essere utile avere altre modalità come "std::ios::in | std::ios::binary" per leggere file binari
```

Per leggere da un file basta usare l'operatore >>  ma viene abbastanza scomodo, conviene usare getline

```cpp
std::string line{};
std::getline(in_file,line); //mette una riga alla volta la riga del txt nella stringa line
```

```cpp
//LEGGERE FILE UNA RIGA ALLA VOTLA
std::ifstream in_file{"./my_file.txt"};
std::String line {};

if (!in_file){ //Controlla se file aperto
    std::cerr << "File open error" << endl;
    return 1;
}
while (!in_file.eof()){  //Finchè non è finito il file
    std::getline(in_file,line);
    std::cout << line << std::endl
}
```

E' possibile anche leggere un carattere alla volta, basta usare il metodo get al posto di getline

```cpp
//ESEMPIO:_ file con elementi in colonna (3 colonne)
//in questo caso conviene usare l'operatore >> e per leggere il file basta
while(in_file >> elem1 >> elem2 >> elem3){
    //Fai cose
}
//In questo modo ad ogni passo del ciclo vengono immagazinate nelle 3 variabili gli elementi presenti nelle colonne riga per riga
//Quando si arriva all'eof il while is ferma
```

## Scrivere su un file

Di default se il file non esiste viene creato e se esiste viene sovrascritto. bisogna includere *ofstream*

```cpp
#include <ofstream>
std::ofstream out_file {"./my_file.txt",std::ios::out} //modalità di default, può anche essere omessa

```

Per aggiungere cose al file invece di sovrascriverlo bisogna usare la modalità std::ios::app

Anche qui è possibile usare il metodo open (utile nel caso il filename venga fornito a posteriori)

```cpp
std::ofstream out_file;
out_file.open(filename, std::ios::app); //per aggiungere al file
```

Di nuovo, anche qui è possibile usare is_open per verificare la corretta apertura e close per chiudere il file

Per scrivere nel file basta usare l'operatore <<

```cpp
out_file << var1 << "\n"
    	 << var2 << "\n" << std::endl;
```

Per scrivere un carattere alla volt ainvece bisogna usare metodo put al posto di get

## String streams

E' un potente strumento che permette di leggere stringhe in memoria come se stessimo leggendo o scrivendo file 

Bisogna includere sstream e dichiarare un oggetto stringstream, isstringstream o ostringstream

```cpp
#include <sstream>
//leggere da stringstream
std::string info {"Mario	10	20"};
std:istringstream iss{info};
int num{}; std:string name{}; int total{};
iss >> name >> num >> total;

//Scrivere a stringstream
int num{10}; std:string name{"Mario"}; int total{20};
std::ostringstream oss{};
oss << name << " " << num << " " << total;
std::cout << oss.str() << std::endl; //metodo str trasforma in stringa
```

Queste operazioni possono essere utili anche per validare gli input, ad esempio se mettiamo il valore di una stringstream in un int (esempio) possiamo usarlo in un if come controllo

```cpp
std::string input{};
std::cin >> input;
std::stringstream strstr{input};
int int_value{};
if(strstr >> int_value){
    //E' intero
}
else{//Non è intero}
```

