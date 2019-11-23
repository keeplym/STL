容器适配器是一个封装了序列容器的类模板，它在一般序列容器的基础上提供了一些不同的功能。
之所以称作适配器类，是因为它可以通过适配容器现有的接口来提供不同的功能。

stack

1. 初始化
stack 容器适配器的模板有两个参数。第一个参数是存储对象的类型，第二个参数是底层容器的类型。
stack<T> 的底层容器默认是 deque<T> 容器，因此模板类型其实是 stack<typename T, typename Container=deque<T>>。
通过指定第二个模板类型参数，可以使用任意类型的底层容器，只要它们支持 back()、push_back()、pop_back()、empty()、size() 这些操作。
下面展示了如何定义一个使用 list<T> 的堆栈：
	stack<string, list<string>> fruit;
创建堆栈时，不能在初始化列表中用对象来初始化，但是可以用另一个容器来初始化，只要堆栈的底层容器类型和这个容器的类型相同。例如：
	list<double> values {1.414, 3.14159265, 2.71828};
	stack<double, list<double>> my_stack (values);
第二条语句生成了一个包含 value 元素副本的 my_stack。
这里不能在 stack 构造函数中使用初始化列表；必须使用圆括号。
如果没有在第二个 stack 模板类型参数中将底层容器指定为 list，那么底层容器可能是 deque，
这样就不能用 list 的内容来初始化 stack, 只能接受 deque。

stack<T> 模板定义了拷贝构造函数，因而可以复制现有的 stack 容器：
	stack<double, list<double>> copy_stack {my_stack}
copy_stack 是 my_stack 的副本。
在使用拷贝构造函数时，既可以用初始化列表，也可以用圆括号。

2.比较
stack<T> 模板也定义了复制和移动版的 operator=() 函数，因此可以将一个 stack 对象赋值给另一个 stack 对象。
stack 对象有一整套比较运算符。比较运算通过字典的方式来比较底层容器中相应的元素。
字典比较是一种用来对字典中的单词进行排序的方式。依次比较对应元素的值，直到遇到两个不相等的元素。
第一个不匹配的元素会作为字典比较的结果。如果一个 stack 的元素比另一个 stack 的多，
但是所匹配的元素都相等，那么元素多的那个 stack 容器大于元素少的 stack 容器。

3.swap(s1,s2)

将栈s1和桟s2的数据进行交换，相当于两个人互换了个名字。

/*********************************************************************************************************************/
queue

queue<T> 默认封装了一个 deque<T> 容器,也可以通过指定第二个模板类型参数来使用其他类型的容器：
	queue<string, list<string>>words;
底层容器必须提供这些操作：front()、back()、push_back()、pop_front()、empty() 和 size()。

swap(q1,q2)

将q1和q2的数据进行交换，相当于两个人互换了个名字。

/*********************************************************************************************************************/
priority_queue（默认为最大堆）

1.初始化
(1)
priority_queue 模板有 3 个参数，其中两个有默认的参数；
第一个参数是存储对象的类型，
第二个参数是存储元素的底层容器，
第三个参数是函数对象，它定义了一个用来决定元素顺序的断言。
因此模板类型是：
	template <typename T, typename Container = vector<T>, typename Compare = less<T>> class priority_queue
priority_queue 实例默认有一个 vector 容器。
函数对象类型 less<T> 是一个默认的排序断言，定义在头文件 function 中，决定了容器中最大的元素会排在队列前面。
fonction 中定义了greater<T>，用来作为模板的最后一个参数对元素排序，最小元素会排在队列前面。
当然，如果指定模板的最后一个参数，就必须提供另外的两个模板类型参数;

(2)
当对容器内容反向排序时，最小的元素会排在队列前面，这时候需要指定 3 个模板类型参数：
	string wrds[] {"one", "two", "three", "four"};
	priority_queue<string, vector<string>, greater<string>> words1 {begin(wrds), end(wrds)}; //"four" "one" "three" "two"

(3)
可以生成 vector 或 deque 容器，然后用它们来初始化 priority_queue。
下面展示了如何以 vector 的元素作为初始值来生成 priority_queue 对象：
	vector<int> values{21, 22, 12, 3, 24, 54, 56};
	priority_queue<int> numbers {less<int>(), values};
priority_queue 构造函数的第一个参数是一个用来对元素排序的函数对象，
第二个参数是一个提供初始元素的容器。在队列中用函数对象对 vector 元素的副本排序。
values 中元素的顺序没有变，但是优先级队列中的元素顺序变为：56 54 24 22 21 12 3。
优先级队列中用来保存元素的容器是私有的，因此只能通过调用 priority_queue 对象的成员函数来对容器进行操作。
构造函数的第一个参数是函数对象类型，它必须和指定的比较模板类型参数相同，函数对象类型默认是 less<T>。

(4)
如果想使用不同类型的函数，需要指定全部的模板类型参数。例如：
std::priority_queue<int, std::vector<int>,std::greater<int>> numbersl {std::greater<int>(), values};
第三个类型参数是一个比较对象类型。如果要指定这个参数，必须指定前两个参数——元素类型和底层容器类型。



2.
以下展示了如何将键盘输入的数据记录到 priority_queue 中：
	priority_queue<string> words;
	string word; 
	cout << "Enter words separated by spaces, enter Ctrl+Z on a separate line to end:\n";
	while (true){
    	if ((cin >> word).eof())
        	break;
    words.push(word);
}
按下 Ctrl+Z 组合键会在输入流中设置文件结束状态，因此可以用来结束循环输入。
istream 对象的成员函数 operator>>() 返回一个输入流对象，因此我们可以用 if 条件表达式来调用 eof() 以检查 cin 的状态。
这里会对输入单词进行排序，所以最大的单词总在 words 队列的前面——自动对输入单词排序。

3.
priority_queue 没有迭代器。如果想要访问全部的元素，
比如说，列出或复制它们，会将队列清空；priority_queue 和 queue 有相同的限制。
如果想在进行这样的操作后，还能保存它的元素，需要先把它复制一份，这里可以使用一个不同类型的容器。下面展示了如何列出优先级队列 words 的内容：

	priority_queue<string> words_copy {words}; // A copy for output
	while(!words_copy.empty()){
    	cout << words_copy.top () <<" ";
    	words_copy.pop();
    }
    cout << endl;

如果需要多次输出 priority_queue 的内容，最好定义一个函数。这个函数应该是通用的，如下所示：

void list_pq(std::priority_queue<T> pq, size_t count = 5){
    size_t n{count};
    while (!pq. empty())
    {
        std::cout << pq. top() << " ";
        pq.pop();
        if (--n) continue;
        std::cout << std::endl;
        n = count;
    }
    std::cout << std::endl;
}

/*****************************************************************************************************************************/
堆(heaps)不是容器，而是一种特别的数据组织方式。堆一般用来保存序列容器。


定义一个堆：这个堆是一个完全二叉树，每个节点与其子节点位置相对。父节点总是大于或等于子节点，这种情况下被叫作大顶堆，
或者父节点总是小于或等于子节点，这种情况下叫作小顶堆。注意，给定父节点的子节点不一定按顺序排列。

1.创建堆
用来创建堆的函数定义在头文件 algorithm 中。max_heap() 对随机访问迭代器指定的一段元素重新排列，生成一个堆。
默认使用的是 < 运算符，可以生成一个大顶堆。例如：
	vector<double>numbers{2.5,10.0,3.5,6.5,8.0,12.0,1.5,6.0};
	make_heap(begin(numbers), rend(numbers));
	// Result: 12 10 3.5 6.5 8 2.5 1.5 6

priority_queue 是一个堆。在底层，一个 priority_queue 实例创建了一个堆。
priority_queue 可以提供堆没有的优势，它可以自动保持元素的顺序；
但我们不能打乱 priority_queue 的有序状态，因为除了第一个元素，我们无法直接访问它的其他元素。如果需要的是一个优先级队列，这一点非常有用。

从另一方面来说，使用 make_heap() 创建的堆可以提供一些 priority_queue 没有的优势：
可以访问堆中的任意元素，而不限于最大的元素，因为元素被存储在一个容器中，就像是我们自己的 vector。
这也提供了偶然破坏元素顺序的可能，但是总可以调用 make_heap() 来还原堆。
可以在任何提供随机访问迭代器的序列容器中创建堆。这些序列容器包括普通数组、string 对象、自定义容器。
这意味着无论什么时候需要，都可以用这些序列容器的元素创建堆，必要时，可以反复创建。甚至还可以为元素的子集创建堆.

这里有另一个版本的 make_heap()，它有第 3 个参数，可以用来指定一个比较函数用于堆的排序。
通过定义一个大于运算符函数，可以生成一个小顶堆。这里可以使用 functional 中的断言。例如：
	vector<double> numbers {2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0};
	make_heap(begin(numbers), end(numbers), greater<>()); // Result: 1.5 6 2.5 6.5 8 12 3.5 10



2.堆操作：

	vector<double> numbers {2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0};
	make_heap(begin(numbers), end(numbers));
	// Result: 12 10 3.5 6.5 8 2.5 1.5 6
	numbers.push_back(11); // Result: 12 10 3.5 6.5 8 2.5 1.5 6 11
	push_heap(begin(numbers), end(numbers));
	// Result: 12 11 3. 5 10 8 2. 5 1. 5 6 6. 5
注释显示了每个操作执行后的效果。必须以这种方式向堆中添加元素。
只能通过调用成员函数向 queue 中添加新元素，而且这个成员函数只接受迭代器作为参数，不能直接以元素作为参数。

push_back() 会在序列末尾添加元素，然后使用 push_heap() 恢复堆的排序。
通过调用 push_heap()，释放了一个信号，指出我们向堆中添加了一个元素，这可能会导致堆排序的混乱。
push_heap() 会因此认为最后一个元素是新元素，为了保持堆结构，会重新排列序列。

当然，也可以用自己的比较函数来创建堆，但是必须和 push_heap() 使用相同的比较函数：
	vector<double> numbers {2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0};
	make_heap(begin(numbers), end(numbers), greater<>());//Result: 1.5 6 2.5 6.5 8 12 3.5 10 numbers. push—back(1. 2);
	//Result: 1.5 6 2.5 6.5 8 12 3.5 10 1.2
	push_heap(begin(numbers), end(numbers), greater<>());
	//Result: 1.2 1.5 2.5 6 8 12 3.5 10 6.5
如果 push_heap() 和 make_heap() 的第 3 个参数不同，代码就无法正常执行。

删除最大元素:
	pop_heap(begin(numbers), end(numbers));
pop_heap() 函数将第一个元素移到最后，并保证剩下的元素仍然是一个堆。然后就可以使用 vector 的成员函数 pop_back() 移除最后一个元素

检查序列是否仍然是堆的方法:
	is_heap(begin(numbers), end(numbers))

如果这里使用的是用 greater<> 创建的堆，就会产生错误的结果。为了得到正确的结果，表达式需要写为：

	is_heap(begin(numbers), end(numbers), greater<>());

is_heap_until() 函数返回一个迭代器，指向第一个不在堆内的元素
	auto iter = is_heap_until(begin(numbers), end(numbers), greater<>());
	if(iter != end(numbers))
    	cout << "numbers is a heap up to "<<*iter<<endl;

STL 提供的最后一个操作是 sort_heap()，它会将元素段作为堆来排序。如果元素段不是堆，程序会在运行时崩溃。
这个函数有以两个迭代器为参数的版本，迭代器指向一个假定的大顶堆(用 less<> 排列)，然后将堆中的元素排成降序。结果当然不再是大顶堆。下面是一个使用它的示例：
	vector<double> numbers {2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0};
	make_heap(std::begin(numbers), std::end(numbers));
	//Result: 12 10 3.5 6.5 8 2.5 1.5 6
	sort_heap(std::begin(numbers), std::end(numbers));
	// Result: 1.5 2.5 3.5 6 6.5 8 10 12
排序操作的结果不是一个大顶堆，而是一个小顶堆.

/*****************************************************************************************************************************/
C++序列容器存储智能指针
// http://c.biancheng.net/view/482.html
//http://c.biancheng.net/view/486.html
主要有两种类型的智能指针：unique_ptr<T> 和 shared_ptr<T>，
其中 unique_ptr<T> 独占它所指向对象的所有权，而 shared_ptr<T> 允许多个指针指向同一个对象。
还有weak_ptr<T> 类型，它是一类从 shared_ptr<T> 生成的智能指针，可以避免使用 shared_ptrs<T> 带来的循环引用问题。
unique_ptr<T> 类型的指针可以通过移动的方式保存到容器中。


