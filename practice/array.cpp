//容器库
//容器库是类模板与算法的汇集，允许程序员简单地访问常见数据结构，例如队列、链表和栈。有三类容器——顺序容器、关联容器和无序关联容器——每种都被设计为支持不同组的操作。
//容器管理为其元素分配的存储空间，并提供直接或间接地通过迭代器（拥有类似指针属性的对象）访问它们的函数。
//大多数容器拥有至少几个常见的成员函数，并共享功能。特定应用的最佳容器不仅依赖于提供的功能，还依赖于对于不同工作量的效率。
/*
顺序容器 顺序容器实现能按顺序访问的数据结构。
    array静态的连续数组
    vector动态的连续数组
    deque双端队列
    forward_list单链表
    list双链表

关联容器 关联容器实现能快速查找（ O(log n) 复杂度）的数据结构。
    set 唯一键的集合，按照键排序
    map 键值对的集合，按照键排序，键是唯一的
    multiset 键的集合，按照键排序
    multimap 键值对的集合，按照键排序

无序关联容器 无序关联容器提供能快速查找（均摊 O(1) ，最坏情况 O(n) 的复杂度）的无序（哈希）数据结构。
    unordered_set 唯一键的集合，按照键生成散列
    unordered_map 键值对的集合，按照键生成散列，键是唯一的
    unordered_multiset 键的集合，按照键生成散列
    unordered_multimap 键值对的集合，按照键生成散列

容器适配器 容器适配器提供顺序容器的不同接口。
    stack 适配一个容器以提供栈（LIFO 数据结构）
    queue 适配一个容器以提供队列（FIFO 数据结构）
    priority_queue 适配一个容器以提供优先级队列
 */

/*
template <class T, size_t N >
struct array
{
    // types:
    typedef T & reference;
    typedef const T & const_reference;
    typedef implementation defined iterator;
    typedef implementation defined const_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // No explicit construct/copy/destroy for aggregate type
    void fill(const T& u);
    void swap(array& a) noexcept(is_nothrow_swappable_v<T>); // 将容器内容与 other 的内容交换。不导致迭代器和引用关联到别的容器。

    // iterators:
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // capacity:
    constexpr size_type size() const noexcept;
    constexpr size_type max_size() const noexcept;  // 因为每个 std::array<T, N> 都是固定大小容器，故 max_size 返回的值等于 N （亦为 size 所返回的值）


    constexpr bool empty() const noexcept;

    // element access:
    reference operator[](size_type n);   // 可修改的左值
    const_reference operator[](size_type n) const; // constexpr in C++14
    const_reference at(size_type n) const; // constexpr in C++14
    reference at(size_type n);      // 可修改的左值

    reference front();      // 返回到容器首元素的引用。在空容器上对 front 的调用是未定义的。
    const_reference front() const; // constexpr in C++14
    reference back();   // 返回到容器中最后一个元素的引用。 在空容器上调用 back 导致未定义行为。
    const_reference back() const; // constexpr in C++14

    T* data() noexcept;
    const T* data() const noexcept;
};
 */


#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

using namespace std;


void t1() {
    // 用聚合初始化构造
    std::array<int, 3> a1{ {1, 2, 3} }; // CWG 1270 重申前的 C++11 中要求双花括号
    // （ C++11 之后的版本和 C++14 起不要求）
    std::array<int, 3> a2 = {1, 2, 3};  // = 后决不要求
    std::array<std::string, 2> a3 = { std::string("a"), "b" };

    // 支持容器操作
    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(),
                      std::ostream_iterator<int>(std::cout, " "));

    std::cout << '\n';

    // 支持带范围 for 循环
    for(const auto& s: a3)
        std::cout << s << ' ';
}

//按字典序比较 lhs 与 rhs 的内容。
//是否相等，即它们是否拥有相同数量的元素且 lhs 中每个元素与 rhs 的同位置元素比较相等。
int tcompare()
{
    std::array<int, 3> alice{1, 2, 3};
    std::array<int, 3> bob{7, 8, 9};
    std::array<int, 3> eve{1, 2, 3};

    std::cout << std::boolalpha;

    // 比较不相等的容器
    std::cout << "alice == bob returns " << (alice == bob) << '\n';
    std::cout << "alice != bob returns " << (alice != bob) << '\n';
    std::cout << "alice <  bob returns " << (alice < bob) << '\n';
    std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
    std::cout << "alice >  bob returns " << (alice > bob) << '\n';
    std::cout << "alice >= bob returns " << (alice >= bob) << '\n';

    std::cout << '\n';

    // 比较相等的容器
    std::cout << "alice == eve returns " << (alice == eve) << '\n';
    std::cout << "alice != eve returns " << (alice != eve) << '\n';
    std::cout << "alice <  eve returns " << (alice < eve) << '\n';
    std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
    std::cout << "alice >  eve returns " << (alice > eve) << '\n';
    std::cout << "alice >= eve returns " << (alice >= eve) << '\n';
}

// 返回位于指定位置 pos 的元素的引用，有边界检查。 若 pos 不在容器范围内，则抛出 std::out_of_range 类型的异常。
int tat() {
    std::array<int,6> data = { 1, 2, 4, 5, 5, 6 };
    // Set element 1
    data.at(1) = 88;
    // Read element 2
    std::cout << "Element at index 2 has value " << data.at(2) << '\n';
    std::cout << "data size = " << data.size() << '\n';
    try {
        // Set element 6
        data.at(6) = 666;
    } catch (std::out_of_range const& exc) {
        std::cout << "exception: " << exc.what() << '\n';
    }
    // Print final values
    std::cout << "data:";
    for (int elem : data)
        std::cout << " " << elem;
    std::cout << '\n';
}

int treference() {
    std::array<char, 6> letters {'o', 'm', 'g', 'w', 't', 'f'};
    if (!letters.empty()) {
        std::cout << "The first character is: " << letters.front() << '\n';
    }
}
int tback() {
    std::array<char, 6> letters {'o', 'm', 'g', 'w', 't', 'f'};
    if (!letters.empty()) {
        std::cout << "before change: The first character is: " << letters.back() << '\n';
        letters.back() = 'z';
        std::cout << "after change: The first character is: " << letters.back() << '\n';
    }
}

int t2()
{
    std::array<int,4> numbers {2, 4, 6, 8};
    std::cout << "Second element: " << numbers[1] << '\n';
    numbers[0] = 5;
    std::cout << "All numbers:";
    for (auto i : numbers) {
        std::cout << ' ' << i;
    }
    std::cout << '\n';
}


// 尽可能不要操作由智能指针所管理的元素指针
int tdata() {
    std::array<char, 6> letters {'o', 'm', 'g', 'w', 't', 'f'};
    char *p = letters.data();
    cout << *p << endl;
    *p = 'z';
    cout << *(p) << endl;

    cout << *(p+1) << endl;
}

// 迭代器采用 [beg, end) 策略只想容器中的元素
int titerator()
{
    std::cout << std::boolalpha;
    std::array<int, 0> empty;
    std::cout << "1) "
              << (empty.begin() == empty.end()) << ' '     // true
              << (empty.cbegin() == empty.cend()) << '\n'; // true
    // *(empty.begin()) = 42; // => 运行时的未定义行为

    std::array<int, 4> numbers{5, 2, 3, 4};
    std::cout << "2) "
              << (numbers.begin() == numbers.end()) << ' '    // false
              << (numbers.cbegin() == numbers.cend()) << '\n' // false
              << "3) "
              << *(numbers.begin()) << ' '    // 5
              << *(numbers.cbegin()) << '\n'; // 5

    *numbers.begin() = 1;
    std::cout << "4) " << *(numbers.begin()) << '\n'; // 1
    // *(numbers.cbegin()) = 42; // 编译时错误：
    // 只读变量不可赋值

    // 打印所有元素
    std::cout << "5) ";
    std::for_each(numbers.cbegin(), numbers.cend(), [](int x) {
        std::cout << x << ' ';
    });
    std::cout << '\n';


    std::array<char, 3> constants{'A', 'B', 'C'};
    assert(constants.begin() != constants.end());   // OK
    assert(constants.cbegin() != constants.cend()); // OK
    assert(*constants.begin() == 'A');              // OK
    assert(*constants.cbegin() == 'A');             // OK
    // *constants.begin() = 'Z'; // 编译时错误：
    // 只读变量不可赋值
}


int tfill() {
    constexpr int xy = 4;
    using Cell = std::array<unsigned char, 8>;
    std::array<Cell, xy * xy> board;

    board.fill({ {0xE2, 0x96, 0x84, 0xE2, 0x96, 0x80, 0, 0} }); // "▄▀";
    for (unsigned i = 0; i != board.size();) {
        std::cout << board[i].data();
        if ((++i % xy) == 0) {
            std::cout.put('\n');
        }
    }
}

int tget()
{
    std::array<int, 3> arr;
    // 设置值：
    std::get<0>(arr) = 1;
    std::get<1>(arr) = 2;
    std::get<2>(arr) = 3;
    // 获取值：
    std::cout << "(" << std::get<0>(arr) << ", " << std::get<1>(arr)
              << ", " << std::get<2>(arr) << ")\n";
}

