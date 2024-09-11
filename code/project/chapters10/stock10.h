#ifndef STOCK10_H_
#define STOCK10_H_

#include <string>

class Stock
{
private:
    /* data */
    std::string company;
    long shares;
    double shares_val;
    double total_val;
    void set_tot() {
        total_val = shares_val * shares;
    }
public:
    Stock(/* args */);
    Stock(const std::string & co, long n = 0, double pr = 0.0);
    ~Stock();
    void buy(long num, double prices);
    void sell(long num, double prices);
    void update(double prices);
    void show();
};
#endif
