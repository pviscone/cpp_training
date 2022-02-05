/*Scrivi funzione apply_all che prende due array
di interi, le loro size e alloca dinamicamente
un nuovo array che è il prodotto dei due.
La funzione deve restituire il puntatore al nuovo array.

Scrivi anche una funzione print che prende un puntatore
all'array di interi e la size e mostra gli elementi

*/
#include <iostream>

int *apply_all(int *arr1, int *arr2, size_t size){
    int *new_arr {nullptr};
    new_arr = new int[size];
    for (size_t i {0};i<size;i++){
        new_arr[i]=(arr1[i])*(arr2[i]);
    }
    return new_arr;
}

void print(int *arr,size_t size){
    std::cout << "( " ;
    for(size_t i{0}; i<size; i++){
        std::cout << (arr[i]) << ", ";
    }
    std::cout << ")\n" << std::endl;
}

int main(){
    size_t size{10};
    int arr1[] {1,2,3,4,5,6,7,8,9,10};
    print(arr1,size);
    int *new_arr=apply_all(arr1,arr1,size);
    print(new_arr,size);
    return 0;
}