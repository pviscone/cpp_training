# Flusso 

## Alternative

### if else

```cpp
if (expression){
	//statement;
}
else if (expression){
	//statement;
}
else{
	//statement;
}
```

L'if else, nel caso serva per fare un assegnamento a una variabile, può essere usato anche con i **conditional operator**

```cpp
nome_variabile = (condizione) ? espressione_true : espressione_false
```



### switch

```cpp
switch (nome_variabile){
    // si intende nome_variabile==expression_1
    case expression_1: statement_1; break;
    case expression_2: statement_2; break;
    //...
    // viene eseguito default se nessuna espressione nei case è soddifatta
    default: statement_default; //opzionale (ma bene metterlo) e non richiede break
        
}
```

Se non si inseriscono i break tutto il codice dopo il case soddisfatto verrà eseguito finchè non si incontra un break

## Looping

### For loop

```cpp
for (initialization; condition; increment){
    //statement;
}

//Esempio classico, si può usare anche int i {0} (inizializz. moderna)
for(int i=0; i<10; i++){}
```

**N.B** la variabile contatore ESISTE SOLO NEL LOOP, al di fuori non esiste

### Range based for loop

Introdotto in C++11, looping su iterabili

```cpp
int array [] {1,2,3};
for (int element: array){
    cout << element <<endl;
}
//stampa uno ad uno gli elementi dell'array, al posto di int elements puoi mettere più semplicemente auto
```

### While

```cpp
while (boolean_expression){
    //statement;
}
```

 ### do while

```cpp
do {
    //statement;
} while (boolean_expression)
```

In questo caso, a differenza del while, il controllo della boolean_expression avviene alla fine del blocco do non prima dell'inizio degli statements nel loop.

Può essere utile in alcuni casi

### Continue, break

continue: il resto delle istruzioni nel loop vengono ignorate e il codice rinizia dal loop successivo

break: il loop viene terminato