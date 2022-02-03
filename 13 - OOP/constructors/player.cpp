#include <iostream>
#include <string>

class Player{
    private:
        std::string name;
        int health;
        int xp;
    public:
        void set_name(std::string name){
            this->name=name;
        }
        void set_health(int i){
                health=i;
            }
        void set_xp(int i){
                xp=i;
            }
        void print(){
            std::cout << name << ":" << health << "PV,"<< xp<< "xp" << std::endl;
        }
    	//Costruttori
        Player();
        Player(std::string str){
            set_name(str);
        };
        Player(std::string str, int health_val, int xp_val){
            set_name(str);
            set_health(health_val);
            set_xp(xp_val);
        };
    	//In questo modo abbiamo 3 diversi modi per 			costruire un'istanza

    	//Distruttore
        ~Player(){
            std::cout<<"Object destroyed"<<std::endl;
        };
};
int main(){

    Player *doom_slayer {};
    doom_slayer = new Player("Doom Slayer", 100, 100);
    doom_slayer->print();
    delete doom_slayer; //Stampa "object destroyed"

    return 0;

}