#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <sstream>
#include <functional>

class StrVec {
public:
    // 初始化列表
    StrVec (std::initializer_list<std::string>);
    StrVec &operator=(std::initializer_list<std::string>);

    std::string &operator[](const size_t pos);
    const std::string &operator[](size_t pos) const ;
private:
    std::string *elements;
};

class StrBlobPtr {
public:
    // 前置运算符
    StrBlobPtr &operator++();
    StrBlobPtr &operator--();

    // 后置运算符
    StrBlobPtr &operator++(int ) { StrBlobPtr ret = *this; ++*this; return ret; }   // 后置运算通过调用前置运算来实现
    StrBlobPtr &operator--(int ) { StrBlobPtr ret = *this; --*this; return ret; }

    // 成员运算符 (请参考针对迭代器的 *， ->)
    std::string& operator*() const ;
    std::string* operator->() const  { return &this->operator*(); }
};

struct AbsInt{
    int i;
    unsigned int operator()() {
        return i < 0 ? -i : i;
    }
};

class PrintString {
public:
    PrintString(std::ostream &o, const std::string &s = " "): os(o), spe(s) {}
    void operator()(const std::string &str) { os << str << spe; }
private:
    std::ostream &os;
    std::string  spe;
};

class SizeCompz {
public:
    SizeCompz(size_t s) :size(s) {}
    bool operator()(const std::string &str) {
        return str.size() >= size;
    }
private:
    size_t size;
};
//此类型的对象(可调用对象) == 下述lambda
/*
    size_t size = 10;
    [size](const std::string &str)->bool { return str.size() >= size; };
 */


void testPrint() {

    PrintString print1( std::cout, " " );
    print1("this is a cout line1");
    print1("this is a cout line2");

    PrintString print2( std::cerr, "\n");
    print2("this is a cerr line1");
    print2("this is a cerr line2");
}

template<typename Arg, typename Result>
struct Unary {
    typedef Arg arg_type;
    typedef Result result_type;
};
template<typename Arg1, typename Arg2, typename Result>
struct Binary {
    typedef Arg1 arg1_type;
    typedef Arg2 arg2_type;
    typedef Result result_type;
};

template <typename Tp>
struct MyAdd:Binary<Tp, Tp, Tp> {
    Tp operator()(Tp f, Tp l) { return f + l; }
};

template<typename Tp>
struct MyEqual:Binary<Tp,Tp,bool> {
    bool operator()(Tp f, Tp l) { return f == l; }
};

void testfunc() {
    std::plus<int> intAdd;
    int num1 = intAdd(10, 20);
    std::cout << num1 << std::endl;

    int num2 = intAdd(num1, 20);
    std::cout << num2 << std::endl;

    std::equal_to<int> equalToInt;
    std::cout << equalToInt(num1, num2) << std::endl;

    MyAdd<int> myAdd;
    MyEqual<int> myEqual;
    std::cout << "MyAdd: 100+200=" << myAdd(100, 200) << std::endl;
    std::cout << "myEqual: 100=200 ? " << myEqual(100, 200) << std::endl;
    std::cout << "myEqual: 200=200 ? " << myEqual(200, 200) << std::endl;
}

int myAdd(int a, int b) {
    return a + b;
}
struct myDivide {
    double operator()(int a, int b) { return a/b; }
};
struct Oper{
    int lhs;
    int rhs;
    std::string op;
    friend std::istream &operator>>(std::istream&is, Oper &oper);
};
inline std::istream &operator>>(std::istream&is, Oper &oper) {
    std::cout << "Enter The Computer Nums And Operator, like 1 + 1" << std::endl;
    std::string str;
    std::getline(is, str);
    std::istringstream iss(str);
    iss >> oper.lhs >> oper.op >> oper.rhs;
    if (iss.fail()) {
        std::cout << "Fail Of Enter: " << str << std::endl;
        oper.lhs = oper.rhs = 0;
        oper.op = "null";
    }
    return is;
}
// 整数桌面计算程序
void testfunc1() {
    auto myMod = [](int a, int b) { return a % b; };
    std::map<std::string, std::function<int(int,int)>> binops = {
            { "null", [](int a, int b) { return 0; } },
            { "+", myAdd },
            { "-", std::minus<int>() },
            { "*", [](int a, int b) { return a * b; } },
            { "/", myDivide() },
            { "%", myMod },
    };
    std::cout << "PROCESS RUNING" << std::endl;
    Oper oper;
    while (std::cin >> oper) {
        if (oper.op == "null") continue;
        auto it = binops.find(oper.op);
        if (it == binops.cend())
            std::cout << "Not Suppose The Operator " << std::endl;
        else
            std::cout << it->second(oper.lhs, oper.rhs) << std::endl;
    }
}

class SmallInt {
public:
    SmallInt(size_t i = 0):val(i) {
        if ( i < 0 || i > 255)
            throw std::out_of_range("Bad SmallInt Value !");
    }
    // 类型转换成员函数（可转换为任意函数可返回类型）
    operator int() { return val; } // 不接受参数也不定义返回数据类型的成员函数
    // 显示的类型转换
    explicit operator bool () { return val != 0; }  // 需要使用强制类型转换才能生效 static_cast<bool>(smallInt)
private:
    std::size_t val;
};

void testSmallInt() {
    SmallInt s1(100), s2 = 200;
    std::cout << s1 + 20 << std::endl;
    std::cout << 20 + s2 << std::endl;

}

struct C {
    int i;
    C(int a):i(a) {}
};
struct D {
    int i;
    D(int a):i(a) {}
};
int func(const C&);
int func(const D&);

int testfunc2() {
    // func(10);    //二义性调用
    // func(C(10)); //true
    // func(D(10)); //true
}

class A {
    friend A operator+(const A &lhs, const A &rhs);
public:
    A(int i):a(i) {}
    operator int() const { return a; }
private:
    int a;
};

void testA() {
    A a1(18), a2(22);
    A a3 = a1 + a2;
//    /int i = a2 + 10;    //二义性; 10 转换为A再调用operator+还是 a2转换为int再执行 + 运算
}

int main () {
    testSmallInt();
}
