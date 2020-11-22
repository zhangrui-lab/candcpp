#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <sstream>
#include <functional>

using namespace std;

class NoDerived final  {};  // 防止继承

class Quote {
    Quote()=default;
public:
    Quote(const string &book, double p):bookNo(book),price(p) {}
    friend ostream &operator<<(ostream &os, const Quote&quote);
    string isbn() const { return bookNo; };
    virtual double netPrice(std::size_t n) const  { return n * price; };  // 虚函数
    // 动态绑定析构函数
    virtual ~Quote() = default;  //继承关系中的根节点通常都应该如此定义析构函数
private:
    string bookNo;
protected:
    double price;
};

class DiscQuote : public Quote {    // 使用某个类作为基类时，则该类必须被声明且定义
public:
    DiscQuote()=default;
    DiscQuote(const string& book, double p, size_t q, double d):Quote(book, p), minQty(q), discount(d) {}
    virtual double netPrice(std::size_t n) const =0;
protected:
    std::size_t minQty  = 0 ;
    double discount = 0.0;
};

class BulkQuote : public DiscQuote {    // 使用某个类作为基类时，则该类必须被声明且定义
public:
    BulkQuote()=default;
    BulkQuote(const string&, double, size_t, double );
    double netPrice(std::size_t n) const override ;
};

// 首先初始化基类部分，然后一句声明的次序初始化派生类的成员
BulkQuote::BulkQuote(const string &book, double price, size_t qty, double dis):
        DiscQuote(book, price, qty, dis){}

double BulkQuote::netPrice(std::size_t n) const {
    if (n > minQty)
        return n * (1 - discount)* price;
    return n * price;
}

// 当使用基类型调用虚函数时会产生动态绑定
double printTotal(ostream &os, const Quote& quote, std::size_t n) {
    double ret = quote.netPrice(n);
    os << "ISBN: " << quote.isbn() << " #sold: " << n <<" totalDue: " << ret << endl;
    return ret;
}

void tQoute() {
    Quote quote("01", 50);
    BulkQuote bulkQuote("02", 50, 5, 0.4);
    printTotal(cout, quote, 10);
    printTotal(cout, bulkQuote, 10);
    //bulkQuote.Quote::netPrice(20);  // 作用域运算符，不执行动态绑定
    //DiscQuote discQuote; //含有纯虚成员的类是抽象的， 不可被定义

}

struct B {
    virtual void f1(int) const;
    virtual void f2();
    void f3();
};

struct D: public B{
    void f1(int) const override;
    void f2() override final ;  // 不允许子类再覆盖f2
    //void f2(int i) override ;  // 编译失败。 基类不存在 void f2(int i) 的虚函数
    // void f3() override ; //error
    void f3() ;
};
struct D1: public D{
    // void f2() override ;  // error
};

struct A {
    virtual void print(int i = 10) { cout << "Parent I: " << i << endl; }
};
struct B1:A {
    void print(int i = 20) override { cout << "Child I: " << i << endl; }   // 默认参数的值取决于调用该函数的对象所定义的静态类型而非动态类型
};

void tAB1() {
    A a, *a1;
    B1 b;
    cout << "Print Object: " << endl;
    a.print();
    b.print();

    cout << "Print Pointer: " << endl;
    a1 = &a;
    a1->print();
    a1 = &b;
    a1->print();
}

class T1;
class Base1 {
    friend  class T1;
public:
protected:
    char c;
private:
    int num;
};

class Child1: public Base1 {
public:
    using Base1::c; // using语句可更改继承自基类的可见部分的访问权限；
private:
    string str;
};

class T1 {  // 友元和类内部可以访问类的所有成员
    void operator()(const Base1 &base1){
        cout << "protected char: " << base1.c << "; private num: " << base1.num << endl;
    }

    // 基类A 的友元类无法访问 A 的派生类中非A定义的私有/受保护成员
    void operator()(const Child1 &child1){
        cout << "Parent protected char: " << child1.c << "; Parent private num: " << child1.num  << endl;   // error << "; Child Private: " << child1.str
    }
};

class T2: public T1 {
    // 友元的派生类不在具有对源对象私有部分的访问权限
    void operator()(const Base1 &base1){
        //cout << "protected char: " << base1.c << "; private num: " << base1.num << endl;
    }
};

// 派生类的成员作用域是嵌套在基类的成员作用域之中的
// {T3 {T4} }
struct T3 {
    T3(int n = 0): i(n) {}
    int i;
};
struct T4: public T3 {
    T4(int n): i(n) {}
    int getI() { return i; }
    int i;   // 内层作用于定义的外层同名变量将对其进行覆盖。（可通过作用域运算符进行调用 :: ）
};

// 名字查找优于类型检查
//声明再外层作用域的函数并不会重载声明在外层作用域的函数
struct Z1 {
    int mmeFun();
};
struct Z2:Z1 {
    int mmeFun(int i);
};
int tz() {
    Z1 z1; Z2 z2;
    z1.mmeFun();
    z2.mmeFun(10);
    //z2.mmeFun();    // error 隐藏外层作用域的同名函数
    z2.Z1::mmeFun();
}

int main () {
}
