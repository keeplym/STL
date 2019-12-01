1.find()
find() 为在输入迭代器所定义的范围内查找单个对象的算法，它可以在前两个参数指定的范围内查找和第三个参数相等的第一个对象。
find 算法会返回一个指向被找到对象的迭代器，如果没有找到对象，会返回这个序列的结束迭代器。

反复调用 find() 来找出这个序列中所有给定元素的匹配项：
	std::vector<int> numbers {5, 46, -5, -6, 23, 17, 5, 9, 6, 5};
	size_t count {};
	int five {5};
	auto start_iter = std::begin(numbers);
	auto end_iter = std::end(numbers);
	while((start_iter = std::find(start_iter, end_iter, five)) != end_iter){
    	++count;
    	++start_iter;
	}
	std::cout << five << " was found " << count << " times." << std::endl; // 3 times

2.find_if()
ind_if() 同 find() 一样，为在输入迭代器所定义的范围内查找单个对象的算法，它可以在前两个参数指定的范围内查找可以使第三个参数指定的谓词返回 true 的第一个对象。
谓词不能修改传给它的对象。

find_if() 会返回一个指向被找到对象的迭代器，如果没有找到对象，会返回这个 序列的结束迭代器。

可以按如下方式使用 find_if() 来查找 numbers 中第一个大于 value 的元素：
	vector<int> numbers {5, 46, -5, -6, 23, 17, 5, 9, 6, 5};
	int value {5};
	auto iter1 = std::find_if(std::begin(numbers), std::end(numbers),[value](int n) { return n > value; });
	if(iter1 != std::end(numbers))
    	std::cout << *iter1 << " was found greater than " << value << ".\n";
find_if() 的第三个参数是一个 lambda 表达式的谓词。这个 lambda 表达式以值的方式捕获 value，并在 lambda 参数大于 value 时返回 true。这段代码会找到一个值为 46 的元素。

3.find_if_not()
find_if_not() 可以在输入迭代器所定义的范围内查找单个对象，该算法会在前两个参数指定的范围内查找可以使第三个参数指定的谓词 返回 false 的第一个对象。谓词不能修改传给它的对象。

4.find_first_of()
ind_first_of() 算法可以在第一个序列中搜索第二个序列在第一个序列中第一次出现的任何元素。

	string text {"The world of searching"};
	string vowels {"aeiou"};
	auto iter = std::find_first_of (std::begin (text), std:: end (text), std::begin (vowels),std::end(vowels));
	if(iter != std::end(text))
    	std::cout << "We found '" << *iter << "'." << std::endl; //We found 'e'.
这段代码会在 text 中查找第一次出现的 vowels 中的任意字符。在这个示例中，返回的迭代器指向“The”的第三个字母。可以用循环来查找 text 中所有匹配 vowels 中字符的字符：

	string found {}; // Records characters that are found
	for(auto iter = std::begin(text);(iter = std::find_first_of (iter,std::end (text),std::begin(vowels),std::end(vowels)))!= std::end(text);)
        found += *(iter++);
	std::cout << "The characters \"" << found << "\" were found in text." << std::endl;



	std::vector<long> numbers {64L, 46L, -65LA -128L, 121L, 17L, 35L, 9L, 91L, 5L};
	int factors[] {7, 11, 13};
	std::vector<long> results;  // Stores elements found
	auto iter = std::begin (numbers);
	while ((iter = std:: find_first_of (iter, std::end (numbers),std::begin(factors), std::end(factors),[](long vr long d) { return v % d == 0; }))!= std::end(numbers))
    	results.push_back(*iter++);
	std::cout << results.size() <<" values were found:\n";
	std::copy(std::begin(results), std::end(results),std::ostream_iterator < long > {std::cout," " });
	std::cout << std::endl;
这段代码可以找出 numbers 中所有以 factors 中的一个元素为因子的元素。while 循环会持续进行，只要 find_first_of() 返回的迭代器不是 numbers 的结束迭代器。
iter 变量开始时指向 numbers 的第一个元素，然后会用它来保存被找到元素的迭代器，先前的值被覆盖。在循环体中，iter 指向的元素会被保存到 result 容器中，
然后 iter 自增指向下一个元素。当循环结束时，results 包含的是找到的所有元素，然后用 copy() 算法输出它们。

5.adjacent_find()
adjacent_find() 算法可以用来搜索序列中两个连续相等的元素。用 == 运算符来比较连续的一对元素，返回的迭代器指向前两个相等元素中的第一个。
如果没有一对相等的元素，这个算法返回这个序列的结束迭代器。

adjacent_find() 算法的第二个版本，允许我们提供一个应用于连续元素的谓词。
下面展示了如何用这个函数来查找这个序列中第一对都为奇数的连续整数：
	std::vector<long> numbers {64L, 46L, -65L, -128L, 121L, 17L, 35L, 9L, 91L, 5L};
	auto iter = std::adjacent_find(std::begin(numbers),std::end(numbers),[](long n1, long n2){ return n1 % 2 && n2 % 2; });
	if(iter != std::end(numbers))
    	std::cout <<"The first pair of odd numbers is "<< *iter << " and " << *(iter+1) << std::endl;
当两个参数都不能被 2 整除时，这个 lambda 表达式就返回 true，所以这段代码会找到 121 和 17。


6.find_end()
find_end() 会在一个序列中查找最后一个和另一个元素段匹配的匹配项，也可以看作在一个元素序列中查找子序列的最后一个匹配项。
这个算法会返回一个指向子序列的最后一个匹配项的第一个元素的迭代器，或是一个指向这个序列的结束迭代器。

	string text {"Smith, where Jones had had \"had\", had had \"had had\"." " \"Had had\" had had the examiners\' approval."};
	std::cout << text << std::endl;
	string phrase {"had had"};
	auto iter = std::find_end(std::begin(text), std::end(text), std::begin (phrase),std::end(phrase));
	if(iter != std::end(text))
		std::cout << "The last \"" << phrase<< "\" was found at index "<< std::distance (std::begin (text), iter) << std::endl;
这段代码会从 text 中搜索“had had”的最后一个匹配项，并输出如下内容：
	The last "had had" was found at index 63

另一个版本的 find_end() 接受一个用来比较元素的二元谓词作为第 5 个参数，可以用它来重复前面的搜索并忽略大小写：
	size_t count {};
	auto iter = std::end(text);
	auto end_iter = iter;
	while((iter = std::find_end(std::begin(text), end_iter, std::begin(phrase), std::end (phrase),
	 [] (char ch1, char ch2) { return std::toupper (ch1) == std::toupper(ch2);})) != end_iter){
    	++count;
    	end_iter = iter;
    }
在将字符转换为大写后，会按对比较这两个序列中的元素。在 text 中会找到 phrase 的 5 个实例，因为找到的"Had had"也和 phrase 相等。

7.search()

在查找序列的子序列方面，search() 算法和 find_end() 算法相似，但它所查找的是第一个匹配项而不是最后一个。

和 find_end() 算法一样，它也有两个版本，第二个版本接受用来比较元素的谓词作为第 5 个参数。

8.search_n()

search_n() 算法会搜索给定元素的匹配项，它在序列中连续出现了给定的次数。它的前两个参数是定义搜索范围的正向迭代器，第 3 个参数是想要查找的第 4 个元素的连续匹配次数。例如：
	std::vector<double> values {2.7, 2.7, 2.7, 3.14, 3.14, 3.14, 2.7, 2.7};
	double value {3.14};
	int times {3};
	auto iter = std::search_n(std::begin(values), std::end(values), times, value);
	if (iter != std::end(values))
    	std::cout << times << " successive instances of " << value<< " found starting index " << std::distance (std::begin (values), iter) <<std::endl;
这段代码会在 values 容器中查找第一个有 3 个 value 实例的匹配项。它找到的序列的索引为 3。注意用来指定个数的第三个参数必须是无符号整型；如果不是，编译这段代码会产生警告。
