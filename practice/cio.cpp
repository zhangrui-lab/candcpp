// c io
/*
 * 文件操作函数
 *  1。 文件访问： 读，写，缓冲...
 *  2。 有格式输入/输出
 *  3。 文件位置
 *  4。 错误处理
 *  5。 文件操作
 */

// <stdio.h> 头文件提供通用文件操作支持并提供有窄字符输入/输出能力的函数。
// <wchar.h> 头文件提供有宽字符输入/输出能力的函数。
// I/O 流为 FILE 对象所代表，只能通过 FILE* 类型指针访问及操作。每个流与外部物理设备（文件、标准输入流、打印机、序列端口等）关联。
/*
    stdio.h synopsis
Macros:

    BUFSIZ
    EOF
    FILENAME_MAX
    FOPEN_MAX
    L_tmpnam
    NULL
    SEEK_CUR
    SEEK_END
    SEEK_SET
    TMP_MAX
    _IOFBF
    _IOLBF
    _IONBF
    stderr
    stdin
    stdout

Types:

FILE
fpos_t
size_t

int remove(const char* filename);
int rename(const char* old, const char* new);
FILE* tmpfile(void);
char* tmpnam(char* s);
int fclose(FILE* stream); // 关闭给定的文件流。冲入任何未写入的缓冲数据到 OS 。舍弃任何未读取的缓冲数据。无论操作是否成功，流都不再关联到文件，且由 setbuf 或 setvbuf 分配的缓冲区若存在，则亦被解除关联，并且若使用自动分配则被解分配。若在 fclose 返回后使用指针 stream 的值则行为未定义。
int fflush(FILE* stream);
FILE* fopen(const char* restrict filename, const char* restrict mode);
FILE* freopen(const char* restrict filename, const char * restrict mode,
              FILE * restrict stream);
//首先，试图关闭与 stream 关联的文件，忽略任何错误。然后，若 filename 非空，则试图用 mode 打开 filename 所指定的文件，如同用 fopen ，然后将该文件与 stream 所指向的文件流关联。若 filename 为空指针，则函数试图重打开已与 stream 关联的文件（此情况下是否允许模式改变是实现定义的）。
void setbuf(FILE* restrict stream, char* restrict buf);
int setvbuf(FILE* restrict stream, char* restrict buf, int mode, size_t size);
int fprintf(FILE* restrict stream, const char* restrict format, ...);
int fscanf(FILE* restrict stream, const char * restrict format, ...);
int printf(const char* restrict format, ...);
int scanf(const char* restrict format, ...);
int snprintf(char* restrict s, size_t n, const char* restrict format, ...);    // C99
int sprintf(char* restrict s, const char* restrict format, ...);
int sscanf(const char* restrict s, const char* restrict format, ...);
int vfprintf(FILE* restrict stream, const char* restrict format, va_list arg);
int vfscanf(FILE* restrict stream, const char* restrict format, va_list arg);  // C99
int vprintf(const char* restrict format, va_list arg);
int vscanf(const char* restrict format, va_list arg);                          // C99
int vsnprintf(char* restrict s, size_t n, const char* restrict format,         // C99
              va_list arg);
int vsprintf(char* restrict s, const char* restrict format, va_list arg);
int vsscanf(const char* restrict s, const char* restrict format, va_list arg); // C99
int fgetc(FILE* stream);    // 从给定的输入流读取下一个字符。 getc() 可以实现为宏。 成功时为获得的字符，失败时为 EOF 。若文件尾条件导致失败，则另外设置 stream 上的文件尾指示器（见 feof() ）。若某些其他错误导致失败，则设置 stream 上的错误指示器（见 ferror() ）。
char* fgets(char* restrict s, int n, FILE* restrict stream);
int fputc(int c, FILE* stream);
int fputs(const char* restrict s, FILE* restrict stream);
int getc(FILE* stream);
int getchar(void);
char* gets(char* s);  // removed in C++14
int putc(int c, FILE* stream);
int putchar(int c);   // 写字符 ch 到 stdout 。在内部，字符于写入前被转换到 unsigned char 。 等价于 putc(ch, stdout) 。 成功时返回写入的字符。失败时返回 EOF 并设置 stdout 上的错误指示器（见 ferror() ）。
int puts(const char* s);    //写入每个来自空终止字符串 str 的字符及附加换行符 '\n' 到输出流 stdout ，如同以重复执行 putc 写入。成功时返回非负值失败时，返回 EOF 并设置 stdout 的错误指示器（见 ferror() ）。
// puts 函数后附一个换行字符到输出，而 fputs 不这么做。不同的实现返回不同的非负数：一些返回最后写入的字符，一些返回写入的字符数（或若字符串长于 INT_MAX 则返回它），一些简单地返回非负常量。在重定向 stdout 到文件时，导致 puts 失败的典型原因是用尽了文件系统的空间。

int ungetc(int c, FILE* stream);
size_t fread(void* restrict ptr, size_t size, size_t nmemb,
             FILE* restrict stream);
size_t fwrite(const void* restrict ptr, size_t size, size_t nmemb,
              FILE* restrict stream);
int fgetpos(FILE* restrict stream, fpos_t* restrict pos);
int fseek(FILE* stream, long offset, int whence);
int fsetpos(FILE*stream, const fpos_t* pos);
long ftell(FILE* stream);
void rewind(FILE* stream);
void clearerr(FILE* stream);
int feof(FILE* stream);
int ferror(FILE* stream);
void perror(const char* s);
*/

/*
每个 FILE 对象指代一个 C 流。
C 标准不指定 FILE 是否为完整对象类型。当可能复制合法的 FILE 时，以指向这种副本的指针为 I/O 函数的参数导致未指定行为。换言之 FILE 可能在语义上不可复制。
I/O 流能用于无格式和有格式的输入及输出。另外，处理输入输出的函数亦能为本地环境敏感，以按需进行宽/多字节转换。

流状态. 在系统指定的需要访问设备的信息（例如 POSIX 文件描述符）外，每个 FILE 对象直接或间接保有下列信息：
    (C95)字符宽度：未设置、窄或宽。
    (C95)多字节与宽字符间转换的分析状态（ mbstate_t 类型对象）
    缓冲状态：无缓冲、行缓冲、全缓冲。
    缓冲区，可为外部的用户提供缓冲区所替换。
    I/O 模式：输入、输出或更新（兼具输入与输出）。
    二进制/文本模式指示器。
    文件尾指示器。
    错误状态指示器。
    文件位置指示器，可作为 fpos_t 类型对象访问，对于宽流包含剖析状态。
    (C11)在多个线程读、写、寻位或查询流时避免数据竞争的再入锁。

fpos_t 是非数组完整对象类型，能用于存储（由 fgetpos ）及恢复（由 fsetpos ） C 流的位置与多字节分析状态（若存在）。

stdin, stdout, stderr
预定义三个文本流。这些流在程序启动时隐式打开，且为无面向。
1) 与标准输入流关联，用于读取约定的输入。程序启动时，该流为完全缓冲当且仅当能确定流不引用交互式设备。
2) 与标准输出流关联，用于写入约定的输出。程序启动时，该流为完全缓冲当且仅当能确定流不引用交互式设备。
3) 与标准错误流关联，用于写入诊断输出。程序启动时，该流不为完全缓冲。



文件访问
模式字符串	含义	解释	若文件已存在的动作	若文件不存在的动作
"r"	读	打开文件以读取	从头读	打开失败
"w"	写	创建文件以写入	销毁内容	创建新文件
"a"	后附	后附到文件	写到结尾	创建新文件
"r+"	读扩展	打开文件以读/写	从头读	错误
"w+"	写扩展	创建文件以读/写	销毁内容	创建新文件
"a+"	后附扩展	打开文件以读/写	写到结尾	创建新文件
文件访问模式标签 "b" 可以可选地指定以二进制模式打开文件。此标签仅在 Windows 系统上生效。
在附加文件访问模式下，数据被写入到文件尾，而不考虑文件位置指示器的当前位置。
当文件以更新模式打开时（ '+' 作为上述模式参数值列表的第二或第三个字符），访问流可以进行输入和输出。然而输出不应直接紧随输入，而中间无对 fflush 函数或对文件定位函数（ fseek 、 fsetpos 或 rewind ）的调用，且输入不应直接紧随输出，而中间无对文件定位函数的调用，除非输入操作遇到文件尾。在一些实现中，以更新模式打开（或创建）文本文件可能取代打开（或创建）二进制流。
文件访问模式标签 "x" 可以可选地后附于 "w" 或 "w+" 指定符。若文件存在，则此标签强制函数失败，而不重写它。(C11)
使用 fopen_s 或 freopen_s 时，任何以 "w" 或 "a" 创建的文件的文件访问许可禁止其他用户访问它。文件访问模式标签 "u" 可以可选地前附于任何以为 "w" 或 "a" 始的指定符，以启用默认的 fopen 许可。(C11)

 */

#include "stdio.h"
#include "stdlib.h"

void tfopen() {
    FILE *fp = fopen("1.txt", "r");
    if(!fp) {
        perror("open file failed");
        exit(EXIT_FAILURE);
    }

    char c;
    while ( (c = fgetc(fp)) != EOF ) {
        putchar(c);
    }

    if (ferror(fp)) {
        puts("I/O error when reading");
    } else if (feof(fp)) {
        puts("End of file reached successfully");
    }
    fclose(fp);
}

void tfreopen1(const char * filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("file %s not exists\n", filename);
        exit(EXIT_FAILURE);
    }
    fputs("a error string write", fp);
    if (ferror(fp)) {
        puts("r model can not wrirte !");
        clearerr(fp);
        fp = freopen(filename, "a+", fp);
    }
    fputs("a success string write", fp);
    if (ferror(fp)) {
        puts("a+ model can not wrirte !");
    }
    fclose(fp);
}

void tfreopen2() {
    puts("stdout is printed to console");
    if (freopen("redir.txt", "w", stdout) == NULL)
    {
        perror("freopen() failed");
        exit(EXIT_FAILURE);
    }
    puts("stdout is redirected to a file"); // 写入 redir.txt
    fclose(stdout);
}

int tremove() {
    FILE* fp = fopen("file1.txt", "w"); // 创建文件
    if(!fp) { perror("file1.txt"); return 1; }
    puts("Created file1.txt");
    fclose(fp);

    int rc = remove("file1.txt");
    if(rc) { perror("remove"); return 1; }
    puts("Removed file1.txt");

    fp = fopen("file1.txt", "r"); // 错误：文件不存在
    if(!fp) perror("Opening removed file failed");

    rc = remove("file1.txt"); // 错误：文件不存在
    if(rc) perror("Double-remove failed");
}


int trename(void)
{
    FILE* fp = fopen("from.txt", "w"); // 创建文件 "from.txt"
    if(!fp) { perror("from.txt"); return 1; }
    fputc('a', fp); // 写入到 "from.txt"
    fclose(fp);

    int rc = rename("from.txt", "to.txt");
    if(rc) { perror("rename"); return 1; }

    fp = fopen("to.txt", "r");
    if(!fp) { perror("to.txt"); return 1; }
    printf("%c\n", fgetc(fp)); // 从 "to.txt" 读取
    fclose(fp);

    remove("to.txt");
}

#include <unistd.h>
int ttmpfile(void)
{
    // 创建并打开一个临时文件。该文件作为二进制文件、更新模式（如同为 fopen 以 "wb+" 模式）打开。该文件的文件名保证在文件系统中唯一。至少可以在程序的生存期内能打开 TMP_MAX 个文件（此极限可能与 tmpnam 共享，并可能为 FOPEN_MAX 所进一步限制）。
    // 返回值 指向与文件关联的文件流的指针，或若出现错误则为空指针。
    FILE* tmpf = tmpfile();
    fputs("Hello, world", tmpf);
    rewind(tmpf);
    char buf[6];
    fgets(buf, sizeof buf, tmpf);
    printf("got back from the file: '%s'\n", buf);

    // 展示临时文件名的 Linux 特定方法
    char fname[FILENAME_MAX], link[FILENAME_MAX] = {0};
    sprintf(fname, "/proc/self/fd/%d", fileno(tmpf));
    if(readlink(fname, link, sizeof link - 1) > 0)
        printf("File name: %s\n", link);
}

void ttmpname() {
    char *name1 = tmpnam(nullptr);
    printf("temporary file name: %s\n", name1);

    char name2[L_tmpnam];
    if (tmpnam(name2))
        printf("temporary file name: %s\n", name2);
}

#include <assert.h>
void tclearerr() {
    FILE *tmp = tmpfile();
    fputs("abcdef\n", tmp);
    rewind(tmp);
    int ch;
    while ( (ch = fgetc(tmp)) != EOF )
        putc(ch, stdout);
    assert(feof(tmp));
    clearerr(tmp);

    if (feof(tmp))
        fputs("EOF indicator set", stdout);
    else
        fputs("EOF indicator cleared", stdout);
    fclose(tmp);
}

void tperror() {
    FILE *f = fopen("non_existent", "r");
    if (f == NULL) {
        perror("fopen() failed");
    } else {
        fclose(f);
    }
}


// ftell 返回流 stream 的文件位置指示器。若流以二进制模式打开，则由此函数获得的值是从文件开始的字节数。若流以文本模式打开，则由此函数返回的值未指定，且仅若作为 fseek() 的输入才有意义。
int tftell(void) {
    /* 准备浮点值的数组。 */
    const int SIZE = 5;
    double A[SIZE] = {1.,2.,3.,4.,5.};
    /* 写数组到文件。 */
    FILE * fp = fopen("test.bin", "wb");
    fwrite(A,sizeof(double),SIZE,fp);
    fclose (fp);

    /* 读取浮点值到数组 B。 */
    double B[SIZE];
    fp = fopen("test.bin","rb");
    long int pos = ftell(fp);   /* 位置指示器在文件起始 */
    if (pos == -1L) {
        perror("ftell()");
        fprintf(stderr,"ftell() failed in file %s at line # %d\n", __FILE__,__LINE__-4);
        exit(EXIT_FAILURE);
    }
    printf("%ld\n", pos);

    int ret_code = fread(B,sizeof(double),1,fp);   /* 读取一个浮点值 */
    pos = ftell(fp);   /* 读取一个浮点值后的位置指示器 */
    if (pos == -1L){
        perror("ftell()");
        fprintf(stderr,"ftell() failed in file %s at line # %d\n", __FILE__,__LINE__-4);
        exit(EXIT_FAILURE);
    }
    printf("%ld\n", pos);
    printf("%.1f\n", B[0]);   /* 打印浮点值 */

    int rc = remove("test.bin");
    if (rc) perror("test.bin remove failed");
    return EXIT_SUCCESS;
}

// fgetpos 获得文件流 stream 的文件位置指示器和当前分析状态（若存在），并将它们存储于 pos 所指向的对象。存储的值仅在作为 fsetpos 的输入的情况有意
int tfgetpos(void)
{
    // 准备保有 4 个 double 类型值的文件
    enum {SIZE = 4};
    FILE* fp = fopen("test.bin", "wb");
    assert(fp);
    int rc = fwrite((double[SIZE]){1.1, 2.2, 3.3, 4.4}, sizeof(double), SIZE, fp);      // 成功写入的对象数，若错误发生则可能小于 count 。若 size 或 count 为零，则 fwrite 返回零并不进行其他行动。
    assert(rc == SIZE);
    fclose(fp);

    // 演示使用 fsetpos 返回到文件起始
    fp = fopen("test.bin", "rb");
    fpos_t pos;
    fgetpos(fp, &pos);               // 存储文件起始于 pos
    double d;

    // 从给定输入流 stream 读取至多 count 个对象到数组 buffer 中，如同以对每个对象调用 size 次 fgetc ，并按顺序存储结果到转译为 unsigned char 数组的 buffer 中的相继位置。流的文件位置指示器前进读取的字符数。
    //若出现错误，则流的文件位置指示器的结果值不确定。若读入部分的元素，则元素值不确定。
    // 成功读取的对象数，若出现错误或文件尾条件，则可能小于 count 。
    rc = fread(&d, sizeof d, 1, fp); // 读取首个 double


    assert(rc == 1);
    printf("First value in the file: %.1f\n", d);
    fsetpos(fp,&pos);                 // 移动文件位置回文件起始
    rc = fread(&d, sizeof d, 1, fp);  // 再次读取首个 double
    assert(rc == 1);
    printf("First value in the file again: %.1f\n", d);
    fclose(fp);

    // 演示错误处理
    rc = fsetpos(stdin, &pos);
    if(rc) perror("could not fsetpos stdin");
    remove("test.bin");
}


// fseek
//int fseek( FILE *stream, long offset, int origin ); 设置文件流 stream 的文件位置指示器为 offset 所指向的值。
//若 stream 以二进制模式打开，则新位置准确地是文件起始后（若 origin 为 SEEK_SET ）或当前文件位置后（若 origin 为 SEEK_CUR ），或文件结尾后（若 origin 为 SEEK_END ）的 offset 字节。不要求二进制流支持 SEEK_END ，尤其是是否输出附加的空字节。
//若 stream 以文本模式打开，则仅有的受支持 offset 值为零（可用于任何 origin ）和先前在关联到同一个文件的流上对 ftell 的调用的返回值（仅可用于 SEEK_SET 的 origin ）。
//若 stream 为宽面向，则一同应用对文本和二进制流的限制（允许 ftell 的结果与 SEEK_SET 一同使用，并允许零 offset 以 SEEK_SET 和 SEEK_CUR 但非 SEEK_END 为基准）。
//除了更改文件位置指示器， fseek 还撤销 ungetc 的效果并清除文件尾状态，若可应用。
//若发生读或写错误，则设置流的错误指示器（ ferror ）而不影响文件位置。
//成功时为 ​0​ ，否则为非零。
int tfseek(void)
{
    // 准备浮点值的数组。
    const int SIZE = 5;
    double A[SIZE] = {1.,2.,3.,4.,5.};
    // 写入数组到文件。
    FILE * fp = fopen("test.bin", "wb");
    fwrite(A,sizeof(double),SIZE,fp);
    fclose (fp);

    // 读浮点值入数组 B。
    double B[SIZE];
    fp = fopen("test.bin","rb");

    // 设置文件位置指示器到第三个浮点值之前。
    if (fseek(fp,sizeof(double)*2L,SEEK_SET) != 0)
    {
        perror("fseek()");
        fprintf(stderr,"fseek() failed in file %s at line # %d\n", __FILE__,__LINE__-5);
        exit(EXIT_FAILURE);
    }

    int ret_code = fread(B,sizeof(double),1,fp);   // 读取一个浮点值
    printf("%.1f\n", B[0]);                        // 打印一个浮点值

    fclose(fp);
    return EXIT_SUCCESS;
}

// rewind
//void rewind( FILE *stream );
//移动文件位置指示器到给定文件流的起始。函数等价于 fseek(stream, 0, SEEK_SET); ，除了它清除文件尾和错误指示器。此函数丢弃任何来自先前对 ungetc 调用的效果。 无返回值

int trewind(void)
{
    char str[20];
    FILE *f;
    char ch;

    f = fopen("file.txt", "w");
    for (ch = '0'; ch <= '9'; ch++) {
        fputc(ch, f);
    }
    fclose(f);

    f = fopen("file.txt", "r");
    fread(str, 1, 10, f);
    puts(str);
    printf("%ld\n", ftell(f));

    rewind(f);
    printf("%ld\n", ftell(f));
    fread(str, 1, 10, f);
    puts(str);
    fclose(f);

    remove("file.txt");
}

// fflush
//int fflush( FILE *stream );
//对于输出流（及最后操作为输出的更新流），从 stream 的缓冲区写入未写的数据到关联的输出设备。对于输入流（及最后操作为输入的更新流），行为未定义。若 stream 是空指针，则冲入所有输出流，包括操作于库包内者，或在其他情况下程序无法直接访问者。

// setbuf
//void setbuf( FILE          *stream, char          *buffer );
//void setbuf( FILE *restrict stream, char *restrict buffer );
//设置用于流操作的内部缓冲区。其长度至少应该为 BUFSIZ 个字符。若 buffer 非空，则等价于 setvbuf(stream, buffer, _IOFBF, BUFSIZ) 。若 buffer 为空，则等价于 setvbuf(stream, NULL, _IONBF, 0) ，这会关闭缓冲。
int tsetbuf(void)
{
    setbuf(stdout, NULL); // 无缓冲的 stdout
    putchar('a'); // 若 stdout 无缓冲，则 'a' 立即出现
    putchar('b');
}


// fgetc, getc
//int fgetc( FILE *stream );
//int getc( FILE *stream );
//从给定的输入流读取下一个字符。返回值成功时为获得的字符，失败时为 EOF 。若文件尾条件导致失败，则另外设置 stream 上的文件尾指示器（见 feof() ）。若某些其他错误导致失败，则设置 stream 上的错误指示器（见 ferror() ）。
int tgetc(void)
{
    FILE* fp = fopen("test.txt", "r");
    if(!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    int c; // 注意：int，非char，要求处理EOF
    while ((c = fgetc(fp)) != EOF) { // 标准C I/O读取文件循环
        putchar(c);
    }

    if (ferror(fp))
        puts("I/O error when reading");
    else if (feof(fp))
        puts("End of file reached successfully");

    fclose(fp);
}


// fgets 从给定文件流读取最多 count - 1 个字符并将它们存储于 str 所指向的字符数组。若文件尾出现或发现换行符则终止分析.  成功时为 str ，失败时为空指针。
int tputs(void)
{
    FILE* tmpf = tmpfile();
    fputs("Alan Turing\n", tmpf);
    fputs("John von Neumann\n", tmpf);
    fputs("Alonzo Church\n", tmpf);

    rewind(tmpf);

    char buf[8];
    while (fgets(buf, sizeof buf, tmpf) != NULL)
        printf("%s\n", buf);

    if (feof(tmpf))
        puts("End of file reached");
}

