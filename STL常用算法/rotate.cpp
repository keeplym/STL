1.rotate()
rotate() 算法会从左边选择序列的元素
rotate() 的第一个参数是这个序列的开始迭代器；第二个参数是指向新的第一个元素的迭代器，它必定在序列之内。第三个参数是这个序列的结束迭代器。
	std::vector<string> words { "one", "two", "three", "four", "five","six", "seven", "eight"};
	auto iter = std::rotate(std::begin(words), std::begin(words)+3, std::end(words));
	std::copy(std::begin(words), std::end(words),std::ostream_iterator<string> {std::cout, " "});
	std::cout << std::endl << "First element before rotation: " << *iter << std::endl;
这段代码对 words 中的所有元素进行了旋转。执行这段代码会生成如下内容：
four five six seven eight one two three
First element before rotation: one
输出说明 "four" 成为新的第一个元素，而且 rotate() 返回的迭代器指向之前的第一个元素"one"。

当然，不需要对容器中的全部元素进行旋转。例如：
	vector<string> words { "one", "two", "three", "four", "five","six", "seven", "eight", "nine", "ten"};
	auto start = std::find(std:begin(words), std::end(words), "two");
	auto end_iter = std::find(std::begin(words), std::end(words), "eight");
	auto iter = std::rotate(start, std::find(std::begin(words), std::end (words), "five") , end_iter);
	std::copy(std::begin(words), std::end(words), std::ostream_iterator<string>{std::cout, " "});
	std::cout << std::endl << "First element before rotation: " << *iter << std::endl;
这里用 find() 算法分别获取了和"two"、"eight"匹配的元素的迭代器。它们定义了被旋转的序列，这个序列是容器元素的子集。
个序列会被旋转为使"five"成为第一个元素，输出说明它是按预期工作的： 
one five six seven two three four eight nine ten
First element before rotation: two

2.rotate_copy() 
在新序列中生成一个序列的旋转副本，并保持原序列不变。rotate_copy() 的前 3 个参数和 copy() 是相同的；第 4 个参数是一个输出迭代器，它指向目的序列的第一个元素。
这个算法会返回一个目的序列的输出迭代器，它指向最后一个被复制元素的下一个位置。

	std::vector<string> words {"one", "two", "three", "four", "five","six", "seven", "eight", "nine"，"ten"};
	auto start = std::find(std::begin(words), std::end(words), "two");
	auto end_iter = std::find (std::begin(words) , std::end (words) ,"eight");
	std::vector<string> words_copy;
	std::rotate_copy(start, std::find(std::begin(words), std::end(words),"five") , end_iter, std::back_inserter (words_copy));
	std::copy(std::begin(words_copy), std::end(words_copy),std::ostream_iterator<string> {std::cout, " "});
	std::cout << std::endl;
这段代码会对 word 中从 "two" 到 "seven" 的元素生成一个旋转副本。通过使用 back_insert_iterator 将复制的元素追加到 words_copy 容器中，
back_insert_iterator 会调用 words_copy 容器的成员函数 push_back() 来插入每个元素。这段代码产生的输出如下：
five six seven two three four