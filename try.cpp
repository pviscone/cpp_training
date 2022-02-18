#include <iostream>
#include <array>
using namespace std;

template <typename T>
T maxim(T x, T y){
    return x > y ? x : y;
}


int main(int argc, const char** argv) {
    int a{10};
    int b{20};
    cout << maxim<int>(a, b) << endl;


    const int size {5};
    array<int, size> arr {1,2,3,4,5};
    cout << arr[2] << endl;
    return 0;
}
