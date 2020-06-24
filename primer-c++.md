* **一个类定义了一个类型，以及与其关联的一组操作**。C++最初的一个设计焦点就是能定义使用上像内置类型一样自然的类类型(class type)

* 为了使用一个类，我们不必关心它是如何实现的，只需知道类对象可以执行什么操作。

* 每个类实际上都定义了一个新的类型，其类型名就是类名。

* 类定义了行为
  
  * 一件要牢记的重要事情是，类的作者定义了类对象可以执行的所有动作。一般而言，类的作者决定了类类型对象上可以使用的所有操作。
  
* 成员函数是定义为类的一部分的函数，有 时也被称为方法(method)。我们通常以一个类对象的名义来调用成员函数。

* 点运算符只能用于类类型的对象。其左侧运算对象必须是一个类类型的对象，右侧运算对象必须是该类型的一个成员名，运算结果为右侧运算对象指定的成员。

* 类(class) —种用于定义自己的数据结构及其相关操作的机制。

* **数据结构（data structure) 是数据及其上所允许的操作的一种逻辑组合。**

* 未赋予初值的变量。类类型的变量如果未指定初值，则按类定义指定的方式进行初始化。定义在函数内部的内置类型变暈默认是不初始化的，除非有显式的初始化语句。试图使用一个未初始化变量的值是错 误的"未初始化变量是bug的常见成因

* 数据类型是程序的基础：它告诉我们数据的意义以及我们能在数据上执行的操作。

* C++定义了一套包括算术类型（arithmetic type）和空类型（void）在内的基本数据类 型。其中算术类型包含了字符、整型数、布尔值和浮点数。空类型不对应具体的值，仅用 于一些特殊的场合，例如最常见的是，当函数不返回任何值时使用空类型作为返回类型。

* **算术类型**分为两类：整型（integral type,包括字符和布尔类型在内）和浮点型。

* 算术类型的尺寸（也就是该类型数据所占的比特数）在不同机器上有所差别。

* C++提供了几种字符类型，其中多数支持国际化。基本的字符类型是char,—个char 的空间应确保可以存放机器基本字符集中任意字符对应的数字值。类型char16_t, ln char32_t则为Unicode字符集服务（Unicode是用于表示所有自然语言中字符的标准）。

* 除字符和布尔类型之外，其他整型用于表示（可能）不同尺寸的整数。C"语言规定 —个int至少和一个short 一样大,一个long至少和一个int —样大，一个long long至少和一个long一样大。其中，数据类型long long是在C++11中新定义的。

* 计算机以比特序列存储数据，每个比特非0即1.

* 大多数计算机以2的整数次幕个比特作为块来处理内存，可寻址的最小内存块称为’字节（byte 存储的基本单元称为字（word）,它通常由几个字节组成。在C++语言 中，**一个字节要至少能容纳机器基本字符集中的字符**。大多数机器的字节由8比特构成, 字则由32或64比特构成，也就是4或8字节.

* 多数计算机将内存中的每个字节与一个数字（被称为地址（address ））关联起 来

* 我们能够使用某个地址来表示从这个地址开始的大小不同的比特串.为了赋予内存中某个地址明 确的含义，必须首先知道存储在该地址的数据的类型。类型决定了数据所占的比特数以 及该如何解释这些比特的内容。

* 浮点型可表示单精度、双精度和扩展精度值。C++标准指定了一个浮点数有效位数的 最小值，然而大多数编译器都实现了更髙的精度。

* 除去布尔型和扩展的字符型之外，其他整型可以划分为带符号的（signed）和无符号 的（unsigned）两种。带符号类型可以表示正数、负数或0,无符号类型则仅能表示大于 等于0的值。

* 其他整型不同,字符型被分为了二种：char、signed char和unsigned char。特别需要注意的是：类型char和类型signed char并不一样。尽管字符型有三种，但是字符的表现形式却只有两种：带符号的和无符号的。类型char实际上会表现为上述两 种形式中的一种，具体是哪种由编译器决定。

* 无符号类型中所有比特都用来存储值，C++标准并没有规定带符号类型应如何表示，但是约定了在表示范围内正值和负值的 量应该平衡。

* 如何选择类型

  * 当明确知晓数值不可能为负时，选用无符号类型。
  * 使用int执行整数运算。如果你的数值超过了 int的表示范围，选用long long。
  * 在算术表达式中不要使用char或bool,只有在存放字符或布尔值时才使用它 们。因为类型char在一些机器上是有符号的，而在另一些机器上又是无符号的， 所以如果使用char进行运算特别容易出问题。如果你需要使用一个不大的整数， 那么明确指定它的类型是signed char或者unsigned char。
  * 执行浮点数运算选用double,这是因为float通常精度不够而且双精度浮点 数和单精度浮点数的计算代价相差无几。

* 类型转换

  * 对象的类型定义了对象能包含的数据和能参与的运算，其中一种运算被大多数类型支持，就是将对象从一种给定的类型转换（convert）为另一种相关类型。
  * 当在程序的某处我们使用了一种类型而其实对象应该取另一种类型时，程序会自动进行类型转换
  * 当我们把一个非布尔类型的算术值赋给布尔类型时，初始值为0则结果为false, 否则结果为true。当我们把一个布尔值赋给非布尔类型时，初始值为false则结果为0,初始值为 true则结果为 1
  * 当我们把一个浮点数赋给整数类型时，进行了近似处理。结果值将仅保留浮点数中 小数点之前的部分
  * 当我们把一个整数值赋给浮点类型时，小数部分记为0。如果该整数所占的空间超 过了浮点类型的容量，精度可能有损失
  * 当我们赋给无符号类型一个超出它表示范围的值时，结果是初始值对无符号类型表示数值总数取模后的余数。例如，8比特大小的unsigned char可以表示0至 255区间内的值，如果我们赋了一个区间以外的值，则实际的结果是该值对256 取模后所得的余数。因此，把-1赋给8比特大小的unsigned char所得的结果 是 255。
  * 当我们赋给带符号类型一个超出它表示范围的值时，结果是未定义的（undefined）o 此时，程序可能继续工作、可能崩溃，也可能生成垃圾数据。

* 避免无法预知和依赖于实现环境的行为

  * 无法预知的行为源于编译器无须（有时是不能）检测的错误。即使代码编译通过了， 如果程序执行了一条未定义的表达式，仍有可能产生错误。
  * 不幸的是,在某些情况和/或某些编译器下,含有无法预知行为的程序也能正确执行。 但是我们却无法保证同样一个程序在别的编译器下能正常工作，甚至已经编译通过的代 码再次执行也可能会出错。此外，也不能认为这样的程序对一组输入有效，对另一组输 入就一定有效。
  * 程序也应该尽量避免依赖于实现环境的行为。如果我们把int的尺寸看成是一个确定不变的已知值，那么这样的程序就称作不可移植的（nonportable ）0当程序移植到别 的机器上后，依赖于实现环境的程序就可能发生错误。要从过去的代码中定位这类错误 可不是一件轻松愉快的工作。

* 尽管我们不会故意给无符号对象赋一个负值，却可能（特别容易）写出这么做的代码。 

* 当从无符号数中减去一个值时，不管这个值是不是无符号数，我们都必须确保结果不 能是一个负值（运算正确， 得到的却是对容量取模的结果）

  ```
  for (unsigned int i = 10; i >= 0; --i) {
    std::cout << i << std::endl;
  }
  ```

* 如果表达式里既有带符号类型又有无符号类型，当带符号类型取值为负时会出现异 常结果，这是因为带符号数会自动地转换成无符号数。

* 字而值常量

* 一个形如42的值被称作字面值常量（literal）,这样的值一望而知。每个字面值常量 都对应一种数据类型，字面值常量的形式和值决定了它的数据类型。

* 我们可以将整型字面值写作十进制数、八进制数或十六进制数的形式。以0开头的整数代表八进制数，以0x或0X开头的代表十六进制数。

* 整型字面值具体的数据类型由它的值和符号决定。**默认情况下，十进制字面值是带符号数， 八进制和十六进制字面值既可能是带符号的也可能是无符号的**。十进制字面值的类型是 int、long和long long中尺寸最小的那个（例如，三者当中最小是int）,当然前提 是这种类型要能容纳下当前的值。八进制和十六进制字面值的类型是能容纳其数值的 int, unsigned int, long、unsigned long、long long 和 unsigned long long 中的尺寸最小者。如果一个字面值连与之关联的最大的数据类型都放不下，将产生错误。 类型short没有对应的字面值。

* 尽管整型字面值可以存储在带符号数据类型中，但严格来说，十进制字面值不会是负 数。如果我们使用了一个形如-42的负十进制字面值，那个负号并不在字面值之内，它的 作用仅仅是对字面值取负值而已。

* 浮点型字面值表现为一个小数或以科学计数法表示的指数，其中指数部分用E或e标识. 默认的，浮点型字面值是一个double

* 字符和字符串字面值

  * 由单引号括起来的一个字符称为char型字面值，双引号括起来的零个或多个字符则 构成字符串型字面值。
  * 字符串字面值的类型实际上是由常量字符构成的数组（array）,编译器在每个字符串的结尾处添加一个空字符（\0）,因此，字符串字 面值的实际长度要比它的内容多1.
  * 字面值A，表示的就是单独的字符A,而字符 串”A"则代表了一个字符的数组，该数组包含两个字符：一个是字母A、另一个是空字符。
  * 如果两个字符串字面值位置紧邻且仅由空格、缩进和换行符分隔，则它们实际上是一 个整体。

* 转义序列

* 有两类字符程序员不能直接使用：一类是不可打印（nonprintable）的字符，如退格或其他控制字符，因为它们没有可视的图符；另一类是在C++语言中有特殊含义的字符（单 引号、双引号、问号、反斜线）。在这些情况下需要用到转义序列（escape sequence）,转义序列均以反斜线作为开始

* 我们也可以使用泛化的转义序列，其形式是\x后紧跟1个或多个十六进制数字，或\后 紧跟1个、2个或3个八进制数字，其中数字部分表示的是字符对应的数值。

* 我们可以像使用普通字符那样使用C++语言定义的转义序列

* 注意，如果反斜线\后面跟着的八进制数字超过3个，只有前3个数字与\构成转义序列。 例如，"\1234"表示2个字符，即八进制数123对应的字符以及字符4。相反，\x要用到后面跟着的所有数字，例如，"\xl234"表示一个16位的字符，该字符由这4个十六 进制数所对应的比特唯一确定。因为大多数机器的char型数据占8位，所以上面这个例 子可能会报错。一般来说，超过8位的十六进制字符都是与表2.2中某个前缀作为开头的 扩展字符集一起使用的。

* 对于一个整型字面值来说，我们能分别指定它是否带符号以及占用多少空间。如果后 缀中有U,则该字面值属于无符号类型，也就是说，以U为后缀的十进制数、八进制数或 十进缶I数都将从 unsigned int% unsigned long 和 unsigned long long 中选择 能匹配的空间最小的一个作为其数据类型。如果后缀中有L,则字面值的类型至少是long； 如果后缀中有LL,则字面值的类型将是long long和unsigned long long中的一种。 显然我们可以将U与L或LL合在一起使用。例如，以UL为后缀的字面值的数据类型将 根据具体数值情况或者取unsigned long,或者取unsigned long long

* true和false是布尔类型的字面值: nullptr 是指针字面值

#### 变量

* 变量提供一个具名的、可供程序操作的存储空间。c++中的每个变量都有其数据类型， 数据类型决定着变量所占内存空间的大小和布局方式、该空间能存储的值的范围，以及变量能参与的运算。对c++程序员来说，"变量(variable)w和"对象(object)"一般可以互 换使用。
* 变量定义的基本形式是：首先是类型说明符(type specifier),随后紧跟由一个或多个 变量名组成的列表，其中变量名以逗号分隔，最后以分号结束。列表中每个变量名的类型 都由类型说明符指定，定义时还可以为一个或多个变量赋初值;
* 何为对象
  * C++程序员们在很多场合都会使用对象(object)这个名词.通常情况下，**对象是指一块能存储数据并具有某种类型的内存空间**。
  * 一些人仅在与类有关的场景下才使用“对象”这个词。另一些人则已把命名的对象和未命名的对象区分开来，他们把命名了的对象叫做变量,还有一些人把对象和值区分 开来，其中对象指能被程序修改的数据，而值(value)指只读的数据。

* 初始值

  * 当对象在创建时获得了一个特定的值，我们说这个对象被初始化(initialized) 了。用 于初始化变量的值可以是任意复杂的表达式。当一次定义了两个或多个变量时，对象的名 字随着定义也就马上可以使用了。因此在同一条定义语句中，可以用先定义的变量值去初 始化后定义的其他变量。
  * C++语言中，初始化和赋值是两个完全不同的操作。
  * 初始化不是赋值，初始化的含义是创建变量时赋予其一个初始值，而赋值的含义土义是把对象的当前值擦除，而以一个新值来替代

* 列表初始化

  * C++语言定义了初始化的好几种不同形式，这也是初始化问题复杂性的一个体现

    ```c++
    int a0 = 10;
    int a1 = {10};
    int a2{10};
    int a3(10);
    ```

  * 当用于内置类型的变量时，这种初始化形式有一个重要特点：如果我们使用列表初始 化且初始值存在丢失信息的风险，则编译器将报错：

    ```c++
    long double ld = 231236431.12313131;
    int a1{ld}, a2 = {ld}; // error
    int a3(ld), a4 = ld;
    ```

* 默认初始化

* 如果定义变量时没有指定初值，则变量被默认初始化（default initialized）,此时变量 赋予了 “默认值”。**默认值到底是什么由变量类型决定，同时定义变量的位置也会对此有影响**。

* 如果是内置类型的变量未被显式初始化，它的值由定义的位置决定。定义于任何函数体之外的变量被初始化为0. 定义在函数体内部的内置类型变量将不被初始化（uninitialized）。一个未被初始化的内置类型变量的值是未定义的，如果试图拷贝或以其他形式访问此类值 将引发错误。

* 每个类各自决定其初始化对象的方式。而且，是否允许不经初始化就定义对象也由类自己决定。如果类允许这种行为，它将决定对象的初始值到底是什么。绝大多数类都支持无须显式初始化而定义对象，这样的类提供了一个合适的默认值。一些类要求每个对象都显式初始化，此时如果创建了一个该类的对象而未对其做明确 的初始化操作，将引发错误。定义于函数体内的内置类型的对象如果没有初始化，则其值未定义. 类的对象 如果没有显式地初始化，则其值由类确定

* 提示：未初始化变量引发运行时故障

  * 未初始化的变量含有一个不确定的值，使用未初始化变量的值是一种错误的编程行 为并且很难调试。尽管大多数编译器都能对一部分使用未初始化变量的行为提出警告， 但严格来说，编译器并未被要求检查此类错误。
  * 使用未初始化的变量将带来无法预计的后果"有时我们足够幸运,一访问此类对象 程序就崩溃并报错，此时只要找到崩溃的位置就很容易发现变量没被初始化的问题。另 外一些时候，程序会一直执行完井产生错误的结果。更糟糕的情况是，程序结果时对时 错、无法把握。而且，往无关的位置添加代码还会导致我们误以为程序对了，其实结果 仍旧有错。
  * **建议初始化每一个内置类型的变量**, 虽然并非必须这么做，但如果我们不能确保初始化后程序安全，那么这么做不失为一种简单可靠的方法。

* 变量声明和定义的关系

  * 为了允许把程序拆分成多个逻辑部分来编写，C++语言支持分离式编译(separate compilation)机制，该机制允许将程序分割为若干个文件，每个文件可被独立编译。

  * 如果将程序分为多个文件，则需要有在文件间共享代码的方法。例如，一个文件的代码可能需要使用另一个文件中定义的变量。一个实际的例子是std: : cout和std: : cin, 它们定义于标准库，却能被我们写的程序使用。

  * 为了支持分离式编译，C++语言将声明和定义区分开来。**声明(declaration)使得名字为程序所知**，一个文件如果想使用别处定义的名字则必须包含对那个名字的声明。而**定义 (definition)负责创建与名字关联的实体**。

  * **变量声明规定了变量的类型和名字**，在这一点上定义与之相同。但是除此之外，**定义还申请存储空间，也可能会为变量赋一个初始值**。

  * **如果想声明一个变量而非定义它，就在变量名前添加关键字extern,而且不要显式地初始化变量**

  * **任何包含了显式初始化的声明即成为定义**。我们能给由extern关键字标记的变量赋 一个初始值，但是这么做也就抵消了extern的作用。extern语句如果包含初始值就不再是声明，而变成定义了

  * 在函数体内部，如果试图初始化一个由extern关键字标记的变量，将引发错误。

  * **变量能且只能被定义一次，但是可以被多次声明**。

  * 如果要在多个文件中使用同一个变量，就必须将声明和定义分离。此时，变量的定义必须出现在且只能出现在一个文件中，而其他用到该变量的文件必须对其进行声明，却绝对不能重复定义。

    ```
    extern int i;	//声明i而非定义i
    int j;	//声明并定义j
    extern double p = 3.1416; // 定义
    ```

* 静态类型

  * C++是一种静态类型(statically typed )语言，其含义是在**编译阶段检查类型**。其中， 检查类型的过程称为**类型检查(type checking )**
  * 我们已经知道，对象的类型决定了对象所能参与的运算。在C++语言中，**编译器负责检查数据类型是否支持要执行的运算,如果试图执行类型不支持的运算，编译器将报错并且不会生成可执行文件。**
  * 程序越复杂，静态类型检查越有助于发现问题然而，前提是编译器必须知道每一 个实体对象的类型，这就要求我们在使用某个变量之前必须声明其类型。

* 标识符

  * C++的标识符(identifier)由字母、数字和下画线组成，其中必须以字母或下画线开 头。标识符的长度没有限制，但是对大小写字母敏感.
  * C++语言保留了一些名字供语言本身使用，这些名字不能被用 作标识符。
  * C++也为标准库保留了一些名字。用户自定义的标识符中不能连续出现两个 画线，也不能以下画线紧连大写字母开头。此外，定义在函数体外的标识符不能以下画线 开头。
  * 变量命名有许多约定俗成的规范，下面的这些规范能有效提高程序的可读性：
    * 标识符要能体现实际含义。
    * 变量名一般用小写字母，如index,不要使用Index或INDEX.
    * 用户自定义的类名一般以大写字母开头，如Sales_itemo
    * 如果标识符由多个单词组成，则单词间应有明显区分，如 Student_loan 或 StudentLoan,不要使用 studentloano

* 名字的作用域

  * **不论是在程序的什么位置，使用到的每个名字都会指向一个特定的实体**：变量、函数、类型等。然而，同一个名字如果出现在程序的不同位置，也可能指向的是不同实体。
  * 作用域(scope)是程序的一部分，在其中名字有其特定的含义。C++语言中大多数作用域都以花括号分隔。
  * **同一个名字在不同的作用域中可能指向不同的实体**。名字的有效区域始于名字的声明语句，以声明语句所在的作用域末端为结束。
  * **定义在函数体之外的名字一样拥有全局作用域(global scope)o 一旦声明之后，全局作用域内的名字在整个程序的范围内都可使用。**
  * **当你第一次使用变量时再定义它**
    * 一般来说.在对象第一次被使用的地方附近定义它是一种好的选择，因为这样做有 助于更容易地找到变量的定义。更重要的是，当变量的定义与它第一次被使用的地方很 近时，我们也会赋给它一个比较合理的初始值。
  * 嵌套的作用域
    * 作用域能彼此包含**，被包含(或者说被嵌套)的作用域称为内层作用域(innerscope), 包含着别的作用域的作用域称为外层作用域(outer scope)**
  * **作用域中一旦声明了某个名字，它所嵌套着的所有作用域中都能访问该名字。同时， 允许在内层作用域中重新定义外层作用域已有的名字**
  * 如果函数有可能用到某全局变量，则不宜再定义一个同名的局部变量。

* 复合类型

  * 复合类型(compound type)是指基于其他类型定义的类型。C++语言有几种复合类型， 本章将介绍其中的两种：引用和指针。
  * 与我们已经掌握的变量声明相比，定义复合类型的变量要复杂很多。一条简单的声明语句由一个数据类型和紧随其后的一个变量名列表组成。其实更通 用的描述是，**一条声明语句由一个基本数据类型(base type)和紧随其后的一个声明符 (declarator)列表组成**。**每个声明符命名了一个变量并指定该变量为与基本数据类型有关的某种类型。**
  * 目前为止，我们所接触的声明语句中，声明符其实就是变量名，此时变量的类型也就是声明的基本数据类型。其实还可能有更复杂的声明符，它基于基本数据类型得到更复杂的类型，并把它指定给变量。

* 引用

  * **引用(reference)为对象起了另外一个名字**，引用类型引用(refers to)另外一种类型。 通过将声明符写成&d的形式来定义引用类型，其中d是声明的变量名
  * 一般在初始化变量时，初始值会被拷贝到新建的对象中。然而**定义引用时，程序把引用和它的初始值绑定（bind）在一起，而不是将初始值拷贝给引用**。一旦初始化完成，引用将和它的初始值对象一直绑定在一起。因为**无法令引用重新绑定到另外一个对象**，因此**引用必须初始化**。

* 引用即别名

  * 引用并非对象，相反的，它只是为一个已经存在的对象所起的另外一个名字定义了一个引用之后，对其进行的所有操作都是在与之绑定的对象上进行的
  * 引用赋值，实际上是把值赋给了与引用绑定的对象。获取引用的值，实际上是获取了与 引用绑定的对象的值。同理，以引用作为初始值，实际上是以与引用绑定的对象作为初 始值
  * 因为**引用本身不是一个对象，所以不能定义引用的引用。**
  * 允许在一条语句中定义多个引用,其中每个引用标识符都必须以符号&开头
  * **所有引用的类型都要和与之绑定的对象严格匹配。而且，引用只能绑定在对象上，而不能与字面值或某个表达式的计算结果绑定在一起**

* 指针

  * 指针（pointer）是“指向（point to）”另外一种类型的复合类型。与引用类似，**指针也实现了对其他对象的间接访问**。然而指针与引用相比又有很多不同点。其一，**指针本身就是一个对象，允许对指针赋值和拷贝，而且在指针的生命周期内它可以先后指向几个不同的对象**。其二，**指针无须在定义时赋初值。和其他内置类型一样，在块作用域内定义的指针如果没有被初始化，也将拥有一个不确定的值**。
  * 定义指针类型的方法将声明符写成\*d的形式，其中d是变量名。如果在一条语句中 定义了几个指针变量，每个变量前面都必须有符号\*
  * 获取对象的地址, 指针存放某个对象的地址，要想获取该地址，需要使用取地址符（操作符&）
  * **因为引用不是对象，没有实际地址，所以不能定义指向引用的指针。**
  * 因为在声明语句中指针的类型实际上被用于指定它所指向对象的类型，所以两者必须匹 配。如果指针指向了一个其他类型的对象，对该对象的操作将发生错误。

* 指针值，指针的值（即地址）应属下列4种状态之一:

  1. 指向一个对象。

  2. 指向紧邻对象所占空间的下一个位置。
  3. 空指针，意味着指针没有指向任何对象。
  4. 无效指针，也就是上述情况之外的其他值。

* **试图拷贝或以其他方式访问无效指针的值都将引发错误**。编译器并不负责检査此类错误， 这一点和试图使用未经初始化的变量是一样的。访问无效指针的后果无法预计，因此程序员必须清楚任意给定的指针是否有效。

* 如果指针指向了一个对象，则允许使用**解引用符（操作符*）**来访问该对象

* 对指针解引用会得出所指的对象，因此如果给解引用的结果赋值，实际上也就是给指针所指的对象赋值

* **解引用操作仅适用于那些确实指向了某个对象的有效指针**

* 关键概念：某些符号有多种含义

  * 像&和*这样的符号，既能用作表达式里的运算符，也能作为声明的一部分出现，符 号的上下文决定了符号的意义
  * 在声明语句中，&和*用于组成复合类型；在表达式中，它们的角色又转变成运算符。在 不同场景下出现的虽然是同一个符号，但是由于含义截然不同，所以我们完全可以把它 当作不同的符号来看待。

* 空指针

  * 空指针（null pointer）不指向任何对象，在试图使用一个指针之前代码可以首先检査它是否为空。
  * 得到空指针最直接的办法就是**用字面值nullptr来初始化指针**，这也是C++11新标准刚 刚引入的一种方法。nullptr是一种特殊类型的字面值，它可以被转换成任意其他的指针类型。另一种办法可以通过**将指针初始化为字面值0来生成空指针**。过去的程序还会**用到一个名为NULL的预处理变量**（preprocessor variable）来给指针赋值，这个变量在头文件cstdlib中定义，它的值就是0。
  * 预处理器是 运行于编译过程之前的一段程序. 预处理变量不属于命名空间,它由预处理器负责管理，因此我们可以直接使用预处理变量而无须在前面加上std::
  * 当用到一个预处理变量时，预处理器会自动地将它替换为实际值，因此用NULL初始 化指针和用0初始化指针是一样的。
  * **把int变量直接赋给指针是错误的操作，即使int变量的值恰好等于0也不行。**(指针变量未初始化，赋值会产生预期之外的错误)

* 建议：初始化所有指针

  * 使用未经初始化的指针是引发运行时错误的一大原因。和其他变量一样，访问未经初始化的指针所引发的后果也是无法预计的、通常这一 行为将造成程序崩溃，而且一旦崩溃，要想定位到出错位置将是特别棘手的问题。
  * 在大多数编译器环境下，如果使用了未经初始化的指针，则该指针所占内存空间的当前内容将被看作一个地址值。访问该指针，相当于去访问一个本不存在的位置上的本不存在的对象。糟糕的是’如果指针所占内存空间中恰好有内容，而这些内容又被当作了某个地址，我们就很难分清它到底是合法的还是非法的了
  * 因此建议初始化所有的指针，并且在可能的情况下，尽量等定义了对象之后再定义指向它的指针。如果实在不清楚指针应该指向何处，就把它初始化为nullptr或者0, 这样程序就能检测并知道它没有指向任何具体的对象了。

* 赋值和指针

  * 指针和引用都能提供对其他对象的间接访问，然而在具体实现细节上二者有很大不 同，其中最重要的一点就是引用本身并非一个对象。一旦定义了引用，就无法令其再绑定到另外的对象，之后每次使用这个引用都是访问它最初绑定的那个对象。
  * 指针和它存放的地址之间就没有这种限制了。和其他任何变量（只要不是引用）一样， 给指针赋值就是令它存放一个新的地址，从而指向一个新的对象：
  * 有时候要想搞清楚一条赋值语句到底是改变了指针的值还是改变了指针所指对象的值不太容易，最好的办法就是记住**赋值永远改变的是等号左侧的对象**。

* 只要指针拥有一个合法值，就能将它用在条件表达式中。如果指针的值是0,取false：任何非0指针对应的条件值都是true
* 对于两个类型相同的合法指针，可以用相等操作符（==）或不相等操作符（!=）来比较它们，比较的结果是布尔类型。**如果两个指针存放的地址值相同，则它们相等**；反之它 们不相等。这里两个指针存放的地址值相同（两个指针相等）有三种可能：它们都为空、 都指向同一个对象，或者都指向了同一个对象的下一地址。需要注意的是，一个指针指向某对象，同时另一个指针指向另外对象的下一地址，此时也有可能出现这两个指针值相同的情况，即指针相等。因为上述操作要用到指针的值，所以不论是作为条件出现还是参与比较运算，都必须使用合法指针，使用非法指针作为条件或进行比较都会引发不可预计的后果。

* void\*指针
  * **void\*是一种特殊的指针类型，可用于存放任意对象的地址**。一个void\*指针存放着一个地址，这一点和其他指针类似。不同的是，我们对该地址中到底是个什么类型的对象并不了解.
  * 利用void\*指针能做的事儿比较有限：拿它和别的指针比较、作为函数的输入或输出，或者赋给另外一个void\*指针。**不能直接操作void\*指针所指的对象，因为我们并不知道这个对象到底是什么类型，也就无法确定能在这个对象上做哪些操作。**
  * 概括说来，**以void\*的视角来看内存空间也就仅仅是内存空间，没办法访问内存空间中所存的对象**

* 理解复合类型的声明

  * 变量的定义包括一个**基本数据类型(base type)**和**一组声明符**。在同一条 定义语句中，虽然基本数据类型只有一个，但是声明符的形式却可以不同。也就是说，一 条定义语句可能定义出不同类型的变量；

  * 很多程序员容易迷惑于基本数据类型和类型修饰符的关系，其实后者不过是声明符的一部分罢了

  * 经常有一种观点会误以为，在定义语句中，**类型修饰符(*或&)**作用于本次定义的全 部变量。造成这种错误看法的原因有很多，其中之一是我们可以把空格写在类型修饰符和 变量名中间：

    ```
    int* p;	//合法但是容易产生误导
    // 种写法可能产生误导是因为int*放在一起好像是这条语句中所有变量共同的类型一样。其实恰恰相反，基本数据类型是int而非int*。*仅仅是修饰了 P而已，对该 声明语句中的其他变量，它并不产生任何作用：
    ```

  * 涉及指针或引用的声明，一般有两种写法。第一种**把修饰符和变量标识符写在一起**,  这种形式着重强调变量具有的复合类型。第二种**把修饰符和类型名写在一起，并且每条语句只定义一个变量**,这种形式着重强调本次声明定义了一种复合类型。

* **指向指针的指针**

  * 一般来说，**声明符中修饰符的个数并没有限制**。当有多个修饰符连写在一起时，按照 其逻辑关系详加解释即可。以指针为例，**指针是内存中的对象**，像其他对象一样也有自己 的地址，因此允许把指针的地址再存放到另一个指针当中。
  * 通过\*的个数可以区分指针的级别。也就是说，\*\*表示指向指针的指针，\*\*\*表示指向指针的指针的指针
  * 解引用int型指针会得到一个int型的数，同样，**解引用指向指针的指针会得到一个指针**。此时为了访问最原始的那个对象，需要对指针的指针做两次解引用

* 指向指针的引用

  * **引用本身不是一个对象，因此不能定义指向引用的指针。但指针是对象，所以存在对指针的引用**

  * 要理解变量的类型到底是什么，最简单的办法是从右向左阅读变量的定义。**离变量名最近的符号对变量的类型有最直接的影响。**声明符的其余部分用以确定变量的类型是什么

    ```
    int *&p; // 只想指针的引用
    ```

  * 面对一条比较复杂的指针或引用的声明语句时，从右向左阅读有助于弄清楚它 的真实含义。

* const限定符

  * 我们希望定义这样一种变量，它的值不能被改变。例如，用一个变量来表示缓冲 区的大小。使用变量的好处是当我们觉得缓冲区大小不再合适时，很容易对其进行调整。 另一方面，也应随时警惕防止程序一不小心改变了这个值。为了满足这一要求，可以用关键字const对变量的类型加以限定

  * 因为**const对象一旦创建后其值就不能再改变**，所以**const对象必须初始化**。一如既往, 初始值可以是任意复杂的表达式

    ```c++
    const int a = get_size(); // //正确：运行时初始化
    const int a = 10;//正确：编译时初始化
    ```

  * 正如之前反复提到的，**对象的类型决定了其上的操作**。与非const类型所能参与的操作相比，const类型的对象能完成其中大部分，但也不是所有的操作都适合。主要的限制就是**只能在const类型的对象上执行不改变其内容的操作**。例如，const int和普通 的int一样都能参与算术运算，也都能转换成一个布尔值，等等。在不改变const对象的操作中还有一种是初始化，**如果利用一个对象去初始化另外 一个对象，则它们是不是const都无关紧要**
  * 拷贝一个对象的值并不会改变const类型，一旦拷贝完成，新的对象就和原来的对象没什么关系了。

* **默认状态下，const对象仅在文件内有效**。当以编译时初始化的方式定义一个const对象时，**编译器将在编译过程中把用到该变量的地方都替换成对应的值**。为了执行上述替换，**编译器必须知道变量的初始值**。如果程序包含多个文件，则每个用了 const对象的文件都必须得能访问到它的初始值才行。要做到这一点，就必须在每 ―个用到变量的文件中都有对它的定义。为了支持这一用法， 同时避免对同一变量的重复定义，默认情况下，const对象被设定为仅在文件内有效。当多个文件中出现了同名的const变量时，其实等同于在不同文件中分别定义了独立的变量。

* 某些时候有这样一种const变量，它的初始值不是一个常量表达式，但又确实有必 要在文件间共享。这种情况下，我们不希望编译器为每个文件分别生成独立的变量。相反， 我们想让这类const对象像其他(非常量)对象一样工作，也就是说，只在一个文件中 定义const.而在其他多个文件中声明并使用它。解决的办法是，对于**const变量不管是声明还是定义都添加extern关键字**，这样只需定义一次就可以了

* **全局变量或函数本质上讲没有区别**，函数名是指向函数二进制块开头处的指针。而全局变量是在函数外部声明的变量。函数名也在函数外，因此函数也是全局的。

* const 的引用

  *  可以把引用绑定到const对象上，就像绑定到其他对象上一样，我们称之为**对常量的引用(**reference to const)。与普通引用不同的是，**对常量的引用不能被用作修改它所绑定的对象**
  * 不能让一个非常量引用指向一个常量对象

* 常量引用是对const的引用

  * 严格来说，并不存在常量引用。因为引用不是一个对象，所以我们没法让引用本身恒定不变。事实上，由于C++语言并不允许随意改变引用所绑定的对象，所以从这层意义上理解所有的引用又都算是常量。**引用的对象是常量还是非常量可以决定其所能参与的操作，却无论如何都不会影响到引用和对象的绑定关系本身**。

* 初始化和对const的引用

  * **引用的类型必须与其所引用对象的类型一致**，但是有两个例外。第一种例外情况就是在初始化常量引用时允许用任意表达式作为初始值，只要该表 达式的结果能转换成（参见2.1.2节，第32页）引用的类型即可。尤其，允许为一个常量 引用绑定非常量的对象、字面值，甚至是个一般表达式：

    ```
        int i = 42;
        const int &rl = i;
        const int &r2 = 42;	//允许将const int&绑定到一个普通int对象上 //正确：rl是一个常量引用
        const int &r3 = rl * 2;	//正确：r3是一个常量引用
        int &r4 = rl * 2;	//错误：r4是一个普通的非常量引用
    ```

  * **所谓临时量对象就是当编译器需要一个空间来暂存表达式的求值结果时临时创建的一个未命名的对象**。C++程序员们常 常把临时量对象简称为临时量。

    ```
    double dval = 3.14;
    const int &ri = dval;
    ----
    const int temp = dval;	//由双精度浮点数生成一个临时的整型常量
    const int &ri = temp;	//让ri绑定这个临时量
    
    在这种情况下，ri绑定了一个临时量（temporary）对象。
    接下来探讨当ri不是常量时，如果执行了类似于上面的初始化过程将带来什么样的 后果。如果ri不是常量，就允许对ri赋值，这样就会改变ri所引用对象的值。注意， 此时绑定的对象是一个临时量而非dval。程序员既然让ri引用dval,就肯定想通过 ri改变dval的值，否则干什么要给ri赋值呢？如此看来，既然大家基本上不会想着把引用绑定到临时量上，C++语言也就把这种行为归为非法。
    ```

* 对const的引用可能引用一个并非const的对象

  * 必须认识到，**常量引用仅对引用可参与的操作做出了限定，对于引用的对象本身是不是一个常量未作限定**。因为对象也可能是个非常量，所以允许通过其他途径改变它的值

* 指针和const

  * 与引用一样，也可以令指针指向常量或非常量。类似于常量引用，指向常量的指针（pointer to const）不能用于改变其所指对象的值。要想存放常量对象的地址，只能使用指向常量的指针
  * 指针的类型必须与其所指对象的类型一致，但是有两个例外。第一种例外情况是**允许令一个指向常量的指针指向一个非常量对象**
  * 和常量引用一样，指向常量的指针也没有规定其所指的对象必须是一个常量。所谓指向常量的指针仅仅要求不能通过该指针改变对象的值，而没有规定那个对象的值不能通过其他途径改变。

* 所谓指向常量的指针或引用，不过是指针或引用“自以为是” 罢了，它们觉得自己指向了常量，所以自觉地不去改变所指对象的值。

* const指针

  * 指针是对象而引用不是，因此就像其他对象类型一样，允许把指针本身定为常量。**常量指针（constpointer）必须初始化，而且一旦初始化完成，则它的值（也就是存放在指针 中的那个地址）就不能再改变了**。把\*放在const关键字之前用以说明指针是一个常量， 这样的书写形式隐含着一层意味，即不变的是指针本身的值而非指向的那个值
  * **要想弄清楚这些声明的含义最行之有效的办法是从右向左阅读。**
  * 指针本身是一个常量并不意味着不能通过指针修改其所指对象的值，能否这样做完全依赖于所指对象的类型。

* 顶层 const

  * 如前所述，指针本身是一个对象，它又可以指向另外一个对象。因此，指针本身是不是常量以及指针所指的是不是一个常量就是两个相互独立的问题。用名词**顶层const (top-level const)表示指针本身是个常量**，而用名词**底层const (low-level const)表示指针所指的对象是一个常量**。
  * 更一般的，**顶层const可以表示任意的对象是常量，这一点对任何数据类型都适用**， 如算术类型、类、指针等。**底层const则与指针和引用等复合类型的基本类型部分有关**。 比较特殊的是，指针类型既可以是顶层const也可以是底层const,这一点和其他类型相比区别明显

* constexpr和常量表达式

  * **常量表达式（const expression）是指值不会改变并且在编译过程就能得到计算结果的表达式**。显然，字面值属于常量表达式，用常量表达式初始化的const对象也是常量表达式。后面将会提到，C++语言中有几种情况下是要用到常量表达式的。
  * 一个对象（或表达式）是不是常量表达式由它的数据类型和初始值共同决定

* constexpr 变量

  * 在一个复杂系统中，很难（几乎肯定不能）分辨一个初始值到底是不是常量表达式。 当然可以定义一个const变量并把它的初始值设为我们认为的某个常量表达式，但在实际使用时，尽管要求如此却常常发现初始值并非常量表达式的情况。可以这么说，在此种情况下，对象的定义和使用根本就是两回事儿。
  * C++11新标准规定，允许将变量声明为constexpr类型以便由编译器来验证变量的值是否是一个常量表达式。声明为constexpr的变量一定是一个常量，而且必须用常量表达式初始化
  * 尽管不能使用普通函数作为constexpr变量的初始值，但是新标准允许定义一种特殊的**constexpr函数**。这种**函数应该足够简单以使得编译时就可以计算其结果**，这样就能用constexpr函数去初始化constexpr变量了。

* 字面值类型

  * 常量表达式的值需要在编译时就得到计算，因此对声明constexpr时用到的类型必须有所限制。因为这些类型一般比较简单，值也显而易见、容易得到，就把它们称为**字面值类型**
  * 接触过的数据类型中，算术类型、引用和指针都属于字面值类型。自定义 类Sales_item、IO库、string类型则不属于字面值类型，也就不能被定义成 constexpr。
