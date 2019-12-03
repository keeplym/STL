
1.
all_of() 算法会返回 true，前提是序列中的所有元素都可以使谓词返回 true。
any_of() 算法会返回 true，前提是序列中的任意一个元素都可以使谓词返回 true。
none_of() 算法会返回 true，前提是序列中没有元素可以使谓词返回 true。

2.count(),count_if()
count()和count_if()可以告诉我们，在前两个参数指定的范围内，有多少满足指定的第三个参数条件的元素。
count() 会返回等同于第三个参数的元素的个数。
count_if() 会返回可以使作为第三个参数的谓词返回 true 的元素个数。


	vector<int> ages {22, 19, 46, 75, 54, 19, 27, 66, 61, 33, 22, 19};
	int the_age{19};
	cout << "There are "<< count(begin(ages),end(ages),the_age)<< " people aged "<< the_age << endl;
	int max_age{60};
	cout << "There are "<< count_if(begin(ages), end(ages),[max_age](int age) { return age > max_age; }) 
	<< " people aged over " << max_age << endl;//大于 max_age 的元素个数
