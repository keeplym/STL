fill() 和 fill_n() 算法提供了一种为元素序列填入给定值的简单方式，
fill() 会填充整个序列； fill_n() 则以给定的迭代器为起始位置，为指定个数的元素设置值。下面展示了 fill() 的用法：

	vector<string> data {12}; // Container has 12 elements
	fill (std::begin (data), std::end (data), "none"); // Set all elements to "none"




fill_n() 的参数分别是指向被修改序列的第一个元素的正向迭代器、被修改元素的个数以及要被设置的值。