#include<iostream>

void may(int);                           // #1
float may(float, float = 3.0F);          // #2
void may(char);                          // #3
char * may(const char *);                // #4
char may(const char &);                  // #5
template<class T> void may(const T &);   // #6
template<typename T> void may(T *);      // #7

/*
may('B') 首先排除4和7，因为证书类型不能隐士转换为指针；
编译器匹配规则：（由好至差）
1、完全匹配：但常规函数优于模板函数
2、提升转换：例如：char 和 short 自动转换成 int， float自动转换成 double
3、标准转换： int 转成 char， long 转成 double
4、用户定义的转换，如在类声明中定义的转换

用户自定义举例：
template<class T>
T lesser(T a, T b)          #1
{
    return a < b ? a : b;
}

int lesser (int 1, int b)   #2
{
    a = a < 0 ? -a : a;
    return a < b ? a : b;
}

int main() 
{
    int m = 20, n = -30;
    double x = 15.5, y = 25.9;
    lesser(m, n); // use #2
    lesser(x, y); // use #1 with double
    lesser<>(m, n); // use #1 with int;  <> 指出选择模板函数
    lesser<int>(m, n); // use #1 with int;  <int> 要求进行显示实例化（使用int 代替 T）
}

函数#1 优于 函数#2，因为char 到int 是提升转换
函数 #3，#5，#6 优于 函数#1，#2 因为他们都是安全匹配
函数 #3，#5， 优于 函数#6 因为函数#6是模板

所以：直接运行报错
call of overloaded 'may(char)' is ambiguous  不知道选 #3 还是#5
*/

using namespace std;
int main()
{
    // actual argument is type char  
    may('B'); // call of overloaded 'may(char)' is ambiguous  不知道选 #3 还是#5
}

void may(int a)
{
    cout << "A void may(int) :" << a << endl;
}

float may(float a, float b)
{
    cout << "B float may(float, float = 3) :" << a + b << endl;
    return 0.0f;
}

void may(char a)
{
    cout << "C void may(char) :" << a << endl;
}

char * may(const char * ch)
{
    cout << "D char * may(const char *) :" << *ch << endl;
    char * temp = new char[5];
    return temp;
}

char may(const char & ch2)
{
    cout << "E char may(const char &) :" << ch2 << endl;
    return ch2;
}

template<class T> void may(const T & t1)
{
    cout << "F template<class T> void may(const T &) :" << t1 << endl;
}

template<typename T> void may(T * t2)
{
    cout << "G template<class T> void may(T *) :" << t2 << endl;
}

/*
直接运行报错
call of overloaded 'may(char)' is ambiguous  不知道选 #3 还是#5

注释 #3的函数声明
E char may(const char &) :B

注释 #5的函数声明
C void may(char) :B
*/