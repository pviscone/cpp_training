#include <iostream>
#include <vector>
using namespace std;
int main(int argc, const char** argv) {
    vector <int> v {1,2,3};
    v.push_back(4);
    //cout << v ;
    for (int i=0; i<v.size(); i++) {
        cout << v[i] << endl;
    }
    return 0;
}