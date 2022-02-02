#include <iostream>

//using namespace std;
void redub(int *arr){
    *arr *=2;


}

void redub2(int &arr){
    arr *=2;


}


int main(int argc, const char** argv) {
    size_t size=5;
    int arr = 1;
    redub(&arr);
    std::cout << arr << std::endl;
    redub2(arr);
    std::cout << arr << std::endl;



}