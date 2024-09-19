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

void myExitFunction(int code) {
    // 处理退出逻辑
}

你可以将 g_defaultGflagsExitFunc 指向这个函数：

g_defaultGflagsExitFunc = myExitFunction;

然后在需要调用这个函数时，可以这样做：

if (g_defaultGflagsExitFunc != nullptr) {
    g_defaultGflagsExitFunc(0); // 调用函数并传递参数
}

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

std::string g_appName;
std::string appName = "ExampleApp";

g_appName = std::move(appName);

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
#define DECLARE_UNCOPYABLE(Class) \
private: \
    Class(const Class&) = delete; \
    Class(Class&&) = delete; \
    Class& operator = (const Class&) = delete; \
    Class& operator = (Class&&) = delete;  这段代码是啥意思？

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

class MyClass {
    DECLARE_UNCOPYABLE(MyClass)

public:
    MyClass() {}
    ~MyClass() {}
};

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
using AdContextMap = ::absl::flat_hash_map<uint64_t, std::unique_ptr<AdContext>>;
const AdContextMap &adContextMap
const auto &[adgroupId, adContext] : adContextMap

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
using AdBucketInfoMap = ::absl::flat_hash_map<AdBucketType, std::unique_ptr<AdBucketInfo>>;

const AdBucketInfoMap &adBucketMap

if (auto comIter = adBucketMap.find(AdBucketType::COMMERCIAL); comIter != adBucketMap.end())
{
    stament
    ... ...
}

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
using ReqAdInfoMap = ::absl::flat_hash_map<uint64_t, ReqAdInfo>;
ReqAdInfoMap &m_reqAdInfoMap;
auto adIter = m_reqAdInfoMap.find(adgroupId);
auto &creativeMap = adIter->second.m_creativeCtxMap;

m_reqAdInfoMap.find(adgroupId) 返回的是一个迭代器，指向 absl::flat_hash_map<uint64_t, ReqAdInfo> 中键为 adgroupId 的元素。具体来说，返回的迭代器类型是 absl::flat_hash_map<uint64_t, ReqAdInfo>::iterator。

这个迭代器是一个指向键值对的指针，键值对的类型是 std::pair<const uint64_t, ReqAdInfo>。你可以通过 adIter->first 访问键，通过 adIter->second 访问值。

例如：

auto adIter = m_reqAdInfoMap.find(adgroupId);

if (adIter != m_reqAdInfoMap.end()) {
    uint64_t key = adIter->first; // 访问键
    ReqAdInfo& value = adIter->second; // 访问值
}


在这个例子中，adIter 是一个迭代器，adIter->first 是键，adIter->second 是值。

# C++ 14 新增的 make_unique 函数
std::make_unique 是 C++14 引入的一个实用函数，用于创建 std::unique_ptr 对象。它的主要优点是简化了动态内存分配，并确保内存安全管理，避免内存泄漏和错误。

优点
异常安全：如果在对象构造过程中抛出异常，std::make_unique 确保不会发生内存泄漏。
简洁：相比直接使用 new 操作符，代码更简洁明了。
避免重复代码：减少了手动管理内存的代码量。

使用方法
std::make_unique 的基本语法如下：
`#include <memory>

auto ptr = std::make_unique<T>(args...);`

T：要创建的对象类型。
args…：传递给对象构造函数的参数。
示例
以下是一个简单的示例，展示如何使用 std::make_unique：
`#include <iostream>
#include <memory>

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
`
在这个示例中，std::make_unique<MyClass>(42) 创建了一个 std::unique_ptr，指向一个 MyClass 对象，并传递 42 给它的构造函数。对象在 myPtr 超出作用域时自动销毁，确保内存安全123。


