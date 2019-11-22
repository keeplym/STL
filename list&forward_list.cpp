1.
list 容器有一个拷贝构造函数，因此可以生成一个现有 list 容器的副本：
list<double> save_values {values}; //初始化列表中的迭代器可以代表任意容器的一段元素，而不仅仅只是 list 容器。

2.
auto iter = begin(data);
advance(iter, 9); // Increase iter by 9, 定义在 iterator 头文件中的全局函数
data.insert(iter, 3, 88);// Insert 3 copies of 88 starting at the 10th

3.
vector<int> numbers(10, 5)/ // Vector of 10 elements with value 5
data.insert(--(--end(data)), cbegin(numbers), cend(numbers));
insert() 的第一个参数是一个迭代器，它指向 data 的倒数第二个元素。
第二和第三个参数指定了 number 中被插入元素的范围，因此从 data 中倒数第二个元素开始，依次插入 vector 的全部元素。

4.
有三个函数可以在 list 容器中直接构造元素：emplace() 在迭代器指定的位置构造一个元素；
emplace_front() 在 list 的第一个元素之前构造元素；emplace_back() 在 list 的尾部元素之后构造元素。

    list<std:: string> names {"Jane", "Jim", "Jules", "Janet"};
    names.emplace_back("Ann");
    string name  = "Alan" ;
    names.emplace_back(move(name)); //move() 函数将 name 的右值引用传入 emplace_back() 函数。这个操作执行后，names 变为空，因为它的内容已经被移到 list 中
    names.emplace_front("Hugo");
    names.emplace(++begin(names), "Hannah");


5.删除元素

remove():
list<int> numbers { 2, 5, 2, 3, 6, 7, 8, 2, 9};
numbers.remove(2); // List is now 5 3 6 7 8 9, 移除了 numbers 中出现的所有值等于 2 的元素。

remove_if():
成员函数 remove_if() 期望传入一个一元断言作为参数。
一元断言接受一个和元素同类型的参数或引用，返回一个布尔值。断言返回 true 的所有元素都会被移除。
numbers.remove_if([](int n){return n%2 == 0;});// Remove even numbers. 

unique():
成员函数 unique() 非常有意思，它可以移除连续的重复元素，只留下其中的第一个。返回迭代器，迭代器指向的是重复元素的首地址

list<string> words { "one", "two", "two", "two","three", "four", "four"};
words.unique () ; // Now contains "one" "two" "three" "four"
可以在对元素进行排序后，再使用 unique()，这样可以保证移除序列中全部的重复元素。

在STL中unique函数是一个去重函数, 其实它并不真正把重复的元素删除，
是把重复的元素移到后面去了，然后依然保存到了原数组中，然后 返回去重后最后一个元素的地址
    int array1[11]={1,2,0,3,3,0,7,7,7,0,8};
    vector<int> vector1;
    for (int i = 0;i < 11;++i)
        vector1.push_back(array1[i]);
    vector<int>::iterator new_end;
    new_end=unique(vector1.begin(),vector1.end());    //"删除"相邻的重复元素     
    vector1.erase(new_end,vector1.end());  //删除（真正的删除）重复的元素
    copy(vector1.begin(),vector1.end(),ostream_iterator<int>(cout," "));
    cout<<endl;


6.排序

(1) sort():
sort() 函数模板定义在头文件 algorithm 中，要求使用随机访问迭代器。
但 list 容器并不提供随机访问迭代器，只提供双向迭代器，因此不能对 list 中的元素使用 sort() 算法。
但是，还是可以进行元素排序，因为 list 模板定义了自己的 sort() 函数。
sort() 有两个版本：无参 sort() 函数将所有元素升序排列。第二个版本的 sort() 接受一个函数对象或 lambda 表达式作为参数，
这两种参数都定义一个断言用来比较两个元素。


names.sort(std::greater<std::string>()); // Names in descending sequence
这里使用了定义在头文件 functional 中的模板 greater<T>。
这个模板定义了一个用来比较 T 类型对象的函数对象。
如果第一个参数大于第二个参数，那么成员函数 operator()() 返回 true。
头文件 functional 中定义了一些定义了断言的模板。

有一个简洁版的 greater<T> 断言，可以如下所示使用：
names.sort(std::greater<>()); // Function object uses perfect forwarding
简洁版的函数对象可以接受任何类型的参数，使用完美转发 (perfect forwarding) 可以避免不必要的参数拷贝。
因此，完美转发总是会快很多，因为被比较的参数会被移动而不是复制到函数中。

假设我们想对 names 中的元素进行排序，但是不想使用字符串对象标准的 std::greater<> 来比较，而是想将相同初始字符的字符串按长度排序。可以如下所示定义一个类：
// Order strings by length when the initial letters are the same
class my_greater
{
    public:
    bool operator () (const std::strings s1, const std::strings s2)
    {
        if (s1[0] == s2 [0])
            return si.length() > s2.length();
        else
            return s1 > s2;
    }
};
可以用这个来对 names 中的元素排序：
names.sort(my_greater()); // Sort using my_greater

//lambda表达式
names.sort([](const std::strings s1, const std::strings s2)
{
    if (s1[0] == s2[0])
        return s1.length() > s2.length();
    else
        return s1 > s2;
});



(2) merge():

以另一个具有相同类型元素的 list 容器作为参数。两个容器中的元素都必须是升序。
参数 list 容器中的元素会被合并到当前的 list 容器中。例如：
	list<int> my_values {2, 4, 6, 14};
	list<int> your_values{ -2, 1, 7, 10};
	my_values.merge (your_values);//my_values contains: -2 1 2 4 6 7 10 14
	your_values.empty(); // Returns true
元素从 your_values 转移到 my_values，因此，在执行完这个操作后，your_values 中就没有元素了。
改变每个 list 节点的指针，在适当的位置将它们和当前容器的元素链接起来，这样就实现了元素的转移。list 节点在内存中的位置不会改变；
只有链接它们的指针变了。在合并的过程中，两个容器中的元素使用 operator()() 进行比较。

在另一个版本的 merge() 函数中，可以提供一个比较函数作为该函数的第二个参数，用来在合并过程中比较元素。例如：
list<string> my_words { "three","six", "eight"};
list<string> your_words { "seven", "four", "nine"};
auto comp_str = [](const strings s1, const strings s2){ return s1[0]<s2[0];};
my_words.sort (comp_str); //"eight" "six" "three"
your_words.sort (comp_str) ;  //"four" "nine" "seven"
my_words.merge (your_words, comp_str) ; // "eight" "four" "nine" "six" "seven" "three"
这里的字符串对象比较函数是由 lambda 表达式定义的，这个表达式只比较第一个字符。比较的效果是，在合并的 list 容器中，"six”在”seven"之前。
在上面的代码中，也可以无参调用 merge()，这样"seven"会在"six"之前，这是一般的排序。


(3) splice():
这个函数将参数 list 容器中的元素移动到当前容器中指定位置的前面。
可以移动单个元素、一段元素或源容器的全部元素。下面是一个剪切单个元素的示例：
	list<string> my_words {"three", "six", "eight"};
	list<string> your_words {"seven", "four", "nine"};
	my_words.splice(++begin(my_words), your_words, ++begin(your_words));
splice() 的第一个参数是指向目的容器的迭代器。第二个参数是元素的来源。第三个参数是一个指向源list容器中被粘接元素的迭代器，它会被插入到第一个参数所指向位置之前。
代码执行完中后，容器中的内容如下：
	your_words: "seven", "nine"
	my_words : "three", "four", "six", "eight"
当要粘接源 list 容器中的一段元素时，第 3 和第 4 个参数可以定义这段元素的范围
	your_words.splice(++begin(your_words),my_words,++sbegin(my_words), end(my_words));
上面的代码会将 my_words 从第二个元素直到末尾的元素，粘接到 your_words 的第二个元素之前。
上面两个 list 容器的内容如下：
	your_words:"seven", "four", "six", "eight","nine" 
	my_words: "three"
下面的语句可以将 your_words 的全部元素粘接到 my_words 中：
	my_words.splice(begin(my_words), your_words);
	your_words 的所有元素被移到了 my_words 的第一个元素"three"之前。
然后，your_words 会变为空。即使 your_words 为空，也仍然可以向它粘接元素：
	your_words.splice(end(your_words), my_words);
现在，my_words 变为空，your_words 拥有全部元素。第一个参数也可以是 begin (your_words)，因为当容器为空时，它也会返回一个结束迭代器。

/*****************************************************************************************************************************************/
forward_list类

forward_list 容器以单链表的形式存储元素。forward_list 的模板定义在头文件 forward_list 中。
fdrward_list 和 list 最主要的区别是:它不能反向遍历元素；只能从头到尾遍历。

forward_list 的单向链接性也意味着它会有一些其他的特性：
(1)无法使用反向迭代器。只能从它得到const或non-const前向迭代器，这些迭代器都不能解引用，只能自增；
(2)没有可以返回最后一个元素引用的成员函数back();只有成员函数front();
(3)因为只能通过自增前面元素的迭代器来到达序列的终点，所以push_back()、pop_back()、emplace_back()也无法使用。

forward_list 的操作比 list 容器还要快，而且占用的内存更少，尽管它在使用上有很多限制，但仅这一点也足以让我们满意了。


forward_list 的迭代器都是前向迭代器。
它没有成员函数 size()，因此不能用一个前向迭代器减去另一个前向迭代器，但是可以通过使用定义在头文件 iterator 中的 distance() 函数来得到元素的个数。例如：

	forward_list<string> my_words {"three", "six", "eight"};
	auto count = distance(begin(my_words),end(my_words));// Result is 3
	distance() 的第一个参数是一个开始迭代器，第二个参数是一个结束迭代器，它们指定了元素范围。
当需要将前向迭代器移动多个位置时，advance() (返回类型为 void)就派上了用场。
	forward_list<int> data {10, 21, 43, 87, 175, 351};
	auto iter = begin(data);
	size_t n {3};
	advance(iter, n);
	cout << "The " << n+1 << "th element is "<< *iter << endl; // The 4th element is 87


forward_list 包含成员函数splice_after() 和 insert_after()，用来代替 list 容器的 splice() 和 insert();
顾名思义，元素会被粘接或插入到 list 中的一个特定位置。当需要在 forward_list 的开始处粘接或插入元素时，这些操作仍然会有问题。
除了第一个元素，不能将它们粘接或插入到任何其他元素之前。

这个问题可以通过使用成员函数 cbefore_begin() 和 before_begin() 来解决。
它们分别可以返回指向第一个元素之前位置的 const 和 non-const 迭代器。所以可以使用它们在开始位置插入或粘接元素。
	forward_list<string> my_words {"three", "six", "eight"}
	forward_list<string> your_words {"seven", "four", "nine"};
	my_words.splice_after(my_words.before_begin(), your_words, ++begin(your_words));
这个操作的效果是将 your_words 的最后一个元素粘接到 my_words 的开始位置，
因此 my_words 会包含这些字符串对象:"nine"、"three"、"six"、"eight"。这时 your_words 就只剩下两个字符串元素："seven"和"four"。

还有另一个版本的 splice_afler()，它可以将 forward_list<T> 的一段元素粘接到另一个容器中：
	my_words.splice_after (my_words.before_begin() , your_words, ++begin(your_words), end(your_words));
最后两个迭代器参数，指定了第三个参数所指定的 fbrward_list<T> 容器的元素范围。
在这个范围内的元素，除了第一个，其他的都被移到第一个参数所指定容器的特定位置。 
因此，如果在容器初始化后执行这条语句，my_words 会包含"four"、"nine"、"three"、"six"、 "eight"，your_words 仅仅包含"seven"。

另一个版本的 splice_after() 会将一个 forward_list<T> 容器的全部元素粘接到另一个容器中：
	my_words.splice_after(my_words.before_begin(), your_words);
上面的代码会将 your_words 中的全部元素拼接到第一个元素指定的位置。


forward_list 和 list —样都有成员函数 sort() 和 merge()，它们也都有 remove()、remove_if() 和unique()，所有这些函数的用法都和 list 相同。