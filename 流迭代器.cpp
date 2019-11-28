1.STL输入流迭代器

输入流迭代器是一个可以在文本模式下从流中提取数据的输入迭代器，这意味着不能用它处理二进制流。

一般用两个流迭代器来从流中读取全部的值：指向要读入的第一个值的开始迭代器，指向流的末尾的结束迭代器。在输入流的文件结束状态(End-Of-File，EOF)被识别时，就可以确定结束迭代器。

定义在 iterator 头文件中的 istream_iterator 模板会用提取运算符 >> 从流中读入 T 类型的值。
对于这些工作，必须有一个从 istream 对象读取 T 类型值的 operator>>() 函数的重载版本。
因为 istream_iterator 是一个输入迭代器，所以它的实例是一个单向迭代器；它只能被使用一次。默认情况下，我们认为这种流包含的是 char 类型的字符。

	std::cout << "Enter one or more words. Enter ! to end:";
	std::istream_iterator<string> in {std::cin}; // Reads strings from cin
	std::vector<string> words;
	while(true){
    	string word = *in;
    	if(word == "!") break;
    	words.push_back(word);
    	++in;
	}
	std::cout << "You entered " << words.size() << "words." << std::endl;


2.STL输出流迭代器

// Using output stream iterator function members
#include <iostream>                                      // For standard streams
#include <iterator>                                      // For iterators and begin() and end()
#include <vector>                                        // For vector container
#include <algorithm>                                     // For copy() algorithm
#include <string>
using std::string;

int main()
{
    std::vector<string> words {"The", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dog"};

    // Write the words container using conventional iterator notation
    std::ostream_iterator<string> out_iter1 {std::cout};   // Iterator with no delimiter output
    for(const auto& word : words)
    {
        *out_iter1++ = word;                                 // Write a word
        *out_iter1++ = " ";                                  // Write a delimiter
    }
    *out_iter1++ = "\n";                                   // Write newline

    // Write the words container again using the iterator
    for(const auto& word : words)
    {
        (out_iter1 = word) = " ";                            // Write the word and delimiter
    }
    out_iter1 = "\n";                                      // Write newline

    // Write the words container using copy()
    std::ostream_iterator<string> out_iter2 {std::cout, " "};
    std::copy(std::begin(words), std::end(words), out_iter2);
    out_iter2 = "\n";
}

三种方式输出words中的元素



3.文件流
这里有 3 个表示文件流的类模板：
ifstream：表示文件的输出流；
ofstream：是为输出定义的文件流；
fstream：定义了可以读和写的文件流；

#include <fstream>
#include <iostream>
using namespace std;
 
int main ()
{
    
   char data[100];
 
   // 以写模式打开文件
   ofstream outfile;
   outfile.open("afile.dat");
 
   cout << "Writing to the file" << endl;
   cout << "Enter your name: "; 
   cin.getline(data, 100);
 
   // 向文件写入用户输入的数据
   outfile << data << endl;
 
   cout << "Enter your age: "; 
   cin >> data;
   cin.ignore();
   
   // 再次向文件写入用户输入的数据
   outfile << data << endl;
 
   // 关闭打开的文件
   outfile.close();
 
   // 以读模式打开文件
   ifstream infile; 
   infile.open("afile.dat"); 
 
   cout << "Reading from the file" << endl; 
   infile >> data; 
 
   // 在屏幕上写入数据
   cout << data << endl;
   
   // 再次从文件读取数据，并显示它
   infile >> data; 
   cout << data << endl; 
 
   // 关闭打开的文件
   infile.close();
 
   return 0;
}


文件位置指针
istream 和 ostream 都提供了用于重新定位文件位置指针的成员函数。
这些成员函数包括关于 istream 的 seekg（"seek get"）和关于 ostream 的 seekp（"seek put"）。

seekg 和 seekp 的参数通常是一个长整型。第二个参数可以用于指定查找方向。查找方向可以是 ios::beg（默认的，从流的开头开始定位），
也可以是 ios::cur（从流的当前位置开始定位），也可以是 ios::end（从流的末尾开始定位）。

文件位置指针是一个整数值，指定了从文件的起始位置到指针所在位置的字节数。
下面是关于定位 "get" 文件位置指针的实例：

	// 定位到 fileObject 的第 n 个字节（假设是 ios::beg）
	fileObject.seekg( n );
 
	// 把文件的读指针从 fileObject 当前位置向后移 n 个字节
	fileObject.seekg( n, ios::cur );
 
	// 把文件的读指针从 fileObject 末尾往回移 n 个字节
	fileObject.seekg( n, ios::end );
 
	// 定位到 fileObject 的末尾
	fileObject.seekg( 0, ios::end );


4.流缓冲区迭代器
流缓冲区迭代器不同于流迭代器，流迭代器只会传送字符到流缓冲区或从流缓冲区读出字符。它们可以直接访问流的缓冲区，因此不包含插入和提取运算符。
也没有数据的转换，数据之间也不需要分隔符，即使有分隔符，也可以自己处理它们。
因为它们读写数据时没有数据转换，流缓冲区迭代器适用于二进制文件。流缓冲区迭代器读写字符的速度比流迭代器快。

输入流缓冲区迭代器：
为了生成可以从流中读取任意给定类型的字符输入流迭代器，需要将一个流对象传给构造函数：
	std::istreambuf_iterator<char> in {std::cin};
这个对象是一个可以从标准输入流读取任意char类型字符的输入流缓冲区迭代器。默认构造函数生成的对象表示的是流结束迭代器：
	std::istreambuf_iterator<char> end_in;
可以用这两个迭代器从 cin 中读取字符序列到字符串中，直到在单行中输入的 Ctrl+Z 被作为流结束的信号。例如：

	std::cout << "Enter something: ";
	string rubbish {in, end_in};
	std::cout << rubbish << std::endl; // Whatever you enter will be output

我们不得不依靠流的结束来终止输入。可以用递增和解引用运算符来从流中读取字符，直到找到特定的字符。
	std::istreambuf_iterator<char> in {std::cin};
	std::istreambuf_iterator<char> end_in;
	char end_ch { '*' };
	string rubbish;
	while(in != end_in && *in != end_ch) 
		rubbish += *in++;
	std::cout << rubbish << std::endl; // Whatever you entered up to ' * ' or EOF

输出流缓冲区迭代器
通过传给构造函数一个流对象，可以生成一个 ostreambuf_iterator 对象来将给定类型的字符写到流中：

	string file_name {"G:/Beginning_STL/junk.txt"};
	std::ofstream junk_out {file_name};
	std::ostreambuf_iterator<char> out {junk_out};


5.string流
（1）istringstream 从string中读取数据
（2）ostringstream 向string中写入数据
（3）stringstream 即可以读又可以写

stringstream特有操作	
sstream ss;	ss是一个未被绑定的stringstream对象。sstream是sstream中定义的一个类型。
sstream ss(s);	ss保存string s的一个拷贝，构造函数是explicit的
ss.str()	返回strm所保存的string的拷贝
ss.str(s)	将s拷贝到ss当中，返回void


int main() {
   stringstream ss;
    string s;
    getline(cin,s); // 输入 1 2 3 abc
    int a=0,b=0,c=0;
    string str;
    ss<<s;//把字符串塞进ss当中
    ss>>a>>b>>c>>str;//读出来
    cout<<a<<" "<<b<<" "<<c<<" "<<a+b+c<<" "<<str<<endl; // 1 2 3 6 abc
    str="123";
    ss.clear();
    ss<<str;
    ss>>a;
    cout<<a<<endl; //123
    return 0;

}
