#include <iostream>
using std::cout;
#include "stringbad.h"

void callme1(StringBad &);
void callme2(StringBad);

/*
    程序输出：
    StringBad an inner block.                               #39
    1: "Celecry Stalks at Midnight" object created      
    2: "Lettuce Prey" object created
    3: "Spinach Leaves Bow1 for Dollars" object created     #42
    headline1: Celecry Stalks at Midnight
    headline2: Lettuce Prey
    sports: Spinach Leaves Bow1 for Dollars                 #46
    String passed by reference:
            "Celecry Stalks at Midnight"                    #48
    headline1: Celecry Stalks at Midnight                   #49
    String passed by value:                                 #51  callme2(headline2);
            "Lettuce Prey"                                  // 值传递，会调用复制构造函数，当callme2函数执行完成之后，有会调用析构函数释放sb对象
    "Lettuce Prey" object deleted, 2 left                   #  故会打印 Lettuce Prey" object deleted, 2 left
    headline2:                                              #52 因为调用了复制构造函数，没有重载=运算服，复制的对象是浅层复制，对象的引用成员变量是直接拷贝地址的，所以 &(headline2.str) = &(sb.str)
    nitialize one object to another:                            又因为 执行完函数之后，调用了析构函数，释放了sb对象的str成员变量占用的内存，导致也释放了 headline2.str的内存，故 #52行打印出： headline2: 
    sailor: Spinach Leaves Bow1 for Dollars
    Assgin one object to another:
    3: "C++" default object created
    knot:Celecry Stalks at Midnight
    "Celecry Stalks at Midnight" object deleted, 2 left       #64 先释放  knot对象（破坏了headline1对象）
    "Spinach Leaves Bow1 for Dollars" object deleted, 1 left  #64 在释放 sailor 对象（破坏了sports对象）
    "?                                                        #64 在释放 sports 对象，因为被 sailor 破坏了，所以执行出错，程序直接退出

*/

int main()
{
    using std::endl;
    {
        cout << "StringBad an inner block.\n";
        StringBad headline1("Celecry Stalks at Midnight");
        StringBad headline2("Lettuce Prey");
        StringBad sports("Spinach Leaves Bow1 for Dollars");

        cout << "headline1: " << headline1 << endl;
        cout << "headline2: " << headline2 << endl;
        cout << "sports: " << sports << endl;

        callme1(headline1);
        cout << "headline1: " << headline1 << endl;

        callme2(headline2);
        cout << "headline2: " << headline2 << endl;

        cout << "Initialize one object to another:\n";
        StringBad sailor = sports;  // 调用复制构造函数（用于讲一个对象复制到新创建的对象中）  也是浅层复制
        cout << "sailor: " << sailor << endl;

        cout << "Assgin one object to another:\n";
        StringBad knot;    // 调用了默认的构造函数（此时有3个对象）
        knot = headline1;  // 调用了编译器默认生成的=运算法，也是浅层复制
        cout << "knot:" << knot << endl;
        
    }
    cout << "End of main()\n";  // 都没有机会执行，内存错乱了
    return 0;
}

void callme1(StringBad & rsb)
{
    cout << "String passed by reference:\n";
    cout << "        \"" << rsb << "\" \n";
}

void callme2(StringBad sb)
{
    cout << "String passed by value:\n";
    cout << "        \"" << sb << "\" \n";
}