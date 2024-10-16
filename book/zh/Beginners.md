# 格式样例
https://docs.github.com/zh/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax
# **函数指针知识点：**
void(*g_defaultGflagsExitFunc)(int) = nullptr;  这个代码是啥意思？

这段代码定义了一个函数指针，并将其初始化为 nullptr。让我们逐步解析这段代码：

函数指针声明：
void(*g_defaultGflagsExitFunc)(int)

void：表示函数的返回类型是 void，即没有返回值。
(*g_defaultGflagsExitFunc)：表示这是一个指向函数的指针，指针的名称是 g_defaultGflagsExitFunc。
(int)：表示这个函数指针指向的函数接受一个 int 类型的参数。
初始化为 nullptr：
= nullptr;

nullptr 是 C++11 引入的关键字，用于表示空指针。它比传统的 NULL 更加类型安全。
综合起来，这段代码的意思是：定义一个名为 g_defaultGflagsExitFunc 的函数指针，它指向一个接受 int 参数且没有返回值的函数，并将这个指针初始化为 nullptr，表示当前没有指向任何实际的函数。

## 调用示例
假设你有一个函数如下：
```
void myExitFunction(int code) {
    // 处理退出逻辑
}
```
你可以将 g_defaultGflagsExitFunc 指向这个函数：
```
g_defaultGflagsExitFunc = myExitFunction;
```
然后在需要调用这个函数时，可以这样做：
```
if (g_defaultGflagsExitFunc != nullptr) {
    g_defaultGflagsExitFunc(0); // 调用函数并传递参数
}
```
这样，你就可以通过 g_defaultGflagsExitFunc 来调用 myExitFunction，并且在不需要时将其设置为 nullptr 来表示没有函数需要调用。

# 将对象转换为右值引用：
g_appName = std::move(appName);  解释这个代码

这段代码使用了 std::move 将 appName 的资源移动到 g_appName。让我们逐步解析这段代码：

std::move：
std::move 是 C++11 引入的一个标准库函数，用于将一个对象转换为右值引用（rvalue reference）。
右值引用允许对象的资源被“移动”而不是复制，从而提高性能，特别是在处理大型对象或资源时。
g_appName = std::move(appName);：
g_appName 是一个变量，可能是一个字符串或其他支持移动语义的类型。
appName 是另一个变量，类型与 g_appName 相同。
std::move(appName) 将 appName 转换为右值引用，表示其资源可以被移动。
赋值操作 g_appName = std::move(appName); 将 appName 的资源移动到 g_appName，而不是复制。这意味着 g_appName 将接管 appName 的资源，而 appName 将被置于一个有效但未指定的状态123。
示例
假设 g_appName 和 appName 是 std::string 类型：
```
std::string g_appName;
std::string appName = "ExampleApp";

g_appName = std::move(appName);
```
在这段代码执行后：

g_appName 将包含 "ExampleApp"。
appName 将变为空字符串，因为它的资源已经被移动到 g_appName。
优点
使用 std::move 可以避免不必要的深度拷贝，提高程序的性能，特别是在处理大型对象时。

# :: 开头表示全局作用域：
::ads::common::Singleton<Ad***Service> 代码中 :: 的作用？

由 Copilot 发送:
在 C++ 中，:: 是作用域解析运算符（scope resolution operator），用于指定命名空间或类的作用域。具体来说：

全局命名空间：
当 :: 出现在最前面时（例如 ::ads::common::Singleton），它表示全局命名空间，确保从全局命名空间开始查找符号。这在避免命名冲突时非常有用。
命名空间：
在 ::ads::common::Singleton 中，ads 和 common 是命名空间，Singleton 是 common 命名空间中的一个类或模板类。
:: 用于逐级访问命名空间中的成员。
类的成员：
:: 也可以用于访问类的静态成员或嵌套类。例如，ClassName::StaticMember。
在你的代码中，::ads::common::Singleton<Ad***Service> 表示 Singleton 类定义在 ads::common 命名空间中，并且你希望使用这个命名空间中的 Singleton 类模板来创建 Ad***Service 的单例。


# 删除复制构造函数与重载复制操作符，确保对象不会被拷贝和移动
```
#define DECLARE_UNCOPYABLE(Class)
private:
    Class(const Class&) = delete;
    Class(Class&&) = delete;
    Class& operator = (const Class&) = delete;
    Class& operator = (Class&&) = delete;  
```
这段代码是啥意思？
这段代码定义了一个宏 DECLARE_UNCOPYABLE，用于防止类的拷贝和移动操作。让我们逐行解析这段代码的含义：

宏定义：
#define DECLARE_UNCOPYABLE(Class) 定义了一个名为 DECLARE_UNCOPYABLE 的宏，接受一个参数 Class。
私有化拷贝构造函数和移动构造函数：
private: 关键字将以下成员函数声明为私有，防止外部代码访问。
Class(const Class&) = delete; 删除拷贝构造函数，防止类的拷贝。
Class(Class&&) = delete; 删除移动构造函数，防止类的移动。
私有化拷贝赋值运算符和移动赋值运算符：
Class& operator = (const Class&) = delete; 删除拷贝赋值运算符，防止类的拷贝赋值。
Class& operator = (Class&&) = delete; 删除移动赋值运算符，防止类的移动赋值。
动机
使用这个宏的动机是确保类的实例不能被拷贝或移动，从而避免潜在的资源管理问题或不期望的行为。这在需要严格控制对象生命周期的场景中特别有用，例如单例模式或管理资源的类。

示例
以下是如何在类中使用这个宏的示例：
```
class MyClass {
    DECLARE_UNCOPYABLE(MyClass)

public:
    MyClass() {}
    ~MyClass() {}
};
```

在这个示例中，MyClass 类通过 DECLARE_UNCOPYABLE 宏删除了拷贝和移动操作，从而确保 MyClass 的实例不能被拷贝或移动。

# C++中的Map对象
::absl::flat_hash_map<AdBucketType, std::unique_ptr<AdBucketInfo>>;  这个是什么类型？

这行代码定义了一个类型别名，具体来说是一个 absl::flat_hash_map，它是 Google 的 Abseil 库中的一种哈希映射容器。让我们逐步分析：

absl::flat_hash_map:

这是 Abseil 库提供的一种哈希映射容器，类似于标准库中的 std::unordered_map。它通常具有更好的性能，特别是在内存使用和查找速度方面。

<AdBucketType, std::unique_ptr<AdBucketInfo>>:

这是 flat_hash_map 的模板参数，定义了键和值的类型。

AdBucketType：这是键的类型，表示哈希映射中每个元素的键。

std::unique_ptr<AdBucketInfo>：这是值的类型，表示哈希映射中每个元素的值。std::unique_ptr 是一种智能指针，负责管理 AdBucketInfo 对象的生命周期，确保在不再需要时自动释放内存。

总结一下，这行代码定义了一个 flat_hash_map，它将 AdBucketType 类型的键映射到 std::unique_ptr<AdBucketInfo> 类型的值。这种结构通常用于高效地存储和查找与 AdBucketType 相关的 AdBucketInfo 对象，同时确保内存管理的安全性。

# C++17 提供的遍历Map对象新特性
```
using AdContextMap = ::absl::flat_hash_map<uint64_t, std::unique_ptr<AdContext>>;
const AdContextMap &adContextMap
const auto &[adgroupId, adContext] : adContextMap
```

类型别名声明：
using AdContextMap = ::absl::flat_hash_map<uint64_t, std::unique_ptr<AdContext>>;

这行代码使用 using 关键字定义了一个类型别名 AdContextMap。
AdContextMap 是一个 absl::flat_hash_map，它将 uint64_t 类型的键映射到 std::unique_ptr<AdContext> 类型的值。
常量引用声明：
const AdContextMap &adContextMap;

这行代码声明了一个常量引用 adContextMap，它引用一个 AdContextMap 类型的对象。
const 关键字表示 adContextMap 是不可修改的。
结构化绑定声明：
const auto &[adgroupId, adContext] : adContextMap;

这行代码使用 C++17 引入的结构化绑定声明来解构 adContextMap 中的元素。
const auto & 表示绑定的变量是常量引用。
[adgroupId, adContext] 是解构绑定的变量名，分别对应 adContextMap 中的键和值。
: adContextMap 表示从 adContextMap 中提取元素。
总结一下，这段代码的作用是：

定义一个类型别名 AdContextMap，表示一个哈希映射容器。
声明一个常量引用 adContextMap，引用一个 AdContextMap 对象。
使用结构化绑定从 adContextMap 中提取键值对，并将键绑定到 adgroupId，将值绑定到 adContext。

# Map对象的find实现原理
## find函数用法1
```
using AdBucketInfoMap = ::absl::flat_hash_map<AdBucketType, std::unique_ptr<AdBucketInfo>>;
const AdBucketInfoMap &adBucketMap
if (auto comIter = adBucketMap.find(AdBucketType::COMMERCIAL); comIter != adBucketMap.end())
{
    stament
    ... ...
}
```
让我们逐步分析这段代码：

类型别名声明：
using AdBucketInfoMap = ::absl::flat_hash_map<AdBucketType, std::unique_ptr<AdBucketInfo>>;

这行代码使用 using 关键字定义了一个类型别名 AdBucketInfoMap。
AdBucketInfoMap 是一个 absl::flat_hash_map，它将 AdBucketType 类型的键映射到 std::unique_ptr<AdBucketInfo> 类型的值。
常量引用声明：
const AdBucketInfoMap &adBucketMap;

这行代码声明了一个常量引用 adBucketMap，它引用一个 AdBucketInfoMap 类型的对象。
const 关键字表示 adBucketMap 是不可修改的。
查找元素并检查是否存在：
auto comIter = adBucketMap.find(AdBucketType::COMMERCIAL);
comIter != adBucketMap.end();

这两行代码首先使用 find 方法在 adBucketMap 中查找键为 AdBucketType::COMMERCIAL 的元素。
auto 关键字让编译器自动推断 comIter 的类型，它是一个迭代器，指向找到的元素或 adBucketMap 的 end 迭代器。
comIter != adBucketMap.end() 检查是否找到了对应的元素。如果 comIter 不等于 adBucketMap.end()，则表示找到了键为 AdBucketType::COMMERCIAL 的元素。
总结一下，这段代码的作用是：

定义一个类型别名 AdBucketInfoMap，表示一个哈希映射容器。
声明一个常量引用 adBucketMap，引用一个 AdBucketInfoMap 对象。
在 adBucketMap 中查找键为 AdBucketType::COMMERCIAL 的元素，并检查该元素是否存在。

## find函数用法2
```
using ReqAdInfoMap = ::absl::flat_hash_map<uint64_t, ReqAdInfo>;
ReqAdInfoMap &m_reqAdInfoMap;
auto adIter = m_reqAdInfoMap.find(adgroupId);
auto &creativeMap = adIter->second.m_creativeCtxMap;
```

m_reqAdInfoMap.find(adgroupId) 返回的是一个迭代器，指向 absl::flat_hash_map<uint64_t, ReqAdInfo> 中键为 adgroupId 的元素。具体来说，返回的迭代器类型是 absl::flat_hash_map<uint64_t, ReqAdInfo>::iterator。

这个迭代器是一个指向键值对的指针，键值对的类型是 std::pair<const uint64_t, ReqAdInfo>。你可以通过 adIter->first 访问键，通过 adIter->second 访问值。

例如：
```
auto adIter = m_reqAdInfoMap.find(adgroupId);

if (adIter != m_reqAdInfoMap.end()) {
    uint64_t key = adIter->first; // 访问键
    ReqAdInfo& value = adIter->second; // 访问值
}
```

在这个例子中，adIter 是一个迭代器，adIter->first 是键，adIter->second 是值。

# C++ 14 新增的 make_unique 函数
std::make_unique 是 C++14 引入的一个实用函数，用于创建 std::unique_ptr 对象。它的主要优点是简化了动态内存分配，并确保内存安全管理，避免内存泄漏和错误。

优点
异常安全：如果在对象构造过程中抛出异常，std::make_unique 确保不会发生内存泄漏。
简洁：相比直接使用 new 操作符，代码更简洁明了。
避免重复代码：减少了手动管理内存的代码量。

使用方法
std::make_unique 的基本语法如下：
```
#include <memory>

auto ptr = std::make_unique<T>(args...);
```

T：要创建的对象类型。
args…：传递给对象构造函数的参数。
示例
以下是一个简单的示例，展示如何使用 std::make_unique：
`#include <iostream>
#include <memory>

```
class MyClass {
public:
    MyClass(int value) : value_(value) {
        std::cout << "Object Created with value: " << value_ << std::endl;
    }
    ~MyClass() {
        std::cout << "Object Destroyed" << std::endl;
    }
private:
    int value_;
};

int main() {
    auto myPtr = std::make_unique<MyClass>(42);
    // 使用 myPtr 进行操作
    return 0;
}
```
在这个示例中，std::make_unique<MyClass>(42) 创建了一个 std::unique_ptr，指向一个 MyClass 对象，并传递 42 给它的构造函数。对象在 myPtr 超出作用域时自动销毁，确保内存安全123。

# Map 的emplace 函数返回
map 的 emplace 函数返回一个 std::pair，其中包含两个元素：

迭代器：指向新插入的元素，或者指向具有等价键的现有元素。
布尔值：表示是否成功插入。如果插入成功，则为 true；如果键已经存在且没有插入新元素，则为 false。
以下是一个示例，展示如何使用 emplace 函数及其返回值：
```
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> myMap;

    // 尝试插入一个新元素
    auto result = myMap.emplace(1, "one");

    if (result.second) {
        std::cout << "插入成功: " << result.first->first << " => " << result.first->second << std::endl;
    } else {
        std::cout << "插入失败，键已存在: " << result.first->first << " => " << result.first->second << std::endl;
    }

    // 尝试插入一个具有相同键的元素
    result = myMap.emplace(1, "uno");

    if (result.second) {
        std::cout << "插入成功: " << result.first->first << " => " << result.first->second << std::endl;
    } else {
        std::cout << "插入失败，键已存在: " << result.first->first << " => " << result.first->second << std::endl;
    }

    return 0;
}
```
在这个示例中，第一次调用 emplace 成功插入了键为 1 的元素，因此 result.second 为 true。第二次调用 emplace 由于键 1 已经存在，插入失败，result.second 为 false.

# std::unique_ptr 智能指针的 get() 方法
std::unique_ptr 的 get 方法用于获取 unique_ptr 所管理的原始指针，而不会改变 unique_ptr 的所有权。它返回一个指向托管对象的指针，如果 unique_ptr 不管理任何对象，则返回 nullptr。

使用示例
以下是一个简单的示例，展示如何使用 get 方法：
```
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);

    // 使用 get 方法获取原始指针
    int* rawPtr = ptr.get();

    std::cout << "Value: " << *rawPtr << std::endl;

    // 注意：不要手动删除 rawPtr 指向的对象
    // delete rawPtr; // 这样做会导致未定义行为

    return 0;
}
```
在这个示例中，ptr.get() 返回一个指向 42 的原始指针 rawPtr。需要注意的是，虽然你可以使用这个原始指针，但你不应该手动删除它，因为 unique_ptr 会在其生命周期结束时自动管理和释放内存123.

主要特点
不改变所有权：get 方法不会改变 unique_ptr 的所有权，只是提供对托管对象的访问。
异常安全：即使在异常情况下，unique_ptr 仍然会正确管理内存。


# std::vector 的 emplace_back方法
std::vector 的 emplace_back 方法是在容器末尾直接构造一个新元素，而不是先创建一个临时对象再将其移动或拷贝到容器中。这样可以避免不必要的拷贝或移动操作，从而提高性能。

### 使用方法
emplace_back 方法接受可变参数列表，并将这些参数直接传递给新元素的构造函数。以下是一个简单的示例：
```
#include <iostream>
#include <vector>

class MyClass {
public:
    MyClass(int x, double y) : x_(x), y_(y) {
        std::cout << "MyClass constructed with x = " << x_ << " and y = " << y_ << std::endl;
    }
private:
    int x_;
    double y_;
};

int main() {
    std::vector<MyClass> vec;
    vec.emplace_back(10, 20.5); // 直接在 vector 末尾构造 MyClass 对象

    return 0;
}
```
在这个示例中，emplace_back 方法直接在 vec 的末尾构造了一个 MyClass 对象，传递的参数是 10 和 20.5123.

### 优点
减少拷贝和移动操作：相比 push_back，emplace_back 可以避免临时对象的创建，从而减少拷贝和移动操作。
提高性能：在需要频繁插入复杂对象的场景中，emplace_back 可以显著提高性能。

### 适用场景
构造复杂对象：当插入的对象需要多个参数构造时，emplace_back 可以直接传递构造函数参数。

性能优化：在性能敏感的应用中，使用 emplace_back 可以减少不必要的开销。

# 类型转换 static_cast<uint32_t>(modelType) 
static_cast<uint32_t>(modelType) 是 C++ 中的一种类型转换操作。它将 modelType 变量转换为 uint32_t 类型。以下是一些详细解释：

类型转换：static_cast 是 C++ 中的四种类型转换操作符之一，其他三种是 dynamic_cast、const_cast 和 reinterpret_cast。static_cast 用于执行编译时类型检查的转换，确保转换是安全的。

转换为 uint32_t：uint32_t 是一个无符号 32 位整数类型，通常用于需要明确大小的整数操作。通过 static_cast，你可以将 modelType 转换为这种类型2。
使用场景：这种转换通常用于需要确保变量类型一致的场景，例如在处理不同类型的枚举值或其他类型的数值时。

示例：
```
enum class ModelType { TypeA, TypeB, TypeC };
ModelType modelType = ModelType::TypeA;
uint32_t modelTypeValue = static_cast<uint32_t>(modelType);
```

// 现在 modelTypeValue 是一个无符号 32 位整数，表示 modelType 的数值
这种转换在编译时进行检查，确保 modelType 可以安全地转换为 uint32_t 类型。

# Lambda 表达式的高阶使用方法
Task类声明
```
class Task final : public Runnable {
public:
    using Callback = std::function<void()>;

    // 调用方保证 closure 不为空
    explicit Task(::ads::common::Closure<void()> *closure, uint64_t priority = 0)
        : m_function([closure] { closure->Run(); }),
          m_priority(priority)
    {
    }
    // 调用方保证 function 不为空
    template<class Function>
    explicit Task(Function &&function, uint64_t priority = 0)
        : m_function(std::forward<Function>(function)),
          m_priority(priority)
    {
    }
    ~Task() override = default;

    void Run() override
    {
        m_function();
    }

    [[nodiscard]] uint64_t GetPriority() const
    {
        return m_priority;
    }

    Callback ExtractFunc()
    {
        return std::move(m_function);
    }

    bool operator<(const Task &other) const
    {
        // m_priority 越小优先级越高
        return m_priority > other.GetPriority();
    }

    DECLARE_UNCOPYABLE(Task);

private:
    Callback m_function;

    // m_priority 越小优先级越高
    uint64_t m_priority{0};
};
```
使用方法
```
        // lambda 表达式，当调用它时，会执行当前对象的 Execute 方法，并传递 task 变量
        auto exeFunc = [this, task] { this->Execute(task); };
        /*
         * exeFunc 赋值给 ::ads::common::Closure<void()> *closure 对象
         * 当你将 exeFunc 传递给 Closure<void()> 接口时，编译器会隐式地创建一个匿名类来实现 Closure<void()> 接口。这个匿名类会将 exeFunc 的调用逻辑包装到 Run 方法中。
         */
        auto exeTask = std::make_unique<dsp::common::Task>(exeFunc, GetTaskPriority(task));
```

代码解释：
当你将 exeFunc 传递给 Closure<void()> 接口时，编译器会隐式地创建一个匿名类来实现 Closure<void()> 接口。这个匿名类会将 exeFunc 的调用逻辑包装到 Run 方法中。

实际上，这个过程如下：

捕获 lambda 表达式：创建一个捕获 this 和 task 的 lambda 表达式。

cpp

```
auto exeFunc = [this, task] { this->Execute(task); };
传递 lambda 表达式：将 exeFunc 传递给 Task 的构造函数。
```
```
std::make_unique<dsp::common::Task>(exeFunc, 1);
```
编译器生成匿名类：编译器会自动生成一个匿名类，实现 Closure<void()> 接口，并将 lambda 表达式的逻辑包装到 Run 方法中。

调用 Run 方法：当 Run 方法被调用时，实际执行的是 exeFunc 内的逻辑，即 this->Execute(task)。

```
m_function([closure] { closure->Run(); }), 那这个代码片段是啥意思呢？
```
这行代码的作用是使用一个 lambda 表达式来初始化 m_function。具体细节如下：

[closure]：这部分捕获列表，表示 lambda 表达式捕获 closure 变量，允许在 lambda 表达式体内使用它。

{ closure->Run(); }：这是 lambda 表达式的主体，表示调用 closure 的 Run 方法。

所以，m_function([closure] { closure->Run(); }) 这段代码的意思是，将一个会调用 closure->Run() 的 lambda 表达式赋值给 m_function。当你以后调用 m_function() 时，它实际上会执行 closure->Run()，相当于间接调用了 closure 的 Run 方法。

## 讲讲捕获参数的含义，它和传递入参有什么区别，并且给出一个传递入参的样例，方便我理解？

捕获参数和传递入参在 lambda 表达式中的用途有所不同：
捕获参数：在定义 lambda 表达式时捕获作用域内的变量，这些变量在 lambda 表达式体内可以直接使用。捕获列表包含在方括号 [] 中。
传递入参：这是函数调用时传递的参数，列在圆括号 () 中，函数体内使用这些传入参数进行操作。

捕获参数示例：
```
#include <iostream>
int main() {
    int x = 10;
    int y = 20;

    // 捕获 x 和 y
    auto lambda = [x, y]() {
        std::cout << "x + y = " << x + y << std::endl;
    };

    lambda(); // 输出: x + y = 30

    return 0;
}
```
在上面的例子中，lambda 捕获了 x 和 y，在 lambda 表达式体内可以直接使用它们。

传递入参示例：
```
#include <iostream>
int main() {
    // 定义一个 lambda，接受两个参数
    auto lambda = [](int a, int b) {
        std::cout << "a + b = " << a + b << std::endl;
    };

    int x = 10;
    int y = 20;
    lambda(x, y); // 输出: a + b = 30

    return 0;
}
```
在这个例子中，lambda 是一个接受两个参数 a 和 b 的函数，在调用时传递 x 和 y。

总结来说，捕获参数是在定义时将外部变量引入 lambda 表达式，而传递入参是在调用时将参数传递给 lambda 表达式。希望这个解释能让你更清晰理解这两者的区别！有其他问题要讨论吗？

