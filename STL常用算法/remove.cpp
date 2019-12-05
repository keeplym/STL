有 4 种移除算法：
remove() 
可以从它的前两个正向迭代器参数指定的序列中移除和第三个参数相等的对象。基本上每个元素都是通过用它后面的元素覆盖它来实现移除的。
它会返回一个指向新的最后一个元素之后的位置的迭代器。

remove_copy() 
可以将前两个正向迭代器参数指定的序列中的元素复制到第三个参数指定的目的序列中，并忽略和第 4 个参数相等的元素。
它返回一个指向最后一个被复制到目的序列的元素的后一个位置的迭代器。序列不能是重叠的。

remove_if() 
可以从前两个正向迭代器指定的序列中移除能够使作为第三个参数的谓词返回 true 的元素。

remove_copy_if() 可以将前两个正向迭代器参数指定的序列中，能够使作为第 4 个参数的谓词返回 true 的元素，复制到第三个参数指定的目的序列中。
它返回一个指向最后一个被复制到目的序列的元素的后一个位置的迭代器。序列不能是重叠的。


可以按如下方式使用 remove():
	deque<double> samples {1.5, 2.6, 0.0, 3.1, 0.0, 0.0, 4.1, 0.0, 6.7, 0.0};
	samples.erase(std::remove(std::begin(samples), std::end(samples), 0.0), std::end(samples));
	copy(std::begin(samples),std::end(samples), std::ostream_iterator <double> {std::cout," "});
	cout << std::endl;
	// 1.5 2.6 3.1 4.1 6.7

remove() 算法会通过左移其他元素来覆盖它们，通过这种方式就可以消除杂乱分布的 0。
remove() 返回的迭代器指向通过这个操作得到的新序列的尾部，所以可以用它作为被删除序列的开始迭代器来调用 samples 的成员函数 erase()。
注释说明容器中的元素没有被改变。


如果想保留原始序列，并生成一个移除选定元素之后的副本，可以使用 remove_copy()。 例如：
	deque<double> samples {1.5, 2.6, 0.0, 3.1, 0.0, 0.0, 4.1, 0.0, 6.7, 0.0}; std::vector<double> edited_samples;
	remove_copy(std::begin(samples), std::end(samples), std::back_inserter(edited_samples), 0.0);
samples 容器中的非零元素会被复制到 edited_samples 容器中，edited_samples 正好是一个 vector 容器。
通过 back_insert_iterator 对象将这些元素添加到 edited_samples，因此这个容器只包含从 sample 中复制的元素。


remove_if() 提供了更强大的能力，它能够从序列中移除和给定值匹配的元素。谓词会决定一个元素是否被移除；它接受序列中的一个元素为参数，并返回一个布尔值。例如：

	using Name = std::pair<string, string>； // First and second name
	set<Name> blacklist {Name {"Al", "Bedo"}, Name {"Ann", "Ounce"}, Name {"Jo","King"}};
	deque<Name> candidates {Name{"Stan", "Down"}, Name {"Al", "Bedo"}, Name {"Dan", "Druff"},Name {"Di", "Gress"}, Name {"Ann", "Ounce"}, Name {"Bea", "Gone"}}; candidates.erase(std::remove_if(std::begin(candidates), std::end(candidates),[&blacklist](const Name& name) { return blacklist.count(name); }), std::end(candidates)); std::for_each(std::begin(candidates), std::end(candidates), [] (const Name& name){std::cout << '"' << name.first << " " << name.second << "\" ";});
	cout << std::endl;  // "Stan Down" "Dan Druff" "Di Gress" "Bea Gone"

	