generate和generate_n

	string chars (30, ' ');// 30 space characters
	char ch {'a'};
	int incr {};
	generate (std::begin (chars) , std::end (chars), [ch, &incr]{
    	incr += 3;
    	return ch + (incr % 26);
    })；
	cout << chars << std: :endl;
	// chars is: dgjmpsvybehknqtwzcfiloruxadgjm
变量 chars 被初始化为了个有 30 个空格的字符串。作为 generate() 的第三个参数的 lambda 表达式的返回值会被治存到 chars 的连续字符中。
lambda 表达式以值的方式捕获 ch，以引用的方式捕获 incr，因此会在 lambda 的主体中对后者进行修改。
lambda 表达式会返回 ch 加上 incr 后得到的字符，增加的值是 26 的模，因此返回的值总是在 'a' 到 'z' 之间，给定的起始值为 'a'。这个操作的结果会在注释中展示出来。
可以对 lambda 表达式做一些修改， 使它可以用于任何大写或小写字母，但只生成保存在 ch 中的这种类型的字母。

generate_n() 和 generate() 的工作方式是相似的。不同之处是，它的第一个参数仍然是序列的开始迭代器，第二个参数是由第三个参数设置的元素的个数。
为了避免程序崩溃，这个序列必须至少有第二个参数定义的元素个数。例如：
	string chars (30,' '); // 30 space characters
	char ch {'a'}/ int incr {};
	generate_n(std::begin(chars), chars.size()/2,[ch, &incr]{
    	incr += 3;
    	return ch + (incr % 26);
    })；
这里，chars 中只有一半的元素会被算法设为新的值，剩下的一半仍然为空格。

