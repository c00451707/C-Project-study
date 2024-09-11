#include<iostream>
#include "namesp.h"

void other(void);

void another(void);

int main()
{
    using debts::Debt;
    using debts::showDebt;
    Debt golf = {{"Benny", "Goatsniff"}, 120.0};
    showDebt(golf);
    other();
    another();
    return 0;
}

void other(void)
{
    using std::cout;
    using std::endl;
    // using 具有传递性  using namespace debts; 相当于 using namespace pers;
    using namespace debts;
    Person dg = {"Doodles", "Glister"};
    showPerson(dg);
    cout << endl;
    Debt zippy[3];
    int i;

    for (i = 0; i < 3; i++)
    {
        getDebt(zippy[i]);
    }

    for (i = 0; i < 3; i++)
    {
        showDebt(zippy[i]);
    }

    cout << "Total deba: $" << sumDebts(zippy, 3) << endl;
    return;
}

void another(void)
{
    using pers::Person;
    Person collector = {"Milo", "Rightshift"};
    pers::showPerson(collector);
    std::cout << std::endl;
}

/*
    程序输出:
    D:\ei-code\c++project> cd .\fileExamples\chapters9\
    D:\ei-code\c++project\fileExamples\chapters9> g++ .\namesp.cpp .\usenmsp.cpp -o namesp
    D:\ei-code\c++project\fileExamples\chapters9> .\namesp.exe
    Goatsniff, Benny: $120
    Glister, Doodles      
    Enter first name:     
    Arabella
    Enter last name: 
    Binx
    Enter deba: 100
    Enter first name: 
    Cleve
    Enter last name: 
    Delaproux
    Enter deba: 120
    Enter first name: 
    Eddie
    Enter last name: 
    Fiotox
    Enter deba: 200
    Binx, Arabella: $100
    Delaproux, Cleve: $120
    Fiotox, Eddie: $200
    Total deba: $420
    Rightshift, Milo

*/
