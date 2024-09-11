#include <iostream>
#include <cstdlib> // rand() srand()
#include <ctime>
#include "vect.h"

int main() 
{
    using namespace std;
    using VECTOR::Vector;
    srand(time(0)); // 返回当前时间作为随机数的种子
    double direction;
    Vector step;
    Vector result(0.0, 0.0);
    unsigned long steps = 0;
    double target;
    double dstep;

    cout << "Enter target distance (q to quit): ";
    while (cin >> target)
    {
        cout << "Enter step length: ";
        if (!(cin >> dstep)) // 输入固定步长
            break;
        
        while (result.magval() < target)
        {
            direction = rand() % 360; // 随机角度
            step.reset(dstep, direction, Vector::POL);
            /*
                运算法+ 创建并返回了一个新的的Vector 对象， 该对象存储了的 result + step 和，然后通过值传递的方式复制给了result,从下面输出也可以看出，确实是两个不同地址
                Enter target distance (q to quit): 2
                Enter step length: 1
                temp address is :0x61fdd0
                result address is: 0x61fd70  result 指向的地址一直不变。只是给改地址上的内容做了修改
                temp address is :0x61fdd0  temp 地址会从新复用？
                result address is: 0x61fd70
                temp address is :0x61fdd0
                result address is: 0x61fd70
                temp address is :0x61fdd0
                result address is: 0x61fd70
                temp address is :0x61fdd0
                result address is: 0x61fd70
                After 5 steps, the subject has the following location:
                (x, y) = (-1.37568, -2.00496)
                or 
                (m,a) = (2.43153, -124.455)
                Average outward distance per step = 0.486306
            */
            result = result + step;
            cout << "result address is: " << &result << endl;
            steps++;  
        }

        cout << "After " << steps << " steps, the subject has the following location:\n";
        cout << result << endl;
        result.polar_mode();
        cout << "or \n" << result << endl;
        cout << "Average outward distance per step = " << result.magval() / steps << endl;
        steps = 0;
        result.reset(0.0, 0.0);
        cout << "Enter target distance (q to quit): ";
    }

    cout << "Bye! \n";
    cin.clear();
    while (cin.get() != '\n')
    {
        continue;
    }
    return 0;
}

/*
    函数输出：
    Enter target distance (q to quit): 50
    Enter step length: 3
    After 169 steps, the subject has the following location:
    (x, y) = (-50.6614, -3.58152)
    or 
    (m,a) = (50.7878, -175.956)
    Average outward distance per step = 0.30052
    Enter target distance (q to quit): 50
    Enter step length: 3
    After 176 steps, the subject has the following location:
    (x, y) = (-7.38976, -49.782)
    or
    (m,a) = (50.3275, -98.4435)
    Average outward distance per step = 0.285952
    Enter target distance (q to quit): 50
    Enter step length: 3
    After 433 steps, the subject has the following location:
    (x, y) = (1.56531, 50.0412)
    or
    (m,a) = (50.0657, 88.2083)
    Average outward distance per step = 0.115625
    Enter target distance (q to quit): 50
    Enter step length: 3
    After 121 steps, the subject has the following location:
    (x, y) = (7.14396, -50.9489)
    or
    (m,a) = (51.4473, -82.0181)
    Average outward distance per step = 0.425185
    Enter target distance (q to quit): 50
    Enter step length: 3
    After 121 steps, the subject has the following location:
    (x, y) = (47.9639, -21.3789)
    or
    (m,a) = (52.5128, -24.0239)
    Average outward distance per step = 0.43399
    Enter target distance (q to quit): 50
    Enter step length: 3
    After 458 steps, the subject has the following location:
    (x, y) = (28.2611, 43.2636)
    or
    (m,a) = (51.6762, 56.8462)
    Average outward distance per step = 0.11283
*/