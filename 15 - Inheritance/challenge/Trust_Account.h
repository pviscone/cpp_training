#ifndef _TRUST_ACCOUNT_H_
#define _TRUST_ACCOUNT_H_
#include "Savings_Account.h"
#include <string>

class Trust_Account : public Savings_Account{
    private:
        int num_withdrawal{0};
        static constexpr const char *def_name = "Unnamed Savings Account";
        static constexpr double def_balance = 0.0;
        static constexpr double def_int_rate = 0.0;
    public:
        bool deposit(double amount);
        bool withdraw(double amount);
        Trust_Account(std::string name = def_name, double balance =def_balance, double int_rate = def_int_rate);
};
#endif // !_TRUST_ACCOUNT_H_