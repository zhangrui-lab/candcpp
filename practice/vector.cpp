/*
元素相继存储，这意味着不仅可通过迭代器，还能用指向元素的常规指针访问元素。这意味着指向 vector 元素的指针能传递给任何期待指向数组元素的指针的函数。
vector 的存储是自动管理的，按需扩张收缩。 vector 通常占用多于静态数组的空间，因为要分配更多内存以管理将来的增长。 vector 所用的方式不在每次插入元素时，而只在额外内存耗尽时重分配。
分配的内存总量可用 capacity() 函数查询。额外内存可通过对 shrink_to_fit() 的调用返回给系统。 (C++11 起)
重分配通常是性能上有开销的操作。若元素数量已知，则 reserve() 函数可用于消除重分配。
vector 上的常见操作复杂度（效率）如下：
    随机访问——常数 O(1)
    在末尾插入或移除元素——均摊常数 O(1)
    插入或移除元素——与到 vector 结尾的距离成线性 O(n)


// 结构原型
template <class T, class Allocator = allocator<T> >
class vector
{
public:
    typedef T                                        value_type;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef implementation-defined                   iterator;
    typedef implementation-defined                   const_iterator;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

    vector()
        noexcept(is_nothrow_default_constructible<allocator_type>::value);
    explicit vector(const allocator_type&);
    explicit vector(size_type n);
    explicit vector(size_type n, const allocator_type&); // C++14
    vector(size_type n, const value_type& value, const allocator_type& = allocator_type());
    template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& = allocator_type());
    vector(const vector& x);
    vector(vector&& x)
        noexcept(is_nothrow_move_constructible<allocator_type>::value);
    vector(initializer_list<value_type> il);
    vector(initializer_list<value_type> il, const allocator_type& a);
    ~vector();
    vector& operator=(const vector& x);
    vector& operator=(vector&& x)
        noexcept(
             allocator_type::propagate_on_container_move_assignment::value ||
             allocator_type::is_always_equal::value); // C++17
    vector& operator=(initializer_list<value_type> il);
    template <class InputIterator>
        void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type& u);
    void assign(initializer_list<value_type> il);

    allocator_type get_allocator() const noexcept;

    iterator               begin() noexcept;
    const_iterator         begin()   const noexcept;
    iterator               end() noexcept;
    const_iterator         end()     const noexcept;

    reverse_iterator       rbegin() noexcept;
    const_reverse_iterator rbegin()  const noexcept;
    reverse_iterator       rend() noexcept;
    const_reverse_iterator rend()    const noexcept;

    const_iterator         cbegin()  const noexcept;
    const_iterator         cend()    const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend()   const noexcept;

    size_type size() const noexcept;
    size_type max_size() const noexcept;
    size_type capacity() const noexcept;
    bool empty() const noexcept;

    // 增加 vector 的容量到大于或等于 new_cap 的值。若 new_cap 大于当前的 capacity() ，则分配新存储，否则该方法不做任何事。reserve() 不更改 vector 的 size 。若 new_cap 大于 capacity() ，
    // 则所有迭代器，包含尾后迭代器和所有到元素的引用都被非法化。否则，没有迭代器或引用被非法化。
    void reserve(size_type new_cap);

    void shrink_to_fit() noexcept;

    reference       operator[](size_type n);    // 不同于 std::map::operator[] ，此运算符决不插入新元素到容器。通过此运算符访问不存在的元素是未定义行为。  (返回引用， 不存在的位置会被赋值， 但容器的 size 不会更新)
    const_reference operator[](size_type n) const;
    reference       at(size_type n);
    const_reference at(size_type n) const;

    reference       front();        // 返回到容器首元素的引用。在空容器上对 front 的调用是未定义的。
    const_reference front() const;
    reference       back(); // 返回到容器中最后一个元素的引用。在空容器上调用 back 导致未定义行为。
    const_reference back() const;

    value_type*       data() noexcept;  // 返回指向作为元素存储工作的底层数组的指针。指针满足范围 [data(); data() + size()) 始终是合法范围，即使容器为空（该情况下 data() 不可解引用）。

    const value_type* data() const noexcept;

    void push_back(const value_type& x);
    void push_back(value_type&& x);
    template <class... Args>
        reference emplace_back(Args&&... args); // reference in C++17
    void pop_back();

    template <class... Args> iterator emplace(const_iterator position, Args&&... args);
    iterator insert(const_iterator position, const value_type& x);
    iterator insert(const_iterator position, value_type&& x);
    iterator insert(const_iterator position, size_type n, const value_type& x);
    template <class InputIterator>
        iterator insert(const_iterator position, InputIterator first, InputIterator last);
    iterator insert(const_iterator position, initializer_list<value_type> il);

    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);

    void clear() noexcept;  // 从容器擦除所有元素。此调用后 size() 返回零。非法化任何指代所含元素的引用、指针或迭代器。任何尾后迭代器亦被非法化。保持 vector 的 capacity() 不变（注意：更改容量上的标准限制在 vector::reserve 的规定中）。

    void resize(size_type sz);
    void resize(size_type sz, const value_type& c);

    void swap(vector&)
        noexcept(allocator_traits<allocator_type>::propagate_on_container_swap::value ||
                 allocator_traits<allocator_type>::is_always_equal::value);  // C++17

    bool __invariants() const;
};
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int tclear()
{
    std::vector<int> container{1, 2, 3};

    auto print = [](const int& n) { std::cout << " " << n; };

    std::cout << "Before clear:";
    std::for_each(container.cbegin(), container.cend(), print);
    std::cout << "\nSize=" << container.size() << '\n';

    std::cout << "Clear\n";
    container.clear();

    std::cout << "After clear:";
    std::for_each(container.begin(), container.end(), print);
    std::cout << "\nSize=" << container.size() << '\n';
}

int tassign()
{
    std::vector<char> characters;
    characters.assign(5, 'a');
    for (char c : characters) {
        std::cout << c << ' ';
    }
    characters.assign({'\n', 'C', '+', '+', '1', '1', '\n'});
    for (char c : characters) {
        std::cout << c;
    }
}

int tat()
{
    std::vector<int> data = { 1, 2, 4, 5, 5, 6 };

    // Set element 1
    data.at(1) = 88;

    // Read element 2
    std::cout << "Element at index 2 has value " << data.at(2) << '\n';

    std::cout << "data size = " << data.size() << '\n';

    try {
        // Set element 6
        data.at(6) = 666;
    } catch (std::out_of_range const& exc) {
        std::cout << "Exception: " << exc.what() << '\n';
    }

    // Print final values
    std::cout << "data:";
    for (int elem : data)
        std::cout << " " << elem;
    std::cout << '\n';
}

int t1()
{
    std::vector<int> numbers {2, 4, 6, 8};
    std::cout << "Second element: " << numbers[1] << '\n';
    numbers[0] = 5;
    numbers[4] = 10;
    std::cout << numbers.size() << " numbers:";
    for (auto i : numbers) {
        std::cout << ' ' << i;
    }
    std::cout << '\n';
    cout << numbers[4] << endl;
}

int tfront()
{
    std::vector<char> letters {'o', 'm', 'g', 'w', 't', 'f'};
    if (!letters.empty()) {
        std::cout << "The first character is: " << letters.front() << '\n';
        letters.front() = 'z';
        std::cout << "The first character is: " << letters.front() << '\n';
    }
    std::vector<int> nums;
    cout << nums.size() << endl;
//    nums.front() = 10;  // error
//    cout << nums.front() << endl;
//    cout << nums.size() << endl;
}

int tdata() {
    vector<string> users = {"jack", "tom", "jordormn", "za"};
    string *p = users.data();
    for (int i = 0; i < users.size(); ++i) {
        cout << *(p+i) << endl;
    }
}

void print_vec(const std::vector<int>& vec)
{
    for (auto x: vec) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';
}

int tinsert()
{
    std::vector<int> vec(3,100);
    print_vec(vec);

    auto it = vec.begin();
    it = vec.insert(it, 200);
    print_vec(vec);

    vec.insert(it,2,300);
    print_vec(vec);

    // "it" 不再合法，获取新值：
    it = vec.begin();

    std::vector<int> vec2(2,400);
    vec.insert(it+2, vec2.begin(), vec2.end());
    print_vec(vec);

    int arr[] = { 501,502,503 };
    vec.insert(vec.begin(), arr, arr+3);
    print_vec(vec);
}

int titerator()
{
    std::vector<int> nums {1, 2, 4, 8, 16};
    std::vector<std::string> fruits {"orange", "apple", "raspberry"};
    std::vector<char> empty;

    // 求和 vector nums 中的所有整数（若存在），仅打印结果。
    std::cout << "Sum of nums: " << std::accumulate(nums.cbegin(), nums.cend(), 0) << "\n";

    // 打印 vector fruits 中的首个 fruis ，不检查是否有一个。
    std::cout << "First fruit: " << *fruits.cbegin() << "\n";

    if (empty.begin() == empty.end())
        std::cout << "vector 'empty' is indeed empty.\n";
}

