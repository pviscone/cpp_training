#include <iostream>

//using namespace std;
int main(int argc, const char** argv) {
    float a=10.8;
    int b;
    b=static_cast<int>(a);
    std::cout<<b<<std::endl;
    return 0;
}