# 04 - Getting started

#include <iostream> è un adirettiva al preprocessore che permette di importare le istruzioni necessarie per eseguire le operazioni di input output

**std::endl** equivale ad aggiungere alla fine "\n" e in più a fare il flush del buffer (si assicura che non ci sia più traccia della roba printata in una memoria temporanea). ATTENZIONE: il flush potrebbe diventare un bottleneck del programma. Evita se va fatto spesso

```cpp
//printare. Le stringhe/variabili si concatenano con il <<
std::cout<<"stringa"<< variabile <<std::endl;
//chiedere un input
double number;
std::cin >> number;
```

Gli operatori << e >> servono a indirizzare o a estrarre dati dallo stream I/O

## Compilare

Il modo più semplice di compilare è g++ ./nome.cpp -o ./nomeoutput