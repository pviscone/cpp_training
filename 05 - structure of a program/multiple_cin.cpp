#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main(int argc, const char** argv) {
    double var1, var2;
    // in questo modo all'utente verranno chieste in ordine due variabili diverse
    cin >> var1 >> var2;
    cout << "var1: " << var1 << "  var2: "<< var2 << endl;
    return 0;
}