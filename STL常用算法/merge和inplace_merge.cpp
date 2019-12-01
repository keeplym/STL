merge和inplace_merge

merge():
合并操作会合并两个有相同顺序的序列中的元素，可以是两个升序序列，也可以是两个降序序列。
结果会产生一个包含来自这两个输入序列的元素副本的序列，并且排序方式和原始序列相同。

int main() {
    std::vector<int> these {2, 15, 4, 11, 6, 7};//1st input to merge
    std::vector<int> those {5, 2, 3, 2, 14, 11, 6}; // 2nd input to merge
    std::stable_sort(std::begin(these), std::end(these),std::greater<>());// Sort 1st range in descending sequence
    std::stable_sort(std::begin(those), std::end(those), std::greater<>()); // Sort 2nd range
    std::vector<int> result(these.size() + those.size() + 10);//Plenty of room for results
    auto end_iter = std::merge(std::begin(these), std::end(these),std::begin(those),
                               std::end(those),std::begin (result), std::greater<>());
    // Merge 1st range and 2nd range into result
    std:: copy (std::begin (result), end_iter, std::ostream_iterator<int>{std::cout, " "}); //15 14 11 11 7 6 6 5 4 3 2 2 2 
}

inplace_merge():

可以合并同一个序列中两个连续有序的元素序列。它有三个参数： first、second、last 和 last 是一个双向迭代器。
这个序列中的第一个输入序列是 [first，second)， 第二个输入序列是 [second,last)，因而 second 指向的元素在第二个输入序列中。
结果为 [first, last)。

int main() {
    std::vector<int> data{ 5, 17, 19, 20, 24, 30, 9, 13, 19, 25, 29, 31, 40, 41 };
    int num = 6;
    inplace_merge(std::begin(data), std::begin(data) + num, std::end(data));
    copy(std::begin(data),std::end(data),std::ostream_iterator<int>(std::cout," ")); //5 9 13 17 19 19 20 24 25 29 30 31 40 41 
}