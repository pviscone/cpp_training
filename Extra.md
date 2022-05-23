# Namespaces

E' possibile creare dei namespace a mano dove poter inserire delle variabili
```cpp
namespace natural_costants{
    float c=1;
    float h_bar=1;
}
cout << natural_costants::c << endl;
//stampa 1
```

# Code convention

Spesso non ci sono delle regole come in python con il PEP8, ogni progetto stabilisce le sue, basta rimanere consistenti.

Alcune regole utili sono:

- L'iniziale delle **funzioni è minuscola**
- L'iniziale di una **classe è maiuscola**
- le variabili sono tutte minuscole e gli spazi sono rappresentati da un underscore \_
- Gli spazi in funzioni e classi sono sostituiti dall'iniziale maiuscola
- Le classi con solo funzioni virtuali finiscono con "Base"

# Compilazione

Alcune flag utili per il compilatore sono:

- -I /header_folder (dove cercare gli header file)
- -L /lib_folder -lib (dove cercare le librerie e quali librerie cercare)

> Per creare una shared libraries
>
> ```bash
> #Compilo
> gcc -c -o lib.o lib.c
> # Creo la shared library
> gcc -shared -o lib.so lib.o
> # Creo l'eseguibile linkando la shared lib
> gcc -L<path to .SO file> -Wall -o code main.c -l<library name>
> 
> # Make shared library available at runtime
> export LD_LIBRARY_PATH=<path to .SO file>:$LD_LIBRARY_PATH
> ```

# Decltype e declvar

E' possibile dichiarare una variabile dello stasso tipo di un'altra variabile con decltype
```cpp
int a=1;
decltype(a) b=2; 
//in questo caso b sarà di tipo int poichè a è int
```

Si può usare anche decltype(auto): è come usare auto ma in più aggiunge aumotaticamente se necessario & o const

declval può essere usato solo all'interno di decltype ed è utile quando all'interno di decltype c'è l'istanza di una classe che richiede degli argomenti. Usando declval si evita di istanziare la classe con dei dati valori

# constexp

sono espressioni che vengono valutate a compile time. Ovviamente tutti i valori all'interno dell'espressione devono essere noti a tempo di compilazione
```cpp
constexpr float x_2(float a) {
    return a*a;
}
float b = x_2(2); //E come scrivere direttamente b=4
```

# Template variadici

Template su un numero arbitrario di tipi

```cpp
template<typename First, typename... Args>
//Specifico anche il tipo che ritorna la funzione con decltype. La sintassi per farlo è la seguente
auto sum_value(const First first, const Args... args)->decltype(first){
    //Assegno tutti i parametri a un container
    const auto values={first,args...};
    //Fai cose con i parametri
}

```

# Tie e structure binding

I valori di una tupla possono essere assegnati a un set di variabili (come unpack di python).

```cpp
std::tie(a,b)=std::tuple(2,3);
//ad a viene assegnato 2, a b 3.
//Credo funzioni su tutti gli iterabili
```

La stessa cosa si può fare in c++17 più facilmente con gli structured binding

```cpp
//analogo del for k,v in tuple di python
for(auto [k,v] : m){}
```

# any

Serve per creare container eterogenei

```cpp
std::vector<std::any> v{};
//in v possiamo metterci oggetti di qualsiasi tipo, anche diversi tra loro.
//L'importante è usare auto quanto si accede a questi elementi o castarli a modo
```

# Multithreading

```cpp
//Per definire un thread
#include <thread>
void func1(){};
void func2(int x){};
int main(){
    std::thread first(func1);
    std::thread second(func2,0);
    
    //metti in pausa finchè thread non finiscono
    first.join();
    second.join();
}
```

Lo stesso può essere fatto in maniera asincrona

**NB** future<type> è un modo per dire che il tipo sarà di tipo tipe ma sarà calcolato solo più avanti

```cpp
#include <future>
std::vector<std::future<int>> futures;
for (int i=0;i<10;++i){
    int parameter=0;
    //async farà partire un thread per elemento
    future.push_back(std::async(std::launch::async,func2,parameter));
	for (auto &e : futures){
        //Ottieni i valori dei thread
        std::cout << e.get() << std::endl;
    }
}
```

Volendo async può essere anche lazy ovvero i thread vengono lanciati solo quando chiamati

# Custom literals

Vogliamo utilizzare una sintassi breve per definire oggetti più complicati (ad esempio 3.4f significa inizializzare o castare un float a 3.4)

Ricorda che i literal definiti dall'utente devono iniziare con un underscore 

```cpp
//Creiamo ad esempio un custom literal per i complessi assegnando come literal _i
struct Complex{
    //Costruttore
    Complex(float r, float i): r(r), i(i) {}
    float r,i;
}
//Custom literals
Complex operator ""_i (float i){return Complex(0,i)};
auto c= 7+4.3_i
```

