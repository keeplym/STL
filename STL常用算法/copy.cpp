1.copy_n()
copy_n() 算法可以从源容器复制指定个数的元素到目的容器中。
第一个参数是指向第一个源元素的输入迭代器，第二个参数是需要复制的元素的个数，第三个参数是指向目的容器的第一个位置的迭代器。
这个算法会返回一个指向最后一个被复制元素的后一个位置的迭代器，或者只是第三个参数——输出迭代器——如果第二个参数为 0.
	
	vector<string> names {"A1","Beth", "Carol", "Dan", "Eve","Fred","George" ,"Harry", "Iain", "Joe"};
	unordered_set<string> more_names {"Janet", "John"};
	copy_n(begin(names)+1, 3, inserter(more_names, std::begin(more_names)));
这个 copy_n() 操作会从 names 的第二个元素开始复制 3 个元素到关联容器 more_names 中。
目的容器是由一个 unordered_set 容器的 insert_iterator 对象指定的，它是由 inserter() 函数模板生成的。
insert_iterator 对象会调用容器的成员函数 insert() 来向容器中添加元素。

当然，copy_n() 的目的地址也可是以流迭代器：
	copy_n(begin(more_names), more_names.size() - 1, ostream_iterator<string> {cout, " "});
这样会输出 more_names 中除了最后一个元素之外的全部元素。
注意，如果被复制元素的个数超过了实际元素的个数，程序会因此崩溃。如果元素的个数为 0 或负数，copy_n() 算法什么也不做。

2.copy_if()

copy_if() 算法可以从源序列复制使谓词返回 true 的元素，所以可以把它看作一个过滤器。
前两个参数定义源序列的输入迭代器，第三个参数是指向目的序列的第一个位置的输出迭代器，第 4 个参数是一个谓词。
会返回一个输出迭代器，它指向最后一个被复制元素的下一个位置。
	vector<string> names {"A1", "Beth", "Carol", "Dan", "Eve","Fred", "George", "Harry", "Iain", "Joe"};
	unordered_set<string> more_names {"Jean", "John"};
	size_t max_length{4};
	copy_if(begin(names), end(names), inserter(more_names, begin(more_names)), [max_length](const string& s) { 
		return s.length() <= max_length;
	});
因为作为第 4 个参数的 lambda 表达式所添加的条件，这里的 copy_if() 操作只会复制 names 中的 4 个字符串或更少。
目的容器是一个 unordered_set 容器 more_names，它已经包含两个含有 4 个字符的名称。

当然，copy_if() 的目的容器也可以是一个流迭代器：

	vector<string> names { "Al", "Beth", "Carol", "Dan", "Eve","Fred", "George", "Harry", "Iain", "Joe"};
	size_t max_length{4};
	copy_if(std::begin(names), std::end(names), std::ostream iterator< string> {std::cout," "}, [max_length](const string& s) { 
		return s.length() > max_length; 
	});
	cout << std::endl;



输入流迭代器可以作为 copy_if() 算法的源，也可以将它用在其他需要输入迭代器的算法上。例如：

	unordered_set<string> names;
	size_t max_length {4};
	cout << "Enter names of less than 5 letters. Enter Ctrl+Z on a separate line to end:\n";
	copy_if(std::istream_iterator<string>{std::cin},std:: istream iterator<string>{}, std::inserter(names, std::begin (names)),[max_length](const string& s) { return s.length() <= max_length; });
	copy(std::begin(names), std::end(names), std::ostream_iterator <string>{std::cout," "});
	cout << std::endl;

3.copy_backward()

像 copy() 那样复制元素，但是从最后一个元素开始直到第一个元素。
copy_backward() 会复制前两个迭代器参数指定的序列。第三个参数是目的序列的结束迭代器，通过将源序列中的最后一个元素复制到目的序列的结束迭代器之前，源序列会被复制到目的序列中。
copy_backward() 的 3 个参数都必须是可以自增或自减的双向迭代器，这意味着这个算法只能应用到序列容器的序列上。

相对于普通的从第一个元素开始复制的 copy() 算法，copy_backward() 提供了哪些优势。

一个回答是，在序列重叠时，可以用 copy() 将元素复制到重叠的目的序列剩下的位置——也就是目的序列第一个元素之前的位置。如果想尝试用 copy() 算法将元素复制到同一个序列的右边，
这个操作不会成功，因为被复制的元素在复制之前会被重写。如果想将它们复制到右边，可以使用 copy_backward()，只要目的序列的结束迭代器在源序列的结束迭代器的右边。

4.reverse_copy()

reverse_copy() 算法可以将源序列复制到目的序列中，目的序列中的元素是逆序的。定义源序列的前两个迭代器参数必须是双向迭代器。
目的序列由第三个参数指定，它是目的序列的开始迭代器，也是一个输出迭代器。
如果序列是重叠的，函数的行为是未定义的。这个算法会返回一个输出迭代器，它指向目的序列最后一个元素的下一个位置。

