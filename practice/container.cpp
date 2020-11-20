/*
//std::stack 类是容器适配器，它给予程序员栈的功能——特别是 FILO （先进后出）数据结构。
//该类模板表现为底层容器的包装器——只提供特定函数集合。栈从被称作栈顶的容器尾部推弹元素。
template <class T, class Container = deque<T>>
class stack
{
public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;

protected:
    container_type c;

public:
    stack() = default;
    ~stack() = default;

    stack(const stack& q) = default;
    stack(stack&& q) = default;

    stack& operator=(const stack& q) = default;
    stack& operator=(stack&& q) = default;

    explicit stack(const container_type& c);
    explicit stack(container_type&& c);
    template <class Alloc> explicit stack(const Alloc& a);
    template <class Alloc> stack(const container_type& c, const Alloc& a);
    template <class Alloc> stack(container_type&& c, const Alloc& a);
    template <class Alloc> stack(const stack& c, const Alloc& a);
    template <class Alloc> stack(stack&& c, const Alloc& a);

    bool empty() const;
    size_type size() const;
    reference top();
    const_reference top() const;

    void push(const value_type& x);
    void push(value_type&& x);
    template <class... Args> reference emplace(Args&&... args); // reference in C++17
    void pop();

    void swap(stack& c) noexcept(is_nothrow_swappable_v<Container>)
};


// std::queue 类是容器适配器，它给予程序员队列的功能——尤其是 FIFO （先进先出）数据结构。
//类模板表现为底层容器的包装器——只提供特定的函数集合。 queue 在底层容器尾端推入元素，从首端弹出元素。
template <class T, class Container = deque<T>>
class queue
{
public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;

protected:
    container_type c;

public:
    queue() = default;
    ~queue() = default;

    queue(const queue& q) = default;
    queue(queue&& q) = default;

    queue& operator=(const queue& q) = default;
    queue& operator=(queue&& q) = default;

    explicit queue(const container_type& c);
    explicit queue(container_type&& c)
    template <class Alloc>
        explicit queue(const Alloc& a);
    template <class Alloc>
        queue(const container_type& c, const Alloc& a);
    template <class Alloc>
        queue(container_type&& c, const Alloc& a);
    template <class Alloc>
        queue(const queue& q, const Alloc& a);
    template <class Alloc>
        queue(queue&& q, const Alloc& a);

    bool      empty() const;
    size_type size() const;

    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;

    void push(const value_type& v);
    void push(value_type&& v);
    template <class... Args> reference emplace(Args&&... args); // reference in C++17
    void pop();

    void swap(queue& q) noexcept(is_nothrow_swappable_v<Container>)
};

//priority_queue 是容器适配器，它提供常数时间的（默认）最大元素查找，对数代价的插入与释出。
//可用用户提供的 Compare 更改顺序，例如，用 std::greater<T> 将导致最小元素作为 top() 出现。
//用 priority_queue 工作类似管理某些随机访问容器中的堆，优势是不可能突然把堆非法化。
template <class T, class Container = vector<T>,
          class Compare = less<typename Container::value_type>>
class priority_queue
{
public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;

protected:
    container_type c;
    Compare comp;

public:
    priority_queue() = default;
    ~priority_queue() = default;

    priority_queue(const priority_queue& q) = default;
    priority_queue(priority_queue&& q) = default;

    priority_queue& operator=(const priority_queue& q) = default;
    priority_queue& operator=(priority_queue&& q) = default;

    explicit priority_queue(const Compare& comp);
    priority_queue(const Compare& comp, const container_type& c);
    explicit priority_queue(const Compare& comp, container_type&& c);
    template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last,
                       const Compare& comp = Compare());
    template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last,
                       const Compare& comp, const container_type& c);
    template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last,
                       const Compare& comp, container_type&& c);
    template <class Alloc>
        explicit priority_queue(const Alloc& a);
    template <class Alloc>
        priority_queue(const Compare& comp, const Alloc& a);
    template <class Alloc>
        priority_queue(const Compare& comp, const container_type& c,
                       const Alloc& a);
    template <class Alloc>
        priority_queue(const Compare& comp, container_type&& c,
                       const Alloc& a);
    template <class Alloc>
        priority_queue(const priority_queue& q, const Alloc& a);
    template <class Alloc>
        priority_queue(priority_queue&& q, const Alloc& a);

    bool            empty() const;
    size_type       size() const;
    const_reference top() const;

    void push(const value_type& v);
    void push(value_type&& v);
    template <class... Args> void emplace(Args&&... args);
    void pop();

    void swap(priority_queue& q)
        noexcept(is_nothrow_swappable_v<Container> &&
                 is_nothrow_swappable_v<Comp>)
};


// std::set 是关联容器，含有 Key 类型对象的已排序集。用比较函数 比较 (Compare) 进行排序。搜索、移除和插入拥有对数复杂度。 set 通常以红黑树实现。
// 在每个标准库使用比较 (Compare) 概念的场所，用等价关系确定唯一性。不精确地说，若二个对象 a 与 b 相互间既不比较大于亦不比较小于： !comp(a, b) && !comp(b, a) ，则认为它们等价。
template <class Key, class Compare = less<Key>,
          class Allocator = allocator<Key>>
class set
{
public:
    // types:
    typedef Key                                      key_type;
    typedef key_type                                 value_type;
    typedef Compare                                  key_compare;
    typedef key_compare                              value_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

    typedef implementation-defined                   iterator;
    typedef implementation-defined                   const_iterator;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef unspecified                              node_type;               // C++17
    typedef INSERT_RETURN_TYPE<iterator, node_type>  insert_return_type;      // C++17

    // construct/copy/destroy:
    set()
        noexcept(
            is_nothrow_default_constructible<allocator_type>::value &&
            is_nothrow_default_constructible<key_compare>::value &&
            is_nothrow_copy_constructible<key_compare>::value);
    explicit set(const value_compare& comp);
    set(const value_compare& comp, const allocator_type& a);
    template <class InputIterator>
        set(InputIterator first, InputIterator last,
            const value_compare& comp = value_compare());
    template <class InputIterator>
        set(InputIterator first, InputIterator last, const value_compare& comp,
            const allocator_type& a);
    set(const set& s);
    set(set&& s)
        noexcept(
            is_nothrow_move_constructible<allocator_type>::value &&
            is_nothrow_move_constructible<key_compare>::value);
    explicit set(const allocator_type& a);
    set(const set& s, const allocator_type& a);
    set(set&& s, const allocator_type& a);
    set(initializer_list<value_type> il, const value_compare& comp = value_compare());
    set(initializer_list<value_type> il, const value_compare& comp,
        const allocator_type& a);
    template <class InputIterator>
        set(InputIterator first, InputIterator last, const allocator_type& a)
            : set(first, last, Compare(), a) {}  // C++14
    set(initializer_list<value_type> il, const allocator_type& a)
        : set(il, Compare(), a) {}  // C++14
    ~set();

    set& operator=(const set& s);
    set& operator=(set&& s)
        noexcept(
            allocator_type::propagate_on_container_move_assignment::value &&
            is_nothrow_move_assignable<allocator_type>::value &&
            is_nothrow_move_assignable<key_compare>::value);
    set& operator=(initializer_list<value_type> il);

    // iterators:
          iterator begin() noexcept;
    const_iterator begin() const noexcept;
          iterator end() noexcept;
    const_iterator end()   const noexcept;

          reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
          reverse_iterator rend() noexcept;
    const_reverse_iterator rend()   const noexcept;

    const_iterator         cbegin()  const noexcept;
    const_iterator         cend()    const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend()   const noexcept;

    // capacity:
    bool      empty()    const noexcept;
    size_type size()     const noexcept;
    size_type max_size() const noexcept;

    // modifiers:
    template <cl
//std::stack 类是容器适配器，它给予程序员栈的功能——特别是 FILO （先进后出）数据结构。
//该类模板表现为底层容器的包装器——只提供特定函数集合。栈从被称作栈顶的容器尾部推弹元素。
template <class T, class Container = deque<T>>
class stack
{
public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;

protected:
    container_type c;

public:
    stack() = default;
    ~stack() = default;

    stack(const stack& q) = default;
    stack(stack&& q) = default;

    stack& operator=(const stack& q) = default;
    stack& operator=(stack&& q) = default;

    explicit stack(const container_type& c);
    explicit stack(container_type&& c);
    template <class Alloc> explicit stack(const Alloc& a);
    template <class Alloc> stack(const container_type& c, const Alloc& a);
    template <class Alloc> stack(container_type&& c, const Alloc& a);
    template <class Alloc> stack(const stack& c, const Alloc& a);
    template <class Alloc> stack(stack&& c, const Alloc& a);

    bool empty() const;
    size_type size() const;
    reference top();
    const_reference top() const;

    void push(const value_type& x);
    void push(value_type&& x);
    template <class... Args> reference emplace(Args&&... args); // reference in C++17
    void pop();

    void swap(stack& c) noexcept(is_nothrow_swappable_v<Container>)
};


// std::queue 类是容器适配器，它给予程序员队列的功能——尤其是 FIFO （先进先出）数据结构。
//类模板表现为底层容器的包装器——只提供特定的函数集合。 queue 在底层容器尾端推入元素，从首端弹出元素。
template <class T, class Container = deque<T>>
class queue
{
public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;

protected:
    container_type c;

public:
    queue() = default;
    ~queue() = default;

    queue(const queue& q) = default;
    queue(queue&& q) = default;

    queue& operator=(const queue& q) = default;
    queue& operator=(queue&& q) = default;

    explicit queue(const container_type& c);
    explicit queue(container_type&& c)
    template <class Alloc>
        explicit queue(const Alloc& a);
    template <class Alloc>
        queue(const container_type& c, const Alloc& a);
    template <class Alloc>
        queue(container_type&& c, const Alloc& a);
    template <class Alloc>
        queue(const queue& q, const Alloc& a);
    template <class Alloc>
        queue(queue&& q, const Alloc& a);

    bool      empty() const;
    size_type size() const;

    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;

    void push(const value_type& v);
    void push(value_type&& v);
    template <class... Args> reference emplace(Args&&... args); // reference in C++17
    void pop();

    void swap(queue& q) noexcept(is_nothrow_swappable_v<Container>)
};

//priority_queue 是容器适配器，它提供常数时间的（默认）最大元素查找，对数代价的插入与释出。
//可用用户提供的 Compare 更改顺序，例如，用 std::greater<T> 将导致最小元素作为 top() 出现。
//用 priority_queue 工作类似管理某些随机访问容器中的堆，优势是不可能突然把堆非法化。
template <class T, class Container = vector<T>,
          class Compare = less<typename Container::value_type>>
class priority_queue
{
public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;

protected:
    container_type c;
    Compare comp;

public:
    priority_queue() = default;
    ~priority_queue() = default;

    priority_queue(const priority_queue& q) = default;
    priority_queue(priority_queue&& q) = default;

    priority_queue& operator=(const priority_queue& q) = default;
    priority_queue& operator=(priority_queue&& q) = default;

    explicit priority_queue(const Compare& comp);
    priority_queue(const Compare& comp, const container_type& c);
    explicit priority_queue(const Compare& comp, container_type&& c);
    template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last,
                       const Compare& comp = Compare());
    template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last,
                       const Compare& comp, const container_type& c);
    template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last,
                       const Compare& comp, container_type&& c);
    template <class Alloc>
        explicit priority_queue(const Alloc& a);
    template <class Alloc>
        priority_queue(const Compare& comp, const Alloc& a);
    template <class Alloc>
        priority_queue(const Compare& comp, const container_type& c,
                       const Alloc& a);
    template <class Alloc>
        priority_queue(const Compare& comp, container_type&& c,
                       const Alloc& a);
    template <class Alloc>
        priority_queue(const priority_queue& q, const Alloc& a);
    template <class Alloc>
        priority_queue(priority_queue&& q, const Alloc& a);

    bool            empty() const;
    size_type       size() const;
    const_reference top() const;

    void push(const value_type& v);
    void push(value_type&& v);
    template <class... Args> void emplace(Args&&... args);
    void pop();

    void swap(priority_queue& q)
        noexcept(is_nothrow_swappable_v<Container> &&
                 is_nothrow_swappable_v<Comp>)
};


// std::set 是关联容器，含有 Key 类型对象的已排序集。用比较函数 比较 (Compare) 进行排序。搜索、移除和插入拥有对数复杂度。 set 通常以红黑树实现。
// 在每个标准库使用比较 (Compare) 概念的场所，用等价关系确定唯一性。不精确地说，若二个对象 a 与 b 相互间既不比较大于亦不比较小于： !comp(a, b) && !comp(b, a) ，则认为它们等价。
template <class Key, class Compare = less<Key>,
          class Allocator = allocator<Key>>
class set
{
public:
    // types:
    typedef Key                                      key_type;
    typedef key_type                                 value_type;
    typedef Compare                                  key_compare;
    typedef key_compare                              value_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

    typedef implementation-defined                   iterator;
    typedef implementation-defined                   const_iterator;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef unspecified                              node_type;               // C++17
    typedef INSERT_RETURN_TYPE<iterator, node_type>  insert_return_type;      // C++17

    // construct/copy/destroy:
    set()
        noexcept(
            is_nothrow_default_constructible<allocator_type>::value &&
            is_nothrow_default_constructible<key_compare>::value &&
            is_nothrow_copy_constructible<key_compare>::value);
    explicit set(const value_compare& comp);
    set(const value_compare& comp, const allocator_type& a);
    template <class InputIterator>
        set(InputIterator first, InputIterator last,
            const value_compare& comp = value_compare());
    template <class InputIterator>
        set(InputIterator first, InputIterator last, const value_compare& comp,
            const allocator_type& a);
    set(const set& s);
    set(set&& s)
        noexcept(
            is_nothrow_move_constructible<allocator_type>::value &&
            is_nothrow_move_constructible<key_compare>::value);
    explicit set(const allocator_type& a);
    set(const set& s, const allocator_type& a);
    set(set&& s, const allocator_type& a);
    set(initializer_list<value_type> il, const value_compare& comp = value_compare());
    set(initializer_list<value_type> il, const value_compare& comp,
        const allocator_type& a);
    template <class InputIterator>
        set(InputIterator first, InputIterator last, const allocator_type& a)
            : set(first, last, Compare(), a) {}  // C++14
    set(initializer_list<value_type> il, const allocator_type& a)
        : set(il, Compare(), a) {}  // C++14
    ~set();

    set& operator=(const set& s);
    set& operator=(set&& s)
        noexcept(
            allocator_type::propagate_on_container_move_assignment::value &&
            is_nothrow_move_assignable<allocator_type>::value &&
            is_nothrow_move_assignable<key_compare>::value);
    set& operator=(initializer_list<value_type> il);

    // iterators:
          iterator begin() noexcept;
    const_iterator begin() const noexcept;
          iterator end() noexcept;
    const_iterator end()   const noexcept;

          reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
          reverse_iterator rend() noexcept;
    const_reverse_iterator rend()   const noexcept;

    const_iterator         cbegin()  const noexcept;
    const_iterator         cend()    const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend()   const noexcept;

    // capacity:
    bool      empty()    const noexcept;
    size_type size()     const noexcept;
    size_type max_size() const noexcept;

    // modifiers:
    // 若容器中无拥有该关键的元素，则插入以给定的 args 原位构造的新元素到容器。
    //细心地使用 emplace 允许在构造新元素的同时避免不必要的复制或移动操作。 准确地以与提供给 emplace 者相同的参数，通过 std::forward<Args>(args)... 转发调用新元素的构造函数。 即使容器中已有拥有该关键的元素，也可能构造元素，该情况下新构造的元素将被立即销毁。没有迭代器或引用被非法化。
    template <class... Args>
        pair<iterator, bool> emplace(Args&&... args);
    template <class... Args>
        iterator emplace_hint(const_iterator position, Args&&... args);
    pair<iterator,bool> insert(const value_type& v);
    pair<iterator,bool> insert(value_type&& v);
    iterator insert(const_iterator position, const value_type& v);
    iterator insert(const_iterator position, value_type&& v);
    template <class InputIterator>
        void insert(InputIterator first, InputIterator last);
    void insert(initializer_list<value_type> il);

    node_type extract(const_iterator position);                                       // C++17
    node_type extract(const key_type& x);                                             // C++17
    insert_return_type insert(node_type&& nh);                                        // C++17
    iterator insert(const_iterator hint, node_type&& nh);                             // C++17

    iterator  erase(const_iterator position);
    iterator  erase(iterator position);  // C++14
    size_type erase(const key_type& k);
    iterator  erase(const_iterator first, const_iterator last);
    void clear() noexcept;

    template<class C2>
      void merge(set<Key, C2, Allocator>& source);         // C++17
    template<class C2>
      void merge(set<Key, C2, Allocator>&& source);        // C++17
    template<class C2>
      void merge(multiset<Key, C2, Allocator>& source);    // C++17
    template<class C2>
      void merge(multiset<Key, C2, Allocator>&& source);   // C++17

    void swap(set& s)
        noexcept(
            __is_nothrow_swappable<key_compare>::value &&
            (!allocator_type::propagate_on_container_swap::value ||
             __is_nothrow_swappable<allocator_type>::value));

    // observers:
    allocator_type get_allocator() const noexcept;
    key_compare    key_comp()      const;
    value_compare  value_comp()    const;

    // set operations:
          iterator find(const key_type& k);
    const_iterator find(const key_type& k) const;
    template<typename K>
        iterator find(const K& x);
    template<typename K>
        const_iterator find(const K& x) const;  // C++14
    template<typename K>
      size_type count(const K& x) const;        // C++14

    size_type      count(const key_type& k) const;
          iterator lower_bound(const key_type& k);
    const_iterator lower_bound(const key_type& k) const;
    template<typename K>
        iterator lower_bound(const K& x);              // C++14
    template<typename K>
        const_iterator lower_bound(const K& x) const;  // C++14

          iterator upper_bound(const key_type& k);
    const_iterator upper_bound(const key_type& k) const;
    template<typename K>
        iterator upper_bound(const K& x);              // C++14
    template<typename K>
        const_iterator upper_bound(const K& x) const;  // C++14
    pair<iterator,iterator>             equal_range(const key_type& k);
    pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
    template<typename K>
        pair<iterator,iterator>             equal_range(const K& x);        // C++14
    template<typename K>
        pair<const_iterator,const_iterator> equal_range(const K& x) const;  // C++14
};
ass... Args>
        pair<iterator, bool> emplace(Args&&... args);
    template <class... Args>
        iterator emplace_hint(const_iterator position, Args&&... args);
    pair<iterator,bool> insert(const value_type& v);
    pair<iterator,bool> insert(value_type&& v);
    iterator insert(const_iterator position, const value_type& v);
    iterator insert(const_iterator position, value_type&& v);
    template <class InputIterator>
        void insert(InputIterator first, InputIterator last);
    void insert(initializer_list<value_type> il);

    node_type extract(const_iterator position);                                       // C++17
    node_type extract(const key_type& x);                                             // C++17
    insert_return_type insert(node_type&& nh);                                        // C++17
    iterator insert(const_iterator hint, node_type&& nh);                             // C++17

    iterator  erase(const_iterator position);
    iterator  erase(iterator position);  // C++14
    size_type erase(const key_type& k);
    iterator  erase(const_iterator first, const_iterator last);
    void clear() noexcept;

    template<class C2>
      void merge(set<Key, C2, Allocator>& source);         // C++17
    template<class C2>
      void merge(set<Key, C2, Allocator>&& source);        // C++17
    template<class C2>
      void merge(multiset<Key, C2, Allocator>& source);    // C++17
    template<class C2>
      void merge(multiset<Key, C2, Allocator>&& source);   // C++17

    void swap(set& s)
        noexcept(
            __is_nothrow_swappable<key_compare>::value &&
            (!allocator_type::propagate_on_container_swap::value ||
             __is_nothrow_swappable<allocator_type>::value));

    // observers:
    allocator_type get_allocator() const noexcept;
    key_compare    key_comp()      const;
    value_compare  value_comp()    const;

    // set operations:
          iterator find(const key_type& k);
    const_iterator find(const key_type& k) const;
    template<typename K>
        iterator find(const K& x);
    template<typename K>
        const_iterator find(const K& x) const;  // C++14
    template<typename K>
      size_type count(const K& x) const;        // C++14        // 返回拥有关键比较等价于指定参数的元素数，因为此容器不允许重复故为 1 或 0。

    size_type      count(const key_type& k) const;
          iterator lower_bound(const key_type& k);
    const_iterator lower_bound(const key_type& k) const;
    template<typename K>
        iterator lower_bound(const K& x);              // C++14
    template<typename K>
        const_iterator lower_bound(const K& x) const;  // C++14

          iterator upper_bound(const key_type& k);
    const_iterator upper_bound(const key_type& k) const;
    template<typename K>
        iterator upper_bound(const K& x);              // C++14
    template<typename K>
        const_iterator upper_bound(const K& x) const;  // C++14
    pair<iterator,iterator>             equal_range(const key_type& k);
    pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
    template<typename K>
        pair<iterator,iterator>             equal_range(const K& x);        // C++14
    template<typename K>
        pair<const_iterator,const_iterator> equal_range(const K& x) const;  // C++14
};



template <class Key, class T, class Compare = less<Key>,
          class Allocator = allocator<pair<const Key, T>>>
class map
{
public:
    // types:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef Compare                                  key_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef implementation-defined                   iterator;
    typedef implementation-defined                   const_iterator;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef unspecified                              node_type;              // C++17
    typedef INSERT_RETURN_TYPE<iterator, node_type>  insert_return_type;     // C++17

    class value_compare
        : public binary_function<value_type, value_type, bool>
    {
        friend class map;
    protected:
        key_compare comp;

        value_compare(key_compare c);
    public:
        bool operator()(const value_type& x, const value_type& y) const;
    };

    // construct/copy/destroy:
    map()
        noexcept(
            is_nothrow_default_constructible<allocator_type>::value &&
            is_nothrow_default_constructible<key_compare>::value &&
            is_nothrow_copy_constructible<key_compare>::value);
    explicit map(const key_compare& comp);
    map(const key_compare& comp, const allocator_type& a);
    template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare& comp = key_compare());
    template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare& comp, const allocator_type& a);
    map(const map& m);
    map(map&& m)
        noexcept(
            is_nothrow_move_constructible<allocator_type>::value &&
            is_nothrow_move_constructible<key_compare>::value);
    explicit map(const allocator_type& a);
    map(const map& m, const allocator_type& a);
    map(map&& m, const allocator_type& a);
    map(initializer_list<value_type> il, const key_compare& comp = key_compare());
    map(initializer_list<value_type> il, const key_compare& comp, const allocator_type& a);
    template <class InputIterator>
        map(InputIterator first, InputIterator last, const allocator_type& a)
            : map(first, last, Compare(), a) {}  // C++14
    map(initializer_list<value_type> il, const allocator_type& a)
        : map(il, Compare(), a) {}  // C++14
   ~map();

    map& operator=(const map& m);
    map& operator=(map&& m)
        noexcept(
            allocator_type::propagate_on_container_move_assignment::value &&
            is_nothrow_move_assignable<allocator_type>::value &&
            is_nothrow_move_assignable<key_compare>::value);
    map& operator=(initializer_list<value_type> il);

    // iterators:
          iterator begin() noexcept;
    const_iterator begin() const noexcept;
          iterator end() noexcept;
    const_iterator end()   const noexcept;

          reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
          reverse_iterator rend() noexcept;
    const_reverse_iterator rend()   const noexcept;

    const_iterator         cbegin()  const noexcept;
    const_iterator         cend()    const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend()   const noexcept;

    // capacity:
    bool      empty()    const noexcept;
    size_type size()     const noexcept;
    size_type max_size() const noexcept;

    // element access:
    mapped_type& operator[](const key_type& k);
    mapped_type& operator[](key_type&& k);

          mapped_type& at(const key_type& k);
    const mapped_type& at(const key_type& k) const;

    // modifiers:
    template <class... Args>
        pair<iterator, bool> emplace(Args&&... args);
    template <class... Args>
        iterator emplace_hint(const_iterator position, Args&&... args);
    pair<iterator, bool> insert(const value_type& v);
    pair<iterator, bool> insert(      value_type&& v);                                // C++17
    template <class P>
        pair<iterator, bool> insert(P&& p);
    iterator insert(const_iterator position, const value_type& v);
    iterator insert(const_iterator position,       value_type&& v);                   // C++17
    template <class P>
        iterator insert(const_iterator position, P&& p);
    template <class InputIterator>
        void insert(InputIterator first, InputIterator last);
    void insert(initializer_list<value_type> il);

    node_type extract(const_iterator position);                                       // C++17
    node_type extract(const key_type& x);                                             // C++17
    insert_return_type insert(node_type&& nh);                                        // C++17
    iterator insert(const_iterator hint, node_type&& nh);                             // C++17

    template <class... Args>
        pair<iterator, bool> try_emplace(const key_type& k, Args&&... args);          // C++17
    template <class... Args>
        pair<iterator, bool> try_emplace(key_type&& k, Args&&... args);               // C++17
    template <class... Args>
        iterator try_emplace(const_iterator hint, const key_type& k, Args&&... args); // C++17
    template <class... Args>
        iterator try_emplace(const_iterator hint, key_type&& k, Args&&... args);      // C++17
    template <class M>
        pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);            // C++17
    template <class M>
        pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);                 // C++17
    template <class M>
        iterator insert_or_assign(const_iterator hint, const key_type& k, M&& obj);   // C++17
    template <class M>
        iterator insert_or_assign(const_iterator hint, key_type&& k, M&& obj);        // C++17

    iterator  erase(const_iterator position);
    iterator  erase(iterator position); // C++14
    size_type erase(const key_type& k);
    iterator  erase(const_iterator first, const_iterator last);
    void clear() noexcept;

    template<class C2>
      void merge(map<Key, T, C2, Allocator>& source);         // C++17
    template<class C2>
      void merge(map<Key, T, C2, Allocator>&& source);        // C++17
    template<class C2>
      void merge(multimap<Key, T, C2, Allocator>& source);    // C++17
    template<class C2>
      void merge(multimap<Key, T, C2, Allocator>&& source);   // C++17

    void swap(map& m)
        noexcept(allocator_traits<allocator_type>::is_always_equal::value &&
            is_nothrow_swappable<key_compare>::value); // C++17

    // observers:
    allocator_type get_allocator() const noexcept;
    key_compare    key_comp()      const;
    value_compare  value_comp()    const;

    // map operations:
          iterator find(const key_type& k);
    const_iterator find(const key_type& k) const;
    template<typename K>
        iterator find(const K& x);              // C++14
    template<typename K>
        const_iterator find(const K& x) const;  // C++14
    template<typename K>
      size_type count(const K& x) const;        // C++14

    size_type      count(const key_type& k) const;
          iterator lower_bound(const key_type& k);
    const_iterator lower_bound(const key_type& k) const;
    template<typename K>
        iterator lower_bound(const K& x);              // C++14
    template<typename K>
        const_iterator lower_bound(const K& x) const;  // C++14

          iterator upper_bound(const key_type& k);
    const_iterator upper_bound(const key_type& k) const;
    template<typename K>
        iterator upper_bound(const K& x);              // C++14
    template<typename K>
        const_iterator upper_bound(const K& x) const;  // C++14

    pair<iterator,iterator>             equal_range(const key_type& k);
    pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
    template<typename K>
        pair<iterator,iterator>             equal_range(const K& x);        // C++14
    template<typename K>
        pair<const_iterator,const_iterator> equal_range(const K& x) const;  // C++14
};
*/

#include <cmath>
#include <queue>
#include <iostream>
#include <set>
#include <cassert>
#include <map>

using namespace std;

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

int tqueue() {
    std::priority_queue<int> q;
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q.push(n);
    print_queue(q);

    std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q2.push(n);
    print_queue(q2);

    // 用 lambda 比较元素。
    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q3.push(n);
    print_queue(q3);
}


void tinsert() {
    std::set<int> set;

    auto result_1 = set.insert(3);
    assert(result_1.first != set.end()); // 它是合法迭代器
    assert(*result_1.first == 3);
    if (result_1.second)
        std::cout << "insert done\n";

    auto result_2 = set.insert(3);
    assert(result_2.first == result_1.first); // 相同迭代器
    assert(*result_2.first == 3);
    if (!result_2.second)
        std::cout << "no insertion\n";
}

int terase()
{
    std::set<int> c = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // 从 c 擦除所有奇数
    for(auto it = c.begin(); it != c.end(); )
        if(*it % 2 == 1)
            it = c.erase(it);
        else
            ++it;
    for(int n : c)
        std::cout << n << ' ';
}

int tfind() {
    std::set<int> example = {1, 2, 3, 4};

    auto search = example.find(2);
    if (search != example.end()) {
        std::cout << "Found " << (*search) << '\n';
    } else {
        std::cout << "Not found\n";
    }
}

// range
int trange() {
    // 不重复元素
    set<int> nums = { 1,2,3,4,5,6,7,8};
    pair<set<int>::const_iterator, set<int>::const_iterator> er = nums.equal_range(4);
    if (er.first == er.second) {
        cout << "elem 4 not find" << endl;
    } else {
        int num = 0;
        auto it = nums.cbegin();
        while ( it++ != er.first )
            num++;
        cout << *er.first << " exists, pos at: " << num << endl;
    }
    // 可重复集合
    multiset<int> mulnums = {1,2,3,4,5,5,5,6,7};
    multiset<int>::const_iterator beg = mulnums.lower_bound(5);
    multiset<int>::const_iterator end = mulnums.upper_bound(5);
    while ( beg != end )
        cout << *beg++ << " ";
}

int t1()
{
    std::map<char, int> letter_counts {{'a', 27}, {'b', 3}, {'c', 1}};

    std::cout << "initially:\n";
    for (const auto &pair : letter_counts) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }

    letter_counts['b'] = 42;  // 更新既存值
    letter_counts['x'] = 9;  // 插入新值

    std::cout << "after modifications:\n";
    for (const auto &pair : letter_counts) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }

    // 统计每个词的出现数
    // （首次调用 operator[] 以零初始化计数器）
    std::map<std::string, size_t>  word_map;
    for (const auto &w : { "this", "sentence", "is", "not", "a", "sentence",
                           "this", "sentence", "is", "a", "hoax"}) {
        ++word_map[w];
    }

    for (const auto &pair : word_map) {
        std::cout << pair.second << " occurrences of word '" << pair.first << "'\n";
    }
}

//
struct Per {
    string name;
    int age;
    Per(const string &s, int a):name(s), age(a) {}
    friend ostream &operator<<(ostream &os, const Per &per);
};
struct PerComp{
    bool operator()(const Per *lhs, const Per *rhs) const {
        return lhs->age < rhs->age;
    }
};
ostream &operator<<(ostream &os, const Per &per) {
    os << "user name :" << per.name << "; age :" << per.age << endl;
    return os;
}
int t2() {
    Per pers[4] = { Per("zr", 10), Per("jack", 20), Per("tom", 24), Per("kius", 70) };
    map<Per*, int, PerComp> fans = {
            { pers, 100 },
            { pers+1, 1000 },
            { pers+2, 123 },
            { pers+3, 8000 },
    };
    for_each(fans.cbegin(), fans.cend(), [](pair<Per*, int> p) { cout << *p.first; });

    vector<int> nums = {1,2,3,4,5};
    for_each(nums.cbegin(), nums.cend(), [](const int &i) { cout << i << " "; }); cout << endl;
}

int t3() {
    map<int, char> con = { {10, 'a'}, {11, 'b'}, {12, 'c'}, {13, 'd'}, };
    void (*ptr)(const pair<int, char> &) = [](const pair<int, char> &val) { cout << "num: " << val.first << "; char: " << val.second << endl; };
    for_each(con.cbegin(), con.cend(), ptr);

    cout << "Do Clear: ";
    con.clear();
    for_each(con.cbegin(), con.cend(), ptr);
}
}
