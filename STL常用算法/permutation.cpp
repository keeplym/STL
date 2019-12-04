1.next_permutation() (可以用来生成全排列)

next_permutation() 会生成一个序列的重排列，它是所有可能的字典序中的下一个排列，默认使用 < 运算符来做这些事情。
它的参数为定义序列的迭代器和一个返回布尔值的函数，这个函数在下一个排列大于上一个排列时返回 true，如果上一个排列是序列中最大的，它返回 false，所以会生成字典序最小的排列。
	std::vector<int> range {1,2,3,4};
	do {
    	std::copy (std::begin(range), std::end(range), std::ostream_iterator<int>{std::cout, " "});
    	std::cout << std::endl;
	}while(std::next_permutation(std::begin(range), std::end(range)));
当 next_permutation() 返回 false 时，循环结束，表明到达最小排列。这样恰好可以生成 序列的全部排列，这只是因为序列的初始排列为 1、2、3、4，这是排列集合中的第一个排列。

有一种方法可以得到序列的全排列，就是使用 next_permutation() 得到的最小排列：
	std::vector<string> words { "one", "two", "three"};
	while(std::next_permutation(std::begin(words),std::end(words)));
	do{
    	std::copy(std::begin(words), std::end(words), std::ostream_iterator<string>{std::cout, " "});
    	std::cout << std::endl;
	} while(std::next_permutation(std::begin(words), std::end(words)));
words 中的初始序列不是最小的排列序列，循环会继续进行，直到 words 包含最小排列。do-while 循环会输出全部的排列。


当排列中的每个元素都小于或等于它后面的元素时，它就是元素序列的最小排列，所以可以用 min_element() 来返回一个指向序列中最小元素的迭代器，
然后用 iter_swap() 算法交换两个迭代器指向的元素，从而生成最小的排列，例如：
	std::vector<string> words { "one", "two", "three", "four", "five","six","seven", "eight"};
	for(auto iter = std::begin(words); iter != std::end(words)-1 ;++iter)
    	std::iter_swap(iter, std::min_element(iter, std::end(words)));
for循环从序列的第一个迭代器开始遍历，直到倒数第二个迭代器。for 循环体中的语句会交换 iter 指向的元素和 min_element() 返回的迭代器所指向的元素。
这样最终会生成一个最小排列，然后可以用它作为 next_permutation() 的起始点来生成全排列。


下面是一个找出单词中字母的全部排列的示例：
// Finding rearrangements of the letters in a word
#include <iostream>                                      // For standard streams
#include <iterator>                                      // For iterators and begin() and end()
#include <string>                                        // For string class
#include <vector>                                        // For vector container
#include <algorithm>                                     // For next_permutation()
using std::string;

int main()
{
    std::vector<string> words;
    string word;
    while(true)
    {
        std::cout << "\nEnter a word, or Ctrl+z to end: ";
        if((std::cin >> word).eof()) break;
        string word_copy {word};
        do
        {
            words.push_back(word);
            std::next_permutation(std::begin(word), std::end(word));
        } while(word != word_copy);

        size_t count{}, max{8};
        for(const auto& wrd : words)
            std::cout << wrd << ((++count % max == 0) ? '\n' : ' ');
        std::cout << std::endl;
        words.clear();                     // Remove previous permutations
    }
}



可以为 next_permutation() 提供一个函数对象作为第三个参数，从而用这个函数对象定 义的比较函数来代替默认的比较函数。
下面展示如何使用这个版本的函数，通过比较最后 一个字母的方式来生成 words 序列的排列：
	std::vector<string> words { "one", "two", "four", "eight"};
	do{
    	std::copy(std:rbegin(words), std::end(words), std::ostream_iterator<string> {std::cout, " "});
    	std::cout << std::endl;
	} while(std::next_permutation(std::begin(words), std::end(words),[](const string& s1, const strings s2) {return s1.back() < s2.back(); }));
通过传入一个 lambda 表达式作为 next_permutation() 的最后一个参数，这段代码会生成 words 中元素的全部 24 种排列。



2.prev_permutation()

next_permutation() 是按照字典升序的方式生成的排列。当我们想以降序的方式生成排列时，可以使用 prev_permutation()。

prev_permutation 和 next_permutation() 一样有两个版本，默认使用 < 来比较元素。因为排列是以降序的方式生成的，所以算法大多数时候会返回 true。
当生成最大排列时，返回 false。例如：
	vector<double> data {44.5, 22.0, 15.6, 1.5};
	do{
    	copy(std::begin(data), std::end(data), std::ostream_iterator<double> {std::cout, " "});
    	cout << std::endl;
	} while(std::prev_permutation(std::begin(data), std::end(data)));
这段代码会输出 data 中 4 个 double 值的全部 24 种排列，因为初始序列是最大排列，所以 prev_permutation() 会在输入最小排列时，才返回 false。



3.is_permutation()

is_permutation() 算法可以用来检查一个序列是不是另一个序列的排列，如果是，会返回 true。下面是在这个算法中使用 lambda 表达式的示例：

	vector<double> data1{44.5, 22.0, 15.6, 1.5};
	vector<double> data2{22.5, 44.5, 1.5, 15.6};
	vector<double> data3{1.5, 44.5, 15.6, 22.0};
	auto test = [] (const auto& d1, const auto& d2){
    copy(std::begin(d1), std::end(d1), std::ostream_iterator<double> {std::cout," "});
    cout << (is_permutation (std::begin (d1), std::end(d1), std::begin (d2), std::end(d2)) ?"is":"is not")<<" a permutation of ";
    copy(std::begin(d2), std::end(d2), std::ostream_iterator<double>{std::cout, " "});
    cout << std::endl;
};
test(data1, data2);
test(data1, data3);
test(data3, data2);
/*
44.5 22 15.6 1.5 is not a permutation of 22.5 44.5 1.5 15.6 
44.5 22 15.6 1.5 is a permutation of 1.5 44.5 15.6 22 
1.5 44.5 15.6 22 is not a permutation of 22.5 44.5 1.5 15.6 
*/
lambda 表达式 test 的类型参数是用 auto 指定的，编译器会推断出它的实际类型为 const std::vector<double>&。
使用 auto 来指定类型参数的 lambda 表达式叫作泛型 lambda。
lambda 表达式 test 用 is_permutation() 来评估参数是否是另一种排列。
