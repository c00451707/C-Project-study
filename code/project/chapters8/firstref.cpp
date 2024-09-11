#include<iostream>
#include<string>

using namespace std;

struct person {
    string name;
    long number;
    int age;
};

int main() 
{
    int rats = 101;
    // 看到没，这里是值传递
    int test = rats;
    int & rodents = rats;

    cout << "rats = " << rats;
    cout << ", rodents = " << rodents << endl;
    rodents++;

    cout << "rats = " << rats;
    cout << ", rodents = " << rodents << endl;

    cout << "rats address = " << &rats;
    cout << ", rodents address= " << &rodents << endl;

    cout << "test = " << test;
    cout << ", test address = " << &test << endl;


    person p = {
        "Huster CB!",
        451707,
        24
    };
    
    cout << "person p.name = " << p.name << endl;
    cout << "person p address = " << &p << endl;

    person p1 = p;
    // p1 address != p address
    cout << "person p.name = " << p1.name << endl;
    cout << "person p1 address = " << &p1 << endl;
    return 0;
}
/*
    rats = 101, rodents = 101
    rats = 102, rodents = 102
    rats address = 0x61fe00, rodents address= 0x61fe00
    test = 101, test address = 0x61fdfc
    person p.name = Huster CB!
    person p address = 0x61fdd0
    person p.name = Huster CB!
    person p1 address = 0x61fda0

*/