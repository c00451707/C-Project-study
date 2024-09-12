#ifndef WORKERMI_H_
#define WORKERMI_H_

#include<string>
// 至少有一个虚函数是纯虚函数的类为抽象类
class Worker
{
    private:
        std::string fullName;
        long id;
    protected:
        virtual void Data() const;  // 虚函数
        virtual void Get();
    public:
        Worker() : fullName("no one"), id(0L) {}
        Worker(const std::string & s, long n) : fullName(s), id(n) {}
        virtual ~Worker() = 0;
        virtual void Set() = 0; // 纯虚函数 函数声明结尾处为=0,当类声明中有纯虚函数时，则不能创建该类的对象。
        virtual void Show() const = 0;
    
};

class Waiter : virtual public Worker // virtual 表明 Worker 被作为虚基类进行继承
{
    private:
        int panache;
    protected:
        void Data() const;
        void Get();
    public:
        Waiter() : Worker(), panache(0) {}
        Waiter(const std::string & s, long n, int p = 0) : Worker(s, n), panache(p) {}
        Waiter(const Worker & wk, int p = 0) : Worker(wk), panache(p) {}
        void Set();
        void Show() const;
};

class Singer : virtual public Worker  // virtual 表明 Worker 被作为虚基类进行继承，通过多种路径继承该类不会出现多个“子对象”问题
{
    protected:
        enum {other, alto, contralto, soprano, bass, baritone, tenor};
        enum {Vtypes = 7};
        void Data() const;
        void Get();
    private:
        static char * pv[Vtypes];
        int voice;
    public:
        Singer() : Worker(), voice(other) {}
        Singer(const std::string & s, long n, int v = other) : Worker(s, n), voice(v) {}
        Singer(const Worker & wk, int v =other) : Worker(wk), voice(v) {}
        void Set();  // 这里使用了多态 特性 根据实际对象类型确定使用那个函数
        void Show() const;
};

class SingingWaiter : public Singer, public Waiter
{
    protected:
        void Data() const;
        void Get();
    public:
        SingingWaiter() {};
        SingingWaiter(const std::string & s, long n, int p = 0, int v = other)
            :Worker(s, n), Waiter(s, n, p), Singer(s, n, v) {}
        SingingWaiter(const Worker & wk, int p = 0, int v = other)
            :Worker(wk), Waiter(wk, p), Singer(wk, v) {}
        SingingWaiter(const Worker & wk, int v = other)
            :Worker(wk), Waiter(wk), Singer(wk, v) {}
        // 'SingingWaiter::SingingWaiter(const Worker&, int)' cannot be overloaded with 'SingingWaiter::SingingWaiter(const Worker&, int)'
        // SingingWaiter(const Worker & wk, int p = 0)
        //     :Worker(wk), Waiter(wk, p), Singer(wk) {}
        void Set(); // 这里使用了多态 特性  根据实际对象类型确定使用那个函数
        void Show() const;
};


#endif