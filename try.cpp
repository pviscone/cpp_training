#include <iostream>
using namespace std;

template <typename T>
T maxim(T x, T y){
    return x > y ? x : y;
}


int main(int argc, const char** argv) {
    int a{10};
    int b{20};
    cout << maxim<int>(a, b) << endl;
    return 0;
}
