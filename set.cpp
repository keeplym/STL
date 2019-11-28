定义 set 容器的模板如下：
set<T> 容器保存 T 类型的对象，而且保存的对象是唯一的。其中保存的元素是有序的，默认用 less<T> 对象比较。可以用相等、不相等来判断对象是否相同。
multiSet<T> 容器和 set<T> 容器保存 T 类型对象的方式相同，但它可以保存重复的对象。
unorderd_set<T> 容器保存 T 类型的对象，而且对象是唯一的。元素在容器中的位置由元素的哈希值决定。默认用 equal_to<T> 对象来判断元素是否相等。
unordered_multiset<T> 容器保存 T 类型对象的方式和 unorderd_set<T> 相同，但它可以保存重复的对象。

从有序和无序关联容器获取的各种迭代器之间有一些区别。我们可以从有序容器得到正向和反向迭代器，但是只能从无序容器得到正向迭代器。

1.初始化

可以用元素段来创建 set 容器，并且可以指定它的比较函数：

	std::set<string> words2 {std::begin(words), std::end(words)};
	std::set<string, std::greater<string>> words3 {++std::begin(words2), std::end(words2)};

2.添加、删除和访问元素

set 中没有实现成员函数 at()，也没有实现 operator[]()。
除了这些操作外，set 容器提供 map 容器所提供的大部分操作。可以使用 insert()、emplace()、emplace_hint() 成员函数来向 set 中添加元素。

3.set_union

第一个版本的 set_union() 函数模板实现了集合的并集运算.
它需要 5 个参数：两个迭代器用来指定左操作数的集合范围，另两个迭代器用来作为右操作数的集合范围，还有一个迭代器用来指向结果集合的存放位置。

	vector<int> set1 {1, 2, 3, 4, 5, 6};
	vector<int> set2 {4, 5, 6, 7, 8, 9};
	vector<int> result;
	set_union(std::begin (set1), std::end(set1), std::begin(set2), std::end(set2),std::back_inserter(result));// Destination for the result:1 2 3 4 5 6 7 8 9
set1 和 set2 中的初始值都是升序。如果它们都不是，那么在使用 set_union() 算法前，需要对 vector 容器排序。
前面章节中介绍的 back_inserter() 函数模板定义在 iterator 头文件中，它会调用传入参数的函数 push_back() 来返回一个 back_inserter_iterator 对象。
所以，set1 和 set2 并集中的元素会被保存在 result 中。
从并集运算得到的元素集合是容器元素的副本，因此这个运算并不会影响容器的原始内容。

当然，如果不保存运算结果；可以用一个流迭代器输出这些元素：

	set_union(std::begin(set1), std::end(set1), std::begin(set2), std::end(set2),std::ostream_iterator<int> {std::cout, " "});

第二个版本的 set_union() 函数模板接收的第 6 个参数是一个用来比较集合元素的函数对象。下面是它可能的一些用法：
	set<int, std::greater<int>>set1 {1, 2, 3, 4, 5, 6}; // Contains 6 5 4 3 2 1
	set<int, std::greater<int>>set2 {4, 5, 6, 7, 8, 9}; // Contains 9 8 7 6 5 4
	set<int, std::greater<int>>result; // Elements in descending sequence
	set_union(std::begin(set1), std::end(set1),std::begin(set2), std::end(set2),std::inserter(result, std::begin(result)), std::greater<int>()); // Result destination: 9 8 7 6 5 4 3 2 1
这一次的集合是 set 容器中的元素。这些元素是用函数对象 greater<int> 排序过的，因此它们都是降序。
set_union() 的最后一个参数是一个用来比较集合元素的 greater<int> 类型的实例。
结果的存放位置是 result 容器的 inserter_iterator，容器会调用成员函数 insert() 来添加元素。
不能对 set 容器使用 back_insert_iterator，因为它没有成员函数 push_back()。
并集运算的结果是从两个集合得到的元素的副本的降序集合。

这两个版本的 set_union() 函数都会返回一个指向被复制元素段末尾后一个位置的迭代器。如果目的容器包含操作前的元素，这是很有用的。
例如，如果目的容器是 vector 容器，set_union() 用 front_insert_iterator，如果用 back_inserter_iterator，可以用这个容器的结束迭代器，
插入这个新元素，set_union() 返回的迭代器会指向第一个原始元素。

4.set_intersection
除了会创建两个集合的交集而不是并集之外，set_intersection() 算法的用法和 set_union() 相同。
有两个版本的 set_intersection()，它们和 set_union() 拥有相同的参数集。下面的一些语句可以说明它的用法：
	set<string> words1 {"one", "two", "three", "four", "five", "six"};
	set<string> words2 {"four"，"five", "six", "seven", "eight", "nine"};
	set<string> result;
	set_intersection(std::begin(words1), std::end(words1), std::begin(words2), std::end(words2),std::inserter(result, std::begin(result)));
	// Result: "five" "four" "six"
这个 set 容器保存 string 对象，默认使用 less<string> 的实例对元素排序。
两个容器中元素的交集是它们共有的元素，它们被保存在 result 容器中。当然，这些元素是升序字符串序列。
set_intersection() 算法会返回一个迭代器，它指向目的容器中插入的最后一个元素的下一个位置。

5.set_difference

set_difference() 算法可以创建两个集合的差集，它也有两个版本的函数并且参数集和 set_union() 相同。下面是一个对降序 set 容器使用这个算法的示例：
	set<string, std::greater<string>> words1 {"one", "two", "three", "four", "five", "six" };
	set<string, std::greater<string>> words2 { "four", "five", "six", "seven", "eight", "nine"};
	set<string, std::greater<string>> result;
	set_difference(begin(words1), end(words1), begin(words2), end(words2), inserter(result, begin(result)), greater<string>());
	// Result: "two", "three", "one"
这里调用的这个版本的函数的第 6 个参数是一个用来比较元素的函数对象，因为来自 set 容器的这段元素也用这个函数排序。
通过从 words1 集合中移除 word1 和 word2 共有的元素来获取差集，差集由来自 word1 的元素组成。结果得到 words1 的前三个元素的降序序列。
这个算法也会返回一个迭代器，它指向目的容器被插入的最后一个元素的下一个位置。


6.set_symmetric_difference

set_symmetric_difference() 算法和先前的集合算法遵循同一种模式。下面的几条语句展示了它的用法：
	set<string> words1 { "one", "two", "three", "four", "five", "six" };
	set<string> words2 {"four", "five", "six", "seven", "eight", "nine"};
	set_symmetric_difference(begin(words1), end(words1), begin(words2), end(words2),ostream_iterator<string> {cout," "});
这个范围内的元素默认是升序排列的。集合的对称差集中的元素是两个集合中不包括它们共有元素的元素。
最后一个函数的参数定义了结果集的存放位置，它是一个 ostream_iterator，因此这些元素会被写入 cout，输出内容如下：
eight nine one seven three two

自然地，这些序列中的 string 元素都是对它们使用 < 运算符后得到的结果，因为默认的比较函数对象类型是 less<string>。

7.includes

includes() 算法可以比较两个元素的集合，如果第一个集合中的全部元素都来自第二个集合，它会返回 true。如果第二个集合是空的集合，它也返回 true。下面是一些示例：
	set<string> words1 { "one", "two", "three", "four", " five", "six"};
	set<string> words2 {"four", "two", " seven"}; 
	multiset<string> words3;
	cout << boolalpha >> includes(begin(words1), end(words1), begin(words2), end(words2))>> endl; //Output: false
	cout << boolalpha >> includes(begin(words1), end(words1), begin(words2), begin(words2))>> endl; //Output: true
    set_union(std::begin(words1), std::end(words1), std::begin(words2), std::end(words2),std::inserter(words3, std::begin(words3)));
	cout << boolalpha >> includes(begin(words3), end(words3), begin(words2), end(words2))>> endl; //Output: true
这里有两个 string 元素的 set 容器，words1 和 words2，它们都是用初始化列表初始化的。
第一条输出语句显示 false，因为 word1 不包含 word2 中的 string("seven") 元素。
第二条输出语句显示 true，因为第二个操作数指定的集合是空的，也就是说它的开始迭代器和结束迭代器相同。
set_union() 函数会通过 inserter_iterator 将 words1 和 words2 中的并集复制 word3 中。
结果 word3 会包含 words2 中的全部元素，因而第三条输出语句会显示 true。

当容器是 multiset 时，会很容易对它们并集运算后的结果感到困惑。尽管 words3 是一个允许包含重复元素的 multiset，但 words1 和 words2 共有的元素并没有重复出现在 words3 中。
下面的语句会输出 words3 中的元素：
	copy(std::begin(words3), std::end(words3),std::ostream_iterator<string> {std::cout," "});
输出结果如下：
five four one seven seven six three two

这是因为并集运算只包含每个重复元素的一个副本。当然，如果 words1 和 words2 是包含重复单词的 multiset 容器，那么结果可能会包含一些重复元素：
	multiset<string> words1 {"one", "two", "nine", "nine", "one", "three", "four", "five", "six"};
	multiset<string> words2 {"four", "two", "seven", "seven", "nine", "nine"};
	multiset<string> words3;
"one" 是 words1 中的重复元素，"seven" 是 words2 中的重复元素。"nine" 在这两个容器中都是重复的。现在可以指向相同的 set_union():
	set_union(std::begin(words1), std::end(wordsl),std::begin(words2), std::end(words2), std::inserter(words3, std::begin(words3)));
输出的 words3 的内容如下:
five four nine nine one one seven seven six three two

并集结果中会有一个或多个重复元素，对于在两个集合中都单独出现的元素，并集运算中不会有重复的元素。当然，如果元素在两个集合中都重复，那么它们在结果中也是重复的。