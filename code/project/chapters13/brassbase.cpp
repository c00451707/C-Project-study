#include <iostream>
#include "brassbase.h"

using std::cout;
using std::endl;
using std::string;
using std::ios_base;

BrassBase::BrassBase(const string & s, long an, double bal)
{
    fullName = s;
    acctNum = an;
    balance = bal;
}

void BrassBase::Deposit(double amt)
{
    if (amt < 0)
    {
        cout << "Negative deposit not allow;"
             << "deposit is cancelled.\n";
    }
    else
    {
        balance += amt;
    }
        
}

void BrassBase::Withdraw(double amt)
{
    balance -= amt;
}

BrassBase::Formatting BrassBase::SetFormat() const
{
    Formatting f;
    f.flag = cout.setf(ios_base::fixed, ios_base::floatfield);
    f.pr = cout.precision(2);
    return f;
}

void BrassBase::Restore(Formatting & f) const
{
    cout.setf(f.flag, ios_base::floatfield);
    cout.precision(f.pr);
}

// 多态
void Brass::Withdraw(double amt)
{
    if (amt < 0)
    {
        cout << "Withdrawal amount must be positive;" << "withdrawal canceled.\n";
    }
    else if (amt <= Balance())
    {
        BrassBase::Withdraw(amt);
    }
    else
    {
        cout << "Withdrawal amout of $" << amt << " exceeds your balance.\n"
             << "Withdrawal canceled. \n";
    }
}
// 多态
void Brass::ViewAcct() const
{
    Formatting f = SetFormat();
    cout << "Brass Client: " << FullName() << endl;
    cout << "Account Number: " << AcctNum() << endl;
    cout << "Balance: $ " << Balance() << endl;
    Restore(f); 
}

BrassPlus::BrassPlus(const string & s, long an, double bal,
                    double ml, double r) : BrassBase(s,an,bal)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

BrassPlus::BrassPlus(const Brass & ba, double ml, double r)
                    : BrassBase(ba)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

// 多态
void BrassPlus::ViewAcct() const
{
    Formatting f = SetFormat();

    cout << "BrassPlus Client: " << FullName() << endl;
    cout << "Account Number: " << AcctNum() << endl;
    cout << "Balance: $" << Balance() << endl;
    cout << "Maximum loan: $" << maxLoan << endl;
    cout << "Owed to bank: $" << owesBank << endl;
    cout.precision(3);
    cout << "Loan Rate: " << 100 * rate << "%\n";
    Restore(f);
}

// 多态
void BrassPlus::Withdraw(double amt)
{
    Formatting f = SetFormat();
    double bal = Balance();
    if (amt <= bal)
    {
        BrassBase::Withdraw(amt);
    }
    else if (amt <= bal + maxLoan - owesBank)
    {
        double advance = amt - bal;
        owesBank += advance * (1 + rate);
        cout << "Bank Advance: $" << advance << endl;
        cout << "Finance charge: $" << advance * rate << endl;
        Deposit(advance);
        BrassBase::Withdraw(amt);
    }
    else
    {
        cout << "Credit limit exceeded. Transaction cancelled.\n";
    }
    Restore(f);

}

