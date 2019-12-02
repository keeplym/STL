1.binary_search()

在前两个参数指定范围内搜索等同于第三个参数的元素。指定范围的迭代器必须是正向迭代器而且元素必须可以使用 < 运算符来比较。
这个序列中的元素必须被排成升序序列或者至少相对于所查找元素是有序的。如果找到第三个参数，这个算法会返回布尔值 true，否则返回 false。
	std::list<int> values {17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43};
	values.sort ();
	//不能对 list 容器中的元素应用 sort() 算法，因为它需要的是随机访问迭代器，而 list 容器只提供了双向迭代器。
	//因为这个 list 定义了一个成员函数 sort()，可以将全部的元素排成升序
	int wanted {22};    // What we are looking for
	if(std::binary_search(std::begin(values), std::end(values), wanted))
    	cout << wanted << " is definitely in there - somewhere..."<< std::endl;
	else
    	std::cout << wanted << " cannot be found - maybe you got it wrong..." << std::endl;

另一个版本的 binary_search() 接受一个额外的参数，它是一个用于查找元素的函数对象；显然，它必须和用于对被查找序列进行排序的比较操作有相同的效果。
	list<int> values {17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43};
	auto predicate = [](int a, int b){ return a > b;};
	values.sort(predicate);
	int wanted {22};
	if (std::binary_search (std::begin (values), end(values), wanted, predicate))
    	cout << wanted << " is definitely in there - somewhere..."<< endl;
	else
    	std::cout << wanted << " cannot be found - maybe you got it wrong..."<< std::endl;


2.lower_bound()

lower_bound() 算法可以在前两个参数指定的范围内查找不小于第三个参数的第一个元素，也就是说大于等于第三个参数的第一个元素。前两个参数必须是正向迭代器。
	
	list<int> values {17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 43};
	values.sort();  // Sort into ascending sequence
	int wanted {22};    // What we are looking for
	cout << "The lower bound for "<< wanted<< " is "<< *std:: lower_bound (std::begin (values), std::end(values), wanted)<< std::endl;

运行结果为：
The lower bound for 22 is 22

3.upper_bound()

upper_bound() 算法会在前两个参数定义的范围内查找大于第三个参数的第一个元素。对于这两个算法，它们所查找的序列都必须是有序的，而且它们被假定是使用 < 运算符来排序的。

4.equal_range() 

可以找出有序序列中所有和给定元素相等的元素。它的前两个参数是指定序列的两个正向迭代器，第三个参数是要查找的元素。
这个算法会返回一个 pair 对象，它有两个正向迭代器成员，其中的 first 指向的是不小于第三个参数的一个元素，second 指向大于第三个参数的一个元素，
所以我们也可以通过在单个调用中调用 lower_bound() 和 upper_bound() 来得到同样的结果。可以用下面这些语句来替换前一个代码段中的两条输出语句：

	auto pr = std::equal_range(std::begin(values) , std::end(values), wanted);
	cout << "the lower bound for " << wanted << " is " << *pr.first << std::endl;
	cout << "Tthe upper bound for " << wanted << " is " << *pr.second << std::endl;

它和前一段代码的输出完全相同。和前面的二分查找算法一样，equal_range() 也有一个有额外参数的版本，这个参数可以为有序序列提供一些不同于 < 运算符的比较。

前面说过，本节的算法要求它们所处理的序列的元素是有序的，但这并不是全部。
所有的二分查找算法都可以用于以特殊方式分区的序列。对于一个给定的希望值，序列中的元素必须按照 (element < wanted) 和 !(wanted < element) 来分区。
可以用 equal_range() 二分查找算法来做这些工作，在对 values 容器中的元素执行 equal_range() 之前，可以按如下方式对它进行分区：
	std::list<int> values {17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43};
	// Output the elements in original order
	std::copy(std::begin(values), std::end(values),std::ostream_iterator<int> {std::cout, " "});
	std::cout << std::endl;
	int wanted {22};    // What we are looking for
	std::partition(std::begin(values), std::end(values),[wanted](double value) { return value < wanted; });
	std::partition(std::begin(values), std::end(values),[wanted](double value) { return !(wanted < value); });
	//Output the elements after partitioning
	std::copy(std::begin(values), std::end(values),std::ostream_iterator<int>{std::cout," "});
	std::cout<< std::endl;
这段代码的输出如下：
17 11 40 36 22 54 48 70 61 82 78 89 99 92 43
17 11 22 36 40 54 48 70 61 82 78 89 99 92 43

第一行显示的是元素原始的顺序，第二行显示的是分区之后的顺序。两次分区操作改变了元素的顺序，但改变的并不多，
现在我们可以将 equal_range() 应用到 values 容器的元素上，期望值为 wanted:
	auto pr = std::equal_range(std::begin(values), std::end(values), wanted);
	std::cout << "the lower bound for " << wanted << " is " << *pr.first << std::endl;
	std::cout << "the upper bound for " << wanted << " is " << *pr.second << std::endl;
这段代码和前一段代码的输出是相同的，在前一段代码中，用容器对象的成员函数 sort() 对元素进行了完全排序。本节的所有算法都可以用于以这种方式分区的序列上。
显然，如果分区使用的是>，那么在查找算法中使用的函数对象也必须和它保持一致。

