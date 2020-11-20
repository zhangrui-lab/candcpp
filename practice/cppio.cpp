
#include <iostream>
#include <fstream>
#include <sstream>
#include <strstream>
#include <vector>
#include <vector>
#include <array>

using namespace std;

//std::ios_base
//class ios_base;
//类 ios_base 是作为所有 I/O 流类的基类工作的多用途类。它维护数种数据：
//1) 状态信息：流状态标志；
//2) 控制信息：控制输入和输出序列格式化和感染的本地环境的标志；
//3) 私有存储：允许 long 和 void* 成员的有下标可扩展数据结构，它可以实现为二个任意长度的数组，或二元素结构体的单个数组，或另一容器；
//4) 回调：从 imbue() 、 copyfmt() 和 ~ios_base() 调用的任意数量用户定义函数。
//典型实现保有对应下列 fmtflags 、 iostate 、 openmode 及 seekdir 所有值的成员常量，维护当前精度、宽度、格式化标志、异常掩码、缓冲区错误状态、保有回调的可调大小容器、当前感染的 locale 、私有存储的成员变量及 xalloc() 所用的静态整数变量。


// 令最近释出的字符再次可用。
int tunget() {
    std::istringstream s1("Hello, world.");
    char c1 = s1.get();
    if (s1.unget())
    {
        char c2 = s1.get();
        std::cout << "Got: " << c1 << " got again: " << c2 << '\n';
    }
}

// std::basic_istream<CharT,Traits>::putback
//basic_istream& putback( char_type ch );
//回放字符 ch 到输入流，从使得下个释出的字符将为 ch 。
//首先清除 eofbit. 若 rdbuf() 为空或若 rdbuf->sputbackc(ch) 返回 Traits::eof() ，则调用 setstate(badbit) 。
int tpuckback()
{
    std::stringstream s1("Hello, world"); // IO 流
    s1.get();
    if (s1.putback('Y')) // 修改缓冲区
        std::cout << s1.rdbuf() << '\n';
    else
        std::cout << "putback failed\n";

    std::istringstream s2("Hello, world"); // 仅输入流
    s2.get();
    if (s2.putback('Y')) // cannot modify input-only buffer
        std::cout << s2.rdbuf() << '\n';
    else
        std::cout << "putback failed\n";

    s2.clear();
    if (s2.putback('H')) // 非修改回放
        std::cout << s2.rdbuf() << '\n';
    else
        std::cout << "putback failed\n";
}

int tget()
{
    std::istringstream s1("Hello, world.");
    char c1 = s1.get(); // 读取'H'
    std::cout << "after reading " << c1 << ", gcount() == " <<  s1.gcount() << '\n';
    char c2;
    s1.get(c2);         // 读取 'e'
    char str[5];
    s1.get(str, 5);     // 读取 "llo,"
    std::cout << "after reading " << str << ", gcount() == " <<  s1.gcount() << '\n';
    std::cout << c1 << c2 << str;
    s1.get(*std::cout.rdbuf()); // 读取剩余，不包括 '\n'
    std::cout << "\nAfter the last get(), gcount() == " << s1.gcount() << '\n';
}

// getline 从流释出字符，直至行尾或指定的分隔符 delim 。
int tgetline()
{
    std::istringstream input("abc|def|gh");
    std::vector<std::array<char, 4>> v;

    // 注意：下列循环在从  getline() 返回的流上的
    // std::ios_base::operator bool() 返回 false 时终止
    for (std::array<char, 4> a; input.getline(&a[0], 4, '|'); ) {
        v.push_back(a);
    }

    for (auto& a : v) {
        std::cout << &a[0] << '\n';
    }
}
// getting the state of stream objects
int tiostate() {
    std::ifstream is;
    is.open("n.txt");
    if ( (is.rdstate() & std::ios_base::failbit ) != 0 )
        std::cerr << "Error opening 'test.txt'\n";
}


// redefine tied object
int ttie () {
    std::ostream *prevstr;
    std::ofstream ofs;
    ofs.open ("test.txt");

    std::cout << "tie example:\n";

    *std::cin.tie() << "This is inserted into cout";
    prevstr = std::cin.tie(&ofs);
    *std::cin.tie() << "This is inserted into the file";
    std::cin.tie (prevstr);

    ofs.close();
    return 0;
}


int tclear () {
    char buffer [80];
    std::fstream myfile;

    myfile.open ("test.txt", std::fstream::in);
    myfile << "test";
    if (myfile.fail())
    {
        std::cout << "Error writing to test.txt\n";
        myfile.clear();
    }

    myfile.getline (buffer,80);
    std::cout << buffer << " successfully read from file.\n";

    return 0;
}

int tsetf() {
    std::cout.setf ( std::ios::hex, std::ios::basefield );  // set hex as the basefield
    std::cout.setf ( std::ios::showbase );                  // activate showbase
    std::cout << 100 << '\n';
    std::cout.unsetf ( std::ios::showbase );                // deactivate showbase
    std::cout << 100 << '\n';
    return 0;
}


void file_it(ostream &os, double fo, const double fe[], int n);
int tformat() {
    const int LIMIT = 5;
    ofstream fout;
    const char*fn = "ep-data.txt";
    fout.open(fn);
    if (!fout.is_open()){
        cout << "can't open " << fn << ".bye.\n";
        exit(EXIT_FAILURE);
    }
    double objective;
    cout << "enter the focal length of your "
            "telescope objective in mm";
    cin >> objective;
    double eps[LIMIT];
    cout << "enter the focal lengths, in mm, of " << LIMIT << " eyepieces.\n";
    for (int i = 0; i < LIMIT; i++){
        cout << "eyepice #" << i + 1 << ":";
        cin >> eps[i];
    }
    file_it(fout, objective, eps, LIMIT);
    file_it(cout, objective, eps, LIMIT);
    cout << "done\n";
    return 0;
}
void file_it(ostream &os, double fo, const double fe[], int n){
    ios_base::fmtflags initial;
    initial = os.setf(ios_base::fixed);
    os.precision(0);
    os << "focal length of objective:" << fo << " mm\n";
    os.setf(ios::showpoint);
    os.precision(1);
    os.width(12);
    os << "f eyepiece";
    os.width(15);
    os << "magnification" << endl;
    for (int i = 0; i < n; i++){
        os.width(12);
        os << fe[i];
        os.width(15);
        os << int(fo / fe[i] + 0.5) << endl;
    }
    os.setf(initial);
}

void tformat1() {
    int a = 21;
    cout.setf(ios::showbase);        // 显示基数符号(0x或)
    cout<<"dec:"<<a<<endl;           // 默认以十进制形式输出
    cout.unsetf(ios::dec);           // 终止十进制格式设置

    cout.setf(ios::hex);             // 设置以十六进制形式输出
    cout<<"hex:"<<a<<endl;
    cout.unsetf(ios::hex);           // 终止十六进制形式输出

    cout.setf(ios::oct);             // 设置以八进制形式输出
    cout<<"oct:"<<a<<endl;
    cout.unsetf(ios::oct);           // 终止八进制形式输出

    char *pt = "China";
    cout.width(10);                  // 指定域宽为10
    cout<<pt<<endl;

    cout.width(10);                  // 指定域宽为10
    cout.fill('*');                  // 设置空白处以*号填充
    cout<<pt<<endl;

    double pi = 22.0/7.0;            // 输出PI值
    cout.setf(ios::scientific);      // 设置以科学计数法形式输出
    cout<<"pi=";
    cout.width(14);                  // 设置域宽为14
    cout<<pi<<endl;
    cout.unsetf(ios::scientific);    // 终止科学计数法形式输出

    cout.setf(ios::fixed);           // 设置以定点形式输出
    cout.width(12);                  // 指定域宽为12
    cout.setf(ios::showpos);         // 正数输出+号
    cout.setf(ios::internal);        // 数符出现在左侧
    cout.precision(6);               // 保留位小数
    cout<<pi<<endl;
}

int tfill () {
    char prev;

    std::cout.width (10);
    std::cout << 40 << '\n';

    prev = std::cout.fill ('x');
    std::cout.width (10);
    std::cout << 40 << '\n';

    std::cout.fill(prev);
    std::cout.width (10);
    std::cout << 40 << '\n';

    return 0;
}

int treadbuf () {
    std::streambuf *psbuf, *backup;
    std::ofstream filestr;
    filestr.open ("test.txt");

    backup = std::cout.rdbuf();     // back up cout's streambuf

    psbuf = filestr.rdbuf();        // get file's streambuf
    std::cout.rdbuf(psbuf);         // assign streambuf to cout

    std::cout << "This is written to the file";

    std::cout.rdbuf(backup);        // restore cout's original streambuf

    filestr.close();

    return 0;
}


int tflags1 () {
    std::cout.flags ( std::ios::right | std::ios::oct | std::ios::showbase );
    std::cout.width (10);
    std::cout << 100 << '\n';
    return 0;
}

int tflags2 () {
    std::cout.setf ( std::ios::hex, std::ios::basefield );  // set hex as the basefield
    std::cout.setf ( std::ios::showbase );                  // activate showbase
    std::cout << 100 << '\n';
    std::cout.unsetf ( std::ios::showbase );                // deactivate showbase
    std::cout << 100 << '\n';
    return 0;
}

int tgcount () {
    char str[20];

    std::cout << "Please, enter a word: ";
    std::cin.getline(str,20);
    std::cout << std::cin.gcount() << " characters read: " << str << '\n';

    return 0;
}

int tignore () {
    char first, last;

    std::cout << "Please, enter your first name followed by your surname: ";

    first = std::cin.get();     // get one character
    std::cin.ignore(256,' ');   // ignore until space

    last = std::cin.get();      // get one character

    std::cout << "Your initials are " << first << last << '\n';

    return 0;
}


int twrite () {
    std::ifstream infile ("test.txt",std::ifstream::binary);
    std::ofstream outfile ("new.txt",std::ofstream::binary);

    // get size of file
    infile.seekg (0,infile.end);
    long size = infile.tellg();
    cout << "file size: "  << size << endl;
    infile.seekg (0);

    // allocate memory for file content
    char* buffer = new char[size];

    // read content of infile
    infile.read (buffer,size);

    // write to outfile
    outfile.write (buffer,size);

    // release dynamically-allocated memory
    delete[] buffer;

    outfile.close();
    infile.close();
    return 0;
}

int tput () {
    std::ofstream outfile ("test.txt");
    char ch;

    std::cout << "Type some text (type a dot to finish):\n";
    do {
        ch = std::cin.get();
        outfile.put(ch);
    } while (ch != '.');

    return 0;
}

int tbuf()
{
    std::ifstream fin("1.txt"); // 只读
    std::ofstream fout("2.txt"); // 只写

    std::string s;
    getline(fin, s);
    std::cout << s << '\n'; // 输出 test.in 的第一行

    fin.rdbuf()->swap(*fout.rdbuf()); // 交换底层缓冲

    getline(fin, s); // 失败：不能从只写 filebuf 读取
    std::cout << s << '\n'; // 打印空行

}

int tbuf1()
{
    std::ifstream fs("test.txt");
    std::filebuf fb;
    fb.open("test.txt", std::ios_base::in);
    std::cout << std::boolalpha
              << "direct call: " << fb.is_open() << '\n'
              << "through streambuf: " << fs.rdbuf()->is_open() << '\n'
              << "through fstream: " << fs.is_open() << '\n';
}


int tread()
{
    // read() 常用于二进制 I/O
    std::string bin = {'\x12', '\x12', '\x12', '\x12'};
    std::istringstream raw(bin);
    std::uint32_t n;
    if(raw.read(reinterpret_cast<char*>(&n), sizeof n))
        std::cout << std::hex << std::showbase << n << '\n';

    // 为下个片段准备文件
    std::ofstream("test.txt", std::ios::binary) << "abcd1\nabcd2\nabcd3";

    // 读取整个文件到 string
    if(std::ifstream is{"test.txt", std::ios::binary | std::ios::ate}) {
        auto size = is.tellg();
        std::string str(size, '\0'); // 构造 string 为流大小
        is.seekg(0);
        if(is.read(&str[0], size))
            std::cout << str << '\n';
    }
}

int ttellg()
{
    std::string str = "Hello, world";
    std::istringstream in(str);
    std::string word;
    in >> word;
    std::cout << "After reading the word \"" << word
              << "\" tellg() returns " << in.tellg() << '\n';
}

int tseekg()
{
    std::string str = "Hello, world";
    std::istringstream in(str);
    std::string word1, word2;

    in >> word1;
    in.seekg(0); // 回溯
    in >> word2;

    std::cout << "word1 = " << word1 << '\n'
              << "word2 = " << word2 << '\n';
}

int treadsome()
{
    char c[10] = {};
    std::istringstream input("This is sample text."); // std::stringbuf 令个缓冲可用于无阻塞读取
    input.readsome(c, 5); // 读取 'This ' 并存储于 c[0] .. c[4]
    input.readsome(c, 9); // 读取 'is sample' 并存储于 c[0] .. c[8]
    std::cout << c;
}

int teof()
{
    std::ifstream file("1.txt");
    if(!file.is_open())  // operator! 用于此
    {
        std::cout << "File opening failed\n";
        return EXIT_FAILURE;
    }

    // 典型的 C++ I/O 循环以 I/O 函数的返回值为循环控制条件，
    // operator bool() 用于此
    for(int n; file >> n; ) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    if (file.bad())
        std::cout << "I/O error while reading\n";
    else if (file.eof())
        std::cout << "End of file reached successfully\n";
    else if (file.fail())
        std::cout << "Non-integer data encountered\n";
}

int tiostate1() {
    std::ostringstream stream;

    if (stream.rdstate() == std::ios_base::goodbit) {
        std::cout << "stream state is goodbit\n";
    }

    stream.setstate(std::ios_base::eofbit);

    // 检查状态为准确的 eofbit （无 failbit 且无 badbit ）
    if (stream.rdstate() & std::ios_base::eofbit) {
        std::cout << "stream state is eofbit\n";
    }
}

int tstr() {
    int n;

    std::istringstream in;  // 亦能用 in("1 2")
    in.rdbuf()->str("1 2"); // 设置获取区
    in >> n;
    std::cout << "after reading the first int from \"1 2\", the int is "
              << n << ", str() = \"" << in.rdbuf()->str() << "\"\n"; // 或 in.str()

    in >> n;
    std::cout << "after reading the first int from \"1 2\", the int is "
              << n << ", str() = \"" << in.rdbuf()->str() << "\"\n"; // 或 in.str()

    std::ostringstream out("1 2");
    out << 3;
    std::cout << "after writing the int '3' to output stream \"1 2\""
              << ", str() = \"" << out.str() << "\"\n";

    std::ostringstream ate("1 2", std::ios_base::ate); // C++11
    ate << 3;
    std::cout << "after writing the int '3' to append stream \"1 2\""
              << ", str() = \"" << ate.str() << "\"\n";
}

int tswap() {
    ostringstream os1("string1");
    ostringstream os2("string2");

    cout <<  "before swap; string1: " << os1.str() << endl << "str2: " << os2.str() << endl;

    os1.swap(os2);
    cout <<  "after swap; string1: " << os1.str() << endl << "str2: " << os2.str() << endl;
}

