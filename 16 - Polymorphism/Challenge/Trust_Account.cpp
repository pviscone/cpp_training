#include "Trust_Account.h"
#include <string>

bool Trust_Account::deposit(double amount){
    if(amount>5000){
        amount=amount+50;
    }
    return Savings_Account::deposit(amount);
}

bool Trust_Account::withdraw(double amount){
    bool valid=true;
    if(amount>balance/5){
        valid=false;
        std::cout << "Your request exceeds the 20% of your balance" << std::endl;
    }
    if(num_withdrawal>3){
        valid=false;
        std::cout << "You have run out of maximum number (3) of withdrawals available" <<std::endl;
    }
    if(!valid){
        return false;
    }
    num_withdrawal++;
    return Savings_Account::withdraw(amount);

}

Trust_Account::Trust_Account(std::string name, double balance, double int_rate):
    Savings_Account{name,balance,int_rate}{}