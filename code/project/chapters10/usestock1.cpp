#include <iostream>
#include "stock10.h"

int main()
{
    /**
     * 代码块
     * 有些编译器可能需要过一段时间才会删除临时对象，因此析构函数的调用将延迟
     */
    {
        using std::cout;
        cout << "Using constructors to creat new objects \n";
        Stock stock1("NanoSmart", 12, 20.0);
        stock1.show();
        // 这里可能会打印 Bye, Boffo Objects!
        /*
        编译器有两种执行方式：
        1、 同 Stock stock1("NanoSmart", 12, 20.0); 一样，不会创建临时变量
        2、 使用构造函数先创建一个临时变量，然后复制给stock2,并且丢弃它，会调用析构函数。
        */
        Stock stock2 = Stock("Boffo Objects", 2, 2.0);
        stock2.show();

        cout << "Assigning stock1 to stock2:\n";
        stock2 = stock1;
        cout << "Listing stock1 to stock2:\n";
        stock1.show();
        stock2.show();

        cout << "Using a constructor to reset an object\n";
        // 当 stock1 已经备注初始化时，  Stock("Nifty Foods", 10, 50.0) 会创建一个临时变量，然后将这个临时变量复制给 stock1, 之后会释放临时变量，所以会打印出 
        /*
         *  Constructor using Nifty Foods called
         *  Bye, Nifty Foods!
         *  Revised stock1: 
         */
        stock1 = Stock("Nifty Foods", 10, 50.0);
        cout << "Revised stock1: \n";
        stock1.show();
        cout << "Done\n";
    }
    // 代码块执行完毕之后，会释放里面的局部变量,故会打印 Bye, NanoSmart! Bye, Nifty Foods!
    return 0;
}

/*
    输出结果：
    Using constructors to creat new objects 
    Constructor using NanoSmart called
    Company NanoSmart Share Price: $20.000 Total Worth: $240.00  
    Constructor using Boffo Objects called
    Company Boffo Objects Share Price: $2.000 Total Worth: $4.00 
    Assigning stock1 to stock2:
    Listing stock1 to stock2:
    Company NanoSmart Share Price: $20.000 Total Worth: $240.00  
    Company NanoSmart Share Price: $20.000 Total Worth: $240.00  
    Using a constructor to reset an object
    Constructor using Nifty Foods called
    Bye, Nifty Foods!
    Revised stock1: 
    Company Nifty Foods Share Price: $50.000 Total Worth: $500.00
    Done
    Bye, NanoSmart!
    Bye, Nifty Foods!

*/