## 编译期编程
### template_base.h文件代码
```
template <bool condition, typename Body>
struct WhileLoop;

template <typename Body>
struct WhileLoop<true, Body> {
  typedef typename WhileLoop<Body::cond_value, typename Body::next_type>::type type;
};

template <typename Body>
struct WhileLoop<false, Body> {
  typedef typename Body::res_type type;
};

template <typename Body>
struct While {
  typedef typename WhileLoop<Body::cond_value, Body>::type type;
};

template <class T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant type;
};

template <int result, int n>
struct SumLoop {
  static const bool cond_value = n != 0;
  static const int res_value = result;
  typedef integral_constant<int, res_value> res_type;
  typedef SumLoop<result + n, n - 1> next_type;
};

template <int n>
struct Sum {
  typedef SumLoop<0, n> type;
};
```

### template_base.cc 文件代码
```
#include <iostream>
#include <string>
#include "template_base.h"

int main() {
  std::cout << "While<Sum<10>::type>::type::value is: " << While<Sum<10>::type>::type::value << std::endl;
  return 0;
}
```

### 程序运行结果
```
/**
 * 程序运行结果：
 * While<Sum<10>::type>::type::value is: 55
   分析过程如下：
   因为：
    template <int n>
    struct Sum {
      typedef SumLoop<0, n> type;
    };
   所以： Sum<10>::type = SumLoop<0, 10>;
   所以源表达式变为：  While<SumLoop<0, 10>>::type::value
   又因为 
    template <typename Body>
    struct While {
      typedef typename WhileLoop<Body::cond_value, Body>::type type;
    };
   所以： 以上的Body 特化为 SumLoop<0, n> 既：Body=SumLoop<0, 10>
   所以：While<SumLoop<0, 10>>::type::value = WhileLoop<SumLoop<0, 10>::cond_value, SumLoop<0, 10>>::type::value
   
   截止目前源表达式又变为： WhileLoop<SumLoop<0, 10>::cond_value, SumLoop<0, 10>>::type::value
   又因为：
    template <int result, int n>
    struct SumLoop {
      static const bool cond_value = n != 0;                   #1
      static const int res_value = result;                     #2
      typedef integral_constant<int, res_value> res_type;      #3
      typedef SumLoop<result + n, n - 1> next_type;            #4
    };
   所以：SumLoop<0, 10>::cond_value 是 true 得到 WhileLoop<SumLoop<0, 10>::cond_value, SumLoop<0, 10>>::type::value
                                                   = WhileLoop<true, SumLoop<0, 10>>::type::value
   又因为：
    template <typename Body>
    struct WhileLoop<true, Body> {
      typedef typename WhileLoop<Body::cond_value, typename Body::next_type>::type type;
    };
   所以： WhileLoop<true, SumLoop<0, 10>>::type::value
           = WhileLoop<SumLoop<0, 10>::cond_value, SumLoop<0, 10>::next_type>::type::value   #4
           = WhileLoop<SumLoop<0, 10>::cond_value, SumLoop<10, 9>>::type::value
           = WhileLoop<true, SumLoop<10, 9>>::type::value
           = WhileLoop<SumLoop<10, 9>::cond_value, SumLoop<10, 9>::next_type>::type::value   #4
           = WhileLoop<true, SumLoop<19, 8>>::type::value
           = WhileLoop<true, SumLoop<27, 7>>::type::value
           = WhileLoop<true, SumLoop<34, 6>>::type::value
           = WhileLoop<true, SumLoop<40, 5>>::type::value
           = WhileLoop<true, SumLoop<45, 4>>::type::value
           = WhileLoop<true, SumLoop<49, 3>>::type::value
           = WhileLoop<true, SumLoop<52, 2>>::type::value
           = WhileLoop<SumLoop<52, 2>, SumLoop<54, 1>>::type::value
           = WhileLoop<SumLoop<54, 1>, SumLoop<55, 0>>::type::value
           = WhileLoop<SumLoop<55, 0>, SumLoop<55, -1>>::type::value
           = WhileLoop<false, SumLoop<55, -1>>::type::value
   又因为：
    template <typename Body>
    struct WhileLoop<false, Body> {
      typedef typename Body::res_type type;
    };
   所以：
    WhileLoop<false, SumLoop<55, -1>>::type::value = SumLoop<55, -1>::res_type::value (#3) = integral_constant<int, 55>::value
  又因为：
    template <class T, T v>
    struct integral_constant {
      static const T value = v;
      typedef T value_type;
      typedef integral_constant type;
    };
   所以： integral_constant<int, 55>::value = 55； 所以最终结果等于55
 */
```
