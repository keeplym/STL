1.sort()
定义在 algorithm 头文件中的函数模板 sort<Iter>() 默认会将元素段排成升序，这也就意味着排序的对象的类型需要支持 < 运算符。 


函数模板 sort<Iter>() 的类型参数 Iter 是元素段元素对应的迭代器类型，而且它们必须支持随机访问迭代器。
这表明 sort() 算法只能对提供随机访问迭代器的容器中的元素进行排序，也说明 sort() 只能接受 array、vector、deque 或标准数组中的元素。
可以回顾前面章节，list 和 forward_list 容器都有成员函数 sort(); 
这些用来排序的特殊成员函数是必要的，因为 list 只提供双向迭代器，且 forward_list 只提供正向迭代器。

为了将元素排成降序，需要提供一个用来比较元素的函数对象，作为 sort() 的第三个参数：

	sort(std::begin(numbers), std::end(numbers), std::greater<>());

Complexity:
On average, linearithmic in the distance between first and last: 
Performs approximately N*log2(N) (where N is this distance) 
comparisons of elements, and up to that many element swaps (or moves).




2.stable_sort()

stable_sort() 算法会对一段元素进行排序并保证维持相等元素的原始顺序，这里有两个版本：其中一个接受两个用来指定排序元素范围的迭代器，另一个接受用于比较的额外参数。

stable_sort() 保证不会改变相等元素的顺序，这是 sort() 算法所不能保证的。当需要使相等元素的顺序保持不变时，应该使用 stable_sort()。

3.partial_sort()

对于部分排序，有一个特殊的算法 partial_sort()，它需要 3 个随机访问迭代器作为参数。
如果这个函数的参数是 first、second 和 last，那么这个算法会被应用到 [first，last) 这个范围内的元素上。执行这个算法后，
[first，second) 会包含降序序列 [first，last) 中最小的 second-first 个元素。

	size_t count {5}; // Number of elements to be sorted
	std::vector<int> numbers {22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10};
	std::partial_sort(std::begin(numbers), std::begin(numbers) + count, std::end(numbers));


	std::partial_sort(std::begin(numbers), std::begin(numbers) + count, std:: end (numbers) , std::greater<>());
	//现在，number 中最大的 count 个元素会是容器开始处的一个降序序列。在此系统上这条语句的输出结果为： 93 88 56 45 22 7 19 12 8 7 15 10


partial_sort_copy() 在本质上和 partial_sort() 是相同的，除了前者会将排序元素复制到一个不同的元素段（另一个容器中）。
它的前两个参数是指定部分排序应用范围的迭代器； 第 3 个和第 4 个参数是标识结果存放位置的迭代器。目的位置的元素个数决定了输入元素段中被排序元素的个数。


int main() {
    vector<int> numbers {22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10};
    int count = 5; // Number of elements to be sorted
    vector<int> result(count); // Destination for the results 一 count elements
    partial_sort_copy(begin(numbers), end(numbers), begin (result) , end (result));
    copy(begin(numbers), end(numbers), ostream_iterator<int>{cout," " });//22 7 93 45 19 56 88 12 8 7 15 10  numbers 中元素的顺序并没有被打乱
    cout << endl;
    copy(begin(result), end(result),ostream_iterator <int> {cout, " "}); //7 7 8 10 12 
    cout << endl;
}


4.is_sorted()
如果两个迭代器参数所指定范围内的元素是升序排列的，函数模板 is_sorted() 就会返回 true。

	std::vector<double> data {1.5, 2.5, 3.5, 4.5};
    std:: cout << "data reversed is "<< (std::is_sorted(std::rbegin(data), std::rend(data), std::greater<>()) ? "":"not ")<< "in descending sequence." << std::endl;
    //data reversed is in descending sequence.

5.is_sorted_until()
也可用函数模板 is_sorted_until() 来判断一个元素段是否有序。它的参数用来定义要测试的迭代器。这个函数会返回一个指向这段元素中升序序列上边界元素的迭代器。\
例如：
	std::vector<string> pets {"cat", "chicken", "dog", "pig", "llama", "coati", "goat"};
	std::cout << "The pets in ascending sequence are:\n";
	std::copy(std::begin(pets), std::is_sorted_until(std::begin(pets), std::end (pets)) , std::ostream_iterator<string>{ std::cout," "});
	//The pets in ascending sequence are:
	//cat chicken dog pig


	std::vector<string> pets {"dog", "coati", "cat", "chicken", "pig", "llama", "goat"};
	std::cout << "The pets in descending sequence are:\n";
	std::copy(std::begin(pets),std::is_sorted_until(std::begin(pets), std::end (pets) , std::greater<>()),std::ostream_iterator<string>{ std::cout," "});
	//The pets in descending sequence are:
	//dog coati cat


6.nth_element()
nth_element() 算法和 partial_sort() 不同。应用的范围由它的第一个和第三个参数指定。第二个参数是一个指向第 n 个元素的迭代器。
如果这个范围内的元素是完全有序的，nth_dement() 的执行会导致第 n 个元素被放置在适当的位置。
这个范围内，在第 n 个元素之前的元素都小于第 n 个元素，而且它后面的每个元素都会比它大。算法默认用 < 运算符来生成这个结果。

第 n 个元素之前的元素都小于它，但不必是有序的。同样，第 n 个元素后的元素都大于它，但也不必是有序的。

	std::nth_element(std::begin(numbers), std::begin(numbers) + count, std::end(numbers) , std::greater<>());
这里使用 > 运算符来比较函数，所以第 n 个元素将是元素按降序排列后的第 n 个元素。第 n 个元素之前的元素都大于它，之后的元素都小于它。
