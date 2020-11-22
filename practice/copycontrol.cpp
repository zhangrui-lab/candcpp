#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;


class PrivateCopy {
    PrivateCopy(const PrivateCopy&);
    PrivateCopy &operator = (const PrivateCopy&);  // 可以声明一个未定义的成员函数的； 调用时产生链接异常
public:
    PrivateCopy() = default;
    ~PrivateCopy() = default;
    int num;
};


/**
 * 行为像值的类型: 我们需要确保赋值前后的对象是完全独立的
 */
class HasPtr {
public:
    HasPtr(const string& s):ptr(new string(s)), i(s.size()) {}
    HasPtr(const HasPtr&o):ptr(new string(*o.ptr)), i(o.i) { }
    HasPtr &operator=(const HasPtr &o) {        // 需要以正确的顺序完成左侧运算对象的销毁和新对象的构建工作 // 自赋值情况
        auto newptr = new string(*o.ptr);
        delete ptr;
        ptr = newptr;
        i = o.i;
        return *this;
    }
    ~HasPtr() {
        delete ptr;
    }
    string *str() {
        return ptr;
    }
private:
    string *ptr;
    int i;
};

/**
 * 行为像指针的类
 *  确保拷贝对象之间共享数据
 *  确保共享数据的生命周期在所有共享对象结束时结束 （引用计数机制）
 */
class HasPtr1{
public:
    HasPtr1(const std::string &s):ptr(new string(s)), i(s.size()),use(new std::size_t(1)) {}
    HasPtr1(const HasPtr1 &o):ptr(o.ptr), i(o.i),use(o.use) { ++*use; }
    HasPtr1 &operator=(const HasPtr1 & o) {
        ++*o.use;
        if (!--*use) {  // 递减当前引用计数，若等于0时释放内存
            delete ptr;
            delete use;
        }
        i = o.i;
        ptr = o.ptr;
        use = o.use;
        return *this;
    }
    ~HasPtr1() {
        if (!--*use) {  // 递减当前引用计数，若等于0时释放内存
            delete ptr;
            delete use;
        }
    }
    string *str() {
        return ptr;
    }
    void swap(HasPtr1 &rhs) {
        using std::swap;
        swap(ptr, rhs.ptr);
        swap(i, rhs.i);
    }
    friend void swap(HasPtr1 &lhs, HasPtr1 &rhs);
private:
    string *ptr;
    std::size_t *use;   // 引用计数器应当所有对象公用
    int i;
};
inline void swap(HasPtr1 &lhs, HasPtr1 &rhs) {
    lhs.swap(rhs);
}


class Message;
class Folder;
class Folder {
public:
    friend ostream & operator<<(ostream&, const Folder&);
    void addMsg(Message &msg);
    void remMsg(Message &msg);
private:
    std::set<Message*>messages;
};
void Folder::addMsg(Message &msg) {
    messages.insert(&msg);
}
void Folder::remMsg(Message &msg) {
    messages.erase(&msg);
}
ostream & operator<<(ostream&os, const Folder&folder) {
    if (folder.messages.empty())
        cout << "Folder Is Empty" << endl;
    else
        cout << "Folder Has " << folder.messages.size() << " files"<< endl;
    for (Message* msg:folder.messages)
        cout << msg << endl;
    return os;
}

class Message {
public:
    friend ostream & operator<<(ostream&, const Message*);
    friend class Folder;
    explicit Message(const string &str = "") :contents(str) {}
    Message(const Message &);
    Message(Message &&);
    Message &operator=(const Message &);
    Message &operator=(Message &&);
    ~Message();
    void save(Folder &);
    void remove(Folder &);
    void swap(Message &lhs, Message &rhs);
    const std::string &getContents() const { return contents; }
private:
    std::string contents;
    std::set<Folder*> folders;
    void addToFolder(const Message &);
    void remFromFolder();
    void moveFolders(Message &);
};

void Message::remove(Folder &folder) {
    folders.erase(&folder);
    folder.remMsg(*this);
}
void Message::save(Folder &folder) {
    folders.insert(&folder);
    folder.addMsg(*this);
}
void Message::addToFolder(const Message &msg) {
    for_each(msg.folders.cbegin(), msg.folders.cend(), [this](Folder*folder){ folder->addMsg(*this);});
}
void Message::remFromFolder() {
    for_each(folders.cbegin(), folders.cend(), [this](Folder*folder){ folder->remMsg(*this);});
}
Message::Message(const Message &msg):contents(msg.contents), folders(msg.folders) {
    addToFolder(msg);
}
Message::Message(Message &&msg) :contents(msg.contents) {
    moveFolders(msg);
}
Message &Message::operator=(Message &&msg) {
    if ( this != &msg ) {
        remFromFolder();
        contents = std::move(msg.contents);
        moveFolders(msg);
    }
    return *this;
}
void Message::moveFolders(Message &msg) {
    folders = std::move(msg.folders);
    for(auto f: folders) {
        f->remMsg(msg);
        f->addMsg(msg);
    }
    msg.folders.clear();
}
Message & Message::operator=(const Message &msg) {
    remFromFolder();
    folders = msg.folders;
    contents = msg.contents;
    addToFolder(*this);
    return *this;
}
Message::~Message() {
    remFromFolder();
}
void Message::swap(Message &lhs, Message &rhs) {
    for (auto f: lhs.folders)
        f->remMsg(lhs);
    for (auto f: rhs.folders)
        f->remMsg(rhs);
    using std::swap;
    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);
    for (auto f: lhs.folders)
        f->addMsg(lhs);
    for (auto f: rhs.folders)
        f->addMsg(rhs);
}
ostream & operator<<(ostream& os, const Message* msg) {
    cout << "Message Contents: " << msg->contents << endl;
    return cout;
}
void testFolder() {
    Folder folder1, folder2, folder3, folder4;
    Message message1("message1"), message2("message2"), message3("message3"), message4("message4");
    message1.save(folder1);
    message2.save(folder1);
    message3.save(folder2);
    message4.save(folder3);


    {
        Message message5(message1);
        Message message6(message1);
        Message message7(message3);
        cout << folder1;
        cout << folder2;
    }
    cout << folder1;
    cout << folder2;
    cout << folder3;
    cout << folder4;
}

// 自己手动实现动态内存管理
// 保存类型固定为string
class StrVec {
public:
    friend ostream &operator<<(ostream&os, const StrVec &o);
    StrVec():elements(nullptr),cap(nullptr),firstFree(nullptr) {}
    StrVec(const StrVec &);
    StrVec(StrVec &&) noexcept ;
    StrVec &operator=(const StrVec &);
    StrVec &operator=(StrVec &&) noexcept;
    void pushBack(const string &);
    void pushBack(string &&);
    std::size_t size() const { return firstFree - elements; }
    std::size_t capacity() const { return cap - elements; }
    string *begin() const { return elements; }
    string *end() const { return firstFree; }
    ~StrVec();
private:
    static std::allocator<string> allocator;    // 内存管理
    string * elements;
    string * cap;
    string * firstFree;
    std::pair<string *, string *> allocNCopy(const string *, const string *);
    void checkNAlloc() {
        if (size() == capacity()) {
            reallocate();
        }
    }
    void free();
    void reallocate();
};
std::allocator<string> StrVec::allocator;
void StrVec::pushBack(const string &str) {
    checkNAlloc();
    allocator.construct(firstFree++, str);
}
void StrVec::pushBack(string &&str) {
    checkNAlloc();
    allocator.construct(firstFree++, std::move(str));
}
void StrVec::free() {
    // allocator.destruct
    // allocator.deallocate
    while(firstFree-- != elements)
        allocator.destroy(firstFree);
    allocator.deallocate(elements, capacity());
}
std::pair<string *, string *> StrVec::allocNCopy(const string *beg, const string *end) {
    auto newdata = allocator.allocate( end - beg );
    return make_pair(newdata, uninitialized_copy(beg, end, newdata));
}
StrVec & StrVec::operator=(const StrVec &rhs) {
    auto newdata = allocNCopy(rhs.begin(), rhs.end());
    free();
    elements = newdata.first;
    cap = firstFree = newdata.second;
    return *this;
}
StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        firstFree = rhs.firstFree;
        cap = rhs.cap;
        rhs.elements = rhs.firstFree = rhs.cap = nullptr;
    }
    return *this;
}
StrVec::StrVec(const StrVec &rhs) {
    auto newdata = allocNCopy(rhs.begin(), rhs.end());
    elements = newdata.first;
    cap = firstFree = newdata.second;
}
StrVec::StrVec(StrVec &&rhs) noexcept :elements(rhs.elements),firstFree(rhs.firstFree), cap(rhs.cap) {
    rhs.elements = rhs.firstFree = rhs.cap = nullptr;
}
void StrVec::reallocate() {
    auto s = size () ? size() * 2 : 1;
    auto newData = allocator.allocate(s);
    string *dest = newData;
    string *source = elements;
    //    for (int i = 0; i < size(); ++i) {    // 移动成员以提高效率
    //        allocator.construct(dest++, std::move(*source++));
    //    }
    auto last = uninitialized_copy( make_move_iterator(elements), make_move_iterator(firstFree), dest );    // 移动迭代器
    free();
    elements = newData;
    firstFree = last;
    cap = newData + s;
}
StrVec::~StrVec() {
    free();
}
inline ostream &operator<<(ostream&os, const StrVec &o) {
    os << "The Container Has " << o.size() << " String; Capacity: " << o.capacity() << "; Elements: " << endl;
    for_each(o.begin(), o.end(), [&os](const string &p) { os << p << endl; });
    cout << endl;
    return os;
}

void testStrVec() {
    StrVec strVec1, strVec2, strVec3;
    strVec1.pushBack("jack1");
    strVec1.pushBack("jack2");
    strVec1.pushBack("jack3");
    strVec1.pushBack("jack4");
    cout << strVec1;
    cout << "do coping: " << endl;
    strVec2 = strVec1;
    cout << "strvec1: " << endl;
    cout << strVec1;
    cout << "strvec2: " << endl;
    cout << strVec2;
    cout << "do moving: " << endl;
    strVec3 = std::move(strVec1);
    cout << "strvec1: " << endl;
    cout << strVec1;
    cout << "strvec3: " << endl;
    cout << strVec3;
}

// 编译器只有在类并未定义任何自己版本的拷贝控制成员且所有成员均可移动时才会合成的移动赋值运算符和移动构造函数
struct X { // 可移动
    int i;  // 内置类型，可移动
    std::string str;    // 定义有移动控制成员
};

struct HasX {   // 可移动
    X x;    // 可移动
};


// 当类定义了拷贝构造函数但未定义移动构造函数时， 对对象的移动操作将会调用拷贝构造函数
/*
class Foo {
public:
    Foo() = default;
    Foo(const Foo &);   //拷贝构造函数
};
void testFoo() {
    Foo x;
    Foo y(x);   //调用拷贝构造函数
    Foo z(std::move(x));   //调用拷贝构造函数; Foo && -> const Foo & (隐式数据转换) 拷贝构造函数肯定式安全的
}
*/

int main () {
    testStrVec();
}