#include <iostream>
#include <string>

class Player{
    private:
        std::string name;
        int health;
        int xp;
    public:
        Player(std::string name_val, int health_val, int xp_val=100):
            name{name_val}, health{health_val}, xp{xp_val}{
                std::cout<<"Constructor called"<<std::endl;
        };
        void print(){
            std::cout << name << ":" << health << "PV,"<< xp<< "xp" << std::endl;
        }

        ~Player(){
            std::cout<<"I was the only thing they feared"<<std::endl;
        };
};
int main(int argc, const char** argv) {

    Player *doom_slayer {};
    doom_slayer = new Player("Doom Slayer", 100,20);
    doom_slayer->print();
    delete doom_slayer;
    return 0;
}