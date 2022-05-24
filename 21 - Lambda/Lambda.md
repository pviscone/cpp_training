 # Lambda functions

Le lambda function sono un modo per definire dei funtori (funzioni anonime) inline in modo che il codice sia più leggibile e il compilatore riesca a ottimizzarle meglio

Un uso tipico delle lambda consiste nello scriverle all'interno di algoritmi della STL (come ad esempio std::any()) invece che scrivere funzioni e passarle all'algoritmo

Struttura della lambda:

- Parentesi quadre [ ]: Tramite diverse istruzioni possiamo dire quali elementi vogliamo catturare e se per valore o per reference
- Parentesi tonde ( ): Lista dei parametri
- return_type: tipo da ritornare (E' OPZIONALE, il compilatore può capirlo da solo)
- specifiers: può essere mutable e constexpr
- Parentesi graffe { }: è il codice da eseguire

```cpp
//Struttura di una lambda
[] () -> return_type specifiers {};
```

Per definire una lambda inline e chiamarla serve anche usare l'operatore di chiamata ()

```cpp
//lambda hello_world
[] () {cout << "hi"} ();
//Stampa "hi"
```

Possiamo assegnare la lambda anche a una variabile (in questo caso conviene dichiarare la variabile con auto)

```cpp
auto lamb=[] (int x) ->int {return x+1};
```

## Stateful lambda expression

Queste sono lambda che usano variabili al di fuori del proprio scope

```cpp
int x=1;
int z=[x] (int y) -> int {return x+y}(2);
//z torna 3
```

Le variabili catturate sono catturate come const value quindi non possono essere modificate. Per modificarle è possibile usare la keyword **mutable**

```cpp
int x=1;
[x] () mutable {
    x+=1;
    cout<<x;}(); //printa 2
cout << x; // printa 1
```

Si noti che la variabile è comunque catturata come valore quindi viene copiata. La modifica effettuata nella lambda valee solo all'interno dello scope della lambda, la variabile esterna non viene modificata

Per modificare la variabile anche esternamente dobbiamo catturarla by reference

```cpp
int x=1;
[&x] ()  {
    x+=1;
    cout<<x;}(); //printa 2
cout << x; // printa 2
```

Altri comandi che si possono passare alla captur list sono le default capture:

- [=] : cattura tutte le variabili nello sope by value
- [&] : cattura tutte le variabili nello scope by reference
- [this] : cattura le referenced member variables dell'oggetto corrente

Ma volendo si può mixare, ad esempio [=,&x] significa cattura x by reference e tutto il resto by value

> **Uso del this**
>
> ```cpp
> //Sia NumClass una classe con solo x come attr
> NumClass inst {1}; //Istanzio numclass con inst.x=1
> auto setX(){
>     //con x si intende this->x
>     return [this] (int new_x){x=new_x;};
> }
> auto changeX=inst.setX();
> changeX(2);
> //inst.x ora è 2
> ```
