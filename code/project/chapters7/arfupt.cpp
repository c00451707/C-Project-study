#include<iostream>
const double * f1(const double ar[], int n);
const double * f2(const double [], int n);
const double * f3(const double *, int n);

using namespace std;
int main()
{
    double av[3] = {1112.3, 1542.6, 2227.9};
    // function pointer p1  调用 (*p1)(av,3);
    const double * (*p1)(const double *, int n)  = f1;
    auto p2 = f2;

    cout << "Using pointers to functions: \n";
    cout << "Adress Value: \n";
    cout << (*p1)(av, 3) << ": " << *(*p1)(av, 3) << endl;
    cout << p2(av, 3) << ": " << *p2(av, 3) << endl;

    // 函数指针数组
    const double * (*pa[3])(const double *, int) = {f1, f2, f3};
    auto pb = pa;

    cout << "\nUsing an array of pointers to function:\n";
    cout << "Adress Values:\n";
    for (int i = 0; i < 3; i++)
        // pa[i] 数组的使用方法 数组表示法比较特殊 (*pa[i])(av, 3) 等效于 pa[i](av, 3)
        cout << (*pa[i])(av, 3) << ": " << *pa[i](av, 3) << endl;
    cout << "\nUsing a pointer to a function: \n";
    for (int i = 0; i < 3; i++)
        cout << pb[i](av,3) << ": " << *pb[i](av, 3) << endl;

    cout << "\nUsing pointers to an array of function pointers: \n";
    cout << "Adress Value:\n";
    // 函数指针 指针
    auto pc = &pa;
    cout << (*pc)[0](av, 3) << ": " << *(*pc)[0](av, 3) << endl;
    // hard way to declare  pd是指向数组（函数指针数组）的指针
    const double * (*(*pd)[3])(const double *, int) = &pa;
    // store return value in pdb
    const double * pdb = (*pd)[1](av, 3);
    cout << pdb << ": " << *pdb << endl;
    // cout << *(*pd)[2](av, 3) << ": " << *(*(*pd)[2])(av, 3) << endl;   -> 2227.9: 2227.9 因为 (*(*pd)[2])(av, 3) 等效于 (*pd)[2])(av, 3) pd是指向数组（函数指针数组）的指针  (*pd) -> 数组
    cout << (*(*pd)[2])(av, 3) << ": " << *(*(*pd)[2])(av, 3) << endl;
    return 0;
}

const double * f1(const double * ar, int n)
{
    return ar;
}

const double * f2(const double ar[], int n)
{
    return ar + 1;
}

const double * f3(const double ar[], int n)
{
    return ar + 2;
}

/*
    Using pointers to functions: 
    Adress Value: 
    0x61fdc0: 1112.3
    0x61fdc8: 1542.6

    Using an array of pointers to function:
    Adress Values:
    0x61fdc0: 1112.3
    0x61fdc8: 1542.6
    0x61fdd0: 2227.9

    Using a pointer to a function:
    0x61fdc0: 1112.3
    0x61fdc8: 1542.6
    0x61fdd0: 2227.9

    Using pointers to an array of function pointers:
    Adress Value:
    0x61fdc0: 1112.3
    0x61fdc8: 1542.6
    0x61fdd0: 2227.9
*/