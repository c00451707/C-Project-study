#include<iostream>
#include<string>
#include "brassbase.h"
const int CLIENTS = 4;

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    BrassBase * p_client[CLIENTS];
    std::string temp;
    long tempnum;
    double tempbal;
    char kind;

    for (int i = 0; i < CLIENTS; i++)
    {
        cout << "Enter client's name: ";
        getline(cin, temp);
        cout << "Enter client's account number: ";
        cin >> tempnum;
        cout << "Enter opening balance: $";
        cin >> tempbal;
        cout << "enter 1 for Brass Account or" << "2 for BrassOlus Account: ";
        while (cin >> kind && (kind != '1' && kind != '2'))
        {
            cout << "Enter either 1 or 2: ";
        }
        if (kind == '1')
        {
            p_client[i] = new Brass(temp, tempnum, tempbal);
        }
        else 
        {
            double tmax, trate;
            cout << "Enter the overdraft limit: $";
            cin >> tmax;
            cout << "Enter the interest rate "
                << "as a decimal fraction: ";
            cin >> trate;
            p_client[i] = new BrassPlus(temp, tempnum, tempbal, tmax, trate);
        }
        while (cin.get() != '\n')
            continue;
        
    }
    cout << endl;
    for (int i = 0; i < CLIENTS; i++)
    {
        p_client[i] -> ViewAcct();
        cout << endl;
    }

    for (int i = 0; i < CLIENTS; i++)
    {
        delete p_client[i];
    }

    cout << "Done.\n";
    return 0;
}

/*
    程序输出：
    Enter client's name: Huster1
    Enter client's account number: 123
    Enter opening balance: $9546255
    enter 1 for Brass Account or2 for BrassOlus Account: 2
    Enter the overdraft limit: $50000
    Enter the interest rate as a decimal fraction: 0.03
    Enter client's name: Huster2
    Enter client's account number: 124
    Enter opening balance: $86252
    enter 1 for Brass Account or2 for BrassOlus Account: 1 
    Enter client's name: Huster3
    Enter client's account number: 125
    Enter opening balance: $8953654
    enter 1 for Brass Account or2 for BrassOlus Account: 2
    Enter the overdraft limit: $5000000
    Enter the interest rate as a decimal fraction: 0.03
    Enter client's name: Huster4
    Enter client's account number: 126
    Enter opening balance: $98562314
    enter 1 for Brass Account or2 for BrassOlus Account: 1

    BrassPlus Client: Huster1
    Account Number: 123      
    Balance: $9546255.00     
    Maximum loan: $50000.00  
    Owed to bank: $0.00      
    Loan Rate: 3.000%

    Brass Client: Huster2
    Account Number: 124
    Balance: $ 86252.00

    BrassPlus Client: Huster3
    Account Number: 125
    Balance: $8953654.00
    Maximum loan: $5000000.00
    Owed to bank: $0.00
    Loan Rate: 3.000%

    Brass Client: Huster4
    Account Number: 126
    Balance: $ 98562314.00

    Done.

*/