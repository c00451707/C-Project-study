## 真正安全的双重检查锁定
```
// 头文件
class singleton {
public:
  static singleton* instance();
  …
private:
  static mutex lock_;
  static atomic<singleton*>
    inst_ptr_;
};

// 实现文件
mutex singleton::lock_;
atomic<singleton*>
  singleton::inst_ptr_;

singleton* singleton::instance()
{
  singleton* ptr = inst_ptr_.load(
    memory_order_acquire);
  if (ptr == nullptr) {
    lock_guard<mutex> guard{lock_};
    ptr = inst_ptr_.load(
      memory_order_relaxed);
    if (ptr == nullptr) {
      ptr = new singleton();
      inst_ptr_.store(
        ptr, memory_order_release);
    }
  }
  return inst_ptr_;
}
```

总结：这段代码实现了一个线程安全的单例模式。其基本思想是：首先尝试在不加锁的情况下检查 inst_ptr_ 是否为 nullptr，如果不是则直接返回实例指针。

如果是 nullptr，则加锁后再次检查，避免多线程情况下重复创建实例。如果仍然是 nullptr，创建实例并存储在 inst_ptr_ 中，同时使用原子操作和不同的内存顺序保证多线程环境下的正确性和内存操作的有序性。

代码的小错误：return inst_ptr_;：最后返回存储在 inst_ptr_ 中的 singleton 实例指针。

这里存在一个错误，应该返回 ptr 而不是 inst_ptr_，因为 inst_ptr_ 可能已经被其他线程修改，而 ptr 是最终有效的实例指针。

