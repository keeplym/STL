transform() 可以将函数应用到序列的元素上，并将这个函数返回的值保存到另一个序列中，它返回的迭代器指向输出序列所保存的最后一个元素的下一个位置。

这个算法有一个版本和 for_each() 相似，可以将一个一元函数应用到元素序列上来改变它们的值，但这里有很大的区别。
for_each() 中使用的函数的返回类型必须为 void，而且可以通过这个函数的引用参数来修改输入序列中的值；而 transform() 的二元函数必须返回一个值，
并且也能够将应用函数后得到的结果保存到另一个序列中。

不仅如此，输出序列中的元素类型可以和输入序列中的元素类型不同。对于 for_each()，函数总是会被应用序列的元素上，但对于 transform()，这一点无法保证。

第二个版本的 transform() 允许将二元函数应用到两个序列相应的元素上，但先来看一下如何将一元函数应用到序列上。
在这个算法的这个版本中，它的前两个参数是定义输入序列的输入迭代器，
第 3 个参数是目的位置的第一个元素的输出迭代器，
第 4 个参数是一个二元函数。这个函数必须接受来自输入序列的一个元素为参数，并且必须返回一个可以保存在输出序列中的值。例如：

	vector<double> deg_C {21.0, 30.5, 0.0, 3.2, 100.0};
	vector<double> deg_F(deg_C.size());
	transform(std::begin(deg_C), std::end(deg_C), std:rbegin(deg_F),[](double temp){ return 32.0 + 9.0*temp/5.0; });
	//Result 69.8 86.9 32 37.76 212
这个 transform() 算法会将 deg_C 容器中的摄氏温度转换为华氏温度，并将这个结果保存到 deg_F 容器中。为了保存全部结果，生成的 deg_F 需要一定个数的元素。
因此第三个参数是 deg_F 的开始迭代器。通过用 back_insert_iterator 作为 transform() 的第三个参数，可以将结果保存到空的容器中：

	vector<double> deg_F; // Empty container
	transform(std::begin(deg_C), std::end(deg_C),std::back_inserter(deg_F),[](double temp){ return 32.0 + 9.0* temp/5.0; });
	// Result 69.8 86.9 32 37.76 212
用 back_insert_iterator 在 deg_F 中生成保存了操作结果的元素；结果是相同的。第三个参数可以是指向输入容器的元素的迭代器。例如：

	vector<double> temps {21.0, 30.5, 0.0, 3.2, 100.0}; // In Centigrade
	transform(std::begin (temps), std::end(temps), std::begin(temps),[](double temp){ return 32.0 + 9.0* temp / 5.0; });
	// Result 69.8 86.9 32 37.76 212
这里将 temp 容器中的值从摄氏温度转换成了华氏温度。第三个参数是输入序列的开始迭代器，应用第 4 个参数指定的函数的结果会被存回它所运用的元素上。

下面的代码展示了目的序列和输入序列是不同类型的情况：
	vector<string> words {"one", "two", "three", "four","five"};
	vector<size_t> hash_values;
	transform (std::begin(words), std::end(words),std::back_inserter(hash_values),std::hash<string>()); // string hashing function
	copy(std::begin(hash_values), std::end(hash_values),std::ostream_iterator<size_t> {std::cout," "});
	cout << endl;

应用二元函数的这个版本的 transform() 含有 5 个参数：
前两个参数是第一个输入序列的输入迭代器。
第3个参数是第二个输入序列的开始迭代器，显然，这个序列必须至少包含和第一个输入序列同样多的元素。
第4个参数是一个序列的输出迭代器，它所指向的是用来保存应用函数后得到的结果的序列的开始迭代器。
第5个参数是一个函数对象，它定义了一个接受两个参数的函数，这个函数接受来自两个输入序列中的元素作为参数，返回一个可以保存在输出序列中的值。
