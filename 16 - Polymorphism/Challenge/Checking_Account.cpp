#include "Checking_Account.h"
#include "Account.h"
#include <string>

bool Checking_Account::withdraw(double amount){
    amount=amount-fee;
    return Account::withdraw(amount);
}
Checking_Account::Checking_Account(std::string name, double balance):
    Account{name,balance}{}

bool Checking_Account::deposit(double amount) {
    return Account::deposit(amount);
}