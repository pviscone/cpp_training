#include <iostream>
using namespace std;

class ClassName{
    private:
        int *i_ptr;
    public:
        int get_i(){
           return *i_ptr;
        }
        ClassName(int i){
            i_ptr= new int;
            *i_ptr=i;
        }
        ClassName(const ClassName &cls)
            :ClassName{*cls.i_ptr}{
            cout<<"pointer copied"<<endl;
        }
        ~ClassName(){
            delete i_ptr;
            cout << "destroyed" <<endl;
        }
};

void display(ClassName cls){
    cout << cls.get_i() <<endl;
}

int main(){
    ClassName obj1{1}; //puntatore i_ptr creato
    display(obj1); //Viene creata una copia dell'oggetto e anche del puntatore i_ptr di obj1 nello stack (scope della funzione display).
    //Quando esce dalla funzione la variabile locale di display (cls) viene distrutta quindi viene sia distrutto il puntatore nello stack che i dati a cui punta nello stack e viene stampato "destroyed"
    
    //Problema, il dato distrutto è lo stesso di quello a cui punta i_ptr di obj1, che ora punta a un'area di memoria invalida
    
    ClassName obj2{obj1}; //Copia i_ptr di obj1 in obj2 ma i_ptr punta a un'area di memoria invalida
    
    return 0; //Gli oggetti vanno fuori scope e vengono distrutti. Ma l'aree di memorie puntate dagli i_ptr sono invalide e il programma crasha
}