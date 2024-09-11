#include <iostream>
#include "coordin.h"
using namespace std;

int main ()
{
    rect rplace;
    polar pplace;

    cout << "Enter the x and y values: ";
    while (cin >> rplace.x >> rplace.y)
    {
        pplace = rect_to_polar(rplace);
        show_polar(pplace);
        cout << "Next two numbers (q to quit): ";
    }
    cout << "Byte!\n";
    return 0;
}
/*
    进入相应文件夹：
    cd .\fileExamples\chapters9\
    编译命令如下：
    g++ file1.cpp file2.cpp -o coordin
    执行命令：
    .\coordin.exe

    Enter the x and y values: 120 80
    distance = 144.222, angle = 33.6901 degrees
    Next two numbers (q to quit): 120 89 
    distance = 149.402, angle = 36.5631 degrees
    Next two numbers (q to quit): 180 180 
    distance = 254.558, angle = 45 degrees
    Next two numbers (q to quit): 180 1098
    distance = 1112.66, angle = 80.6901 degrees
    Next two numbers (q to quit): q
    Byte!
*/