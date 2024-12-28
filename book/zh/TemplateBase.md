## C++中的std::forward 作用
### 1. 基本概念与所属头文件
std::forward定义在<utility>头文件中，它是一个模板函数，主要用于在特定的模板编程场景中，尤其是涉及完美转发（perfect forwarding）时，按照参数原本的类型（左值或右值属性）去转发参数。
### 2. 完美转发的关联
在模板编程里，我们常常会编写函数模板或者类模板，有时候需要把接收到的参数再传递给其他函数。完美转发的目标就是让这个传递过程能精准地保持参数原来的左值或者右值属性，使得接收这些转发参数的函数能够按照预期正确处理（比如对于右值参数能利用移动语义进行高效的资源转移等）。
例如，有这样一个函数模板：
```
template<typename T>
void wrapper(T&& arg) {
    innerFunction(std::forward<T>(arg));
}
```
这里的wrapper函数模板接收一个参数arg，它可能是左值也可能是右值（利用了 C++11 的引用折叠规则，T&&既可以绑定左值也可以绑定右值），而std::forward<T>(arg)的作用就是将arg以其原本传入wrapper时的左值或右值属性准确无误地转发给innerFunction。
### 3. 避免不必要的拷贝和移动
如果没有std::forward进行正确的转发，在传递参数时可能会出现不符合预期的拷贝或者移动情况。比如，当传入一个右值给函数模板时，原本期望能利用移动语义高效地把资源传递给其他函数，但如果转发不当，可能会变成进行拷贝构造等相对低效的操作，而std::forward确保了按照参数原始的性质进行转发，最大程度避免这种不必要的资源操作，提升程序性能。

***总之：*** std::forward是 C++ 中实现完美转发的关键工具，能让模板函数在传递参数时精准保持参数的原始属性，利于正确利用移动语义等机制来优化程序的行为和性能。
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



## 模板编程示例2，map_reduce示例
### map_reduce.h 代码
```
#include <vector>
#include <type_traits>

/**
  * 用 decltype 来获得用 f 来调用 inputs 元素的类型（参考[第 8 讲]）；
  * 用 decay_t 来把获得的类型变成一个普通的值类型；
  * 缺省使用 vector 作为返回值的容器，但可以通过模板参数改为其他容器；
  * 使用基于范围的 for 循环来遍历 inputs，对其类型不作其他要求（参考[第 7 讲]）；
  * 存放结果的容器需要支持 push_back 成员函数（参考[第 4 讲]）。
*/
template <template <typename, typename> class OutContainer = std::vector, typename F, class R>
auto fmap(F&& f, R&& inputs)
{
  typedef std::decay_t<decltype(f(*inputs.begin()))> result_type;
  OutContainer<result_type, std::allocator<result_type>> result;
  for (auto&& item : inputs) {
    result.push_back(f(item));
  }
  return result;
}

int add_1(int x)
{
    return x + 1;
}
```
### map_reduce.cc 代码
```
#include <iostream>
#include <string>
#include "map_reduce.h"

int main() 
{
    std::vector<int> v{1, 2, 3, 4, 5};
    auto result = fmap(add_1, v);
    std::cout << "auto result = fmap(add_1, v) is: {";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << " " << result[i] << " ";
    }
    std::cout << " }" << std::endl;
    return 0;
}

/**
 *  程序输出：
 *  auto result = fmap(add_1, v) is: { 2  3  4  5  6  }
 */
```
### 代码解释
```
/**
 * 代码解释：
 * 函数模板 fmap 解释：
 * template <template <typename, typename> class OutContainer = std::vector, typename F, class R>：
 *   这是一个函数模板，它有三个模板参数。
 *   template <typename, typename> class OutContainer = std::vector 是一个模板模板参数，它本身是一个模板，并且默认使用 std::vector。这意味着 OutContainer 应该是一个容器模板，接受两个类型参数，例如 std::vector 接受元素类型和分配器类型。
 *   typename F 是一个类型模板参数，代表可调用对象（函数、函数对象、lambda 等）的类型。
 *   class R 是一个类型模板参数，代表输入容器的类型。
 * 
 * auto fmap(F&& f, R&& inputs)：
 *   F&& f：这里使用了右值引用，目的是可以接受左值和右值。使用右值引用结合转发引用（universal reference）可以实现完美转发，允许 f 可以是任何可调用对象，无论它是左值还是右值，在函数内部调用时可以保持其原始的左值或右值属性，这在传递函数对象时可以避免不必要的复制和移动操作，提高性能。
 *   R&& inputs：同理，这里的右值引用允许 inputs 可以是任何容器，无论它是左值还是右值，也能实现完美转发，避免不必要的复制和移动。
 * 
 * typedef std::decay_t<decltype(f(*inputs.begin()))> result_type;：
 *   decltype(f(*inputs.begin())) 用于推导调用 f 对 inputs 容器的第一个元素进行操作后的结果类型。
 *   std::decay_t 用于对推导出的类型进行退化处理，比如去除引用和 const 修饰符，得到一个纯类型，作为存储结果的容器元素类型。
 * 
 * OutContainer<result_type, std::allocator<result_type>> result;：
 *   OutContainer 是一个容器模板，它使用 result_type 作为元素类型，std::allocator<result_type> 作为分配器。
 *   std::allocator<result_type> 的作用是为 OutContainer 容器中的元素分配内存。std::allocator 是 C++ 标准库中的一个内存分配器，它负责为容器元素分配和释放内存。使用自定义的分配器可以对内存管理进行更多的控制，例如使用不同的内存池或实现更复杂的内存分配策略，但通常使用 std::allocator 可以满足大多数情况，它会调用全局的 new 和 delete 操作符来分配和释放内存。
 * 
 * for (auto&& item : inputs) { result.push_back(f(item)); }：
 *   这是一个范围 for 循环，遍历 inputs 容器中的每个元素。
 *   对每个元素调用 f 函数，并将结果使用 push_back 方法添加到 result 容器中。
 * 
 * return result;：返回存储结果的 OutContainer 容器。
 * 
 * 函数 add_1 解释：
 *   int add_1(int x)：
 *     这是一个简单的函数，接受一个整数 x 作为输入。
 *     return x + 1;：返回 x 加 1 的结果。
 * 
 * 关于 std::vector 容器的模板参数：
 *   std::vector 可以接收两个模板参数：
 *     第一个参数是存储在 std::vector 中的元素类型，例如 std::vector<int> 中的 int。
 *     第二个参数是分配器类型，默认为 std::allocator 的实例化，如 std::vector<int, std::allocator<int>>。使用分配器可以实现自定义的内存分配和释放策略，例如，如果想要使用自定义的内存分配策略，可以提供自定义的分配器，否则，使用默认的 std::allocator 会自动管理内存，通过 new 和 delete 进行元素存储和释放。
 * 
 * 综上所述，这段代码中的 fmap 函数是一个通用的映射函数，它接受一个可调用对象和一个容器作为输入，将可调用对象应用到容器的每个元素上，并将结果存储在一个新的容器中。使用右值引用是为了实现完美转发，提高性能和代码的通用性，std::allocator 是为容器元素分配内存的分配器，std::vector 接收两个模板参数以允许元素类型和分配器类型的自定义。
 */
```

## 模板编程示例3，检测一个类是否有一个名叫 reserve、参数类型为 size_t 的成员函数

sinae.h 文件代码
```
#include <iostream>

template <typename T>
struct has_reserve
{
  struct good { char dummy; };
  struct bad { char dummy[2]; };
  
  template <class U, void (U::*)(size_t)>
  struct SFINAE {};
  
  template <class U>
  static good reserve(SFINAE<U, &U::reserve>*);
  
  template <class U>
  static bad reserve(...);
  
  static const bool value = sizeof(reserve<T>(nullptr)) == sizeof(good);
};

class test_class {
  public:
    void reserve(size_t t) {
      std::cout << "size_t: " << t << std::endl;
    }
};
```


sfinae.cc 文件代码示例
```
#include <iostream>
#include <string>
#include "sfinae.h"

int main() 
{
    has_reserve<test_class> is_has_reserve;
    std::cout << "has_reserve<test_class> is_has_reserve::value is " << is_has_reserve.value << std::endl;
    return 0;
}
/**
 * 程序输出值：
 * class test_class {
 *   void reserve(size_t t) {
 *     std::cout << "size_t: " << t << std::endl;
 *     }
 * };
 *
 * has_reserve<test_class> is_has_reserve::value is 0
 *   class test_class {
 *     public:    ### 区别
 *       void reserve(size_t t) {
 *         std::cout << "size_t: " << t << std::endl;
 *       }
 *   };
 * has_reserve<test_class> is_has_reserve::value is 1
 */
```

### 代码解释
![image](https://github.com/user-attachments/assets/fd394c31-8809-4152-a5cd-6342b956feb0)

```
/**
 * 1. SFINAE（Substitution Failure Is Not An Error，替换失败不是错误）机制回顾
 *   在 C++ 模板元编程中，SFINAE 是一个非常重要的概念。当编译器在实例化模板的过程中，如果进行模板参数替换导致了某种语法或者语义上的错误，但只要这个错误是在对模板参数进行替换过程中产生的，编译器就不会将其当作一个硬错误来处理，而是简单地忽略掉这个特定的模板实例化版本，继续去寻找其他可能有效的模板实例化版本。
 * 
 * 2. 关于 has_reserve 结构体中的模板函数和 SFINAE 应用
 *   在 has_reserve 结构体里，有两个重载的 reserve 静态函数模板：
 *     第一个 reserve 函数模板：
 *       template <class U>
 *       static good reserve(SFINAE<U, &U::reserve>*);
 *     它的参数是一个指向 SFINAE<U, &U::reserve> 类型的指针。这里关键在于模板参数 U 以及 &U::reserve 这个表达式。这个函数模板实际上是期望 U 类型中存在名为 reserve 的成员函数，其返回类型为 void 并且接受一个 size_t 类型的参数，这样 &U::reserve 才能正确地获取到这个成员函数的地址用于构建 SFINAE 类型，并且能让这个函数模板参与重载决议。
 * 
 *     第二个 reserve 函数模板：
 *       template <class U>
 *       static bad reserve(...);
 *     它是一个可变参数函数模板，本质上是一个兜底的版本，当其他更具体的重载版本无法匹配调用时，编译器就会尝试匹配这个版本。
 * 
 * 3. nullptr 参与匹配时的情况
 *   如果 T 类型有符合条件的 reserve 成员函数：
 *     也就是 T 类型中存在返回类型为 void、接受一个 size_t 类型参数的 reserve 成员函数时，对于表达式 &T::reserve 是合法有效的，这样 SFINAE<T, &T::reserve> 类型可以正常构建，此时 reserve<T>(nullptr) 就能匹配到第一个 reserve 函数模板（那个参数为 SFINAE<U, &U::reserve>* 的版本），因为 nullptr 可以作为一个空指针赋值给指向 SFINAE<T, &T::reserve> 类型的指针参数，符合这个函数模板对于参数的要求，于是编译器会选择这个更具体的重载版本，进而 sizeof(reserve<T>(nullptr)) 就相当于 sizeof(good)。
 *   如果 T 类型没有符合条件的 reserve 成员函数：
 *     当 T 中不存在满足上述条件的 reserve 成员函数时，&T::reserve 这个表达式在进行模板参数替换过程中就会出现错误（找不到对应的合适成员函数来获取其地址），根据 SFINAE 机制，包含这个导致替换失败的模板函数版本（也就是第一个 reserve 函数模板）就会被编译器忽略掉，此时编译器就只能选择那个可变参数的兜底版本，即第二个 reserve 函数模板，那么 sizeof(reserve<T>(nullptr)) 就相当于 sizeof(bad) 了。
 * 
 * 所以说，nullptr 与 SFINAE<U, &U::reserve>* 是否能匹配成功取决于 T 类型是否具备符合特定要求的 reserve 成员函数，这也是利用了 SFINAE 机制巧妙地通过重载决议和模板参数替换情况来判断类型特征（这里就是判断是否存在特定的 reserve 成员函数）的一种常见的 C++ 元编程技巧。
 *  
 * 在 C++ 中，使用 &U::reserve 这种形式是在取成员函数的地址。当 U 是一个类类型时，
 * &U::reserve 是获取 U 类中名为 reserve 的成员函数的指针。这里 :: 是作用域解析运算符，
 * 它用于明确指出 reserve 是属于 U 类的成员函数。
 *
 */
```
