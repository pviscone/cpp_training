#ifndef _CHECKING_ACCOUNT_H_
#define _CHECKING_ACCOUNT_H_
#include "Account.h"
#include <string>

class Checking_Account : public Account{
    private:
        static constexpr double fee=1.5;
        static constexpr const char *def_name = "Unnamed Savings Account";
        static constexpr double def_balance = 0.0;
    public:
        virtual bool withdraw(double amount) override;
        virtual bool deposit (double amount) override;
        Checking_Account(std::string name=def_name, double balance=def_balance);
        virtual ~Checking_Account()=default;
};

#endif // !_CHECKING_ACCOUNT_H_
