map 容器是关联容器的一种，底层为红黑树。

为了保持二叉树的平衡，当添加一个新的元素时，可能会导致根节点发生改变。
所以显然，在添加新元素时，为了保持树的平衡，会产生一些额外的开销。
作为回报，容器中的元素越多，相对于线性排列和非平衡树，平衡树组织元素的效率也越高。
从包含 n 个元素的平衡二叉树中检索一个随机元素所需的时间为 O(log2n)，从序列中检索元素所需的时间为 O(n)。

1.插入数据
insert():
成员函数 insert() 会返回一个 pair<iterator,bool> 对象。对象的成员 first 是一个迭代器，
它要么指向插入元素，要么指向阻止插入的元素。如果 map 中已经保存了一个和这个键相同的对象，就会出现后面这种情况。
这个对象的成员变量 second (布尔型)是返回对象，如果插入成功，返回值为 true，否则为 false。

int main() {
    map<string,size_t> people {make_pair ("Ann",25),make_pair("Bill",46) , make_pair ("Jack",32),
                               make_pair("Jill",32)};
    auto pr = make_pair("Fred",22); //Create a pair element and insert it
    auto ret_pr = people.insert(pr);
    cout << ret_pr.first->first << " "<< ret_pr.first->second<< " " << boolalpha <<ret_pr.second << "\n"; // Fred 22 true
    //boolalpha 让输出流将bool解析成为true或者 false（而不是0或1）。
}

int main() {
    map<string,size_t> people {make_pair ("Ann",25),make_pair("Bill",46) , make_pair ("Jack",32),
                               make_pair("Jill",32)};
    auto pr = make_pair("Ann",22); //Create a pair element and insert it
    auto ret_pr = people.insert(pr);
    cout << ret_pr.first->first << " "<< ret_pr.first->second<< " " << boolalpha <<ret_pr.second << "\n"; // Ann 25 false
}

2.erase删除元素
(1) 移除键和参数匹配的元素，然后返回所移除元素的个数，例如：
	std::map<std::string, size_t> people {{ "Fred", 45}, {"Joan", 33},{"Jill", 22}};
	std::string name{"Joan"};
	if(people.erase(name))
    	std::cout << name << " was removed." << std::endl;
	else
    	std::cout << name << " was not found" << std::endl;
显然，map 容器的返回值只可能是 0 或 1，0 表明元素不在容器中。
(2) 也可以用指向删除元素的迭代器作为 erase() 的参数。
这种情况下，返回的迭代器指向被删除元素的下一个位置。这个参数必须是容器中的有效迭代器，不能是结束迭代器。
如果迭代器参数指向的是容器的最后一个元素，那么会返回结束迭代器。例如：
	auto iter = people.erase(std::begin(people));
	if(iter == std::end(people))
    	std::cout << "The last element was removed."<< std::endl;
	else
    	std::cout << "The element preceding " << iter->first << "was removed." << std::endl;
当最后一个元素被移除时，这段代码会输出一条消息或被移除元素后面元素的键。
(3) 也有更高级版本的 erase()，它可以移除两个迭代器参数所定义范围内的元素，例如：
	auto iter = people.erase(++std::begin(people), --std::end(people));//Erase all except 1st & last
返回的迭代器指向这段元素中最后一个被删除的元素。

如果想删除容器中的所有元素，可以调用成员函数 clear()。

/***********************************************************************************************************************************************/
pair

只有两个 public 数据成员 first 和 second.

4 种不同的方式来创建一个 pair 对象:
	std::string s1 {"test"}, s2{"that"};
	std::pair<std::string, std::string> my_pair{s1, s2}; //复制了所有参数的值
	std::pair<std::string, std::string> your_pair{std::string {"test"},std::string {"that"}}; //移动参数值
	std::pair<std::string, std::string> his_pair{"test", std::string {"that"}};//为了隐式转换而将第一个参数传给 string 的构造函数
	std::pair<std::string, std::string> her_pair{"test", "that"}; //将两个参数隐式转换为 string 对象而且它们会被移到 pair 的成员变量 first 和 second 中

make_pair<T1，T2> 函数模板是一个辅助函数，可以生成并返回一个 pair<T1，T2> 对象。 可以如下所示生成先前代码块中的 pair 对象：

	auto my_pair = std::make_pair(s1, s2);
	auto your_pair = std::make_pair(std::string {"test"},std::string {"that"});
	auto his_pair = std::make_pair<std::string, std::string>("test",std::string {"that"});
	auto her_pair = std::make_pair<std::string, std::string>("test", "that");
前两条语句中的函数模板的类型参数由编译器推断。在最后两条语句中，类型是明确的。
如果在最后两条语句中忽略模板类型参数，那么对象类型将是 pair<const char*，string> 和 pair<const char*, const char*>。

当 pair 对象包含不同类型的成员变量时，也可以将一个 pair 对象赋值给另一个 pair 对象，只要作为右操作数的 pair 对象的成员变量可以隐式转换为左操作数的 pair 对象的成员变量的类型。
例如：
	auto prl = std::make_pair ("these", "those"); // Type pair<const char*, const char*>
	std::pair<std::string, std::string> pr2; // Type pair<string, string>
	pr2 = prl; // OK in this case
prl 成员变量 first 和 second 的类型是 const char*。这个类型可以隐式转换为 string，即 pr2 成员变量的类型，因此可以成功赋值。

对于小于或大于比较，pair 对象的成员变量是按字典顺序比较的。如果 new_pair.first 小于 old_pair.first 的话，
表达式 new_pair<old_pair 会返回 true。如果它们的成员变量 first 相等，但new_pair.second 小于 old_pair.second，new_pair < old_pair 也为 true。
	std::pair<int, int> p1 {10, 9};
	std::pair<int, int> p2 {10, 11};
	std::pair<int, int> p3 {11, 9};
	std::cout<<std::boolalpha << (p1 < p2) <<" "<<(p1 > p3) << " "<< (p3 > p2) << std::endl;
第一个比较的结果为 true，因为 p1 和 p2 的成员变量 first 相等，p1 的成员变量 second 小于 p2 的成员变量 second。
第二个比较的结果为 false，因为 p1 的 first 小于 p3 的 first。 
第三个比较的结果则为 true，因为 p3 的 first 大于 p2 的 first。

pair 的成员函数 swap() 可以和作为参数传入的另一个 pair 对象交换其成员变量 first 和 second。显然，参数必须是相同类型。下面有一个示例：
	std::pair<int, int> p1 {10, 11};
	std::pair<int, int> p2 {11, 9};
	p1.swap(p2); // p1={ll,9} p2={10, 11}
如果执行两次 swap()，对象恢复成原来的值。如果这些类型不能隐式转换，这条赋值语句就无法通过编译。

/***********************************************************************************************************************************************/
tuple

tuple<> 模板是 pair 模板的泛化，但允许定义 tuple 模板的实例，可以封装不同类型的任意数量的对象，因此 tuple 实例可以有任意数量的模板类型参数。

1.构造
生成 tuple 对象的最简单方式是使用定义在 tuple 头文件中的辅助函数 make_tuple()。这个函数可以接受不同类型的任意个数的参数，返回的 tuple 的类型由参数的类型决定.
	auto my_tuple = std::make_tuple (Name{"Peter"，"Piper"},42,std::string{"914 626 7890"})；
my_tuple 对象是 tuple<Name，int，string> 类型，因为模板类型参数是由 make_tuple() 函数的参数推导出来的。
如果提供给 make_tuple() 的第三个参数是一个字符串常量，my_tuple 的类型将是 tuple<Name,int,const*>.

tuple 对象的构造函数提供了可能会用到的每一种选择
	std::tuple<std::string, size_t> my_tl;//Default initialization
	std:: tuple<Name, std::string> my_t2 {Name {"Andy", "Capp"},std::string{“Programmer”}};
	std::tuple<Name,std::string> copy_my_t2{my_t2}; // Copy constructor
	std::tuple<std::string, std::string> my_t3 {"this", "that"};
	// Implicit conversion
tuple 中的对象由默认构造函数用默认值初始化。为 my_t2 调用的构造函数将参数移到 tuple 的元素中。
下一条语句会调用拷贝构造函数来生成 tuple，在最后一个构造函数调用中，将参数隐式转换为 string 类型并生成了一个 tuple 元素。

也可以用 pair 对象构造 tuple 对象，pair 可以是左值，也可以是右值。显然，tuple 只能有两个元素。下面有两个示例：
	auto the_pair = std::make_pair("these","those");
	std::tuple<std::string, std::string> my_t4 {the_pair}; 
	std::tuple<std::string, std::string> my_t5 {std::pair <std::string, std::string > { "this", "that"}};
第二条语句从 the_pair 生成了一个 tuple，它是一个左值。the_pair 的成员变量 first 和 second 可以隐式转换为这个 tuple 中的元素的类型。
最后一条语句从右值 pair 对象生成了一个 tuple。

2.访问
get<>():

因为 tuple 是 pair 的泛化，所以它的工作方式不同。pair 的对象个数是固定的，因此它们有成员名。
tuple 中的对象数目是不固定的，所以访问它们的机制必须能够满足这种情况。函数模板 get<>() 可以返回 tuple 中的一个元素。
第一个模板类型参数是 size_t 类型值，它是tuple中元素的索引，因此 0 会选择 tuple 中的第一个元素，1 会选择第二个元素，以此类推。
get<>() 模板剩下的类型参数是和 tuple 的参数同样推导的。下面是一个使用 get<>() 和索引来获取元素的示例：
	auto my_tuple = std::make_tuple (Name {"Peter","Piper"}, 42, std::string {"914 626 7890"});
	std::cout << std::get<0>(my_tuple)<< "age = "<<std::get<1>(my_tuple)<< " tel: " << std::get<2>(my_tuple) << std::endl;

也可以用基于类型的 get<>() 从 tuple 获取元素，但要求 tuple 中只有一个这种类型的元素。例如：
	auto my_tuple = std::make_tuple(Name{"Peter", "Piper"}, 42, std::string {"914 626 7890"});
	std::cout << std::get<Name>(my_tuple)<<" age = " << std::get<int> (my_tuple)<< " tel: " <<std::get<std::string>(my_tuple) << std::endl;
如果 tuple 中包含的 get<>() 类型参数值的元素不止一个，代码就无法编译通过。这里 tuple 的全部 3 个成员为不同类型，所以可以正常使用。

tie():

全局的 tie<>() 函数模板定义在 tuple 头文件中，它提供了另一种访问 tuple 元素的方式。
这个函数可以把 tuple 中的元素值转换为可以绑定到 tie<>() 的左值集合。tie<>() 的模板类型参数是从函数参数中推导的。
例如：
	auto my_tuple = std::make_tuple(Name{"Peter","Piper"}, 42, std::string{"914 626 7890"});
	Name name{};
	size_t age{};
	std::string phone{};
	std::tie(name, age, phone) = my_tuple;
在最后一条语句中，赋值运算符的左操作数表达式会返回一个参数的 tuple 引用。
因此，赋值运算符左右的操作数都是 tuple 对象，并且用 my_tuple 中的元素值来对 tie() 参数中的变量赋值。
我们可能并不想存储每一个元素的值。下面展示了如何只保存 my_tuple 中 name 和 phone 的值：
	std::tie(name, std::ignore,phone) = my_tuple;
ignore 定义在 tuple 中，它被用来标记 tie() 函数中要被忽略的值。tuple 中被忽略的元素的值将不会被记录下来。在这个示例中只复制了第一个和第三个元素。

也可以用 tie() 函数来实现对类的数据成员的字典比较。例如，可以在 Name 类中实现 operator<() 函数：
bool Name::operator<(const Name& name) const
{
    return std::tie(second, first) < std::tie(name.second, name.first);
}
在这个函数体中，调用 tie() 得到的 tuple 对象的元素是按顺序比较的。
用 < 运算符来比较连续的元素对，出现的第一对不同值会决定比较的结果；这个表达式的比较结果就是不同元素的比较结果。
如果全部元素都相等或等价，那么结果为 false。