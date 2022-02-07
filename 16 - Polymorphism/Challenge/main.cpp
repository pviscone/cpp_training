/*
1) modifica la classe Account in modo da renderla astratta rendendo deposit e withdraw virtuali pure

2) Crea classe interfaccia  I_Printable che overloada << e forisce metodo print a tutti

3) Modifica le funzioni in Account_Util in modo tale da avere una sola versione per tutte le classi

4) Prova a usare sia base class pointers che oggetti locali
*/
#include <iostream>
#include <vector>
#include "Account.h"
#include "Savings_Account.h"
#include "Checking_Account.h"
#include "Trust_Account.h"
#include "Account_Util.h"

int main(){

    std::vector<Savings_Account> sav_accounts;
    sav_accounts.push_back(Savings_Account {} );
    sav_accounts.push_back(Savings_Account {"Superman"} );
    sav_accounts.push_back(Savings_Account {"Batman", 2000} );
    sav_accounts.push_back(Savings_Account {"Wonderwoman", 5000, 5.0} );

    display(sav_accounts);
    deposit(sav_accounts, 1000);
    withdraw(sav_accounts,2000);


    return 0;
}