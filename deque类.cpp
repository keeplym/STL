
1.deque<T>，一个定义在 deque 头文件中的容器模板，可以生成包含 T 类型元素的容器，它以双端队列的形式组织元素。
可以在容器的头部和尾部高效地添加或删除对象，这是它相对于 vector 容器的优势。当需要这种功能时，可以选择这种类型的容器。


2.deque 容器中的元素是序列，但是内部的存储方式和 vector 不同。它组织元素的方式导致容器的大小总是和容量相等。
因为这个，所以没有定义成员函数 capacity()，deque 只有成员函数 size()，它以成员类型 size_type 的无符号整型来返回当前元素个数。

3.同样因为 deque 内部组织元素的方式不同，deque 的操作和 vector 相比要慢。

4.为了用进行边界检查的索引来访问元素，可以选择使用成员函数 at()，这和 vector 相同：
cout << words.at(2) << sendl; // Output the third element in words
参数必须是一个 size_t 类型的值，因此不能是负数。
如果 at() 的参数不在范围内，例如大于 words.size()-1，就会抛出一个 std::out_of_range 异常。


5.deque 容器和 vector 一样，有三种不同重载版本的 resize() 函数，它们的操作基本相同。

6.deque 和 vector 都有成员函数 push_back() 和 pop_back()，
它们在序列尾部添加或删除元素的方式相同。deque 也有成员函数 push_front() 和 pop_front()，可以在序列头部执行相似的操作。

7.除了和 vector —样都有 emplace_back() 函数外，deque 还有成员函数 emplace_front()，可以在序列的开始位置生成新的元素。
和 vector 一样，也可以使用 emplace() 或 insert() 在 deque 内部添加或移除元素。这个过程相对要慢一些，因为这些操作需要移动现有的元素。


