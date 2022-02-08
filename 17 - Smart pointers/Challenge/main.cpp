/*
Create a program that has the following:

1.Funzione make che crea e ritorna unique_ptr a un vettore di shared pointers a Test objects.

2. Funzione fill che prende vettore di shared pointers a Test objects e un int (numero di oggetti Test da creare dinamicamente e aggiungere al vettore)

3. Funzione display che prende vettore di shared_ptrs a  oggetti Test mostra i dati di ogni oggetto Test


Below is a sample run for the user entering 3 at the console:
How many data points do you want to enter: 3
Enter data point [1] : 10
        Test constructor (10)
Enter data point [2] : 20
        Test constructor (20)
Enter data point [3] : 30
        Test constructor (30)
Displaying vector data
=======================
10
20
30
=======================
        Test destructor (10)
        Test destructor (20)
        Test destructor (30)

I am providing the function prototypes in the code.
However, feel free to modify these as you wish.
Have fun and experiment!


*/

#include <memory>
#include <vector>
#include <iostream>

class Test {
private:
    int data;
public:
    Test(){
        std::cout << "Enter data point : ";
        std::cin >> data;
        std::cout << "\tTest constructor (" << data << ")" << std::endl;
        }
    Test(int data) : data {data} { std::cout << "\tTest constructor (" << data << ")" << std::endl; }
    int get_data() const {return data; }
    ~Test() {std::cout << "\tTest destructor (" << data << ")" << std::endl; }
};


std::unique_ptr<std::vector<std::shared_ptr<Test>>> make();
void fill(std::vector<std::shared_ptr<Test>> &vec, int num);
void display(const std::vector<std::shared_ptr<Test>>&vec);

int main() {
    std::unique_ptr<std::vector<std::shared_ptr<Test>>> vec_ptr;
    vec_ptr = make();
    std::cout << "How many data points do you want to enter: ";
    int num;
    std::cin >> num;
    fill(*vec_ptr, num);
    display(*vec_ptr);
    return 0;
}