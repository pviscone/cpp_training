#include "Vector.h"
#include <iostream>

void Vector::set_values(double a, double b){
    x = a;
    y = b;
}

void Vector::print(){
    std::cout << "(" << x << ", " << y << ")" << std::endl;
}