multimap

multimap 容器保存的是有序的键/值对，但它可以保存重复的元素。multimap 中会出现具有相同键的元素序列，它们会被添加到容器中。
multimap 和 map 有相同范围的构造函数，默认的比较键的函数是 less<K>()。

multimap 大部分成员函数的使用方式和 map 相同。因为重复键的原因，multimap 有一些函数的使用方式和 map 有一些区别。

接下来介绍 multimap 和 map 容器不同的那些成员函数的用法。

1.
multimap 容器的成员函数 insert() 可以插入一个或多个元素，而且插入总是成功。这个函数有很多的版本都可以插入单个元素，它们都会返回一个指向插入元素的迭代器。
下面有一个示例，假设我们已经使用了声明 using std::string：

	std::multimap<string, string〉 pets; // Element is pair{pet_type, pet_name}
	auto iter = pets.insert (std::pair<string, string>{string{"dog"}, string{"Fang"}});
	iter = pets.insert(iter, std::make_pair("dog", "Spot")); // Insert Spot before Fang
	pets.insert(std::make_pair("dog", "Rover"));// Inserts Rover after Fang
	pets.insert (std::make_pair ("cat", "Korky"));// Inserts Korky before all dogs
	pets.insert ({{ "rat", "Roland"}, {"pig", "Pinky" }, {"pig", "Perky"}});//Inserts list elements
第三条语句的第一个参数是一个作为提示符的迭代器，它说明了元素应该被插入的位置。元素会被立即插入到 iter 所指向元素的前面，
因此，这使我们可以覆盖默认的插入位置。对于默认的插入位置来说，元素会被插入到先前插入的键为 "dog" 的元素的后面。元素默认是按照键的升序插入的。
如果没有用提示符改变插入位置，有相同键的元素的位置和插入位置相同。
最后一条语句插入了一些初始化列表中的元素。有高级版本的 insert()，它可以接收两个迭代器参数，用来指定插入元素的范围。

2.
multimap 不支持下标运算符，因为键并不能确定一个唯一元素。

3.
如果使用 multimap 容器，几乎可以肯定它会包含键重复的元素；否则，就应该使用 map。一般来说，我们想访问给定键对应的所有元素。成员函数 equal_range() 就可以做到这一点。它会返回一个封装了两个迭代器的 pair 对象，这两个迭代器所确定范围内的元素的键和参数值相等。例如：
	auto pr = people.equal_range("Ann");
	if(pr.first != std::end(people)){
    	for (auto iter = pr.first ; iter != pr.second; ++iter)
        	std:cout << iter->first << " is " << iter->second << std::endl;
	}
equal_range() 的参数可以是和键同类型的对象，或是不同类型的但可以和键比较的对象。
返回的 pair 对象的成员变量 first 是一个迭代器，它指向第一个大于等于参数的元素；如果键和参数相等的元素存在的话，
它是第一个键和参数相同的元素。如果键不存在，pair 的成员变量 first 就是容器的结束迭代器，所以应该总是对它们进行捡查。

pair 的成员变量 second 也是一个迭代器，它指向键值大于参数的第一个参数；如果没有这样的元素，它会是一个结束迭代器。
这段代码会输出容器中键值为”Ann”的元素的一些信息。

4.
multimap 的成员函数 lower_bound() 会返回一个迭代器，它指向键值和参数相等或大于参数的第一个元素，或者指向结束迭代器。
upper_bound() 也返回一个迭代器，它指向键值大于函数参数的第一个元素，如果这样的元素不出现的话，它就是一个结束迭代器。
所以，当存在一个或多个相等键时，这些函数会返回一个开始迭代器和一个结束迭代器，它们指定了和参数匹配的元素的范围，这和 equal_range() 返回的迭代器是相同的。
因而前面的代码段可以这样重写：
	auto iter1 = people.lower_bound("Ann");
	auto iter2 = people.lower_bound("Ann");
	if(iter1 != std::end(people)){
    	for(auto iter = iterl ; iter != iter2; ++iter)
        	std::cout << iter->first << " is " << iter->second << std::endl;
	}
它和前一个代码段的输出结果是相同的。通过调用 multimap 的成员函数 count() 可以知道有多少个元素的键和给定的键相同。
	auto n = people.count("Jack"); // Returns 2

或
	std::string key{"Jack"};
	auto n = std::distance( people.lower_bound(key),people.upper_bound(key)); // # of elements matching key

/***********************************************************************************************************************************************/

自定义比较函数（map和multimap）

假设我们想用堆上生成的对象的指针作为 map 容器的键。下面用指向 string 对象的智能指针来说明这种情况。这个容器的键可以是 unique_ptr<string> 类型，
在这个示例中我们需要含两个 unique_ptr<string> 参数的比较函数，这个函数可以比较它的参数所指向的 string 对象。可以用伪函数，即函数对象来定义它，
这里假设使用了 using_std::string：
// Compares keys that are unique_ptr<string> objects
class Key_compare
{
public:
    bool operator () (const std::unique_ptr<string>& p1, const std::unique_ptr <string>& p2) const
    {
        return *p1 < *p2;
    }
};
可以用 Key_compare 类型作为 map 容器来比较键的函数对象的类型：
	std::map<std::unique_ptr<string>,std::string,Key_compare> phonebook;
