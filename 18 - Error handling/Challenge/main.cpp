/*

1) Crea IllegalBalanceException ereditando da std::exception
e implementa metodo what

2) classe Account deve fare il throw dell'eccezione se il bilancio è negativo

3) crea InsufficentFundsException derivando da std::exception e implementa metodo what

4) Account deve fare il throw dell'eccezione se il withdraw porta a un bilancio negativo

*/

#include <iostream>
#include <memory>
#include "Account.h"
#include "Checking_Account.h"
#include "Savings_Account.h"
#include "Trust_Account.h"
#include "Account_Util.h"

using namespace std;

int main() {
    // test your code here
    std::cout << "Program completed successfully" << std::endl;
    return 0;
}

