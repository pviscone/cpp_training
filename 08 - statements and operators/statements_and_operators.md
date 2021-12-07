# 08 - Statements and Operators

## Operatori

### Assegnamento

Con = è possibile assegnare un valore a una variabile

```cpp
//lhs è la variabile (che il programma vede come un idirizzo di memoria) e rhs il valore assegnato
lhs=rhs;
```

E' possibile anche fare assegnazioni del tipo 

```cpp
// Le assegnazioni vengono fatte in ordine da destra a sinistra
num1=num2=100;

//num1=num2 assegna a num1 il valore di num2, SE cambia num2 dopo l'assegnazione NON cambia anche num1
```

### Aritmetiche

- +
- -
- *
- / (sugli interi prende la parte intera della divisione)
- % modulo (funziona solo con interi)

### Incremento e decremento

- ++ (incrementa di 1)
- -- (decrementa di 1)

```cpp
//L'uso come prefisso o postfisso è differente

//Printa a e poi fa a+1
cout << a++;

//Prima fa a+1 e poi printa il nuovo valore di a 
cout << ++a;
```

```cpp
int counter {10};
int result {0};

result = counter++ + 10;
//Questo equivale a:
result= counter + 10;
counter = counter + 1; 

result = ++counter + 10;
//Equivale a:
counter = counter + 1;
result = counter + 10;
```

### Compound assignment

```cpp
// Vale con un qualsiasi operatore seguito da =
a+=10;
//Equivale a:
a=a+10;
```

### Relazionali 

< , > , ==,  !=, <=, >= 

### Logici

- ! NOT
- || OR
- && AND

C++ valuta le espressioni booleane da sinistra a destra e calcola solo ciò che è necessario ignorando il resto

```cpp
//Esempio: Questa torna false senza che la funzione sia calcolata poichè l'elemento a sinistra è falso
(5==10) && funzione_complicatissima();

//Questa torna True senza calcolare la funzione poichè lo è il primo elemento a sinistra
(5==5) && funzione_complicatissima();

```

### Bitwise operators

Ricorda che le operazioni logiche operano su booleani mentre gli operatori bitwise funzionano (sui bit) di numeri interi e tornano numeri interi

- & AND
- | OR
- ^ XOR
- ~ NOT
- << shift bit a sinistra
- \>> shift bit a destra