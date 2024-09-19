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

