1.创建vector
values.reserve(20);
这样就设置了容器的内存分配，至少可以容纳 20 个元素。
如果当前的容量已经大于或等于 20 个元素，那么这条语句什么也不做。
注意，调用 reserve() 并不会生成任何元素。values 容器这时仍然没有任何元素，直到添加了 20 个元素后，才会分配更多的内存。
调用 reserve() 并不会影响现有的元素;
std::array<std :: string, 5> words {"one", "two","three", "four", "five"};
std::vector<std::string> words_copy {std::begin(words) , std::end(words)};

words_copy 被 words 数组容器中的元素初始化; 如果使用移动迭代器指定 words_copy 的初始化范围，
words 中的元素将会从 words 移到 words_copy。这里有一个示例：
std::vector<std::string〉 words_copy {std::make_move_iterator(std::begin(words)),std::make_move_iterator(std:: end(words))};

words_copy 会像前面那样被初始化。但元素是移动过来的而不是复制过来的，所以 words 数组中的字符串对象现在都是空字符串.

resize():

void resize (size_type n);
void resize (size_type n, const value_type& val);

Resizes the container so that it contains n elements.

If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).

If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. 
If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.

If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.

Notice that this function changes the actual content of the container by inserting or erasing elements from it.

2. 访问元素

data():

Return A pointer to the first element in the array used internally by the vector.
// vector::data
#include <iostream>
#include <vector>

int main ()
{
  std::vector<int> myvector (5);

  int* p = myvector.data();

  *p = 10;
  ++p;
  *p = 20;
  p[2] = 100;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}

Output:
myvector contains: 10 20 0 100 0


3.迭代器
    vector<string> words;                     // Stores words to be sorted
    words.reserve(10);                        // Allocate some space for elements
    std::cout << "Enter words separated by spaces. Enter Ctrl+Z on a separate line to end:" << std::endl;

    std::copy(std::istream_iterator <string> {std::cin}, std::istream_iterator <string>{},std::back_inserter(words)); //从输入流读入数据存在vector中
    std::copy(std::begin(words), std::end(words), std::ostream_iterator < string > {std::cout, " "});//vector的数据输出

4.添加元素

emplace_back():

std::string str {"alleged"};
words.emplace_back(str, 2, 3);
// Create string object corresponding to "leg" in place
emplace_back() 函数会调用接收三个参数的 string 构造函数，生成 string 对象，然后把它添加到 words 序列中。
构造函数会生成一个从索引 2 幵始、包含 str 中三个字符的子串。

5.插入元素

	std::vector<std::string> words {"first", "second"};
	// Inserts string(5,'A') as 2nd element
	auto iter = words.emplace(++std::begin(words),5,'A');
	//Inserts string ("$$$$") as 3rd element
	words.emplace(++iter, "$$$$");

	这段代码执行后，vector 中的字符串对象如下:
	"first" "AAAAA" "$$$$" "second"

insert():

vector<std::string> words { "one","three","eight"};


(1) 插入第二个参数指定的单个元素

auto iter = words.insert(++std::begin(words), "two"); //返回的迭代器指向被插入的元素 string(”two”)
在这个示例中，插入点是由 begin() 返回的迭代器递增后得到的。
它对应第二个元素，所以新元素会作为新的第二个元素插入，之前的第二个元素以及后面的元素，
为了给新的第二个元素留出空间，都会向后移动一个位置。

这里有两个 insert 重载版本，它们都可以插入单个对象，其中一个的参数是 constT& 类型，另一个是 T&&类 型——右值引用。
因为上面的第二个参数是一个临时对象，所以会调用第二个函数重载版本，临时对象会被移动插入而不是被复制插入容器。

执行完这条语句后，words vector 容器包含的字符串元素为：
"one" "two" "three" "eight" 
需要注意的是，在使用同样参数的情况下，调用 insert() 没有调用 emplace() 高效。
在 insert() 调用中，构造函数调用 string("two")  生成了一个对象，作为传入的第二个参数。
在 emplace() 调用中，构造函数用第二个参数直接在容器中生成了字符串对象。


(2) 插入一个由第二个和第三个参数指定的元素序列

std:: string more[] {"five", "six", "seven" }; //返回的迭代器指向插入的第一个元素"five"
iter = words.insert(--std::end(words) , std::begin(more), std::end(more));
第二条语句中的插入点是一个迭代器，它是由 end() 返回的迭代器递减后得到的。
对应最后一个元素，因此新元素会被插入到它的前面。执行这条语句后，words 中的字符串对象为：
"one" "two" "three" "five" "six" "seven" "eight"   

(3) 在 vector 的末尾插入一个元素

iter = words.insert(std::end(words), "ten"); //返回的迭代器指向插入的元素"ten"
插入点是最后一个元素之后的位置，因此新元素会被添加到最后一个元素之后。执行完这条语句后，words 中的字符串对象如下：
"one" "two" "three" "five" "six" "seven" "eight" "ten" 

这和上面的情况 (1) 相似；这表明，当第一个参数不指向元素而是指向最后一个元素之后的位置时，它才发挥作用。


(4) 在插入点插入多个单个元素。第二个参数是第三个参数所指定对象的插入次数

iter = words.insert(std::cend(words)-1, 2, "nine"); //返回的迭代器指向插入的第一个元素"nine"
插入点是最后一个元素，因此新元素 string("nine") 的两个副本会被插入到最后一个元素的前面。

执行完这条语句后，words vector 容器中的字符串对象如下：
"one" "two" "three" "five" "six" "seven" "eight" "nine" "nine" "ten" 
注意，示例中的第一个参数是一个 const 迭代器，这也表明可以使用 const 迭代器。

(5) 在插入点，插入初始化列表指定的元素。第二个参数就是被插入元素的初始化列表

iter = words.insert(std::end(words), {std::string {"twelve"},std::string {"thirteen"}}); //返回的迭代器指向插入的第一个元素"twelve"

插入点越过了最后一个元素，因此初始化列表中的元素被添加到容器的尾部。执行完这条语句后，words vector 容器中的字符串对象如下：
"one" "two" "three" "five" "six" "seven" "eight" "nine" "nine" "ten" "twelve" "thirteen" 


初始化列表中的值必须和容器的元素类型相匹配。
T 类型值的初始化列表是std::initializer_list<T>，所以这里的 list 类型为 std::initializer_list<std::string>。
前面的 insert() 调用中以单词作为参数的地方，参数类型是 std::string，所以单词作为字符串对象的初始值被传入到函数中。

记住，所有不在 vector 尾部的插入点都会有开销，需要移动插入点后的所有元素，从而为新元素空出位置。
当然，如果插入点后的元素个数超出了容量，容器会分配更多的内存，这会增加更多额外开销。



6. 删除元素

erase():

iterator erase (const_iterator position);
iterator erase (const_iterator first, const_iterator last);
如果是删除指定位置的元素时：返回值是一个迭代器，指向删除元素下一个元素;如果是删除某范围内的元素时：返回值也表示一个迭代器，指向最后一个删除元素的下一个元素

remove():

remove() 算法由定义在 algorithm 头文件中的模板生成，它可以删除匹配特定值的一段元素。例如：

std::vector<std::string> words { "one", "none","some", "all", "none", "most","many"};
auto iter = std::remove(std::begin(words), std::end(words), "none");
第二条语句在头两个参数指定的元素范围内，移除了所有匹配 remove() 的第三个参数 string("none") 的元素。移除元素这个表述有一点误导，
remove() 是一个全局函数，所以它不能删除容器中的元素。
remove() 移除元素的方式和从字符串中移除空格的方式相似，都是通过用匹配元素右边的元素来覆盖匹配元素的方式移除元素

如果在 remove() 操作后输出 words 中的元素，只会输出前 5 个元素。尽管 size() 返回的值仍然是 7，而且最后两个元素仍然存在，
但是它们被替换成了空字符串对象。为了摆脱这些多余的元素，可以使用成员函数 erase()。

remove() 返回的迭代器可以这样使用：
words.erase(iter, std::end(words));//Remove surplus elements

这被叫作 erase-remove，执行删除操作后，iter 指向最后一个元素之后的位置，所以它标识了被删除序列的第一个元素，
被删除序列的结束位置由 std::end(words) 指定。当然，在一条语句中，也能先移除元素，然后再删除末尾不想要的元素：

words.erase(std::remove(std::begin(words), std::end(words),"none"), std::end(words));
remove() 算法返回的迭代器作为 erase() 的第一个参数，erase() 的第二个参数是所指向容器中最后一个元素后一个位置的迭代器。








