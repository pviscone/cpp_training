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

    std::vector<Account*> sav_accounts;
    Account *sav_ptr1 = new Savings_Account{};
    Account *sav_ptr2 = new Savings_Account{"Superman"};
    Account *sav_ptr3 = new Savings_Account{"Batman",2000};
    Account *sav_ptr4 = new Savings_Account{"Wonderwoman", 5000, 5.0};
    sav_accounts.push_back(sav_ptr1);
    sav_accounts.push_back(sav_ptr2 );
    sav_accounts.push_back(sav_ptr3 );
    sav_accounts.push_back(sav_ptr4 );

    display(sav_accounts);
    deposit(sav_accounts, 1000);
    withdraw(sav_accounts,2000);

    std::vector<Account*> check_accounts;
    Account *check_ptr1=new Checking_Account {};
    Account *check_ptr2=new Checking_Account {"Kirk"};
    Account *check_ptr3=new Checking_Account {"Spock", 2000};
    Account *check_ptr4=new Checking_Account {"Bones", 5000};
    check_accounts.push_back(check_ptr1);
    check_accounts.push_back(check_ptr2 );
    check_accounts.push_back(check_ptr3 );
    check_accounts.push_back(check_ptr4 );

    display(check_accounts);
    deposit(check_accounts, 1000);
    withdraw(check_accounts, 2000);

    // Trust

    std::vector<Account*> trust_accounts;
    Account *trust_ptr1= new Trust_Account {};
    Account *trust_ptr2= new Trust_Account {"Athos", 10000, 5.0};
    Account *trust_ptr3= new Trust_Account {"Porthos", 20000, 4.0};
    Account *trust_ptr4= new Trust_Account {"Aramis", 30000};
    trust_accounts.push_back(trust_ptr1);
    trust_accounts.push_back(trust_ptr2 );
    trust_accounts.push_back(trust_ptr3 );
    trust_accounts.push_back(trust_ptr4 );


    display(trust_accounts);
    deposit(trust_accounts, 1000);
    withdraw(trust_accounts, 3000);

    // Withdraw 5 times from each trust account
    // All withdrawals should fail if there are too many withdrawals or if the withdrawl is > 20% of the balance
    for (int i=1; i<=5; i++)
        withdraw(trust_accounts, 1000);

    std::vector<Account*> mixed_accounts;
    mixed_accounts.push_back(trust_ptr4);
    mixed_accounts.push_back(check_ptr4);
    mixed_accounts.push_back(sav_ptr4);

    display(mixed_accounts);
    deposit(mixed_accounts, 1000);
    withdraw(mixed_accounts, 2000);

    delete trust_ptr1;
    delete trust_ptr2;
    delete trust_ptr3;
    delete trust_ptr4;
    delete check_ptr1;
    delete check_ptr2;
    delete check_ptr3;
    delete check_ptr4;
    delete sav_ptr1;
    delete sav_ptr2;
    delete sav_ptr3;
    delete sav_ptr4;
    return 0;
}