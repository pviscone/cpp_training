#include <iostream>
#include<string>
using namespace std;

class person{
    protected:
        string name;
        int age;
    public:
        string get_name(){
            return name;
        }
        int get_age(){
            return age;
        }
        void set_name(string name_val){
            name=name_val;
        }
        void set_age(int age_val){
            age=age_val;
        }
        person(string name_val, int age_val){
            name=name_val;
            age=age_val;
        }
};
class student : public person{
    private:
        string curriculum;
        int average_grades;
    public:
        string get_curriculum(){
            return curriculum;
        }
        int get_grades(){
            return average_grades;
        }

        student(string name_val, int age_val, string curriculum_val, int average_grades_val):
            person{name_val,age_val},curriculum{curriculum_val},average_grades{average_grades_val}{}
};

int main(){
    student piero{"piero",24,"Physics",28};
    cout << piero.get_name() << endl;
    cout << piero.get_grades() << endl;
    return 0;
}