1.partition()
对元素进行排列，所有使给定谓词返回 true 的元素会被放在所有使谓词返回 false 的元素的前面。
partition 的前两个参数是定义被分区序列范围的正向迭代器，第三个参数是一个谓词。
下面展示如何使用 partition() 来重新排列序列中的值，所有小于平均值的元素会被放在所有大于平均值的元素的后面：
	vector<double> temperatures {65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50};
	copy(std::begin(temperatures), std::end(temperatures),ostream_iterator<double>{std::cout, " "});
	cout << std::endl;
	auto average = std::accumulate(std::begin(temperatures),std::end(temperatures), 0.0)/temperatures.size();
	cout << "Average temperature: "<< average << std::endl;
	partition(std::begin(temperatures), std::end(temperatures),[average](double t) { return t < average; });
	copy(std::begin(temperatures), std::end(temperatures),std::ostream_iterator<doiible>{std::cout, " "});
	cout << endl;
这段代码会输出下面这些内容：
65 75 56 48 31 28 32 29 40 41 44 50
Average temperature: 44.9167
44 41 40 29 31 28 32 48 56 75 65 50

可以对表示个体的 Person 对象进行分区，将所有女性放在男性的前面.
下面是一个对 tuple 对象的序列进行分区的示例，这个元组对象用来表示人和标识他们的性别：
	using gender = char;
	using first = string;
	using second= string;
	using Name = std::tuple<first, second, gender>;
	vector<Name> names {std::make_tuple ("Dan", "old", 'm'),std::make_tuple("Ann", "old", 'f'),std::make_tuple ("Ed", "old",'m'),std::make_tuple ("Jan", "old", 'f'), std::make_tuple ("Edna", "old", 'f')};
	partition(std::begin(names), std::end(names),[](const Names name) { return std::get<2>(name) == 'f'; });
	for(const auto& name : names)
    	cout << std::get<0> (name) << " "<< std::get<1> (name) << std::endl;
这里使用 using 声明来解释 tuple 对象成员变量的意义。当 tuple 对象的最后一个成员变量是“f”时，这个谓词会返回 true，所以输出中会出现 Edna、Ann 以及处在 Ed 和 Dan 之前的 Jan。
在这个谓词中，可以用表达式 std::get<gender>(name) 来引用 tuple 的第三个成员变量。这样做是可行的，因为第三个成员是唯一的，这就允许用它的类型来识别这个成员。

2.stable_partition() 
partition() 算法并不保证维持这个序列原始元素的相对顺序。在上面的示例中，对于原 始序列，元素 44 和 41 在 40 的后面。但在进行这项操作之后，它们就不是那样了。
为了维持元素的相对顺序，可以使用 stable_partition() 算法。
它的参数和 partition() 一样，可以用下面这些语句来代替前一段代码中的 partition() 调用：
	stable_partition(std::begin(temperatures), std::end(temperatures),[average](double t) { return t < average; });
做出这些修改后，对应的输出如下：
65 75 56 48 31 28 32 29 40 41 44 50
Average temperature: 44.9167
31 28 32 29 40 41 44 65 75 56 48 50

可以看到，重排序时并不一定要对序列进行分区，元素的相对顺序被保留了。所有小于平均值的元素的相对顺序都没有被改变，所有大于平均值的元素也是如此。

3.partition_copy()

partition_copy() 算法以和 stable_partition() 相同的方式对序列进行分区，但那些使谓词返回 true 的元素会被复制到一个单独的序列中，
使谓词返回 false 的那些元素会被复制到第三个序列中。这个操作不会改变原始序列。

原始序列由前两个参数指定，它们必须是输入迭代器。
第 3 个参数用来确定目的序列的开始位置，它会保存那些使谓词返回 true 的元素。
第 4 个参数用来确定另一个目的序列的开始位置，它会保存那些使谓词返回 false 的元素。
第 5 个参数是用来分区元素的谓词。
// Using partition_copy() to find values above average and below average
#include <iostream>                              // For standard streams
#include <vector>                                // For vector container
#include <algorithm>                             // For partition_copy(), copy()
#include <numeric>                               // For accumulate()
#include <iterator>                              // For back_inserter, ostream_iterator
int main()
{
    std::vector<double> temperatures {65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50};
    std::vector<double> low_t;                       // Stores below average temperatures
    std::vector<double> high_t;                      // Stores average or above temperatures
    auto average = std::accumulate(std::begin(temperatures), std::end(temperatures), 0.0) / temperatures.size();
    std::partition_copy(std::begin(temperatures), std::end(temperatures), std::back_inserter(low_t), std::back_inserter(high_t),[average](double t) { return t < average; });
    // Output below average temperatures
    std::copy(std::begin(low_t), std::end(low_t), std::ostream_iterator<double>{std::cout, " "});
    std::cout << std::endl;
    // Output average or above temperatures
    std::copy(std::begin(high_t), std::end(high_t), std::ostream_iterator<double>{std::cout, " "});
    std::cout << std::endl;
}


4.partition_point()

可以用 partition_point() 算法来获取分区序列中第一个分区的结束迭代器，它的前两个参数定义检查范围的正向迭代器，最后一个参数是用来对序列进行分区的谓词。
我们通常不知道每个分区中元素的个数，这个算法使我们能够访问和提取这些分区中的元素。

	vector<double> temperatures {65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50};
	auto average = std::accumulate(std::begin(temperatures),std::end(temperatures), 0.0)/ temperatures.size();
	auto predicate = [average](double t) { return t < average; };
	stable_partition(std::begin(temperatures), std::end(temperatures), predicate);
	auto iter = std::partition_point(std::begin(temperatures),std::end(temperatures), predicate);
	cout << "Elements in the first partition: ";
	copy(std::begin(temperatures), iter,std::ostream_iterator<double>{std::cout, " "});
	cout << "\nElements in the second partition: ";
	copy(iter, std::end(temperatures),std::ostream_iterator<double>{std::cout, " "});
	cout << std::endl;
	//Elements in the first partition: 31 28 32 29 40 41 44
	//Elements in the second partition: 65 75 56 48 50

在使用 partition_point() 之前，需要确定序列是否已经被分区。如果对此不是很确定，在这种情况下可以使用 is_partitioned() 来判断。
它的参数是用来指定序列的输入迭代器和用来对序列进行分区的谓词。如果这个序列已经被分区，这个算法就返回 true，否则返回 false。

